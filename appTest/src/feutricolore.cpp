#include "feutricolore.hpp"

FeuTricolore::FeuTricolore(sf::Clock& clk):clock(clk){
    cercle.setRadius(rayon);
    cercle.setOrigin(rayon,rayon);
    cercle.setPosition(950.f, 100.f);
    buffer.loadFromFile(getAssetPath("audio/race_start.wav").string());
    sound.setBuffer(buffer);
}

FeuTricolore::FeuTricolore(float r,sf::Clock& clk):clock(clk){
    rayon = r;
    cercle.setRadius(rayon);
}

void FeuTricolore::demarrer(){
    clock.restart();
    cercle.setFillColor(sf::Color::Red);
    sound.play();
}


void FeuTricolore::update(){
    float t = clock.getElapsedTime().asSeconds();
    if(t>=0.f){
        etat = EtatFeu::Rouge;
        cercle.setFillColor(sf::Color::Red);
    }
    if (t >= 1.f) {
        cercle.setFillColor(sf::Color::Yellow);
    }
    if(t>=2.f){
        etat = EtatFeu::Orange;
        cercle.setFillColor(sf::Color(255, 165, 0));
    }
    if (t >= 3.f) {
        etat = EtatFeu::Vert;
        cercle.setFillColor(sf::Color::Green);
    }
    if (t >= 4.5f) {
        cercle.setFillColor(sf::Color::Transparent);
    }
}

void FeuTricolore::draw(sf::RenderWindow& window){
    window.draw(cercle);
}

filesystem::path FeuTricolore::getAssetPath(const std::string& relativePath){
    // __FILE__ donne le chemin du fichier source courant
    filesystem::path sourceDir = filesystem::path(__FILE__).parent_path();
    
    // Remonte jusqu’au dossier du projet (ex: depuis src/jeu.cpp → ../../assets/...)
    filesystem::path assetDir = sourceDir / ".." / "assets";

    // Normalise le chemin
    assetDir = filesystem::canonical(assetDir);

    return assetDir / relativePath;
}