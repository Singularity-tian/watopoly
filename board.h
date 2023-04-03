#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "subject.h"
#include "observer.h"
#include "player.h"

class Board: public Subject, public Observer {
  int position;
  string name;
  string type;
  Game* game;
  vector<Player*> curPlayer;
public:
  Board(int position, string name, string type, Game* game);
  ~Board();
  string getName();
  int getPosition();
  vector<Player*> getCurPlayer();
  int getVisitorNum();
  string getType() = 0;
};

#endif

