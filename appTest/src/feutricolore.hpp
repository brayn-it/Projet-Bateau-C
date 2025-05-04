#ifndef FEUTRICOLORE_HPP
#define FEUTRICOLORE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <filesystem>

#include <string>
using namespace std;

enum class EtatFeu {Rouge, Orange, Vert};

class FeuTricolore{
    private:
        EtatFeu etat;
        //sf::Sound son;
        sf::SoundBuffer buffer;
        sf::Sound sound;
        //cercle rouge, orange, vert
        sf::CircleShape cercle;
        //rayon du cercle
        float rayon=25;
        sf::Clock& clock;
        bool active=false;
        filesystem::path getAssetPath(const std::string&);
    public:
        FeuTricolore(sf::Clock&);
        FeuTricolore(float, sf::Clock&);
        void demarrer();
        void update();
        void draw(sf::RenderWindow &);

};

#endif