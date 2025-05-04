#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "physics/dynamicModel.h"
#include "physics/physicsEngine.h"
#include "physics/common.h"
#include "physics/platform_core.h"
#include <filesystem>
#include <iostream>
using namespace std;

class Menu{
    private:
        sf::RenderWindow& window;
        sf::RectangleShape OnePlayerButton;
        sf::RectangleShape TwoPlayerButton;
        sf::RectangleShape StartButton;
        sf::Font font;
        sf::Text titletText;
        sf::Text OnePlayerText;
        sf::Text TwoPlayerText;
        sf::Text StartText;

        int selectedPlayers = 0;
        bool StartOK = false;

        filesystem::path getAssetPath(const std::string&);
    public:
        Menu(sf::RenderWindow&);
        void initButtons();
        void pollEvents(const sf::Event &);
        int getSelectedPlayer();
        void render();
        bool isMouseOver(const sf::RectangleShape&);
        void update();
        bool isReadyToStart();
};


#endif