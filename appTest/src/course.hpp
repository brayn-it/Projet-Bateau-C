#ifndef COURSE_HPP
#define COURSE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "physics/dynamicModel.h"
#include "physics/physicsEngine.h"
#include "physics/common.h"
#include "physics/platform_core.h"

#include <filesystem>
#include <iostream>
using namespace std;

#include "ligne.hpp"
#include "obstacle.hpp"
#include "bateau.hpp"
#include "menu.hpp"
#include "feutricolore.hpp"
#include "resultdashboard.hpp"


enum class RaceState{Starting,Running,Finished};

class Course{
    private:

        sim::physics::PhysicsEngine engine; //Moteur physique de la simulation
        double dt;

        sim::physics::DynamicModel model; 

        sf::RenderWindow& window;

        sf::Clock clock;
        float startTime; //apres depart de course
        float endTime;//ligne d'arrivee franchie

        Ligne ligneDepart;
        Ligne ligneArrivee;

        vector<Obstacle> obstacles;
        vector<Bateau> Bateaux;

        int mode=1; //1 joueur ou 2

        RaceState state = RaceState::Starting;

        bool active_command=false; //pour savoir si les commandes sont actives

        //Feu depart
        FeuTricolore feu;

        //Sons
        sf::SoundBuffer endingSoundbuffer;
        sf::Sound endingSound;

        //ResultDashboard
        ResultDashboard result;

        void command_control();
        sim::common::Vector2 inObstacle(Bateau&, Obstacle&);
        sim::common::Vector2 intersection_seg(sim::common::Vector2, sim::common::Vector2, sim::common::Vector2, sim::common::Vector2);
        void SetPos(Bateau&, Obstacle&, sim::common::Vector2&);
        sf::Color randomColor();

        void creerObstacle1();
        void creerObstacle2();

        void creerBateau();
        void bateauVsObstacle(Bateau bateau);
        void updateRaceState();
        filesystem::path getAssetPath(const std::string&);
    public:
        //Course();
        ~Course();
        Course(sf::RenderWindow&,sf::Clock&);
        void init(int);
        sim::physics::PhysicsEngine getPhysicsEngine();
        void run();
        void pollEvents();
        void update();
        void render();
};

#endif