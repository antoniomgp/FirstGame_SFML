#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Class that acts as the game engine
	Wrapper class
*/
class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	
	//Mouse positions
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;
	sf::Text OverText;

	//Game logic
	unsigned int points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	unsigned int maxEnemies;
	bool mouseHold;
	bool endGame;
	

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	

	//Private functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initEnemies();
	void initText();
	void initOverText();
public:
	Game();
	~Game();
	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void spawnEnemy();
	void pollEvents();
	void updateText();
	void updateEnemies();
	void update();
	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
	void updateMousePositions();
	void GameOverText();
};

