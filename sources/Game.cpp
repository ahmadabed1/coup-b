#include "Game.hpp"
#include "Player.hpp"
#include <stdexcept>

using namespace coup;
using namespace std;
const int Game::MAX_AMOUNT_OF_PLAYERS = 6;
const int Game::MIN_AMOUNT_OF_PLAYERS = 2;
const int Game::COINS_TO_COUP = 10;


Game::Game() : m_turn(0), gameStarted(false){
}

string Game::turn() const{
	return m_players[m_turn].first;
}

bool Game::isPlayerAlive(Player& player){
	for (size_t i = 0; i < m_players.size(); i++){
		if (m_players[i].first == player.getName()){
			return m_players[i].second;
		}
	}
	return false;
}

void Game::checkTurn(Player& player) {
	if (m_players.size() >= MIN_AMOUNT_OF_PLAYERS){
		gameStarted = true;
	}
	if(!gameStarted){
		throw std::invalid_argument("Game has not started");
	}
	if (turn() != player.getName()){
		throw std::invalid_argument("Not this player's turn.");
	}

	//player's turn means he can not be blocked anymore
	vector<BlockableOperation>::iterator itr = m_operations.begin();
	while (itr != m_operations.end()){
		if (itr->src->getName() == turn()){
			itr = m_operations.erase(itr);
			continue;
		}
		itr++;
	}
}

void Game::addPlayer(Player& player){
	if(gameStarted){
		throw std::invalid_argument("Game already started.");
	}
	if (m_players.size() < MAX_AMOUNT_OF_PLAYERS){
		this->m_players.push_back(make_pair(player.getName(), true));
	}
	else{
		throw std::invalid_argument("Too many players");
	}
}
void Game::addBlockableOperation(Player& src, Operation operation, Player& dst, int stealAmount){
	m_operations.push_back({ &src, operation, &dst , stealAmount});
}

void Game::foreign_aid(Player& player){
	checkTurn(player);
	if(player.coins() >= COINS_TO_COUP){
		throw std::invalid_argument("Must coup at more than 10 coins");
	}
	player.addCoins(2);
	addBlockableOperation(player, Operation::ForeinAid, player);
	endTurn();
}

void Game::income(Player& player){
	checkTurn(player);
	if(player.coins() >= COINS_TO_COUP){
		throw std::invalid_argument("Must coup at more than 10 coins");
	}
	player.addCoins(1);
	endTurn();
}
size_t Game::findPlayerIndex(Player& player) const{
	vector<string> names = players();
	for (size_t i = 0; i < names.size(); i++){
		if (names[i] == player.getName()){
			return i;
		}
	}
	return (size_t)-1;
}

void Game::coup(Player& killer, int dummy, Player& victim){
    dummy = 0;
	checkTurn(killer);
	removePlayer(victim.getName());
	killer.takeCoins(dummy + Player::COUP_PRICE);
	size_t playerIndex = findPlayerIndex(killer);
	if (playerIndex < m_turn){
		m_turn--;
	}
	endTurn();
}

void Game::assassinsCoup(Assassin& killer, Player& victim){
	checkTurn(killer);
	markDead(victim.getName());
	killer.takeCoins(Assassin::ASSASSIN_COUP_PRICE);
	addBlockableOperation(killer, Operation::AssassinCoup, victim);
	endTurn();	
}

void Game::steal(Captain& stealer, Player& victim){
	checkTurn(stealer);
	int stealAmount = min(2, victim.coins());
	victim.takeCoins(stealAmount);
	stealer.addCoins(stealAmount);
	addBlockableOperation(stealer, Operation::CaptainSteal, victim, stealAmount);
	endTurn();
}

void Game::transfer(Player& takeFrom, Ambassador* transferer, Player& giveTo){
	checkTurn(*transferer);
	takeFrom.takeCoins(1);
	giveTo.addCoins(1);
	endTurn();
}

void Game::tax(Duke* taxer){
	checkTurn(*taxer);
	taxer->addCoins(Duke::TAX_AMOUNT);
	endTurn();
}

void Game::stealBlock(Player& blocker, Player& blocked){
	bool confirmBlocked = false;
	vector<BlockableOperation>::iterator itr = m_operations.begin();
	while (itr != m_operations.end()){
		if (itr->src->getName() == blocked.getName()){
			if (itr->operation == Operation::CaptainSteal){
				//revert operation
				itr->src->takeCoins(itr->stealAmount);
				itr->dst->addCoins(itr->stealAmount);
				m_operations.erase(itr);
				confirmBlocked = true;
				break;
			}
		}
		itr++;
	}
	if (!confirmBlocked){
		throw std::invalid_argument("Block wasn't successful");
	}
}

void Game::coupBlock(Contessa& blocker, Assassin& blocked){
	bool confirmBlocked = false;
	vector<BlockableOperation>::iterator itr = m_operations.begin();
	while (itr != m_operations.end()){
		if (itr->src->getName() == blocked.getName()){
			if (itr->operation == Operation::AssassinCoup){
				//revert operation
				markAlive(itr->dst->getName());
				m_operations.erase(itr);
				confirmBlocked = true;
				break;
			}
		}
		itr++;
	}
	if (!confirmBlocked){
		throw std::invalid_argument("Block wasn't successful");
	}
}
void Game::aidBlock(Player& blocker, Player& blocked){
	bool confirmBlocked = false;
	vector<BlockableOperation>::iterator itr = m_operations.begin();
	while (itr != m_operations.end()){
		if (itr->src->getName() == blocked.getName()){
			if (itr->operation == Operation::ForeinAid){
				//revert operation
				blocked.takeCoins(2);
				m_operations.erase(itr);
				confirmBlocked = true;
				break;
			}
		}
		itr++;
	}
	if (!confirmBlocked){
		throw std::invalid_argument("Block wasn't successful");
	}
}

void Game::markDead(const std::string& name){
	for (vector<std::pair<std::string, bool>>::iterator itr = m_players.begin();
		itr < m_players.end(); itr++){
		if (itr->first == name){
			itr->second = false;
			return;
		}
	}
	throw std::invalid_argument("Player not found.");
}

void Game::markAlive(const std::string& name){
	for (vector<std::pair<std::string, bool>>::iterator itr = m_players.begin();
		itr != m_players.end(); itr++){
		if (itr->first == name){
			itr->second = true;
			return;
		}
	}
	throw std::invalid_argument("Player not found.");
}

void Game::removePlayer(const std::string& name){
	for (vector<std::pair<std::string, bool>>::iterator itr = m_players.begin();
		itr < m_players.end(); itr++){
		if (itr->first == name){
			m_players.erase(itr);
			return;
		}
	}
	throw std::invalid_argument("Player not found.");
}

void Game::endTurn(){
	do{
		m_turn = (m_turn + 1) % m_players.size();
	}while(!m_players[m_turn].second);

}

std::vector<std::string> Game::players() const{
	std::vector<std::string> names;
	for (size_t i = 0; i < m_players.size(); i++){
		if (m_players[i].second){
			names.push_back(m_players[i].first);
		}
	}
	return names;
}

std::string Game::winner() const{
	if(!gameStarted){
		throw std::invalid_argument("Game has not started.");
	}
	vector<string> names = players();
	if (names.size() != 1){
		throw std::invalid_argument("There is more than 1 player in the game");
	}
	return names[0];
}
