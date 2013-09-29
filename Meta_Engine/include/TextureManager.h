#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include <memory>
#include <stdexcept>
#include <cassert>

namespace Textures
{
    enum ID { CHARS, ITENS, MAP };
}
class TextureManager
{
    public:
        static TextureManager TextureControl;
        TextureManager();
        virtual ~TextureManager();

        void load(Textures::ID, const std::string& filename);
        const sf::Texture& get(Textures::ID id) const;
        sf::Texture& get(Textures::ID id);
    protected:
    private:
        std::map<Textures::ID, std::unique_ptr<sf::Texture>>
            mTextureMap;
};

