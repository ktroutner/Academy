#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "GameController.hpp"
using namespace std;

vector<Player*> GameController::getPlayers() {
    return players;
}

Player* GameController::getCurrentPlayer() {
    return players.at(currentPlayerIdx);
}

bool GameController::isRunning() {
    return gameRunning;
}

void GameController::startGame(map<Position,Unit*,PositionCompare> mp, vector<Player*> ps) {
    gameMap = mp;
    players = ps;
    currentPlayerIdx = 0;
    gameRunning = true;
}

void GameController::nextPlayer() {
    players.at(currentPlayerIdx)->refresh();
    currentPlayerIdx++;
    if (currentPlayerIdx >= players.size())
        currentPlayerIdx = 0;
}

bool GameController::isOccupied(Position p) {
    map<Position,Unit*,PositionCompare>::iterator it = gameMap.find(p);
    return it != gameMap.end();
}

bool GameController::inRange(Position fromPos, Position toPos, int range) {
    return abs(toPos.x - fromPos.x) + abs(toPos.y - fromPos.y) <= range;
}

Unit* GameController::getUnitAtPosition(Position p) {
    return gameMap.at(p);
}

void GameController::move(Unit* u, Position p) {
    Position oldp = u->getPosition();
    u->move(p);
    gameMap.erase(oldp);
    gameMap[p] = u;
}

void GameController::attack(Unit* u, Unit* target) {
    int damage = u->getInfo().atk - target->getInfo().def;
    if (damage < 0)
        damage = 0;
    target->setHp(target->getInfo().hp - damage);
    cout << damage << " damage!\n";
    if (target->getInfo().hp <= 0) {
        target->getInfo().player->removeUnit(target);
        gameMap.erase(target->getPosition());
        cout << target->getInfo().name << " killed!\n";
    }
    u->finishMove();
}

void GameController::printState() {
    Player* cur = players.at(currentPlayerIdx);
    cout << "= = = = = = = = = =\n";
    for (int i=0; i<=10; i++) {
        for (int j=0; j<=10; j++) {
            Position p = {i,j};
            if (isOccupied(p)) {
                Unit* u = getUnitAtPosition(p);
                if (u->getInfo().player == cur)
                    cout << "O ";
                else
                    cout << "X ";
            } else
                cout << "  ";
        }
        cout << "\n";
    }
    cout << "= = = = = = = = = =\n";
}

