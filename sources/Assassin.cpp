#include "Assassin.hpp"
#include "Game.hpp"
#include <stdexcept>
using namespace coup;

const int Assassin::ASSASSIN_COUP_PRICE = 3;

Assassin::Assassin(Game& game, const std::string& name): Player(game, name){}
Assassin::~Assassin(){}

void Assassin::coup(Player& player){
	if (this->m_coins < ASSASSIN_COUP_PRICE){
		throw std::invalid_argument("player does not have enough coins");
	}

	if (this->m_coins < COUP_PRICE){
		this->m_game->assassinsCoup(*this, player);
	}
	else{
		this->m_game->coup(*this, 0 ,player);
	}
}

std::string Assassin::role() const{
	return "Assassin";
}