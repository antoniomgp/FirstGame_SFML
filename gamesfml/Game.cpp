#include "Game.h"

// Private functions
void Game::initVariables() {

	//Window initialization
	this->window = nullptr;

	//Game logic initialization
	this->endGame = false;
	this->health = 10;
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHold = false;
}

void Game::initWindow() {

	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (this->font.loadFromFile("Fonts/arial.ttf")) {
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n" << std::endl;
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}

void Game::initOverText()
{
	this->OverText.setFont(this->font);
	this->OverText.setCharacterSize(90);
	this->OverText.setFillColor(sf::Color::Red);
	this->OverText.setPosition(150,250);
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
	this->initFonts();
	this->initText();
	this->initOverText();
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
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

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n" << "Health: " << this->health << "\n";
	this->uiText.setString(ss.str());
}



//Functions
void Game::update(){
	this->pollEvents();

	if(this->endGame == false)
		this->updateMousePositions();
		this->updateText();
		this->updateEnemies();
		this->GameOverText();

		//End game condition
		if (this->health <= 0) {	
			this->endGame = true;
			
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
	target.draw(this->OverText);
}


void Game::updateMousePositions() {
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePositionWindow);
}

void Game::GameOverText()
{
	if (health <= 0) {
		std::stringstream sf;
		sf << "GAMEOVER";
		this->OverText.setString(sf.str());
	}
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

	//Move and updating enemies
	for (unsigned i = 0; i < this->enemies.size(); i++) {

		this->enemies[i].move(0.f, 5.f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << std::endl;
		}
	}
	//Check if clicked upon
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		if (this->mouseHold == false) {
			this->mouseHold = true;
			for (size_t i = 0; i < this->enemies.size(); i++) {
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
					//Delete the enemy
					this->enemies.erase(this->enemies.begin() + i);
					//Gain points
					this->points += 1;
					std::cout << "Points: " << this->points << std::endl;
					break;
				}
			}
		}
		
	}
	else {
		this->mouseHold = false;
	}
}

void Game::renderEnemies(sf::RenderTarget& target){
	for (auto& e : this->enemies)
	{
		target.draw(e);
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
	this->renderEnemies(*this->window);

	this->renderText(*this->window);

	this->window->display();
}

