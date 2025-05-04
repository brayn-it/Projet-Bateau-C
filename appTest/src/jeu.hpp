#ifndef JEU_HPP
#define JEU_HPP

#include <SFML/Graphics.hpp>

#include "physics/dynamicModel.h"
#include "physics/physicsEngine.h"

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
using namespace std;

#include "ligne.hpp"
#include "obstacle.hpp"
#include "bateau.hpp"
#include "menu.hpp"
#include "feutricolore.hpp"
#include "course.hpp"
#include "dashboard.hpp"

enum class EtatJeu {Menu, Joue};

class Jeu{
    private:
        sim::physics::PhysicsEngine engine; //Moteur physique du jeu
        sf::Clock clock;
        double dt;

        //Largeur et Hauteur de la fenetre du jeu == type unsigned int requis pour param video
        unsigned int width;
        unsigned int height;
        string titre;

        //Video mode
        sf::VideoMode vm;

        sf::RenderWindow window;

        //Fenetre de menu
        Menu menu;

        EtatJeu etat;

        int mode=1;
        sf::Font font;
        //COURSE
        Course course;
        void initWindow();
        void pollEvents();
        void updating();
        void rendering();

        filesystem::path getAssetPath(const std::string&);
    public:
        Jeu();
        ~Jeu();

        sim::physics::PhysicsEngine getPhysicsEngine();
        void running();
        void creerObstacle(sf::Vector2f,sf::Vector2f,sf::Color);
        void creerBateau(sf::Color);
};

#endif