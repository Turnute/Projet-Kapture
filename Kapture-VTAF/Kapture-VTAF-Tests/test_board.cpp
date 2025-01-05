#include "pch.h"

namespace kpt {

    class BoardTest : public ::testing::Test {
    protected:
        std::vector<enum_cell> cells;
        void SetUp() override {
            cells = std::vector<enum_cell>(100, EMPTY);
            // Ajout de quelques obstacles
            cells[25] = FOREST;  // Position (2,5)
            cells[67] = RIVER;   // Position (6,7)
        }
    };

    // Test de création du plateau
    TEST_F(BoardTest, BoardCreation) {
        Board board(cells);
        EXPECT_EQ(board.getWidth(), 10);
        EXPECT_EQ(board.getHeight(), 10);
    }

    // Test d'accès aux cellules
    TEST_F(BoardTest, CellAccess) {
        Board board(cells);
        // Test d'accès valide
        EXPECT_NO_THROW(board.seek({ 0,0 }));

        // Tests d'accès invalides
        EXPECT_THROW(board.seek({ -1,0 }), std::out_of_range);
        EXPECT_THROW(board.seek({ 10,0 }), std::out_of_range);
        EXPECT_THROW(board.seek({ 0,-1 }), std::out_of_range);
        EXPECT_THROW(board.seek({ 0,10 }), std::out_of_range);
    }

    // Test des types de cellules
    TEST_F(BoardTest, CellTypes) {
        Board board(cells);
        EXPECT_EQ(board.seek({ 2,5 })->getType(), FOREST);
        EXPECT_EQ(board.seek({ 6,7 })->getType(), RIVER);
        EXPECT_EQ(board.seek({ 0,0 })->getType(), EMPTY);
    }

    // Test des mouvements de token
    TEST_F(BoardTest, TokenMovement) {
        Board board(cells);
        Player player{ "P1", {}, {0,0} };
        scout* s = new scout("S1", { 0,0 }, player);

        // Placement initial
        board.setToken({ 0,0 }, s);
        EXPECT_TRUE(board.seek({ 0,0 })->getToken() != nullptr);

        // Déplacement
        cell* origin = board.seek({ 0,0 });
        cell* dest = board.seek({ 0,1 });
        origin->moveTokenTo(dest);

        EXPECT_TRUE(board.seek({ 0,0 })->getToken() == nullptr);
        EXPECT_TRUE(board.seek({ 0,1 })->getToken() != nullptr);

        delete s;
    }

    // Test de la gestion du drapeau
    TEST_F(BoardTest, FlagHandling) {
        Board board(cells);
        flag f("P1", { 0,0 });

        board.setFlag({ 0,0 }, &f);
        EXPECT_TRUE(board.seek({ 0,0 })->getFlag() != nullptr);

        board.resetFlag(&f);
        EXPECT_TRUE(board.seek({ 0,0 })->getFlag() != nullptr);
    }
}
