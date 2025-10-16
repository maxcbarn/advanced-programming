#include "../lib/Points.hpp"

Points::Points() {
}

Points::~Points() {
    points.clear();
}

void Points::CreatePoint( Vector2 positon , Constrains * constrains , Color color , int radius ){
    for ( size_t index = 0 ; index < points.size() ; index++ ) {
        if( points.at( index ).get()->GetPosition().x == positon.x && points.at( index ).get()->GetPosition().y == positon.y ) {
            return;
        }
    }
    points.push_back( std::make_unique< Point >( positon , constrains , color , radius ) );
}

void Points::Draw() {
    for ( int index = 0 ; index < ( int )points.size() ; index++ ) {
        points[index].get()->Draw();
    }
}

Point * Points::Search( Vector2 mousePosition ){
    float xDif, yDif;
    int radius;
    for ( int index = 0 ; index < ( int )points.size() ; index++ ) {
        xDif = points.at( index ).get()->GetPosition().x - mousePosition.x;
        yDif = points.at( index ).get()->GetPosition().y - mousePosition.y;
        radius = points.at( index ).get()->GetRaius();
        if( radius * -1 <= xDif && radius >= xDif && radius * -1 <= yDif && radius >= yDif ) {
            return points.at( index ).get();
        }
    }
    return nullptr;
}

bool Points::ClickInputAction( MouseButton mouseButton , Vector2 mousePosition , Color color ) {
    Point * point = Search( mousePosition );
    if( point == nullptr ) {
        return false;
    }
    if( mouseButton == MOUSE_BUTTON_LEFT ) {
        std::cout << "Point: (" << point->GetPosition().x << "," << point->GetPosition().y << ")\n";
    }
    if( mouseButton == MOUSE_BUTTON_RIGHT ) {
        PopPoint( point );
    } 
    return true;
}

void Points::PopPoint( Point * point ) {
    std::deque< std::unique_ptr< Point > > auxDeque;
    int indexElement;
    for ( indexElement = 0 ; indexElement < ( int )points.size() ; indexElement++ ) {
        if( points.at( indexElement ).get() == point ){
            break;
        }
    }
    for ( int index = 0 ; index <= indexElement ; index++) {
        auxDeque.push_back( std::move( points.front() ) );
        points.pop_front();
    }
    auxDeque.pop_back();
    for ( int index = 0 ; index < indexElement ; index++ ) {
        points.push_front( std::move( auxDeque.back() ) );
        auxDeque.pop_back();
    }
}

int Points::GetPointsQuantity() {
    return points.size();
}

std::vector< Vector2 > Points::GetPoints() {
    std::vector< Vector2 > aux;
    for ( size_t index = 0 ; index < points.size() ; index++ ) {
        aux.push_back( points.at( index ).get()->GetPosition() );
    }
    return aux;
}
