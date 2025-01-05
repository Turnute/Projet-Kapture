#include "pch.h"

namespace kpt {

    class GameManagerTest : public ::testing::Test {
    protected:
        GameManager* game;
        void SetUp() override {
            // Création d'un fichier de configuration temporaire pour les tests
            std::ofstream testFile("test_config.txt");
            testFile << "empty;empty;empty;empty;empty;empty;empty;empty;empty;empty\n";
            testFile << "empty;empty;empty;empty;empty;empty;empty;empty;empty;empty\n";
            testFile << "empty;empty;empty;empty;empty;empty;empty;empty;empty;empty\n";
            testFile << "empty;empty;empty;empty;empty;empty;empty;empty;empty;empty\n";
            testFile << "empty;empty;empty;empty;empty;empty;empty;empty;empty;empty\n";
            testFile << "empty;empty;empty;empty;empty;empty;empty;empty;empty;empty\n";
            testFile << "empty;empty;empty;empty;empty;empty;empty;empty;empty;empty\n";
            testFile << "empty;empty;empty;empty;empty;empty;empty;empty;empty;empty\n";
            testFile << "empty;empty;empty;empty;empty;empty;empty;empty;empty;empty\n";
            testFile << "empty;empty;empty;empty;empty;empty;empty;empty;empty;empty\n";
            testFile << "\n";
            testFile << "P1\n";
            testFile << "scout: 0:0;0:1\n";
            testFile << "elite: 1:0;1:1\n";
            testFile << "fodder: 2:0;2:1\n";
            testFile << "flag: 0:9\n";
            testFile << "\n";
            testFile << "P2\n";
            testFile << "scout: 9:9;9:8\n";
            testFile << "elite: 8:9;8:8\n";
            testFile << "fodder: 7:9;7:8\n";
            testFile << "flag: 9:0\n";
            testFile.close();

            game = new GameManager("test_config.txt");
        }

        void TearDown() override {
            delete game;
            std::remove("test_config.txt");
        }
    };

    // Test d'initialisation du jeu
    TEST_F(GameManagerTest, GameInitialization) {
        EXPECT_FALSE(game->isOver());
    }

    // Test de mouvement d'unité
    TEST_F(GameManagerTest, TokenMovement) {
        // Test de mouvement valide
        EXPECT_NO_THROW(game->moveToken({ 0,0 }, { 1,0 }));

        // Test de mouvement hors limites
        EXPECT_THROW(game->moveToken({ -1,0 }, { 0,0 }), std::out_of_range);

        // Test de mouvement sur une case occupée
        EXPECT_NO_THROW(game->moveToken({ 0,1 }, { 0,0 }));  // Devrait échouer silencieusement
    }

    // Test des conditions de victoire
    TEST_F(GameManagerTest, VictoryConditions) {
        EXPECT_FALSE(game->isOver());
    }

    // Test de résolution des batailles
    TEST_F(GameManagerTest, BattleResolution) {
        // Création de deux unités pour le test
        Player p1{ "P1", {}, {0,0} };
        Player p2{ "P2", {}, {9,9} };

        scout s1{ "S1", {0,0}, p1 };
        elite e2{ "E2", {0,1}, p2 };

        game->battle(s1, e2);
        // Vérifier que le scout a perdu et a été renvoyé à sa position d'origine
        EXPECT_EQ(s1.getPosition(), s1.getOrigin());
    }
}
