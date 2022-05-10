#pragma once
#include <vector>
#include <string>
#include "Player.hpp"
#include "Duke.hpp"
#include "Assassin.hpp"
#include "Ambassador.hpp"
#include "Captain.hpp"
#include "Contessa.hpp"
#include "BlockableOperation.hpp"

namespace coup{
	class Game{
	private:
		std::vector<std::pair<std::string, bool>> m_players;
		std::vector<BlockableOperation> m_operations;
		size_t m_turn;
		bool gameStarted;
		static const int MAX_AMOUNT_OF_PLAYERS;
        static const int MIN_AMOUNT_OF_PLAYERS;
        static const int COINS_TO_COUP;
		

		bool isPlayerAlive(Player& player);
		void addBlockableOperation(Player& src, Operation operation, Player& dst, int stealAmount=0);
		void removePlayer(const std::string& name);
		void markDead(const std::string& name);
		void markAlive(const std::string& name);
		size_t findPlayerIndex(Player& player) const;
		void checkTurn(Player& player);
		void endTurn();
	public:
		Game();
		void foreign_aid(Player& player);
		void income(Player& player);
		void addPlayer(Player& player);
		void coup(Player& killer, int dummy, Player& victim);
		
		void tax(Duke* taxer);
		void transfer(Player& takeFrom, Ambassador* transferer, Player& giveTo);
		void steal(Captain& stealer, Player& victim);
		void assassinsCoup(Assassin& killer, Player& victim);

		void stealBlock(Player& blocker, Player& blocked);
		void coupBlock(Contessa& blocker, Assassin& blocked);
		void aidBlock(Player& blocker, Player& blocked);

		std::string turn() const;
		std::vector<std::string> players() const;
		std::string winner() const;
	};
}