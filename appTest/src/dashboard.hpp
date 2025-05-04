#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <SFML/Graphics.hpp>
#include "physics/dynamicModel.h"
#include "physics/physicsEngine.h"
#include "physics/common.h"
#include "physics/platform_core.h"
#include <filesystem>
#include <cmath>
#include <iostream>
using namespace std;


class Dashboard{
    private:
        sf::Vector2f position=sf::Vector2f(120, 600);
        sf::Font* font = new sf::Font; //pour corriger l'erreur de core dumped car font est detruit
        sf::RectangleShape background;
        sf::Text textPlayer;
        sf::Text textSpeed;
        sf::Text textAcceleration;
        sf::Text textAngle;
        sf::Text textRotation;
        
        void init();

        void setupText(sf::Text &, sf::Vector2f);
        filesystem::path getAssetPath(const std::string&);
    public:
        Dashboard();
        Dashboard(const sf::Vector2f&);
        ~Dashboard();
        void update(float speed, float accel, float yawDeg, float rot);
        void draw(sf::RenderWindow&);
        void setPosition(const sf::Vector2f&);
        void configPlayerText(int j);

};

#endif