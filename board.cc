#include "board.h"
using namespace std;

Board::Board(int position, string name, string type): position{position}, name{name}, type{type} {
  vector<string> nonpro = {"COLLECT OSAP", "SLC", "TUITION", "NEEDLES HALL", "DC Tims Line", "SLC", "Goose Nesting", "NEEDLES HALL", "GO TO TIMS", "SLC", "NEEDLES HALL", "COOP FEE"};
  vector<string> academic = {"AL", "ML", "ECH", "PAS", "HH", "RCH", "DWE", "CPH", "LHI", "BMH", "OPT", "EV1", "EV2", "EV3", "PHYS", "B1", "B2", "EIT", "ESC", "C2", "MC", "DC"};
  vector<string> residence = {"MKV", "UWP", "V1", "REV"};
  vector<string> gyms = {"PAC", "CIF"};
  for (auto i : nonpro) {
    if (name == i) type{"NonProperty"};
  } for (auto i : academic) {
    if (name == i) type{"AcademicBuilding"};
  } for (auto i : residence) {
    if (name == i) type{"Residence"};
  } for (auto i : gyms) {
    if (name == i) type{"Gym"};
  }
}

Board::~Board() {
  delete game;
  for (auto i:curPlayer) {
    delete i;
  }
}

string Board::getName() {
  return name;
}

int Board::getPosition() {
  return position;
}

vector<Player*> Board::getCurPlayer() {
  return curPlayer;
}

int Board::getVisitorNum() {
  return curPlayer.size();
}


