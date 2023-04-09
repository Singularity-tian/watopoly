#ifndef DCTIMSLINE_H
#define DCTIMSLINE_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>
#include "nonproperty.h"


class DCTimsLine: public NonProperty {
    int roll() {
        std::vector<int> v = { 1, 2, 3, 4, 5, 6};
        std::vector<int> s = {};
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng{seed};
        for ( int i = 0; i < 1; i++ ) {
        std::shuffle( v.begin(), v.end(), rng );
        for ( int i : v ) s.emplace_back(i);
	    } 

	return s[0];
    }
    int nextmove;

public:
    DCTimsLine(int position, std::string name): NonProperty(position, name) {}
    ~DCTimsLine() {};


    int getNextMove() override {return nextmove;}


    int action(Player &p, int cup) override{
        int tmpCup = cup;
        nextmove = 0;
        if (!p.getsentToDCTL()) std::cout << "==> Nothing happens." << std::endl;
        else {
            std::cout << "==> You are in DC Tims Line." << std::endl;
            std::cout << "==> Roll doubles (input 'Roll'), pay $50 (input 'Pay') or use a Roll Up the Rim cup (input 'RimCup') to leave." << std::endl;
            std::cout << "==> Input: ";
            std::string choice;
            
            while (std::cin >> choice){
                if (choice == "Roll") {
                    int dice1 = roll();
                    int dice2 = roll();
                    std::cout << "==> Roll result: " << dice1 << " " << dice2 << std::endl;
                    if (dice1 == dice2) {
                        // doubles
                        std::cout << "==> You rolled doubles and you may leave the DC Tims Line." << std::endl;
                        p.setsentToDCTL(false);
                        p.setDCTLtimes(0);
                        p.setOSAPcollect(true);
                        nextmove = dice1 + dice2;
                        std::cout << "==> You will move " << nextmove << " steps." << std::endl;

                    } else {
                        // not doubles
                        if (p.getDCTLtimes() == 2) {
                            // but third turn, leave by moving last roll;
                            int sum = dice1 + dice2;
                            std::cout << "==> It's yoru third turn at DC Tims Line" << std::endl;

                            // have neither
                            if (p.getCashAmount() < 50 && p.getRURCup() == 0) {
                                std::cout << "==> You don't have $50 or any Roll Up the Rim cups so you must pay 50." << std::endl;
                                p.addCash(-50);
                                std::cout << "==> You paid $50 and you may leave the DC Tims Line." << std::endl;
                                p.setsentToDCTL(false);
                                p.setDCTLtimes(0);
                                p.setOSAPcollect(true);
                                //move
                            }

                            std::cout << "==> You must pay $50 (input 'Pay') or use a Roll Up the Rim cup (input 'RimCup') to leave." << std::endl;
                            std::cout << "==> Input: ";
                            std::string option = " ";

                            while (std::cin >> option) {
                                if (option == "Pay") {
                                    // if has 50$, pay. 
                                    if (p.getCashAmount() < 50) {
                                        std::cout << "==> You don't have $50, choose a valid option." << std::endl;
                                        std::cout << "==> Input: ";
                                        continue;
                                    } else {
                                        p.addCash(-50);
                                        std::cout << "==> You paid $50 and you may leave the DC Tims Line." << std::endl;
                                        p.setsentToDCTL(false);
                                        p.setDCTLtimes(0);
                                        p.setOSAPcollect(true);
                                        //move
                                    }
                                    break;
                                    

                                } else if (option == "RimCup") {
                                    // if has cup, pay
                                    if (p.getRURCup() == 0) {
                                        std::cout << "==> You do not have any Roll Up the Rim cups, choose a valid option." << std::endl;
                                        std::cout << "==> Input: ";
                                        continue;

                                    } else {
                                        std::cout << "==> You used a Roll Up the Rim cup and left DC Tims Line." << std::endl;
                                        p.setsentToDCTL(false);
                                        p.setDCTLtimes(0);
                                        p.setRURCup(p.getRURCup() - 1);
                                        tmpCup--;
                                        p.setOSAPcollect(true);
                                        //move
                                    }
                                    break;

                                } else {
                                    std::cout << std::endl << "==> Invalid input. Please try again." << std::endl;
                                    std::cout << "==> Input: ";
                                }
                            }

                            nextmove = sum;
                            std::cout << "==> You will move " << nextmove << " steps." << std::endl;

                        } else {
                            std::cout << "==> Unfortunately, you didn't roll doubles. You will stay in DC Tims Line." << std::endl;
                            p.setDCTLtimes(p.getDCTLtimes() + 1);
                        }
                    }
                    break;

                } else if (choice == "Pay") {
                    if (p.getCashAmount() < 50) {
                        std::cout << "==> You do not have $50. Choose a valid option." << std::endl << "Input: ";
                        continue;
                    } else {
                        p.addCash(-50);
                        std::cout << "==> You paid $50 and you may leave the DC Tims Line." << std::endl;
                        p.setsentToDCTL(false);
                        p.setDCTLtimes(0);
                        p.setOSAPcollect(true);
                        int dice1 = roll();
                        int dice2 = roll();
                        std::cout << "==> Roll result: " << dice1 << " " << dice2 << std::endl;
                        nextmove = dice1 + dice2;
                        std::cout << "==> You will move " << nextmove << " steps." << std::endl;
                        //move
                    }
                    break;

                } else if (choice == "RimCup") {
                    if (p.getRURCup() == 0) {
                        std::cout << "==> You do not have any Roll Up the Rim cups. Choose a valid option" << std::endl;
                        std::cout << "==> Input: ";
                        continue;
                        //move
                    } else {
                        std::cout << "==> You used a Roll Up the Rim cup and left DC Tims Line." << std::endl;
                        p.setsentToDCTL(false);
                        p.setDCTLtimes(0);
                        p.setRURCup(p.getRURCup() - 1);
                        tmpCup--;
                        p.setOSAPcollect(true);
                        int dice1 = roll();
                        int dice2 = roll();
                        std::cout << "==> Roll result: " << dice1 << " " << dice2 << std::endl;
                        nextmove = dice1 + dice2;
                        std::cout << "==> You will move " << nextmove << " steps." << std::endl;
                        //move
                    }
                    break;

                } else {
                    std::cout << std::endl << "==> Invalid input. Please try again." << std::endl;
                    std::cout << "==> Input: ";
                }
            }
        }
        return tmpCup;
    }

};

#endif
    