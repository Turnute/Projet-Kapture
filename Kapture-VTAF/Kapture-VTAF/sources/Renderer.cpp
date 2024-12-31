//  TOURENNE    FERRY
//  Vincent     Antony

#include "Renderer.h"

#include <iomanip>
#include <iostream>
#include <utility>

kpt::Renderer::Renderer(const std::vector<Player>& players, const Board& board) : players(players), board(board) {}

void kpt::Renderer::render() const
{
    const std::pair<int, int> dim = board.getDimensions();
    const int width = dim.first;
    const int heigth = dim.second;

    std::cout << std::setw(6);
    std::string bar = "  ";
    for (int i = 0; i < width; i++){
        std::cout << i;
        std::cout << std::setw(4);
        bar+="+---";
    }
    bar+="+";
    std::cout << std::endl;
    for (int i = 0; i < heigth; i++){
        std::cout << bar << std::endl;
        std::cout << i << " ";
        for (int j = 0; j < width; j++){
            std::cout << "|";
            std::cout << *(board.seek(i, j));
        }
        std::cout << "|" << std::endl;
    }
    std::cout << bar << std::endl;
}
