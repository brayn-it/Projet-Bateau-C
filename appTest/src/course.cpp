#include "course.hpp"

Course::Course(sf::RenderWindow& wd, sf::Clock & clk):window(wd),feu(clk){
    //INIT DE TOUS LES ELEMENTS SELON LE MODE
    clock = clk;
    dt = 0.01;
    ligneDepart = Ligne(sf::Vector2f(10.f,700.f),sf::Vector2f(120.f,40.f),sf::Color::Green);
    ligneArrivee = Ligne(sf::Vector2f(10.f,700.f),sf::Vector2f(1150.f,10.f),sf::Color::Red);
    creerBateau();
    endingSoundbuffer.loadFromFile(getAssetPath("audio/endrace.wav").string());
    endingSound.setBuffer(endingSoundbuffer);
}

void Course::init(int m){
    feu.demarrer();
    mode=m;
    clock.restart();
    if(mode==1){
        //Obstacles
        creerObstacle1();
        //Init text Joueur dashboard
        Bateaux[0].setDashboardPlayerText(1);
    }
    else if(mode==2){
        //Obstacles
        creerObstacle2();
        //Dashboard bateau2 a  droite
        Bateaux[1].setDashboardPosition({1000,600});

        //Text joueur
        Bateaux[0].setDashboardPlayerText(1);
        Bateaux[1].setDashboardPlayerText(2);

        //Placer 2e bateau a la bonne position
        Bateaux[1].setBoatPosition({84,500});
    }
}

void Course::creerBateau(){
    for(int i=0;i<2;i++){
        sim::physics::RigidBody* body = engine.createGenericBoat();
        Bateau B(body, randomColor());
        Bateaux.push_back(B);
    }
}

void Course::creerObstacle1(){
    //Obstacles pour 1 joueur
    sf::Vector2f dim({25,50});
    float x = 300;
    float y;
    for(int i=0;i<7;i++){
        y = rand()%720*1.0;
        Obstacle obs(dim,{x,y},randomColor());
        obstacles.push_back(obs);
        x=x+100;
    }
}

void Course::creerObstacle2(){
    //Obstacles pour 2 joueurs
    sf::Vector2f dim({25,50});
    float x = 300;
    float y;
    for(int i=0;i<7;i++){
        y = rand()%250*1.0;
        Obstacle obs(dim,{x,y},randomColor());
        obstacles.push_back(obs);
        x=x+100;
    }
    x=300;
    for(int i=0;i<7;i++){
        y = rand()%250*1.0+250;
        Obstacle obs(dim,{x,y},randomColor());
        obstacles.push_back(obs);
        x=x+100;
    }
}

void Course::pollEvents(){
    if(active_command)
        command_control();
}


void Course::updateRaceState(){
    float t = clock.getElapsedTime().asSeconds();
    //Debut de la course en activant les commandes
    if(state == RaceState::Starting && t>=4.5f){
        state = RaceState::Running;
        active_command=true;
        //DEBUT DE TIME
        startTime = clock.getElapsedTime().asSeconds();
    }

    if(state == RaceState::Running){
        //SELON LE MODE JOUEURs
        //Desactive les controles quand un des joueur a franchi la ligne
        //Affiche les resultats
        if(mode==1){
            float xBoat = Bateaux[0].Get_Body()->getState().position.x/Bateaux[0].Get_Facteur().x; //Division par le facteur pour avoir la pos sur ecran
            if(xBoat>=ligneArrivee.getPosition().x){
                endingSound.play();
                state =  RaceState::Finished;
                active_command=false;
                //AFFICHAGE RESULTAT
                result.setResult(1,endTime-startTime);
            }
        }
        else if(mode==2){
            float xBoat1 = Bateaux[0].Get_Body()->getState().position.x/Bateaux[0].Get_Facteur().x;;
            float xBoat2 = Bateaux[1].Get_Body()->getState().position.x/Bateaux[1].Get_Facteur().x;;
            if(xBoat1>=ligneArrivee.getPosition().x || xBoat2>=ligneArrivee.getPosition().x){
                endingSound.play();
                state =  RaceState::Finished;
                active_command=false;
                //END TIME
                endTime = clock.getElapsedTime().asSeconds();
                //AFFICHAGE RESULTAT
                if(xBoat1>=ligneArrivee.getPosition().x)
                    result.setResult(1,endTime-startTime);
                else
                    result.setResult(2,endTime-startTime);
            }
        }
    }
}

