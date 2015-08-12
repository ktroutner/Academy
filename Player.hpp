#include <string>
#include <vector>
#include "Unit.hpp"
using namespace std;

class Player {
    string name;
    vector<Unit*> units;
  public:
    Player(string nm);
    string getName();
    vector<Unit*> getUnits();
    void addUnit(Unit* u);
    void removeUnit(Unit* u);
    bool hasAvailableUnits();
    void refresh();
};
