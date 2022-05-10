#pragma once
#include "Player.hpp"

namespace coup{
	class Duke: public Player{
	public:
		static const int TAX_AMOUNT;
		Duke(Game& game, const std::string& name);
		virtual ~Duke();

		void block(Player& player);
		void tax();
		virtual std::string role() const;
	};
}