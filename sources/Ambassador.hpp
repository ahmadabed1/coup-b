#pragma once
#include "Player.hpp"
namespace coup{
	class Ambassador : public Player{
	private:

	public:
		Ambassador(Game& game, const std::string& name);
		virtual ~Ambassador();
		void block(Player& player);
		void transfer(Player& takeFrom, Player& giveTo);

		virtual std::string role() const;
	};
}