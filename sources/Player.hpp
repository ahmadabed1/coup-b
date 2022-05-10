#pragma once
#include <string>
namespace coup{
	class Game;

	class Player{
	protected:
		int m_coins;
		Game* m_game;
		std::string m_name;

	public:
		static const int COUP_PRICE;

		Player(Game& game, const std::string& name);
		virtual ~Player();
		void addCoins(int n);
		void takeCoins(int n);
		void income();
		void foreign_aid();
		void coup(Player& player);
		int coins() const;
		std::string getName() const;
		
		virtual std::string role() const;
	};
}
