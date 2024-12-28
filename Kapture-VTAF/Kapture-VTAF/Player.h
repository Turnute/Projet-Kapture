//  TOURENNE    FERRY
//  Vincent     Antonny

#pragma once
namespace kpt
{
	class Player
	{
		const std::string name;
		std::vector<token> tokens;
		std::vector<std::pair<int, int>> visitedCells;
	public:
		Player(const std::string& name, const std::vector<std::pair<enum_token, std::pair<int, int>>> tokens);
	};
}

