#include "Game.h"

// Private functions
void Game::initVariables() {
	this->window = nullptr;
}

void Game::initWindow() {

	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close);
}

//Constructors / Destructors
Game::Game() {
	this->initVariables();
	this->initWindow();
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
}

void Game::render(){

	/*
		Renders the game objects

		- clear old frames
		- render objects
		- display frame in window
	*/

	this->window->clear(sf::Color(255, 0, 0, 255));

	//Draw game objects

	this->window->display();
}
