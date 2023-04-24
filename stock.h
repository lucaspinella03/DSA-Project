//
// Created by aidan on 4/11/2023.
//

#ifndef MARKETSIMULATION_STOCK_H
#define MARKETSIMULATION_STOCK_H

#include <string>

class Stock {
private:
    std::string ticker;
                            //name of stock ex. ("PFE" for "Pfizer")

    std::string outstandingShares;
                            // the total amount of shares issued by the company

    double price;
                            // the dollar value of the stock
                            // WHEN supply REACHES 0 price will increase between $0.01 and $0.04
                            // WHEN supply REACHES 1/1000 of the OUTSTANDINGSHARES price will decrease between $0.01 and $0.04

    int volume;
                            // the amount of shares bought or sold over a period of time
                            // BUYING shares INCREASES the VOLUME
                            // SELLING shares INCREASES the VOLUME

    std::string marketCap;
                            // the total value of the shares held by investors
                            // BUYING shares INCREASES the MARKETCAP
                            // SELLING shares DECREASES the MARKETCAP

    int supply;
                            // the total amount of shares being sold at the price
                            // BUYING shares DECREASES the supply
                            // SELLING shares INCREASES the supply
    int daysTradingBelow1 = 0;
    bool delisted = false;
                            //if a stock trades negatively for 30 days, it is DELISTED.
    int timeWhenBought = -100;
    int timeWhenSold = -100;
    int timeSinceUpdate = 0;

public:
    Stock(std::string ticker, std::string outstandingShares, double price);
    Stock();
    std::string getTicker();

    std::string getOutstandingShares() const;
    double getPrice() const;
    int getVolume() const;
    std::string getMarketCap() const;
    int getSupply() const;

    void buyShares(int num, int time);
    void sellShares(int num, int time);
    int getBought();
    int getSold();
    int getUpdateTime();
    void setUpdateTime(int num);
    int getDelisted();

    friend class LLRBTNode;


};


#endif //MARKETSIMULATION_STOCK_H
