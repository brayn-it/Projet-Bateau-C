#include "bateau.hpp"
#include <cmath>
#include <iostream>
using namespace std;

Bateau::Bateau(sim::physics::RigidBody* pbody, sf::Color Color){
    // Récupération de la physique d'un bateau
    Facteur.x = 0.1;
    Facteur.y = 0.1;
	body = pbody;
    body->setPosition(84*Facteur.x, 70*Facteur.y);

    // Initialisation des points du bateau par rapport au barycentre (distance)
    L_point[0] = sf::Vector2f(-34.f, -20.f);
    L_point[1] = sf::Vector2f(16.f, -20.f);
    L_point[2] = sf::Vector2f(36.f, 0.f);
    L_point[3] = sf::Vector2f(16.f, 20.f);
    L_point[4] = sf::Vector2f(-34.f, 20.f);

	// Créer les formes du bateau
	forme.setPointCount(5);
    for (int i=0; i<5; i++){
        forme.setPoint(i, L_point[i]);
    }
	forme.setFillColor(Color);

    engineSoundBuffer.loadFromFile(getAssetPath("audio/boatengine.mp3").string());
    engineSound.setBuffer(engineSoundBuffer);
    engineSound.setLoop(true);
}

sf::ConvexShape& Bateau::Get_Forme(){
    return forme;
}

sim::physics::RigidBody* Bateau::Get_Body(){
    return body;
}

sf::Vector2f& Bateau::Get_P(int id){
    return L_point[id];
}

sim::common::Vector2& Bateau::Get_Facteur(){
    return Facteur;
}

void Bateau::Deplacement_X(sim::physics::DynamicModel model, double RPM, double Angle, double Rho){
    sim::common::ForceTorque2D Force = model.computeActuators(*body, RPM, Angle, Rho);
    body->addForce(Force);
}

void Bateau::Deplacement_Y(sim::physics::DynamicModel model, double Angle, double Rho){
    sim::common::ForceTorque2D Force = model.computeActuators(*body, 3500, Angle, Rho);
    body->addForce(Force);
}

void Bateau::update(sim::physics::DynamicModel model){
    sim::common::ForceTorque2D Force = model.computeDamping(*body, 1026);
    if (body->getState().velocity_body.x < 0){
       Force.y = -15000 * body->getState().velocity_body.y;
    }
    body->addForce(Force);
    update_point();
    updateDashboard();
}

void Bateau::updateDashboard(){
    //float speed = norm({this->Get_Body()->getState().velocity_body.x,this->Get_Body()->getState().velocity_body.y}); //Vitesse
    float speed = this->Get_Body()->getState().velocity_body.x; //Vitesse
    //float accel = norm({this->Get_Body()->getState().acc_body.x,this->Get_Body()->getState().acc_body.y});
    float accel = this->Get_Body()->getState().acc_body.x;
    float yawDeg = this->Get_Body()->getState().yaw * 180 / M_PI;
    dashboard.update(speed,1.f,5.f,this->Get_Body()->getState().r);
}

sim::common::Vector2 Bateau::rotation_point(const sf::Vector2f& p, float angle) const{
    float cs = cos(angle);
    float sn = sin(angle);
    return sim::common::Vector2(p.x*cs - p.y*sn, p.x*sn + p.y*cs);
}

void Bateau::update_point(){
    sim::common::Vector2 pos = body->getState().position;
    float angle = body->getState().yaw * sim::common::RAD_TO_DEG;
    sim::common::Vector2 pos_ecran = sim::common::worldToScreen(pos, Facteur);
    forme.setPosition(pos_ecran.x, pos_ecran.y);
    forme.setRotation(angle);
}

float Bateau::norm(const sim::common::Vector2& vec){
    //Renvoie norme d'un vecteur
    return sqrt(pow(vec.x,2)*pow(vec.y,2));
}

void Bateau::draw(sf::RenderWindow &window){
    window.draw(forme);
    dashboard.draw(window);
}

Dashboard Bateau::getDashboard(){
    return dashboard;
}

void Bateau::setDashboardPosition(const sf::Vector2f& pos){
    dashboard = Dashboard(pos);
}

void Bateau::setDashboardPlayerText(int j){
    dashboard.configPlayerText(j);
}

void Bateau::setBoatPosition(const sf::Vector2f& pos){
    body->setPosition(pos.x*Facteur.x,pos.y*Facteur.y);
    update_point();
}

filesystem::path Bateau::getAssetPath(const std::string& relativePath){
    // __FILE__ donne le chemin du fichier source courant
    filesystem::path sourceDir = filesystem::path(__FILE__).parent_path();
    
    // Remonte jusqu’au dossier du projet (ex: depuis src/jeu.cpp → ../../assets/...)
    filesystem::path assetDir = sourceDir / ".." / "assets";

    // Normalise le chemin
    assetDir = filesystem::canonical(assetDir);

    return assetDir / relativePath;
}
