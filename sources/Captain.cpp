#include "Captain.hpp"
#include "Game.hpp"
#include <stdexcept>

using namespace coup;
 
Captain::Captain(Game& game, const std::string& name): Player(game, name){}
Captain::~Captain(){}

void Captain::block(Player& player){
	m_game->stealBlock(*this, player);
}
void Captain::steal(Player& src){
	m_game->steal(*this, src);
}

std::string Captain::role() const{
	return "Captain";
}