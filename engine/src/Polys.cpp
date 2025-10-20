#include "../lib/Polys.hpp"

Polys::Polys() {

}
Polys::~Polys() {
    for ( size_t index = 0 ; index < polys.size() ; index++ ) {
        polys.at( index ).clear();
    }
    polys.clear();
    colors.clear();
}
void Polys::Draw() {

}
void Polys::AddPoly( std::vector< Vector2 > poly ) {

}
size_t Polys::SearchPoly( Vector2 position ) {

}
void Polys::RemovePoly( Vector2 position ) {

}
void Polys::InputAction( MouseButton input ) {
    
}