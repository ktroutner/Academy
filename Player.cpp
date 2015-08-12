#include <iostream>
#include <string>
#include <vector>
#include "Player.hpp"
using namespace std;

Player::Player(string nm) {
    name = nm;
}

void Player::addUnit(Unit* u) {
    units.push_back(u);
}

void Player::removeUnit(Unit* u) {
    for (int i=0; i<units.size(); i++) {
        if (units.at(i) == u)
            units.erase(units.begin()+i);
    }
}

string Player::getName() {
    return name;
}

vector<Unit*> Player::getUnits() {
    return units;
}

bool Player::hasAvailableUnits() {
    for (int i=0; i<units.size(); i++) {
        if (units.at(i)->canMove())
            return true;
    }
    return false;
}

void Player::refresh() {
    for (int i=0; i<units.size(); i++) {
        units.at(i)->refresh();
    }
}

/*
int main() {
    UnitInfo info = {"Player 1", "Test", "Soldier", 25, 3, 1, 4, 1, {0,0}};
    Unit un = Unit(info);
    vector<Unit*> units = {&un};
    Player pl = Player("Player 1", units);
    vector<Player> players = {pl};
    Player& player = players.at(0);
    Unit& u = *player.getUnits().at(0);
    Position p = {1,1};
    cout << u.canMove() << "\n";
    u.move(p);
    u = *player.getUnits().at(0);
    cout << u.canMove() << "\n";
}
*/
