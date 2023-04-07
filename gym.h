#ifndef GYM_H
#define GYM_H

#include "property.h"

class Gym: public Property {
public:
  Gym(int position, std::string name, unsigned int purchasePrice, unsigned int visitPrice);
  ~Gym();
  int getPrice() const;
  // std::string getType() const;
  void setVisitPrice();
  int getVisitPrice(Player& visitor);
  int getImproveLevel() const override {return 0;}
  int getImproveCost() const override {return 0;}
  void improve() override {return;}
  void degrade() override {return;}
};

#endif



