#ifndef BATEAU_HPP
#define BATEAU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "physics/dynamicModel.h"
#include "physics/physicsEngine.h"
#include "physics/common.h"
#include "physics/platform_core.h"
#include"dashboard.hpp"

class Bateau{
    private:
        sim::physics::RigidBody* body;
        sf::ConvexShape forme;
        sf::Vector2f L_point[5];
        sim::common::Vector2 Facteur;
        Dashboard dashboard;
        float norm(const sim::common::Vector2&);
        sf::SoundBuffer engineSoundBuffer;
        sf::Sound engineSound;
        filesystem::path getAssetPath(const std::string&);
    public:
        Bateau(sim::physics::RigidBody* pbody, sf::Color Color);
        sf::ConvexShape& Get_Forme();
        sim::physics::RigidBody* Get_Body();
        sf::Vector2f& Get_P(int);
        sim::common::Vector2& Get_Facteur();
        void Deplacement_X(sim::physics::DynamicModel, double, double, double);
        void Deplacement_Y(sim::physics::DynamicModel model, double Angle, double Rho);
        void update(sim::physics::DynamicModel);
        sim::common::Vector2 rotation_point(const sf::Vector2f&, float) const;
        void update_point();
        void draw(sf::RenderWindow &);
        Dashboard getDashboard();
        void updateDashboard();
        void setDashboardPosition(const sf::Vector2f&);
        void setDashboardPlayerText(const int j);
        void setBoatPosition(const sf::Vector2f&);
};

#endif