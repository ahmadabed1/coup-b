#pragma once
#include "Player.hpp"
namespace coup{
	class Assassin : public Player{
	public:
		static const int ASSASSIN_COUP_PRICE;
		Assassin(Game& game, const std::string& name);
		virtual ~Assassin();
		
		void coup(Player& player);

		virtual std::string role() const;
	};

	
}