int main() {
    GameController control;
    cout << "Starting game...\n";
    vector<Unit*> p1Units;
    vector<Unit*> p2Units;
    vector<Unit*> p3Units;
    vector<Unit*> p4Units;
    Player player1 = Player("Player 1");
    Player player2 = Player("Player 2");
    Player player3 = Player("Player 3");
    Player player4 = Player("Player 4");
    UnitInfo p1u1Info = {&player1, "Knight A", "Knight", 50, 3, 1, 6, 2, {0,0}};
    Unit p1u1 = Unit(p1u1Info);
    player1.addUnit(&p1u1);
    UnitInfo p1u2Info = {&player1, "Knight B", "Knight", 60, 3, 1, 7, 2, {0,1}};
    Unit p1u2 = Unit(p1u2Info);
    player1.addUnit(&p1u2);
    UnitInfo p1u3Info = {&player1, "Swordsman A", "Swordsman", 30, 4, 1, 5, 1, {0,2}};
    Unit p1u3 = Unit(p1u3Info);
    player1.addUnit(&p1u3);
    UnitInfo p1u4Info = {&player1, "Archer A", "Archer", 20, 5, 2, 4, 1, {0,3}};
    Unit p1u4 = Unit(p1u4Info);
    player1.addUnit(&p1u4);
    UnitInfo p1u5Info = {&player1, "Healer A", "Healer", 10, 3, 3, 1, 0, {0,4}};
    Unit p1u5 = Unit(p1u5Info);
    player1.addUnit(&p1u5);
    UnitInfo p2u1Info = {&player2, "Knight A", "Knight", 40, 3, 1, 5, 2, {2,2}};
    Unit p2u1 = Unit(p2u1Info);
    player2.addUnit(&p2u1);
    UnitInfo p2u2Info = {&player2, "Knight B", "Knight", 40, 3, 1, 5, 2, {2,3}};
    Unit p2u2 = Unit(p2u2Info);
    player2.addUnit(&p2u2);
    UnitInfo p3u1Info = {&player3, "Knight A", "Knight", 50, 3, 1, 5, 2, {3,3}};
    Unit p3u1 = Unit(p3u1Info);
    player3.addUnit(&p3u1);
    UnitInfo p3u2Info = {&player3, "Archer A", "Archer", 20, 4, 2, 3, 1, {3,4}};
    Unit p3u2 = Unit(p3u2Info);
    player3.addUnit(&p3u2);
    UnitInfo p4u1Info = {&player4, "Dragon A", "Dragon", 100, 2, 3, 9, 5, {5,5}};
    Unit p4u1 = Unit(p4u1Info);
    player4.addUnit(&p4u1);
    vector<Player*> players = {&player1, &player2, &player3, &player4};
    map<Position,Unit*,PositionCompare> mp;
    for (int i=0; i < players.size(); i++) {
        for (int j=0; j < players.at(i)->getUnits().size(); j++) {
            Unit* u = players.at(i)->getUnits().at(j);
            mp[u->getInfo().startingPos] = u;
        }
    }
    control.startGame(mp, players);
    while(control.isRunning()) {
        control.printState();
        Player* cur = control.getCurrentPlayer();
        vector<Unit*> units = cur->getUnits();
        cout << cur->getName() << "'s turn\n";
        if (!cur->hasAvailableUnits()) {
            string resp;
            cout << "You have no remaining units to move. Do you want to end your turn? ";
            getline(cin, resp);
            if (resp == "yes" || resp == "y") {
                control.nextPlayer();
                continue;
            }
        }
        string command;
        cout << "Command: ";
        getline(cin, command);
        if (command == "end")
            control.nextPlayer();
        else if (command.substr(0,4) == "move") {
            int i  = stoi(command.substr(4));
            Unit* u = cur->getUnits().at(i);
            if (u->canMove()) {
                string xStr, yStr;
                int x,y;
                cout << "X Position: ";
                getline(cin, xStr);
                cout << "Y Position: ";
                getline(cin, yStr);
                stringstream(xStr) >> x;
                stringstream(yStr) >> y;
                Position p = {x,y};
                if (!control.isOccupied(p))
                {
                    if (control.inRange(u->getPosition(), p, u->getInfo().moveRange)) {
                        cout << "Moving " << cur->getName() << "'s " << u->getInfo().name << " to position {" << p.x << "," << p.y << "}\n";
                        control.move(u, p);
                    } else 
                        cout << "This position is not in range.  Please select a different position.\n";
                } else
                    cout << "This position is occupied. Please select a different position.\n";
            } else
               cout << "This unit has already moved.  Please select a different unit.\n"; 
        } else if (command.substr(0,6) == "attack") {
            int i = stoi(command.substr(6));
            Unit* u = cur->getUnits().at(i);
            if (u->canAttack()) {
                string xStr, yStr;
                int x,y;
                cout << "X Position: ";
                getline(cin, xStr);
                cout << "Y Position: ";
                getline(cin, yStr);
                stringstream(xStr) >> x;
                stringstream(yStr) >> y;
                Position p = {x,y};
                if (control.inRange(u->getPosition(), p, u->getInfo().range)) {
                    if (control.isOccupied(p)) {
                        Unit* target = control.getUnitAtPosition(p);
                        if (u->getInfo().player != target->getInfo().player) {
                            cout << cur->getName() << "'s " << u->getInfo().name << " attacks " << target->getInfo().player->getName() << "'s " << target->getInfo().name << "!\n";
                            control.attack(u, target);
                        } else 
                            cout << "This unit is on your side!  Please select a different unit to attack.\n";
                    } else
                        cout << "There is no unit at this position.  Please select a different position to attack.\n";
                } else 
                    cout << "This position is not in range.  Please select a different position to attack.\n";
            } else
                cout << "This unit is not able to attack. Please select a different command.\n";
        } else if (command.substr(0,2) == "hp") {
            int i = stoi(command.substr(2));
            cout << units.at(i)->getInfo().hp << "\n";
        } else if (command.substr(0,3) == "pos") {
            int i = stoi(command.substr(3));
            Position p = units.at(i)->getPosition();
            cout << "{" << p.x << "," << p.y << "}\n";
        } else if (command == "peek") {
            string xStr, yStr;
            int x,y;
            cout << "X Position: ";
            getline(cin, xStr);
            cout << "Y Position: ";
            getline(cin, yStr);
            stringstream(xStr) >> x;
            stringstream(yStr) >> y;
            Position p = {x,y};
            if (control.isOccupied(p)) {
                Unit* u = control.getUnitAtPosition(p);
                cout << u->getInfo().name << "\n";
            } else
                cout << "This position is empty.\n";
        } else if (command == "quit")
            break;
        else cout << "Command not found.  Please input a valid command.\n";
    }
}
