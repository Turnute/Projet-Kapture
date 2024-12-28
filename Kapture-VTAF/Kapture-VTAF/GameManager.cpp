//  TOURENNE    FERRY
//  Vincent     Antonny

#include "GameManager.h"

namespace kpt
{
	void GameManager::battle(token& t1, token& t2)
	{
		switch (t1.battle(t2))
		{
		case 0:
			switch (t1.getType())
			{
			case SCOUT:
				break;
			case ELITE:
				// TODO : Les deux reculent d'une case
				break;
			case FODDER:
				// TODO : 50/50 qui gagne ou perd
				break;
			}
			break;
		case 1:
			resetToken(t2);
		case 2:
			resetToken(t1);
		default:
			break;
		}
	}
	void GameManager::resetToken(token& t_token)
	{
		//TODO :
		// 
		// Drop le flag sur une case libre s'il en a un
			// Commence le compte du flag

		// Reset le token à sa position initiale
	}
}