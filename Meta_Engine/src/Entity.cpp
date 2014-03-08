#include "Entity.h"

#include "MetaEngine.h"
#include "Defines.h"
#include "Map.h"
#include "ConsoleInfo.h"
#include <list>
#include "Player.h"
#include "Item.h"
#include "TextureManager.h"
#include "DataHolder.h"
#include <sstream>
std::vector<Entity*> Entity::EntityList;
Entity::Entity()
{
    //ctor
    type = TYPE_ENEMY;
    mDelay = 0;
    mSpeedCost = 100;
    mAtk = 2;
    mDef = 1;
    mRange = 5;
    mHP = 10;
    mMP = 10;
    mDead = false;
    setTexture(TextureManager::TextureControl.get(Textures::ID::CHARS));
}
Entity::Entity(ENUM_TYPE_OBJ tipo)
{
    type = tipo;
    mDelay = 0;
    mSpeedCost = 100;
    mAtk = 2;
    mDef = 1;
    mRange = 5;
    mHP = 10;
    mDead = false;
    mPosition.x = mPosition.y = 0;
    setTexture(TextureManager::TextureControl.get(Textures::ID::CHARS));
}

Entity::~Entity()
{
    //dtor
}

//----------------- Draw --------------------------------------
void Entity::draw()
{
    if(mDead) return;

    if(MetaEngine::EngineControl.isMapFog() &&
        Map::MapControl.has_seens(mPosition.x, mPosition.y) == false) return;

    if(type == TYPE_ENEMY)
    {
        sf::Color c;
        c.g = 10;
        c.b = 10;
        c.a = 100;
        c.r = 255;
        //Imprime area;

        for(int i = -mRange; i <= mRange; ++i)
        {
            for(int j = -mRange; j <= mRange; ++j)
            {
                float dist = (abs(mPosition.x+i - mPosition.x)
                      + abs(mPosition.y+j - mPosition.y));

                if(dist > mRange) continue;

                MetaEngine::EngineControl.drawRectVertex( (mPosition.x+i)*TILE_SIZE,
                                                         (mPosition.y+j)*TILE_SIZE,
                                                 TILE_SIZE, TILE_SIZE, c);
            }
        }
    }

    GameObject::draw();
}
//----------------- Update --------------------------------------
void Entity::update(float dt, unsigned int delay)
{
    if(mHP <= 0)
    {
        mDead = true;
        DataHolder::RunData.enemys_KO++;
        removeFromObjectList();//delete this

        return;
    }

    moveAnimation(dt);
    anim.update(dt);

    //dt será usado para movimento smoth futuramente
    //Quando delay for mais que speed, realiza 1 movimento.
    mDelay += delay;

    while(mDelay >= mSpeedCost)
    {
        mDelay -= mSpeedCost;

        if(type == TYPE_ENEMY)
        {
            runAI();
        }
    }

}
//----------------- Move Animation ------------------------------
bool Entity::moveAnimation(float dt)
{
    if(g_animationSpeed == 0)
    {
        anim.mPosition.x = mPosition.x;
        anim.mPosition.y = mPosition.y;
    } else
    {
        sf::Vector2f direction = sf::Vector2f(mPosition) - anim.mPosition;
        if( (direction.x >= -g_animationSpeed*dt && direction.x <= g_animationSpeed*dt) &&
            (direction.y >= -g_animationSpeed*dt && direction.y <= g_animationSpeed*dt) ){
                anim.mPosition = sf::Vector2f(mPosition);
            }
        else
        {
            if(direction.x > 0)
                direction.x = 1;
            else if(direction.x < 0)
                direction.x = -1;
            if(direction.y > 0)
                direction.y = 1;
            else if(direction.y < 0)
                direction.y = -1;

            direction *= dt;
            direction *= (float)g_animationSpeed;
            anim.mPosition  += direction;
            g_animationsLeft = true;
            moving = true;
            return true;
        }

    }
    moving = false;
    return false;
}
//----------------- Run AI --------------------------------------
void Entity::runAI()
{
    float dist = (abs(Player::PlayerControl->getPosition().x - mPosition.x)
                  + abs(Player::PlayerControl->getPosition().y - mPosition.y));
    //cout << "Dist: " << dist << endl;
    if( dist  > mRange ) return;
    geraRota(Player::PlayerControl->getPosition().x, Player::PlayerControl->getPosition().y);

    if(RotaList.empty()) return;

    int last = RotaList.size()-1;
    movePosition(RotaList[last].x - mPosition.x, RotaList[last].y - mPosition.y);
}
//----------------- movePosition --------------------------------------
void Entity::movePosition(int px, int py)
{
    if(px == 0 && py == 0) return;

    if(g_animationSpeed)
        anim.jumpAnimation();

    Tile* tile = Map::MapControl.getTile(mPosition.x + px, mPosition.y + py);
    //Se solido, ou se objeto no tile,  não anda.
    if (tile == nullptr || tile->tipo == TILE_SOLID)
    {
        ConsoleInfo::MessageControl.addMessage("Passagem bloqueada.");
        return;
    } else //Se algo no tile.
    if (tile->obj != nullptr) {
        Entity* ent = (Entity*) tile->obj;
        int dano = mAtk - ent->mDef;

        if( dano > 0) {
            ent->mHP-= dano;
            if(ent->mHP < 0) ent->mHP = 0;
        } else { dano = 0; }

// TODO (gust#1#): Tratar Inimigo atacar Inimigo ou colocar nomes nas entidades        //Se estiver atacando um inimigo
        if(tile->obj->type == TYPE_ENEMY)
        {
            std::stringstream stream;
            stream << "Voce ataca inimigo com  " << dano << " de dano! ";
            ConsoleInfo::MessageControl.addMessage( stream.str() );
        } else
        {
            std::stringstream stream;
            stream << "Inimigo ataca voce com " << dano << " de dano! ";
            std::cout <<  tile->obj->type << std::endl;
            ConsoleInfo::MessageControl.addMessage( stream.str() );
        }

        return;
    }
    for(unsigned int i = 0; i < tile->itens.size(); ++i)
    {
        if (this->type == TYPE_PLAYER)
        {
            Item* item = (Item*)tile->itens[i];

            item->useItem();
            --i; //Deleta tile do vetor então i diminui
            DataHolder::RunData.itens_get++;
        }
    }

    //Realiza movimento
    Tile* tileOld = Map::MapControl.getTile(mPosition.x, mPosition.y);
    //Remove da lista de tiles
    tileOld->obj = nullptr;
    //Move e adciona a lista de tiles
    mPosition.x += px;
    mPosition.y += py;
    tile->obj = (this);
}

