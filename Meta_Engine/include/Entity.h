#pragma once
#include "GameObject.h"
#include <vector>
class Tile;

class Entity : public GameObject
{
    public:
        static std::vector<Entity*> EntityList;
        Entity(ENUM_TYPE_OBJ tipo);
        Entity();
        virtual ~Entity();

        virtual void draw();
        void update(unsigned int dt, unsigned int delay);

        void movePosition(int x, int y = 0);
        void movePosition(int number);
    //futuro protected
        double mSpeedCost;
        double mDelay;
        bool mDead;
        int mHP;
        int mMP;
        int mAtk;
        int mDef;
        int mRange;
        std::vector<sf::Vector2i> RotaList;

        void geraRota(int dx, int dy);
        bool isRota();
        void moveRota();
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