void Course::update(){
    //Update de tous les elements de la course
    //UPDATE BATEAUX
    for(Bateau& b:Bateaux){// c++ moderne for each
        b.update(model);
    }
    //cout << Bateaux[0].Get_Body()->getState().acc_body.x << " | " << Bateaux[0].Get_Body()->getState().acc_body.y << endl;
    //engine.step(dt);
    
    //UPDATE FEU
    feu.update();
    updateRaceState();
    cout<<Bateaux[0].Get_Body()->getState().position.x<<endl;
}

void Course::render(){
    //Render carte et tout ce qui s'y passe
    window.clear(sf::Color::Blue);

    //DESSIN LIGNES DEPART ET ARRIVEE
    ligneDepart.draw(window);
    ligneArrivee.draw(window);

    //Obstacles
    for(const Obstacle& o:obstacles){
        o.draw(window);
    }

    //Bateaux
    if(mode==1){
        Bateaux[0].draw(window);
        bateauVsObstacle(Bateaux[0]);
    }
    else if(mode ==2){
        Bateaux[0].draw(window);
        bateauVsObstacle(Bateaux[0]);

        Bateaux[1].draw(window);
        bateauVsObstacle(Bateaux[1]);
    }

    //On laise le tableau jusqu'a la fin
    if(state==RaceState::Finished)
        result.draw(window);

    //Feu
    feu.draw(window);
}

void Course::bateauVsObstacle(Bateau bateau){
    //Gere collision avec obstacles
    int i = 0;
    sim::common::Vector2 P_inter = sim::common::Vector2 (-1, -1);
    while (i<obstacles.size() && P_inter.x == -1 && P_inter.y == -1){
        P_inter = inObstacle(bateau, obstacles[i]);
        i++;
    }
    if (P_inter.x != -1 && P_inter.y != -1){
        sim::common::Vector2 velo = bateau.Get_Body()->getState().velocity_body;
        SetPos(bateau, obstacles[i-1], P_inter);
        bateau.Get_Body()->setVelocity_body(-velo.x, -velo.y);
    }
}


Course::~Course(){

}

void Course::run(){
    sf::Int64 temps_boucle = 0;
    pollEvents();
    sf::Int64 begin = clock.getElapsedTime().asMicroseconds();
    update();
    render();
    sf::Int64 end = clock.getElapsedTime().asMicroseconds();
    temps_boucle += end - begin;
    /*while (temps_boucle >= dt*1000000){ // dt*1000000 -> 10000 microseconde -> 10 miliseconde
        engine.step(dt);
        temps_boucle -= dt*1000000;
    }*/
    engine.step(dt);
    window.display();
} 



sf::Color Course::randomColor(){
    //Renvoie une couleur aleatoire
    int r = rand()%255;
    int g = rand()%255;
    int b = rand()%255;
    return sf::Color(r,g,b,255);
}

void Course::command_control(){
    //Commande bateau 1
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) Bateaux[0].Deplacement_X(model, 6000, 0, 1026);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) Bateaux[0].Deplacement_Y(model, 90, 1026);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) Bateaux[0].Deplacement_X(model, 6000, 180, 1026);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) Bateaux[0].Deplacement_Y(model, -90, 1026);

    //Commande Bateau 2
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) Bateaux[1].Deplacement_X(model, 6000, 0, 1026);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) Bateaux[1].Deplacement_Y(model, 90, 1026);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) Bateaux[1].Deplacement_X(model, 6000, 180, 1026);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) Bateaux[1].Deplacement_Y(model, -90, 1026);
}



void Course::SetPos(Bateau& b, Obstacle& O, sim::common::Vector2& P){
    double gauche = O.get_Position().x;
    double haut = O.get_Position().y;
    double droite = O.get_Position().x + O.get_Dimention().x;
    double bas = O.get_Position().y + O.get_Dimention().y;
    // 0.00001 -> marge d'erreur : travail en double
    if (P.x - gauche < 0.00001) b.Get_Body()->setPosition(b.Get_Body()->getState().position.x - 1 * b.Get_Facteur().x, b.Get_Body()->getState().position.y);
    else if (P.y - haut < 0.00001) b.Get_Body()->setPosition(b.Get_Body()->getState().position.x, b.Get_Body()->getState().position.y - 1 * b.Get_Facteur().y);
    else if (P.x - droite < 0.00001) b.Get_Body()->setPosition(b.Get_Body()->getState().position.x + 1 * b.Get_Facteur().x, b.Get_Body()->getState().position.y);
    else if (P.x - bas < 0.00001) b.Get_Body()->setPosition(b.Get_Body()->getState().position.x, b.Get_Body()->getState().position.y + 1 * b.Get_Facteur().y);
}

