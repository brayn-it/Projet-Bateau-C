#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>

#include "physics/dynamicModel.h"
#include "physics/physicsEngine.h"

#include <iostream>

#include <string>
using namespace std;

class Obstacle{
    private:
        sf::RectangleShape forme; //Amelioration tout type de forme
        sf::Vector2f position;
        sf::Vector2f dimension;
        sf::Color couleur;

    public:
        Obstacle();
        Obstacle(sf::Vector2f,sf::Vector2f,sf::Color);
        ~Obstacle();
        sf::Vector2f& get_Position();
        sf::Vector2f& get_Dimention();
        void draw(sf::RenderWindow &)const;

};

#endif