#include "../lib/Minkowski.hpp"

Minkowski::Minkowski() {

}

void Minkowski::SetData(  std::vector< std::vector< Vector2 > > polys , std::vector< Vector2 > robot ) {
    this->polys = polys;
    this->robot = robot;
}

std::vector< std::vector< Vector2 > > Minkowski::Compute() {
    auto sumVector = []( Vector2 point1 , Vector2 point2 ) {
        return Vector2{ point1.x + point2.x , point1.y + point2.y };
    };
    auto subVector = []( Vector2 point1 , Vector2 point2 ) {
        return Vector2{ point1.x - point2.x , point1.y - point2.y };
    };
    auto crossProduct = []( Vector2 point1 , Vector2 point2 ) {
        return point1.x * point2.y - point1.y * point2.x;
    };

    // pre-computing first index being the lowest y
    
    size_t lowestIndex = 0;

    for ( size_t index = 0 ; index < robot.size() ; index++ ) {
        if( robot.at( index ).y < robot.at( lowestIndex ).y || ( robot.at( index ).y == robot.at( lowestIndex ).y && robot.at( index ).x < robot.at( lowestIndex ).x ) ) {
            lowestIndex = index;
        }
    }
    std::rotate( robot.begin(), robot.begin() + lowestIndex , robot.end() );

    for ( size_t indexPoly = 0 ; indexPoly < polys.size() ; indexPoly++ ) {
        lowestIndex = 0;
        for ( size_t index = 0 ; index < polys.at( indexPoly ).size() ; index++ ) {
            if( polys.at( indexPoly ).at( index ).y < polys.at( indexPoly ).at( lowestIndex ).y || ( polys.at( indexPoly ).at( index ).y == polys.at( indexPoly ).at( lowestIndex ).y && polys.at( indexPoly ).at( index ).x < polys.at( indexPoly ).at( lowestIndex ).x ) ) {
                lowestIndex = index;
        }
        }
        std::rotate( polys.at( indexPoly ).begin(),  polys.at( indexPoly ).begin() + lowestIndex ,  polys.at( indexPoly ).end() );
    }

    float xSum = 0 , ySum = 0;
    Vector2 transformation;
    for ( size_t index = 0 ; index < robot.size() ; index++ ) {
        xSum += robot.at( index ).x;
        ySum += robot.at( index ).y;
    }
    xSum = xSum / robot.size();
    ySum = ySum / robot.size();
    
    transformation = Vector2{ xSum , ySum };
    for ( size_t index = 0 ; index < robot.size() ; index++ ) {
        robot.at( index ) = subVector( robot.at( index ) , transformation );
    }

    // Computing

    std::vector< std::vector< Vector2 > > result; 
    std::vector< Vector2 > poly, polyResult;
    size_t indexRobot, indexPoly;
    double cross;
    
    for ( size_t indexPolyVector = 0 ; indexPolyVector < polys.size() ; indexPolyVector++ ) {
        poly = polys.at( indexPolyVector );
        polyResult.clear();
        indexPoly = 0;
        indexRobot = 0;
        while ( indexPoly < poly.size() || indexRobot < robot.size() ) {
            polyResult.push_back( sumVector( poly.at( indexPoly % poly.size() ) , robot.at( indexRobot % robot.size() ) ) );
            cross = crossProduct( subVector( poly.at( ( indexPoly + 1 ) % poly.size() ) , poly.at( indexPoly % poly.size() ) ) , subVector( robot.at( ( indexRobot + 1 ) % robot.size() ) , robot.at( indexRobot % robot.size() ) ) );

            if ( cross <= 0 && indexPoly < poly.size() ) {
                indexPoly++;
            }
            if( cross >= 0 && indexRobot < robot.size() ) {
                indexRobot++;
            }
        }
        result.push_back( polyResult );
    }
    return result;
}

Minkowski::~Minkowski() {
    robot.clear();
    polys.clear();
}