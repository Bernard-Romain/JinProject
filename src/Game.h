 #pragma once
#include "Player.h"
#include "Room.h"
#include "Door.h"
#include <SFML/Audio.hpp>
#include <functional>

/*
* Classe Game
* 
* Classe principale qui affiche le jeu, l'update à chaque seconde, contient le joueur et les différentes salles.
*/

class Game {

public:
	Game() = default;
	void	run();

	void	triggerLoose();

	void	checkIfWin(); //Boucle pour vérifier si toutes les rooms ont le Room_State Cleared, ce qui amène à la victoire

	void	handleCollisionPlayerDoor(const Door* door); //Gère la collision entre le joueur et une porte
	Player* getPlayer() const { return player.get(); }


private:
	void	processEvents();
	void	load();
	void	render();
	void	update();
	void	save() const; //TODO : A implémenter, sauvegarde du xml actuel dans un fichier.


	void	setCallbacks(); //Initialise les callbacks 
	void	initialiseSprites();

	sf::RenderWindow		mWindow{ sf::VideoMode::getFullscreenModes()[0], "SFML Application", sf::Style::Close};
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Room>> rooms;
	std::vector<std::unique_ptr<Room>>::iterator currentRoom; //Permet de pointer la salle dans laquelle se trouve le joueur, qui sera render à l'écran
	static const sf::Time	TimePerFrame;

	bool win = false;
	sf::Sprite winSprite;
	sf::Texture winTexture;

	bool loose = false;
	sf::Sprite looseSprite;
	sf::Texture looseTexture;

	sf::SoundBuffer winSoundBuffer;
	sf::Sound winSound;

	sf::SoundBuffer looseSoundBuffer;
	sf::Sound looseSound;
};