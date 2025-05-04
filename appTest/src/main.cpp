#include "jeu.hpp"
#include <iostream>
using namespace std;

int main()
{	
	sf::Font font;
	font.loadFromFile("../appTest/assets/fonts/arial.ttf");

	Jeu *jeu = new Jeu();
	jeu->running();
	delete jeu;
	return 0;
}
