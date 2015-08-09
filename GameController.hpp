#include <vector>
#include <map>
#include "Player.hpp"
using namespace std;

class GameController {
    map<Position,Unit*,PositionCompare> gameMap;
    vector<Player> players;
    int currentPlayerIdx;
    bool gameRunning;
  public:
    void startGame(map<Position,Unit*,PositionCompare> mp, vector<Player> ps);
    void nextPlayer();
    vector<Player> getPlayers();
    Player& getCurrentPlayer();
    bool isRunning();
    void move(Unit* u, Position p);
    bool isOccupied(Position p);
    bool inMoveRange(Position fromPos, Position toPos, int moveRange);
    Unit getUnitAtPosition(Position p);
    void printState();
};
