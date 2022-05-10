#pragma once
#include "Player.hpp"
#include <string>

namespace coup{
	enum Operation{
		AssassinCoup,
		CaptainSteal,
		ForeinAid
	};

	typedef struct {
		Player* src;
		Operation operation;
		Player* dst;
		int stealAmount;
	}BlockableOperation;


}