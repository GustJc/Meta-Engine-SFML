#pragma once

namespace sf
{
    class Event;
}
class Entity;

class PlayerController
{
    public:
        PlayerController();
        virtual ~PlayerController();

        void events(sf::Event& event);
        //prot

        Entity* player;
    protected:
    private:
};
