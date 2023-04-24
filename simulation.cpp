//
// Created by aidan on 4/17/2023.
//

// written in loving memory of Norman (still alive)
// created the stack library

#include "simulation.h"
#include "stock.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <cmath>
#include <stack>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iomanip>

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
        file.open(fileName);

    }

    std::string aniResult;
    bool incorrect = false;
    while(aniResult != "y" && aniResult != "n") {
        if(incorrect) std::cout << "invalid response -- please input either 'y' or 'n' " << std::endl;
        std::cout << "Animations on (y/n):";
        std::cin >> aniResult;
        incorrect = true;
    }

    if(aniResult == "y") animations = true;
    else animations = false;

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

    this->tickersSize = int(this->tickers.size());
    this->totalAmountOfStocks = int(this->tickers.size());

    this->mainWindow.create(sf::VideoMode(1920, 1080), "Market Simulation");
    this->offset = 0;

    this->timeSinceStart = -1;

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
    std::uniform_int_distribution<> coinFlip(0,100);
    std::uniform_int_distribution<> buyGen;
    std::uniform_int_distribution<> sellGen;

    auto startTime = std::chrono::steady_clock::now();
    while(true){ // 30 frames a second
        draw();
        auto time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - startTime);
        if(time.count() != timeSinceStart && delistedStocks != this->totalAmountOfStocks){
            timeSinceStart = int(time.count());
            int tradeAmount = tradeGen(randGenerator);
            int buyOdds;
            if(this->event == "bear market"){
                tradeAmount = int(std::round(tradeAmount * 0.85));
                buyOdds = 45;
                std::uniform_int_distribution<> tempBuyGen(50,800);
                std::uniform_int_distribution<> tempSellGen(100,5000);
                buyGen = tempBuyGen;
                sellGen = tempSellGen;
            } else if (this->event == "bull market") {
                tradeAmount = int(std::round(tradeAmount * 1.75));
                buyOdds = 65;
                std::uniform_int_distribution<> tempBuyGen(100,4800);
                std::uniform_int_distribution<> tempSellGen(50,800);
                buyGen = tempBuyGen;
                sellGen = tempSellGen;
            } else if (this->event == "recession"){
                tradeAmount = int(std::round(tradeAmount * 2.05));
                buyOdds = 15;
                std::uniform_int_distribution<> tempBuyGen(50,500);
                std::uniform_int_distribution<> tempSellGen(400,25000);
                buyGen = tempBuyGen;
                sellGen = tempSellGen;
            } else if (this->event == "economic boom"){
                tradeAmount = int(std::round(tradeAmount * 2.50));
                buyOdds = 85;
                std::uniform_int_distribution<> tempBuyGen(600,30000);
                std::uniform_int_distribution<> tempSellGen(50,500);
                buyGen = tempBuyGen;
                sellGen = tempSellGen;
            } else { // stagnation
                tradeAmount = int(std::round(tradeAmount * 0.65));
                buyOdds = 50;
                std::uniform_int_distribution<> tempBuyGen(50,2500);
                std::uniform_int_distribution<> tempSellGen(50,2500);
                buyGen = tempBuyGen;
                sellGen = tempSellGen;
            }
            for(int i = 0; i < tradeAmount; i++) {
                if(delistedStocks == this->totalAmountOfStocks) break;
                int tickerIndex = tickerGen(randGenerator);
                Stock *tempStock = this->stockTree.search(this->tickers.at(tickerIndex));
                bool listed = tempStock->getDelisted();
                if (!tempStock->getDelisted()) {
                    int flipResult = coinFlip(randGenerator);
                    if (flipResult <= buyOdds) {
                        tempStock->buyShares(buyGen(randGenerator), this->timeSinceStart);
                    } else {
                        tempStock->sellShares(sellGen(randGenerator), this->timeSinceStart);
                    }

                }
                if(listed != tempStock->getDelisted()){
                    this->tickers.erase(this->tickers.begin() + tickerIndex);
                    this->tickersSize = int(this->tickers.size());
                    std::uniform_int_distribution<> tempTickerGen(0, this->tickersSize-1);
                    tickerGen = tempTickerGen;
                    this->delistedStocks++;
                }
            }

            if(timeSinceStart % 60 == 0){ // change event
                this->minutesPassed++;
                int eventIndex = eventGen(randGenerator);
                this->event = events[eventIndex];
                //std::cout << events[eventIndex] << std::endl;




            }
        }

    }

}

