#include "obstacle.hpp"

Obstacle::Obstacle(){
    dimension = sf::Vector2f(10.f,700.f);
    position = sf::Vector2f(50.f,50.f);
    couleur = sf::Color::Green;
    forme.setSize(dimension);
    forme.setPosition(position);
    forme.setFillColor(couleur);
}

Obstacle::Obstacle(sf::Vector2f d, sf::Vector2f p,sf::Color c){
    position = p;
    dimension = d;
    couleur = c;
    forme.setSize(dimension);
    forme.setPosition(position);
    forme.setFillColor(couleur);
}

Obstacle::~Obstacle(){}


sf::Vector2f& Obstacle::get_Position(){
    return position;
}


sf::Vector2f& Obstacle::get_Dimention(){
    return dimension;
}


void Obstacle::draw(sf::RenderWindow &window) const{
    window.draw(forme);
}