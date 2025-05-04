#include "resultdashboard.hpp"

ResultDashboard::ResultDashboard(){
    font = new sf::Font;
    font->loadFromFile(getAssetPath("fonts/arial.ttf").string());

    position = sf::Vector2f(350,110);
    background.setFillColor({30,30,30,100});
    background.setSize(sf::Vector2f(500,500));
    background.setPosition(position);

    textWinner.setPosition(position + sf::Vector2f(10,10));
    textWinner.setCharacterSize(35);
    textWinner.setFont(*font);

    textTime.setPosition(position + sf::Vector2f(10,100));
    textTime.setCharacterSize(20);
    textTime.setFont(*font);
}

void ResultDashboard::draw(sf::RenderWindow& window){
    window.draw(background);
    window.draw(textWinner);
    window.draw(textTime);
}

void ResultDashboard::setResult(int win, float time){
    textWinner.setString("WINNER  -  J-"+to_string(win));
    textTime.setString("Time : "+to_string(time)+"s");
}

ResultDashboard::~ResultDashboard(){

}

filesystem::path ResultDashboard::getAssetPath(const std::string& relativePath){
    // __FILE__ donne le chemin du fichier source courant
    filesystem::path sourceDir = filesystem::path(__FILE__).parent_path();
    
    // Remonte jusqu’au dossier du projet (ex: depuis src/jeu.cpp → ../../assets/...)
    filesystem::path assetDir = sourceDir / ".." / "assets";

    // Normalise le chemin
    assetDir = filesystem::canonical(assetDir);
    return assetDir / relativePath;
}