sim::common::Vector2 Course::intersection_seg(sim::common::Vector2 A, sim::common::Vector2 B, sim::common::Vector2 C, sim::common::Vector2 D){
    // Renvoie le point d'intersection des segments AB et CD s'il existe sinon None
    float det = (B.x - A.x) * (C.y - D.y) - (C.x - D.x) * (B.y - A.y); // determinant de Cramer de l'equation

    if (det != 0){ // non colineaire
        float t1 = ((C.x - A.x) * (C.y - D.y) - (C.x - D.x) * (C.y - A.y)) / det;
        float t2 = ((B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y)) / det;

        if (!(t1>1 || t1<0 || t2>1 || t2<0)){ // Point d'intersection
            if (t1 == 0) return A;
            else if (t1 == 1) return B;
            else if (t2 == 0) return C;
            else if (t2 == 1) return D;
            else return sim::common::Vector2 (A.x + t1*(B.x-A.x), A.y + t1*(B.y-A.y));
        }
    }
    return sim::common::Vector2 (-1, -1);
}

sim::common::Vector2 Course::inObstacle(Bateau& b, Obstacle& O){
    int i = 0;
    int nb_point_bateau = b.Get_Forme().getPointCount();
    float angle = b.Get_Body()->getState().yaw;
    sim::common::Vector2 Point_inter = sim::common::Vector2 (-1, -1);
    while (i<nb_point_bateau && Point_inter.x == -1 && Point_inter.y == -1){
        sim::common::Vector2 tmp = b.rotation_point(b.Get_P(i), angle);
        sim::common::Vector2 P1_Bat = sim::common::Vector2 (b.Get_Forme().getPosition().x + tmp.x, b.Get_Forme().getPosition().y + tmp.y);
        tmp = b.rotation_point(b.Get_P((i+1) % nb_point_bateau), angle);
        sim::common::Vector2 P2_Bat = sim::common::Vector2 (b.Get_Forme().getPosition().x + tmp.x, b.Get_Forme().getPosition().y + tmp.y);
        sim::common::Vector2 P1_Ob = sim::common::Vector2 (O.get_Position().x, O.get_Position().y);
        sim::common::Vector2 P2_Ob = sim::common::Vector2 (O.get_Position().x + O.get_Dimention().x, O.get_Position().y);
        sim::common::Vector2 P3_Ob = sim::common::Vector2 (O.get_Position().x + O.get_Dimention().x, O.get_Position().y + O.get_Dimention().y);
        sim::common::Vector2 P4_Ob = sim::common::Vector2 (O.get_Position().x, O.get_Position().y + O.get_Dimention().y);
        tmp = intersection_seg(P1_Bat, P2_Bat, P1_Ob, P2_Ob);
        if (tmp.x != -1 && tmp.y != -1) Point_inter = tmp;
        tmp = intersection_seg(P1_Bat, P2_Bat, P2_Ob, P3_Ob);
        if (tmp.x != -1 && tmp.y != -1) Point_inter = tmp;
        tmp = intersection_seg(P1_Bat, P2_Bat, P3_Ob, P4_Ob);
        if (tmp.x != -1 && tmp.y != -1) Point_inter = tmp;
        tmp = intersection_seg(P1_Bat, P2_Bat, P4_Ob, P1_Ob);
        if (tmp.x != -1 && tmp.y != -1) Point_inter = tmp;
        i++;
    }
    return (Point_inter);
}

filesystem::path Course::getAssetPath(const std::string& relativePath){
    // __FILE__ donne le chemin du fichier source courant
    filesystem::path sourceDir = filesystem::path(__FILE__).parent_path();
    
    // Remonte jusqu’au dossier du projet (ex: depuis src/jeu.cpp → ../../assets/...)
    filesystem::path assetDir = sourceDir / ".." / "assets";

    // Normalise le chemin
    assetDir = filesystem::canonical(assetDir);

    return assetDir / relativePath;
}
