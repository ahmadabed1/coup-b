#include "Player.hpp"
#include "Game.hpp"
#include <stdexcept>

using namespace coup;
const int Player::COUP_PRICE = 7;
 
Player::Player(Game& game, const std::string& name) :m_coins(0), m_game(&game), m_name(name){
	this->m_game->addPlayer(*this);
}

Player::~Player(){
}

void Player::addCoins(int n){
	this->m_coins+= n;
}

void Player::takeCoins(int n){
	if (this->m_coins < n){
		throw std::invalid_argument("Not enough coins for this player.");
	}
	this->m_coins-= n;
}

void Player::income(){
	m_game->income(*this);
}

void Player::foreign_aid(){
	m_game->foreign_aid(*this);
}

void Player::coup(Player& player){
	if (this->m_coins < COUP_PRICE){
		throw std::invalid_argument("player does not have enough coins");
	}
	this->m_game->coup(*this, 0, player);
}

int Player::coins() const{
	return m_coins;
}

std::string Player::getName() const{
	return this->m_name;
}
std::string Player::role() const{
    return "";
}
