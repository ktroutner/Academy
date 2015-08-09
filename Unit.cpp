#include <vector>
#include <string>
#include "Unit.hpp"
using namespace std;

Unit::Unit() {
    UnitInfo defaultInfo = {"DefaultPlayer", "Default", "Soldier", 10, 1, 1, 1, 1, {0,0}};
    info = defaultInfo;
    pos = defaultInfo.startingPos;
    moveFlag = true;
}

Unit::Unit(UnitInfo inf) {
    info = inf;
    pos = inf.startingPos;
    moveFlag = true;
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

void Unit::setHp(int hp) {
    info.hp = hp;
}

void Unit::move(Position p) {
    pos = p;
    moveFlag = false;
}

void Unit::refresh() {
    moveFlag = true;
}
