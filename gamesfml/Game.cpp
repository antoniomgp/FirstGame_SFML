#include "Game.h"

// Private functions
void Game::initVariables() {

	//Window initialization
	this->window = nullptr;

	//Game logic initialization
	this->points = 0;
	this->enemySpawnTimerMax = 1000.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
}

void Game::initWindow() {

	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initEnemies(){
	this->enemy.setPosition(10.f,10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(0.5f, 0.5f);
	this->enemy.setFillColor(sf::Color::Red);
}

//Constructors / Destructors
Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

const bool Game::running() const
{
	return this->window->isOpen();
}

Game::~Game() {
	delete this->window;
}




void Game::pollEvents(){
	while (this->window->pollEvent(this->event)) {
		switch (event.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}



//Functions
void Game::update(){
	this->pollEvents();

	this->updateMousePositions();

	this->updateEnemies();
}


void Game::updateMousePositions() {
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);
}

void Game::spawnEnemy(){
	this->enemy.setPosition(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),0.f);

	this->enemy.setFillColor(sf::Color::Green);

	this->enemies.push_back(this->enemy);


}

void Game::updateEnemies(){

	//Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies) {
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else {
			this->enemySpawnTimer += 1.f;
		}
	}

	//Move enemies
	for (auto &e : this->enemies)
	{
		e.move(0.f, 1.f);
	}
}

void Game::renderEnemies(){
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
	
}


void Game::render(){

	/*
		Renders the game objects

		- clear old frames
		- render objects
		- display frame in window
	*/

	this->window->clear();

	//Draw game objects
	this->renderEnemies();

	this->window->display();
}




