#include "menu.hpp"

Menu::Menu(sf::RenderWindow &wd):window(wd){//Initialise la reference de window ne peut pas etre affecte dans le constructeur
    if (!font.loadFromFile(getAssetPath("fonts/DejaVuSans.ttf").string())){
        // Gérer une erreur éventuelle ici (mettre une police par défaut sinon)
        std::cerr << "Erreur chargement police !" << std::endl;
    }
    initButtons();
}

void Menu::initButtons(){
    OnePlayerButton.setSize({200,60});
    OnePlayerButton.setFillColor(sf::Color::Yellow);
    OnePlayerButton.setPosition({300,400});

    TwoPlayerButton.setSize({200, 60});
    TwoPlayerButton.setPosition({100, 250});
    TwoPlayerButton.setFillColor(sf::Color::Blue);

    StartButton.setSize({200, 60});
    StartButton.setPosition({100, 400});
    StartButton.setFillColor(sf::Color::Green);

    titletText.setFont(font);
    titletText.setString("BOAT RACE");
    titletText.setCharacterSize(50);
    titletText.setFillColor(sf::Color::Green);
    titletText.setPosition(10,10);

    OnePlayerText.setFont(font);
    OnePlayerText.setString("1 Joueur");
    OnePlayerText.setCharacterSize(24);
    OnePlayerText.setFillColor(sf::Color::White);
    OnePlayerText.setPosition(OnePlayerButton.getPosition().x + 30, OnePlayerButton.getPosition().y + 15);

    TwoPlayerText.setFont(font);
    TwoPlayerText.setString("2 Joueurs");
    TwoPlayerText.setCharacterSize(24);
    TwoPlayerText.setFillColor(sf::Color::White);
    TwoPlayerText.setPosition(TwoPlayerButton.getPosition().x + 30, TwoPlayerButton.getPosition().y + 15);

    StartText.setFont(font);
    StartText.setString("Start");
    StartText.setCharacterSize(24);
    StartText.setFillColor(sf::Color::Green);
    StartText.setPosition(StartButton.getPosition().x + 60, StartButton.getPosition().y + 15);

}

void Menu::render(){
    window.draw(titletText);

    window.draw(OnePlayerButton);
    window.draw(OnePlayerText);

    window.draw(TwoPlayerButton);
    window.draw(TwoPlayerText);

    window.draw(StartButton);
    window.draw(StartText);

}

void Menu::pollEvents(const sf::Event& event){
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
        if (isMouseOver(OnePlayerButton)) {
            selectedPlayers = 1;
            cout<<"1 PLAYER"<<endl;
        }
        else if (isMouseOver(TwoPlayerButton)) {
            selectedPlayers = 2;
            cout<<"2 PLAYERS"<<endl;
        }
        else if (isMouseOver(StartButton) && selectedPlayers != 0) {
            StartOK = 1;
        }
    }
}


bool Menu::isMouseOver(const sf::RectangleShape& button){
    //Renvoie vrai si la souris survole le bouton
    auto mousePos = sf::Mouse::getPosition(window);
    auto translatedPos = window.mapPixelToCoords(mousePos);

    //Souris sur le bouton?
    return button.getGlobalBounds().contains(translatedPos);
}

void Menu::update()
{
    // Option : changer la couleur des boutons si survolés
    if (isMouseOver(OnePlayerButton))
        OnePlayerButton.setFillColor(sf::Color(100, 100, 255)); // Bleu clair
    else
        OnePlayerButton.setFillColor(sf::Color::Blue);

    if (isMouseOver(TwoPlayerButton))
        TwoPlayerButton.setFillColor(sf::Color(100, 100, 255)); 
    else
        TwoPlayerButton.setFillColor(sf::Color::Blue);

    if (selectedPlayers == 0)
        StartButton.setFillColor(sf::Color(100, 255, 100)); // Vert clair désactivé
    else
        StartButton.setFillColor(sf::Color::Green);
}

int Menu::getSelectedPlayer(){
    //Renvoie le mode joueur choisi
    return selectedPlayers;
}

bool Menu::isReadyToStart(){
    return StartOK;
}

filesystem::path Menu::getAssetPath(const std::string& relativePath){
    // __FILE__ donne le chemin du fichier source courant
    filesystem::path sourceDir = filesystem::path(__FILE__).parent_path();
    
    // Remonte jusqu’au dossier du projet (ex: depuis src/jeu.cpp → ../../assets/...)
    filesystem::path assetDir = sourceDir / ".." / "assets";

    // Normalise le chemin
    assetDir = filesystem::canonical(assetDir);

    return assetDir / relativePath;
}
