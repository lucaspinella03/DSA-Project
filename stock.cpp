//
// Created by aidan on 4/11/2023.
//

#include "stock.h"
#include <utility>
#include <random>
#include <iostream>

//CONSTRUCTORS
Stock::Stock(std::string ticker, std::string outstandingShares, double price){
    this->ticker = std::move(ticker);
    this->outstandingShares = std::move(outstandingShares);
    this->price = price;
    this->volume = 0;
    this->marketCap = std::to_string(std::stod(this->outstandingShares) * this->price);
    this->supply = 0;
}

//GETTERS AND SETTERS

std::string Stock::getTicker() {
    return this->ticker;
}

std::string Stock::getOutstandingShares() const {
    return this->outstandingShares;
}

double Stock::getPrice() const {
    return this->price;
}

int Stock::getVolume() const {
    return this->volume;
}

std::string Stock::getMarketCap() const {
    return this->marketCap;
}

int Stock::getSupply() const {
    return this->supply;
}

// FUNCTIONS

void Stock::buyShares(int num, int time) {
    this->volume += num;
    this->timeWhenBought = time;
    this->timeSinceUpdate = 0;

    std::random_device randomDevice;
    std::mt19937 randGenerator(randomDevice());
    std::uniform_int_distribution<> priceChange(1, 9);
    int limit = int(25*log(std::stod(this->outstandingShares)));
    int increase = (num - this->supply) / limit;
    this->supply = (num - this->supply) % limit;

    this->price += double(increase)*(double(priceChange(randGenerator))/100.f);


}

void Stock::sellShares(int num, int time) {
    this->volume += num;
    this->timeWhenSold = time;
    this->timeSinceUpdate = 0;

    std::random_device randomDevice;
    std::mt19937 randGenerator(randomDevice());
    std::uniform_int_distribution<> priceChange(1, 9);

    this->supply += num;
    int increase = supply / int(25*log(std::stod(this->outstandingShares)));
    this->supply %= int(25*log(std::stod(this->outstandingShares)));

    this->price -= (double(increase)*(double(priceChange(randGenerator))/100));

    if(this->price < 1.00){
        daysTradingBelow1++;
        if(this->daysTradingBelow1 == 30 || price <= 0.009){
            delisted = true;
        }
    } else {
        daysTradingBelow1 = 0;
    }

}

Stock::Stock() {

}

int Stock::getBought() {
    return this->timeWhenBought;
}

int Stock::getSold() {
    return this->timeWhenSold;
}

int Stock::getUpdateTime() {
    return this->timeSinceUpdate;
}

void Stock::setUpdateTime(int num) {
    timeSinceUpdate = num;
}

int Stock::getDelisted() {
    return this->delisted;
}


