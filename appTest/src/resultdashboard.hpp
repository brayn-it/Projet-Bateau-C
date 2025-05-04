#ifndef RESULTDASHBOARD_HPP
#define RESULTDASHBOARD_HPP

#include <SFML/Graphics.hpp>
#include "physics/dynamicModel.h"
#include "physics/physicsEngine.h"
#include "physics/common.h"
#include "physics/platform_core.h"
#include <filesystem>
#include <cmath>
#include <iostream>
using namespace std;

class ResultDashboard{
    private:
        sf::Font* font;
        sf::Vector2f position;
        sf::RectangleShape background;
        sf::Text textTime;
        sf::Text textWinner;
        void setupText(const sf::Text&,const sf::Vector2f&);
        filesystem::path getAssetPath(const std::string& relativePath);
    public:
        ResultDashboard();
        ~ResultDashboard();
        void draw(sf::RenderWindow&);
        void setResult(int,float);

};

#endif