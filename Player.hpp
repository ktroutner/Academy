#include <string>
#include <vector>
#include "Unit.hpp"
using namespace std;

class Player {
    string name;
    vector<Unit*> units;
  public:
    Player(string nm, vector<Unit*> us);
    string getName();
    vector<Unit*> getUnits();
    bool hasAvailableUnits();
    void refresh();
};
