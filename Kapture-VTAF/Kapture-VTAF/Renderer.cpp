//  TOURENNE    FERRY
//  Vincent     Antony

#include "Renderer.h"

#include <iomanip>
#include <iostream>

void kpt::Renderer::render() const
{
    const int width = 10;
    const int heigth = 10; //TODO: real size
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
            std::cout << "|   "; //TODO: current token at (i, j)
        }
        std::cout << "|" << std::endl;
    }
    std::cout << bar << std::endl;
}
