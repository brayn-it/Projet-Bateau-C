#include "dashboard.hpp"

Dashboard::Dashboard(){
    //Creer Dashboard selon position
    if (!font->loadFromFile(getAssetPath("fonts/arial.ttf").string())){
        // Gérer une erreur éventuelle ici (mettre une police par défaut sinon)
        cerr << "Erreur chargement police !" << std::endl;
    }
    background.setSize({200.f, 120.f});
    background.setFillColor(sf::Color(30, 30, 30, 200));
    background.setPosition(position);

    init();
}

Dashboard::Dashboard(const sf::Vector2f& pos){
    if (!font->loadFromFile(getAssetPath("fonts/arial.ttf").string())){
        // Gérer une erreur éventuelle ici (mettre une police par défaut sinon)
        cerr << "Erreur chargement police !" << std::endl;
    }
    position = pos;
    //Creer Dashboard selon position
    init();
}

void Dashboard::init(){
    background.setSize({200.f, 120.f});
    background.setFillColor(sf::Color(30, 30, 30, 200));
    background.setPosition(position);

    textPlayer.setString("J-");
    setupText(textPlayer,position+sf::Vector2f(10,10));
    setupText(textSpeed, position + sf::Vector2f(10, 35));
    setupText(textAcceleration, position + sf::Vector2f(10, 60));
    setupText(textAngle, position + sf::Vector2f(10, 85));
    setupText(textRotation, position + sf::Vector2f(10, 100));
}

void Dashboard::setupText(sf::Text &text, sf::Vector2f pos){
    if(font)
        text.setFont(*font);
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::White);
    text.setPosition(pos);
}

void Dashboard::setPosition(const sf::Vector2f& pos){
    position = pos;
    background.setPosition(position);

    setupText(textSpeed, position + sf::Vector2f(10, 10));
    setupText(textAcceleration, position + sf::Vector2f(10, 35));
    setupText(textAngle, position + sf::Vector2f(10, 60));
    setupText(textRotation, position + sf::Vector2f(10, 85));

}

void Dashboard::configPlayerText(int j){
    //Joueur 1 ou 2
    if(j==1 || j==2){
        textPlayer.setString("J-"+to_string(j));
    }
}

void Dashboard::update(float speed, float accel, float yawDeg, float rot){
    textSpeed.setString("Speed: " + to_string(speed) + " m/s");
    textAcceleration.setString("Acc.: " + to_string(accel) + " m/s²");
    textAngle.setString("Angle: " + to_string(yawDeg)+ "°");
    textRotation.setString("Rot.: " + to_string(rot)+ " rad/s");
}

void Dashboard::draw(sf::RenderWindow &window){
    window.draw(background);
    window.draw(textPlayer);
    window.draw(textSpeed);
    window.draw(textAcceleration);
    window.draw(textAngle);
    window.draw(textRotation);
}

filesystem::path Dashboard::getAssetPath(const std::string& relativePath){
    // __FILE__ donne le chemin du fichier source courant
    filesystem::path sourceDir = filesystem::path(__FILE__).parent_path();
    
    // Remonte jusqu’au dossier du projet (ex: depuis src/jeu.cpp → ../../assets/...)
    filesystem::path assetDir = sourceDir / ".." / "assets";

    // Normalise le chemin
    assetDir = filesystem::canonical(assetDir);

    return assetDir / relativePath;
}

Dashboard::~Dashboard(){
    //if(font)
        //delete font;
}