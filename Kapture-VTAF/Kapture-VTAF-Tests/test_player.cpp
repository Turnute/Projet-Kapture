#include "pch.h"

namespace kpt {

    class PlayerTest : public ::testing::Test {
    protected:
        std::vector<std::pair<enum_token, std::pair<int, int>>> tokens = {
            {SCOUT, {0,0}},
            {ELITE, {0,1}},
            {FODDER, {0,2}}
        };
        Player player{ "P1", tokens, {0,9} };
    };

    // Test de création de joueur
    TEST_F(PlayerTest, PlayerCreation) {
        EXPECT_EQ(player.getName(), "P1");
        EXPECT_EQ(player.getTokens().size(), 3);
        EXPECT_EQ(player.getFlag().getPosition(), std::make_pair(0, 9));
    }

    // Test des cellules visitées
    TEST_F(PlayerTest, VisitedCells) {
        EXPECT_FALSE(player.hasVisitedCell(5, 5));
        player.addVisitedCell({ 5,5 });
        EXPECT_TRUE(player.hasVisitedCell(5, 5));

        // Test d'ajout multiple de la même cellule
        player.addVisitedCell({ 5,5 });
        EXPECT_TRUE(player.hasVisitedCell(5, 5));
    }

    // Test des unités du joueur
    TEST_F(PlayerTest, PlayerUnits) {
        const auto& units = player.getTokens();

        // Vérifie les types d'unités
        int scoutCount = 0, eliteCount = 0, fodderCount = 0;
        for (const auto& unit : units) {
            if (unit->getType() == SCOUT) scoutCount++;
            if (unit->getType() == ELITE) eliteCount++;
            if (unit->getType() == FODDER) fodderCount++;
        }

        EXPECT_EQ(scoutCount, 1);
        EXPECT_EQ(eliteCount, 1);
        EXPECT_EQ(fodderCount, 1);
    }

    // Test du drapeau du joueur
    TEST_F(PlayerTest, PlayerFlag) {
        EXPECT_EQ(player.getFlag().getPosition(), std::make_pair(0, 9));
        EXPECT_EQ(player.getFlag().getOrigin(), std::make_pair(0, 9));
    }

    // Test de comparaison de joueurs
    TEST_F(PlayerTest, PlayerComparison) {
        Player player2{ "P1", tokens, {0,9} };
        Player player3{ "P2", tokens, {9,0} };

        EXPECT_EQ(player, player2);
        EXPECT_NE(player, player3);
    }
}