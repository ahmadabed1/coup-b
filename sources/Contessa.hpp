#pragma once
#include "Player.hpp"
namespace coup{
	class Contessa : public Player{
	private:

	public:
		Contessa(Game& game, const std::string& name);
		virtual ~Contessa();
		
		void block(Player& player);
		virtual std::string role() const;
	};
}