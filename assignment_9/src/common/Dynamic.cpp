#include "common/Dynamic.hpp"

Dynamic::Dynamic( Vector2 dynamicPosition , float velocity ) {
    this->dynamicPosition = dynamicPosition;
    this->velocity = velocity;
}

Dynamic::~Dynamic() {

}

Vector2 Dynamic::GetDynamicPosition() {
    return dynamicPosition;
}

float Dynamic::GetVelocity() {
    return velocity;
}

void Dynamic::SetDynamicPosition( Vector2 position ) {
    this->dynamicPosition = position;
}