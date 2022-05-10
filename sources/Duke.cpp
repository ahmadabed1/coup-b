#include "Duke.hpp"
#include "Game.hpp"

using namespace coup;
const int Duke::TAX_AMOUNT = 3;
 
Duke::Duke(Game& game, const std::string& name): Player(game, name){}
Duke::~Duke(){}

void Duke::block(Player& player){
	m_game->aidBlock(*this, player);
}
void Duke::tax(){
	m_game->tax(this);
}
std::string Duke::role() const{
	return "Duke";
}