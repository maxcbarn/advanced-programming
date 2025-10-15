#include "../lib/ConvexHull.hpp"

ConvexHull::ConvexHull( std::vector< Vector2 > points , Sides * sides , Constrains * constrains ) {
    if( points.size() < 3 ) {
        return;
    }
    std::vector< Vector2 > upper , lower; 
    double cross;
    Vector2 aux;
    
    auto crossProduct = []( Vector2 point1 , Vector2 point2 , Vector2 point3 ) {
        Vector2 vector1 = Vector2{ point1.x - point2.x , point1.y - point2.y };
        Vector2 vector2 = Vector2{ point3.x - point2.x , point3.y - point2.y };
        return vector1.x * vector2.y - vector1.y * vector2.x;
    };

    this->sides = sides;
    this->points = points;
    std::sort( points.begin() , points.end() , []( const Vector2 &a , const Vector2 &b ){ return a.x < b.x; } );
    upper.push_back( points.at( 0 ) );
    upper.push_back( points.at( 1 ) );
    for ( size_t index = 2 ; index < points.size() ; index++ ) {
        upper.push_back( points.at( index ) );
        cross = crossProduct( upper.at( upper.size() - 3 ) , upper.at( upper.size() - 2 ) , upper.at( upper.size() - 1 ) );
        while ( cross >= 0 ) {
            aux = upper.back();
            upper.pop_back();
            upper.pop_back();
            upper.push_back( aux );
            if( upper.size() <=2 ) {
                break;
            }
            cross = crossProduct( upper.at( upper.size() - 3 ) , upper.at( upper.size() - 2 ) , upper.at( upper.size() - 1 ) );
        }
    }

    lower.push_back( points.back() );
    lower.push_back( points.at( points.size() - 2 ) );

    for ( int index = points.size() - 3 ; index >= 0 ; index-- ) {
        lower.push_back( points.at( index ) );
        cross = crossProduct( lower.at( lower.size() - 3 ) , lower.at( lower.size() - 2 ) , lower.at( lower.size() - 1 ) );

        while ( cross >= 0 ) {
            aux = lower.back();
            lower.pop_back();
            lower.pop_back();
            lower.push_back( aux );
            if( lower.size() <=2 ) {
                break;
            }
            cross = crossProduct( lower.at( lower.size() - 3 ) , lower.at( lower.size() - 2 ) , lower.at( lower.size() - 1 ) );
        }
    }

    lower.pop_back();
    for ( size_t index = 1; index < lower.size(); index++) {
        upper.push_back( lower.at( index ) );
    }
    

    for ( size_t index = 0 ; index < upper.size() ; index++ ) {
        sides->CreateSide( upper.at( index ) , upper.at( ( index + 1 ) % upper.size() ) , constrains , BLUE , 5 );
    }
    



}

ConvexHull::~ConvexHull() {
    points.clear();
    sides = nullptr;
}