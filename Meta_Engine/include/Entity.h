#pragma once
#include "GameObject.h"
#include <vector>
enum ENUM_ENT_TYPE{
    ENT_PLAYER,
    ENT_ENEMY
};

class Tile;

class Entity : public GameObject
{
    public:
        static std::vector<Entity*> EntityList;
        Entity(ENUM_ENT_TYPE tipo);
        Entity();
        virtual ~Entity();

        void draw();
        void update(unsigned int dt, unsigned int delay);

        void movePosition(int x, int y = 0);
        void movePosition(int number);

        ENUM_ENT_TYPE type;
    //futuro protected
        double mSpeed;
        double mDelay;
        bool mDead;
        int mHP;
        int mAtk;
        int mDef;
        int mRange;
        std::vector<sf::Vector2i> RotaList;

        void geraRota(int dx, int dy);
    protected:
        void runAI();



        class TileNode
        {
        public:
                TileNode(int ix, int iy);
                void setParent(TileNode* parentNode);
                TileNode* getParent();
                bool hasParent();
                int getHScore();
                int getGScore();
                int getFScore();
                int getHScore(TileNode* node);
                int getGScore(TileNode* node);
                void computeScores(TileNode* dest);
                int x, y, id;
                TileNode* parent;
        private:
                int f,g,h;
        };
    private:
};
