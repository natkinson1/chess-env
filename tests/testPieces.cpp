#include <iostream>
#include <vector>
#include <assert.h>
#include "../environment.h"

int main() {
    Environment env;

    // env.reset();
    std::vector<std::unique_ptr<Piece>> pieceList;
    pieceList.push_back(std::make_unique<Pawn>(std::vector<int>{3,3}, 1, true));
    pieceList.push_back(std::make_unique<Pawn>(std::vector<int>{3,4}, 1, false));
    env.loadState(pieceList);
    std::vector<std::vector<std::vector<int>>> moves = env.getActions();

    std::cout << "Number of moves: " << moves.size() << std::endl;
    assert(moves.size() == 3);

    pieceList.clear();

    pieceList.push_back(std::make_unique<Bishop>(std::vector<int>{0,0}, 1));
    env.loadState(pieceList);
    std::vector<std::vector<std::vector<int>>> moves2 = env.getActions();

    std::cout << "Number of moves: " << moves2.size() << std::endl;
    assert(moves2.size() == 7);

    pieceList.clear();

    pieceList.push_back(std::make_unique<King>(std::vector<int>{4,4}, 1, false));
    env.loadState(pieceList);
    std::vector<std::vector<std::vector<int>>> moves3 = env.getActions();

    std::cout << "Number of moves: " << moves3.size() << std::endl;
    assert(moves3.size() == 8);

    pieceList.clear();

    pieceList.push_back(std::make_unique<Knight>(std::vector<int>{4,4}, 1));
    env.loadState(pieceList);
    std::vector<std::vector<std::vector<int>>> moves4 = env.getActions();

    std::cout << "Number of moves: " << moves4.size() << std::endl;
    assert(moves4.size() == 8);

    pieceList.clear();

    pieceList.push_back(std::make_unique<Queen>(std::vector<int>{0,0}, 1));
    env.loadState(pieceList);
    std::vector<std::vector<std::vector<int>>> moves5 = env.getActions();

    std::cout << "Number of moves: " << moves5.size() << std::endl;
    assert(moves5.size() == 21);

    pieceList.clear();

    pieceList.push_back(
        std::make_unique<Bishop>(std::vector<int>{0,0}, 1)
    );
    pieceList.push_back(
        std::make_unique<Pawn>(std::vector<int>{1,1}, 1, true)
    );
    env.loadState(pieceList);
    std::vector<std::vector<std::vector<int>>> moves6 = env.getActions();

    std::cout << "Number of moves: " << moves6.size() << std::endl;
    assert(moves6.size() == 1);

    return 0;

}