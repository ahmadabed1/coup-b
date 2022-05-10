#include "Ambassador.hpp"
#include "Game.hpp"

using namespace coup;

Ambassador::Ambassador(Game& game, const std::string& name): Player(game, name){}

Ambassador::~Ambassador(){}

void Ambassador::block(Player& player){
	m_game->stealBlock(*this, player);
}

void Ambassador::transfer(Player& takeFrom, Player& giveTo){
	this->m_game->transfer(takeFrom, this, giveTo);
}

std::string Ambassador::role() const{
	return "Ambassador";
}