void Entity::movePosition(int number)
{
    switch(number)
    {
    case 2:
        movePosition(0,1);
        break;
    case 4:
        movePosition(-1,0);
        break;
    case 6:
        movePosition(1,0);
        break;
    case 8:
        movePosition(0,-1);
        break;
    case 1:
        movePosition(-1,1);
        break;
    case 3:
        movePosition(1,1);
        break;
    case 7:
        movePosition(-1,-1);
        break;
    case 9:
        movePosition(1,-1);
        break;
    }
}

bool Entity::isMoving()
{
    return moving;
}
void Entity::stopMoving()
{
    moving = false;
}

bool Entity::isRota()
{
    return (RotaList.empty() == false);
}

void Entity::moveRota()
{
    if (RotaList.empty()) return;

    int last = RotaList.size()-1;
    movePosition(RotaList[last].x - mPosition.x, RotaList[last].y - mPosition.y);

    RotaList.erase(RotaList.end());
}

//----------------- Get Route --------------------------------------
sf::Vector2i Entity::getRotaTarget()
{
    sf::Vector2i target;
    if(RotaList.empty() == false)
    {
        target = RotaList[0];
    }
    //Se não existir, retorna (0,0)
    return target;
}


//----------------- Get Route --------------------------------------
void Entity::geraRota(int dx, int dy)
{

    int mapWidth = Map::MapControl.getMapWidth();
    int mapHeight = Map::MapControl.getMapHeight();

    //Area, checa se nodo esta ou não aberto
    vector<vector<bool>>areaClosed;
    vector<vector<bool>>areaOpened;
    areaClosed.resize(mapWidth);
    areaOpened.resize(mapWidth);
    for(int i = 0; i < mapWidth;++i)
    {
        areaClosed[i].resize(mapHeight, false);
        areaOpened[i].resize(mapHeight, false);
    }

    list<TileNode*> openList;
    list<TileNode*> closedList;
    list<TileNode*>::iterator it;

    TileNode* inicio = new TileNode(mPosition.x, mPosition.y);
    TileNode* destino = new TileNode(dx, dy);
    TileNode* atual = inicio;
    TileNode* filho = NULL;

    openList.push_back(inicio);
    inicio->computeScores(destino);
    areaOpened[inicio->x][inicio->y] = true;

    while(atual != destino)
    {
        //Se não tiver nodos abertos
        if(openList.empty())
        {
            break;
        }
        atual = *openList.begin();
        //Se iterador tiver um F menor ou igual ao atual, abre.
        for(it = openList.begin(); it != openList.end(); ++it)
        {
            if( (*it)->getFScore() <= atual->getFScore())
            {
                atual = (*it);
            }
        }
        //cout << "@ " << atual->x << "," << atual->y << " GScore: " << atual->getFScore() << endl;

        //Para se tiver chego em destino
        if(atual->x == destino->x && atual->y == destino->y)
        {
            break;
        }

        openList.remove(atual);
        areaOpened[atual->x][atual->y] = false;

        closedList.push_back(atual);
        areaClosed[atual->x][atual->y] = true;

        for(int ix = -1; ix < 2; ++ix)
        {
            for(int iy = -1; iy < 2; ++iy)
            {
                //Pula se ponto atual
                if( ix == 0 && iy == 0){
                    continue;
                }

                if(Map::MapControl.getTile(atual->x+ix, atual->y+iy) == nullptr)
                {
                    continue;
                }
                //Pega tile
                filho = new TileNode(atual->x+ix, atual->y+iy);


                //Se solido ou já explorado, continua
                if(filho->id == TILE_SOLID || areaClosed[filho->x][filho->y])
                {
                    continue;
                }

                //Se já estiver na openList
                if(areaOpened[filho->x][filho->y])
                {
                    if(filho->getGScore() > filho->getGScore(atual))
                    {
                        filho->setParent(atual);
                        filho->computeScores(destino);
                    }

                }
                else
                {
                    openList.push_back(filho);
                    areaOpened[filho->x][filho->y] = true;

                    //Computa score g = f + h
                    filho->setParent(atual);
                    filho->computeScores(destino);
                }
            }
        }
    } //Fim while

    RotaList.clear();
    //Cria rota
    while(atual->hasParent() && atual != inicio)
    {
        RotaList.push_back(sf::Vector2i(atual->x, atual->y));
        atual = atual->parent;
    }

    //Limpa dados
    for(it = openList.begin(); it != openList.end(); ++it)
    {
        delete *it;
        *it = nullptr;
    }
    for(it = closedList.begin(); it != closedList.end(); ++it)
    {
        delete *it;
        *it = nullptr;
    }

    delete destino;
}
Entity::TileNode::TileNode(int ix, int iy)
{
    this->x = ix;
    this->y = iy;
    this->id = Map::MapControl.getTile(x,y)->tipo;
    parent = nullptr;

    f = g = h = 0;

}
int Entity::TileNode::getHScore(TileNode* node)
{
    return (abs(node->x - x) + abs(node->y - y)) * 10;
}
int Entity::TileNode::getGScore(TileNode* node)
{
    if(node == nullptr){
        return 0;
    }
    //Todos os caminhos possuem o mesmo custo. 10.
    return node->getGScore() + 10;
}

int Entity::TileNode::getGScore()
{
    return g;
}


int Entity::TileNode::getHScore()
{
    return h;
}

int Entity::TileNode::getFScore()
{
    return f;
}
void Entity::TileNode::setParent(TileNode* parentNode)
{
    this->parent = parentNode;
}
Entity::TileNode* Entity::TileNode::getParent()
{
    return parent;
}
bool Entity::TileNode::hasParent()
{
    return (parent != nullptr);
}
void Entity::TileNode::computeScores(TileNode* dest)
{
    g = getGScore(parent);
    h = getHScore(dest);
    f = g + h;
}