void Simulation::draw() {
    this->mainWindow.clear();
    sf::Event windowEvent{};
    sf::Font font;
    font.loadFromFile("IBMPlexMono-Regular.ttf"); //AOTFShinGoProBold.otf RobotoMono-VariableFont_wght.ttf IBMPlexMono-Regular.ttf
    sf::Text tempText;
    tempText.setFont(font);
    tempText.setFillColor(sf::Color::White);
    tempText.setCharacterSize(15);
    //tempText.setStyle(sf::Text::Bold);

    std::stack<LLRBTNode*> stack;
    //stack.push(this->stockTree.getRoot());

    // Sounds :D

    int x = -1;
    int y = 10;
    int i = 0;


    LLRBTNode* tempNode = this->stockTree.getRoot();

    Stock lowest = *tempNode->getData();
    Stock highest = *tempNode->getData();
    while(tempNode != nullptr || !stack.empty()){

        while(tempNode != nullptr) {
            stack.push(tempNode);
            tempNode = tempNode->getLeft();
        }
        tempNode = stack.top();
        stack.pop();

        Stock* tempStock = tempNode->getData();

        y++;
        if(i % int(std::ceil((double(this->totalAmountOfStocks)/12.0))) == 0){
            x++;
            y = 10;
        }

        if(tempStock->getPrice() > highest.getPrice()){
            highest = *tempStock;
        }
        if(!tempStock->getDelisted() && tempStock->getPrice() < lowest.getPrice()){
            lowest = *tempStock;
        }

        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << tempStock->getPrice();
        std::stringstream ss2;
        ss2 << std::setw(5) << std::left << tempStock->getTicker() << " ";
        if(!tempStock->getDelisted()) {
            ss2 << "$" << std::setw(5) << std::left << std::fixed << std::setprecision(2) << ss.str();
        } else {
            ss2 << std::setw(5) << std::left << std::fixed << "DELISTED";
        }

        int animationTime = animations; //animation time after color hold
        double animationSpeed = animations * 1.13; // 0 - 0 // 1 - 1.13 // 3 - 0.12 //

        if(tempStock->getDelisted()){
            tempText.setFillColor(sf::Color::Red);
        } else if(tempStock->getBought()+animationTime >= this->timeSinceStart){

            int updateTime = tempStock->getUpdateTime();

            updateTime = int(std::round(updateTime * updateTime * animationSpeed));
            if(updateTime > 255){
                updateTime = 255;
            }
            tempText.setFillColor(sf::Color(updateTime,255,updateTime));
            if(tempStock->getSold() != this->timeSinceStart){
                tempStock->setUpdateTime(tempStock->getUpdateTime()+1);
            }

            //tempText.setFillColor(sf::Color::Green);
        } else if(tempStock->getSold()+animationTime >= this->timeSinceStart){

            int updateTime = tempStock->getUpdateTime();

            updateTime = int(std::round(updateTime * updateTime * animationSpeed));
            if(updateTime > 255){
                updateTime = 255;
            }
            tempText.setFillColor(sf::Color(255,updateTime,updateTime));
            if(tempStock->getSold() != this->timeSinceStart){
                tempStock->setUpdateTime(tempStock->getUpdateTime()+1);
            }

            //tempText.setFillColor(sf::Color::Red);
        }



        tempText.setString(ss2.str());
        tempText.setPosition(160.f*float(x), 15.f*float(y)+offset);
        this->mainWindow.draw(tempText);
        i++;

        tempText.setFillColor(sf::Color::White);

        tempNode = tempNode->getRight();
    }


    tempText.setString("Time Elapsed:     " + std::to_string(this->timeSinceStart));
    tempText.setPosition(10, 15+offset);
    this->mainWindow.draw(tempText);
    tempText.setString("Market Update In: " + std::to_string(60 - this->timeSinceStart % 60));
    tempText.setPosition(10, 30+offset);
    this->mainWindow.draw(tempText);
    tempText.setString("Market Sentiment: " + this->event);
    tempText.setPosition(10, 45+offset);
    this->mainWindow.draw(tempText);
    tempText.setString("Delisted Stocks: " + std::to_string(this->delistedStocks));
    tempText.setPosition(10, 60+offset);
    this->mainWindow.draw(tempText);
    tempText.setString("Remaining Stocks: " + std::to_string(this->totalAmountOfStocks-this->delistedStocks));
    tempText.setPosition(10, 75+offset);
    this->mainWindow.draw(tempText);

    std::stringstream ss1;
    std::stringstream ss2;
    std::stringstream ss3;
    std::stringstream ss4;

    ss1 << std::fixed << std::setprecision(2) << highest.getPrice();
    ss2 << std::setw(5) << std::left << highest.getTicker() << " ";
    ss2 << "$" << std::setw(5) << std::left << std::fixed << std::setprecision(2) << ss1.str();

    ss3 << std::fixed << std::setprecision(2) << lowest.getPrice();
    ss4 << std::setw(5) << std::left << lowest.getTicker() << " ";
    ss4 << "$" << std::setw(5) << std::left << std::fixed << std::setprecision(2) << ss3.str();

    tempText.setString("Most Expensive Stock:  " + ss2.str());
    tempText.setPosition(10, 90+offset);
    this->mainWindow.draw(tempText);
    tempText.setString("Least Expensive Stock: " + ss4.str());
    tempText.setPosition(10, 105+offset);
    this->mainWindow.draw(tempText);
    
    while(this->mainWindow.pollEvent(windowEvent)){

        if(windowEvent.type == sf::Event::Closed) {
            this->mainWindow.close();
            exit(-5);
        }
        if(windowEvent.type == sf::Event::MouseWheelScrolled){
            if (windowEvent.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
                if((windowEvent.mouseWheelScroll.delta > 0 && offset < 0) || (windowEvent.mouseWheelScroll.delta < 0 && offset > -12.3*(std::ceil((double(this->totalAmountOfStocks)/12.0))))){
                    this->offset += windowEvent.mouseWheelScroll.delta * 10;
                }
            }
        }

    }

    this->mainWindow.display();
}
