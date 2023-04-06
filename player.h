#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include "dice.h"
#include "board.h"
class Board;

class Player {
  std::string name;
  char nameChar;
  int cash;
  int position;
  std::vector<shared_ptr<Board>> property;
  // std::vector<Board*> property;

  std::vector<std::pair<std::string, int>> ownBlock;
  std::vector<std::string> monopoly;
  bool OSAPcollect;
  bool sentToDCTL;
  int DCTLtimes;
  int RUR_cup;
  // Dice *dice; 
  std::shared_ptr<Dice> dice;
public:
  Player(std::string name, char nameChar);
  ~Player();
  int roll();
  int getCashAmount();
  int getTotalWorth();
  // void giveCash(Player* other, int amount);
  // void addProperties(Board* b);
  // void sellProperties(Board* b);
  void giveCash(std:shared_ptr<Player> other, int amount);
  void addProperties(std:shared_ptr<Board> b);
  void sellProperties(std:shared_ptr<Board> b);
  int getPosition();
  void setPosition(int position);
  void addCash(int amount);
  std::string getName();
  char getNameChar();
  void ifMonopoly(Board type);
  int getResidenceNum();
  bool getOSAPcollect();
  void setOSAPcollect(bool boo);
  bool getsentToDCTL();
  void setsentToDCTL(bool boo);
  int getDCTLtimes();
  void setDCTLtimes(int times);
  int getRURCup();
  void setRURCup(int cup);
};

#endif
