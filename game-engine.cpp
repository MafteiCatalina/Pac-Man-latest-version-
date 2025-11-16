#include "game-engine.hpp"
#include "painter.hpp"
#include <algorithm>
#include <iterator>
#include <memory>

#include "external/json.hpp"
#include <fstream>
using json = nlohmann::json;

GameEngine::GameEngine() { 
    _painter = std::make_unique<Painter>(); 
}

void GameEngine::Init() { 
    Point initialPositions[] = {{10, 10}, {10, 11}, {11, 10}, {11, 11}};
    std::copy(std::begin(initialPositions), std::end(initialPositions), _ghosts.begin());
    _pacman = Pacman({1, 1});
    _painter->WriteText({1, 22}, "Jocul Pac-Man a inceput!");
}

void GameEngine::Run() {
    bool areFantomeVulnerabile = std::any_of(_ghosts.begin(), _ghosts.end(), 
                                            [](const Ghost& g){ return g.IsVulnerable(); });

    if (areFantomeVulnerabile) {
        _painter->WriteText({1, 23}, "Fantomele sunt vulnerabile!");
    }

    json data;
    data["score"] = _pacman.GetScore();
    std::ofstream file("save.json");
    file << data;
}
