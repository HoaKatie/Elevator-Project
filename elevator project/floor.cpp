#include "floor.h"

int Floor::index = 1;

Floor::Floor(): fID(index++), requestUp(false), requestDown(false) {}
Floor::Floor(int i): fID(i), requestUp(false), requestDown(false) {}
Floor::~Floor() {}

int Floor::getFID() {return fID;}

void Floor::setRequestingUp(bool isUp) {requestUp = isUp;}
void Floor::setRequestingDown(bool isDown) {requestDown = isDown;}

bool Floor::isRequestingUp() {return requestUp;}
bool Floor::isRequestingDown() {return requestDown;}
