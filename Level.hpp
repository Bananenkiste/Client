#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <iostream>
#include <vector>

#include <sfml/graphics.hpp>
#include <sfml/window.hpp>
#include <sfml/system.hpp>


class Level
{
    public:
        Level(std::string lvl);
        virtual ~Level();

        std::string getLevelString();
        void draw(sf::RenderWindow* window);
    private:
        std::vector<sf::Vector2i> spawn;
        std::string levelstring;
        sf::Sprite* leveldata[16][10];
};

#endif // LEVEL_HPP
