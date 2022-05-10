#include "Contessa.hpp"
#include "Assassin.hpp"
#include "Game.hpp"
#include <stdexcept>

using namespace coup; 

Contessa::Contessa(Game& game, const std::string& name): Player(game, name){}
Contessa::~Contessa(){}

void Contessa::block(Player& player){
	Assassin* ass = dynamic_cast<Assassin*>(&player);
	if (ass == nullptr){
		throw std::invalid_argument("Contessa can only block steal from Assassin");
	}
	m_game->coupBlock(*this, *ass);
}

std::string Contessa::role() const{
	return "Contessa";
}