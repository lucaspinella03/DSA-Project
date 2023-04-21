//
// Created by aidan on 4/17/2023.
//

#include "simulation.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>

Simulation::Simulation() {

    std::string fileName;
    std::cout << "file name: ";
    std::cin >> fileName;
    std::cout << std::endl;
    std::fstream file;
    file.open(fileName);

    while(!file.is_open()){
        std::cout << "file not found -- please input valid file name" << std::endl;
        std::cout << "file name: ";
        std::cin >> fileName;
        std::cout << std::endl;
        file.open(fileName);

    }
    std::string line;
    std::getline(file, line); // burn first line

    std::vector<std::string> tempInfo;

    std::string tempStr;

    while(std::getline(file, line) ) {
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string tempLine;

        while(std::getline(ss, tempLine, ',')){
            tokens.push_back(tempLine);
        }

        this->tickers.push_back(tokens.at(0));
        Stock tempStock(tokens.at(0), tokens.at(1), std::stod(tokens.at(2)));
        this->stockTree.insert(tempStock);

    }

    this->tickersSize = this->tickers.size();

    this->mainWindow.create(sf::VideoMode(1920, 1080), "SFML Test");

    simulation();

}

void Simulation::printInformation() {

    this->stockTree.preorder(std::cout);
}

void Simulation::simulation() {

    std::random_device randomDevice;
    std::mt19937 randGenerator(randomDevice());
    std::uniform_int_distribution<> eventGen(0,4);
    std::uniform_int_distribution<> tickerGen(0, this->tickersSize-1);
    std::uniform_int_distribution<> tradeGen(200, 1000);

    auto startTime = std::chrono::steady_clock::now();
    long long int previousTime = -1;
    int countMinutes = 0;
    while(true){
        draw();
        auto time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - startTime);

        if(time.count() != previousTime){
            previousTime = time.count();
            int tradeAmount = tradeGen(randGenerator);
            if(this->event == "bear market"){
                tradeAmount *= 0.85;
            } else if (this->event == "bull market") {
                tradeAmount *= 1.75;
            } else if (this->event == "recession"){
                tradeAmount *= 2.05;
            } else if (this->event == "economic boom"){
                tradeAmount *= 2.50;
            } else { // stagnation
                tradeAmount *= 0.65;
            }
            for(int i = 0; i < tradeAmount; i++){
                int tickerIndex = tickerGen(randGenerator);
                std::cout << this->tickers.at(tickerIndex) << " ";
            }
            std::cout << std::endl;
            std::cout << previousTime << std::endl;
            std::cout << std::endl;

            if(previousTime % 60 == 0){ // change event
                countMinutes++;
                int eventIndex = eventGen(randGenerator);
                this->event = events[eventIndex];
                std::cout << events[eventIndex] << std::endl;



            }
        }

    }

}

void Simulation::draw() {
    sf::Event eventTest{};

    for(int i = 0; i < this->tickersSize; i++){
        sf::Text tempText;
        tempText.setFont()
    }

    while(this->mainWindow.pollEvent(eventTest)){
        if(eventTest.type == sf::Event::Closed){
            this->mainWindow.close();
        }
    }

    this->mainWindow.clear();
    this->mainWindow.display();
}
