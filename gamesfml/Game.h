#pragma once

#include <iostream>
#include <vector>
#include <ctime>

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

	//Game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	unsigned int maxEnemies;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//Private functions
	void initVariables();
	void initWindow();
	void initEnemies();
public:
	Game();
	~Game();
	//Accessors
	const bool running() const;

	//Functions
	void spawnEnemy();
	void pollEvents();
	void updateEnemies();
	void update();
	void renderEnemies();
	void render();
	void updateMousePositions();
};

