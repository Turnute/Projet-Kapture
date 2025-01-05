#include "pch.h"

namespace kpt {

    class TokenTest : public ::testing::Test {
    protected:
        Player player1{ "P1", {}, {0,0} };
        Player player2{ "P2", {}, {9,9} };

        scout scout1{ "S1", {0,0}, player1 };
        elite elite1{ "E1", {0,1}, player1 };
        fodder fodder1{ "F1", {0,2}, player1 };

        scout scout2{ "S2", {9,9}, player2 };
        elite elite2{ "E2", {9,8}, player2 };
        fodder fodder2{ "F2", {9,7}, player2 };

        flag& flag1 = player1.getFlag();
    };

    // Tests de base des unités
    TEST_F(TokenTest, BasicProperties) {
        EXPECT_EQ(scout1.getName(), "S1");
        EXPECT_EQ(scout1.getPosition(), std::make_pair(0, 0));
        EXPECT_EQ(scout1.getMaxTravel(), 5);
        EXPECT_FALSE(scout1.hasFlag());
    }

    // Tests des points de déplacement
    TEST_F(TokenTest, MovementPoints) {
        // Test pour Scout
        EXPECT_EQ(scout1.getMaxTravel(), 5);
        for (int i = 0; i < 5; i++) {
            EXPECT_TRUE(scout1.canMove());
            scout1.move();
        }
        EXPECT_FALSE(scout1.canMove());
        scout1.resetTravel();
        EXPECT_TRUE(scout1.canMove());

        // Test pour Elite
        EXPECT_EQ(elite1.getMaxTravel(), 3);

        // Test pour Fodder
        EXPECT_EQ(fodder1.getMaxTravel(), 2);
    }

    // Tests des combats
    TEST_F(TokenTest, CombatScenarios) {
        // Scout vs tous
        EXPECT_EQ(scout1.battle(scout2), 0);  // égalité
        EXPECT_EQ(scout1.battle(elite2), 2);  // perd
        EXPECT_EQ(scout1.battle(fodder2), 2); // perd

        // Elite vs tous
        EXPECT_EQ(elite1.battle(scout2), 1);  // gagne
        EXPECT_EQ(elite1.battle(elite2), 0);  // égalité
        EXPECT_EQ(elite1.battle(fodder2), 1); // gagne

        // Fodder vs tous
        EXPECT_EQ(fodder1.battle(scout2), 1); // gagne
        EXPECT_EQ(fodder1.battle(elite2), 2); // perd
    }

    // Dans test_token.cpp
    TEST_F(TokenTest, FlagHandling) {
        flag testFlag("P2", { 0,9 });  // Créer un nouveau drapeau pour le test

        // Scout ne peut pas prendre le drapeau
        scout1.takeFlag(testFlag);
        EXPECT_FALSE(scout1.hasFlag());

        // Elite peut prendre le drapeau
        elite1.takeFlag(testFlag);
        EXPECT_TRUE(elite1.hasFlag());
        EXPECT_EQ(elite1.getFlag(), &testFlag);

        if (elite1.hasFlag()) {
            elite1.dropFlag();
            EXPECT_FALSE(elite1.hasFlag());
        }

        // Fodder peut prendre le drapeau
        fodder1.takeFlag(testFlag);
        EXPECT_TRUE(fodder1.hasFlag());
        EXPECT_EQ(fodder1.getFlag(), &testFlag);
    }

    // Tests de possession d'unité
    TEST_F(TokenTest, UnitOwnership) {
        EXPECT_TRUE(scout1.isOwnedBy(player1));
        EXPECT_FALSE(scout1.isOwnedBy(player2));
    }
}