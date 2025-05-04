#ifndef LIGNE_HPP
#define LIGNE_HPP

#include <SFML/Graphics.hpp>

#include "physics/dynamicModel.h"
#include "physics/physicsEngine.h"

#include <iostream>

#include <string>
using namespace std;

class Ligne{
    private:
        sf::RectangleShape rectangle;
        sf::Vector2f position;
        sf::Vector2f dimension;
        sf::Color couleur;

    public:
        Ligne();
        Ligne(sf::Vector2f,sf::Vector2f,sf::Color);
        ~Ligne();
        void draw(sf::RenderWindow &) const;
        sf::Vector2f getPosition();
};

#endif