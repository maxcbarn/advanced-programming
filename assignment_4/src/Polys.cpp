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
    for ( size_t index = 0 ; index < polys.size() ; index++ ) {
        DrawTriangleFan( polys.at( index ).data() , polys.at( index ).size() , colors.at( index ) );
    }
}
void Polys::AddPoly( std::vector< Vector2 > poly , Color color ) {
    polys.push_back( poly );
    colors.push_back( color );
}
size_t Polys::SearchPoly( Vector2 position ) {
    return polys.size() + 1;
}
void Polys::RemovePoly( Vector2 position ) {
    return;
}
void Polys::InputAction( MouseButton input ) {
    return;
}
std::vector< std::vector< Vector2 > > Polys::GetPolys() {
    return polys;
}