//
// Created by aidan on 4/11/2023.
//

#include "stock.h"

#include <utility>

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

void Stock::buyShares(int num) {
    this->volume += num;


}

void Stock::sellShares(int num) {

}

Stock::Stock() {

}


