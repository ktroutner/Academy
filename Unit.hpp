#include <vector>
#include <string>
using namespace std;

class Player;

struct Position {
    int x;
    int y;
};

struct PositionCompare {
    bool operator() (const Position& lhs, const Position& rhs) const{
        if (lhs.x != rhs.x)
            return lhs.x < rhs.x;
        else
            return lhs.y < rhs.y;
    }
};

//basic unit info
struct UnitInfo {
    Player* player;
    string name;
    string type;
    int hp;
    int moveRange;
    int range;
    int atk;
    int def;
    Position startingPos;
};

class Unit {
    UnitInfo info;
    //other unit info related to game state
    Position pos;
    bool moveFlag;
    bool attackFlag;
  public:
    Unit();
    Unit(UnitInfo inf);
    UnitInfo getInfo();
    Position getPosition();
    bool canMove();
    bool canAttack();
    void setHp(int hp);
    void move(Position p);
    void finishMove();
    void refresh();
};
