//
// Created by aidan on 4/17/2023.
//

#ifndef MARKETSIMULATION_SIMULATION_H
#define MARKETSIMULATION_SIMULATION_H

#include "llrbtree.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Simulation {
private:
    int timeSinceStart;
    int minutesPassed;
    float offset;
    int delistedStocks = 0;
    sf::RenderWindow mainWindow;
    std::vector<std::string> tickers;
    std::string events[5] = {"bear market","bull market","recession","economic boom","stagnation"};
    int tickersSize;
    int totalAmountOfStocks;
    LLRBTree stockTree;
    std::string event = "stagnation";

    [[noreturn]] void simulation();
    void draw();

public:
    Simulation();
    void printInformation();
};


#endif //MARKETSIMULATION_SIMULATION_H
