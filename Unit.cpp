#include <vector>
#include <string>
#include "Player.hpp"
using namespace std;

Unit::Unit() {
    UnitInfo defaultInfo = {nullptr, "Default", "Soldier", 10, 1, 1, 1, 1, {0,0}};
    info = defaultInfo;
    pos = defaultInfo.startingPos;
    moveFlag = true;
    attackFlag = true;
}

Unit::Unit(UnitInfo inf) {
    info = inf;
    pos = inf.startingPos;
    moveFlag = true;
    attackFlag = true;
}

UnitInfo Unit::getInfo() {
    return info;
}

Position Unit::getPosition() {
    return pos;
}

bool Unit::canMove() {
    return moveFlag;
}

bool Unit::canAttack() {
    return attackFlag;
}

void Unit::setHp(int hp) {
    info.hp = hp;
}

void Unit::move(Position p) {
    pos = p;
    moveFlag = false;
}

void Unit::finishMove() {
    moveFlag = false;
    attackFlag = false;
}

void Unit::refresh() {
    moveFlag = true;
    attackFlag = true;
}
