#include "ligne.hpp"

Ligne::Ligne(){
    dimension = sf::Vector2f(10.f,700.f);
    position = sf::Vector2f(50.f,50.f);
    couleur = sf::Color::Green;
    rectangle.setSize(dimension);
    rectangle.setPosition(position);
    rectangle.setFillColor(couleur);
}

Ligne::Ligne(sf::Vector2f d, sf::Vector2f p,sf::Color c){
    position = p;
    dimension = d;
    couleur = c;
    rectangle.setSize(dimension);
    rectangle.setPosition(position);
    rectangle.setFillColor(couleur);
}

Ligne::~Ligne(){

}

void Ligne::draw(sf::RenderWindow &window) const{
    window.draw(rectangle);
}

sf::Vector2f Ligne::getPosition(){
    return position;
}