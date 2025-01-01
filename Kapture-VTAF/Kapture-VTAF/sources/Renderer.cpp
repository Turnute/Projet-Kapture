//  TOURENNE    FERRY
//  Vincent     Antony

#include "../headers/Renderer.h"

#include <iomanip>
#include <iostream>
#include <utility>

namespace kpt
{
    Renderer::Renderer()
        : players(nullptr), board(nullptr) {}

    Renderer::Renderer(const std::vector<Player>& players, const Board& board)
        : players(&players), board(&board)
    {
        if (!this->players) {
            std::cerr << "Players pointer is null!" << std::endl;
        }
        if (!this->board) {
            std::cerr << "Board pointer is null!" << std::endl;
        }
    }

    Renderer& Renderer::operator=(const Renderer& other)
    {
        if (this != &other) {
            this->players = other.players;
            this->board = other.board;
        }
        return *this;
    }

    void Renderer::render() const
    {
        const std::pair<int, int> dim = board->getDimensions();
        const int width = dim.first;
        const int heigth = dim.second;

        std::cout << std::setw(6);
        std::string bar = "  ";
        for (int i = 0; i < width; i++) {
            std::cout << i;
            std::cout << std::setw(4);
            bar += "+---";
        }
        bar += "+";
        std::cout << std::endl;
        for (int i = 0; i < heigth; i++) {
            std::cout << bar << std::endl;
            std::cout << i << " ";
            for (int j = 0; j < width; j++) {
                const cell* currentCell = board->seek(i, j);
                std::cout << "|";
                std::cout << *currentCell;
            }
            std::cout << "|" << std::endl;
        }
        std::cout << bar << std::endl;
    }
}