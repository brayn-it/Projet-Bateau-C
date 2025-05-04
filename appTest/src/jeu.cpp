#include "jeu.hpp"
/*
void Jeu::initWindow():menu(window){
    width = 1200;
    height = 800;
    titre = "BOAT RACE";
    vm = sf::VideoMode({width,height});
    window = new sf::RenderWindow(vm,titre);
    window->setFramerateLimit(60);
    // Dans classe Carte ==================================================================
    ligneDepart = Ligne(sf::Vector2f(20.f,720.f),sf::Vector2f(50.f,40.f),sf::Color::Green);
    ligneArrivee = Ligne(sf::Vector2f(20.f,720.f),sf::Vector2f(720.f,40.f),sf::Color::Red);
    //Creation obstacle
    Jeu::creerObstacle(sf::Vector2f(30.f,80.f),sf::Vector2f(200.f,80.f),sf::Color::Magenta);
    Jeu::creerBateau(sf::Color::Yellow);
    Jeu::creerBateau(sf::Color::Green);
    // ====================================================================================
}*/

//INIT Jeu
Jeu::Jeu():width(1280),height(720),vm(sf::VideoMode(width,height)),window(vm,"BOAT RACE"),
            menu(window),etat(EtatJeu::Menu),course(window,clock){//Init des attrib en ref
    window.setFramerateLimit(60);
    dt = 0.01;
    clock = sf::Clock();
}


void Jeu::pollEvents(){
    sf::Event event;
    //event processing

    while (window.pollEvent(event))
    {
        //Close window
        if(event.type == sf::Event::Closed)
            window.close();
        
        //EVENT DE CHAQUE FENETRE
        if(etat==EtatJeu::Menu){
            menu.pollEvents(event);
            //Apres appui du bouton start
            if(menu.isReadyToStart()){
                mode = menu.getSelectedPlayer();
                course.init(mode);
                etat = EtatJeu::Joue;
            }
        }
        else if(etat==EtatJeu::Joue){
            course.pollEvents();
        }
    }
}

void Jeu::rendering(){
    //Render carte et tout ce qui s'y passe
    window.clear(sf::Color::Blue);
    course.render();
}


Jeu::~Jeu(){

}

void Jeu::running(){
    while(window.isOpen()){
        if(etat==EtatJeu::Menu){
            pollEvents();
            menu.update();
            menu.render();
        }
        else if(etat==EtatJeu::Joue){
            course.run();
        }
        window.display();
    }
} 


filesystem::path Jeu::getAssetPath(const std::string& relativePath){
    // __FILE__ donne le chemin du fichier source courant
    filesystem::path sourceDir = filesystem::path(__FILE__).parent_path();
    
    // Remonte jusqu’au dossier du projet (ex: depuis src/jeu.cpp → ../../assets/...)
    filesystem::path assetDir = sourceDir / ".." / "assets";

    // Normalise le chemin
    assetDir = filesystem::canonical(assetDir);

    return assetDir / relativePath;
}
