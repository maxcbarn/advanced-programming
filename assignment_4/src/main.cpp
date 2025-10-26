#include "../lib/raylib.hpp"
#include "../lib/Points.hpp"
#include "../lib/Edges.hpp"
#include "../lib/Polys.hpp"
#include "../lib/Minkowski.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#include <cmath>

bool Input( Points * points , Edges * edges , Polys * polys , bool &polyCreation , std::vector< Vector2 > &polyAux );
void ComputeAlgorithn( Polys * polys , Minkowski * minkowski , std::vector< Vector2 > robot , Polys * &minkowskiPolys , std::ofstream &outFile );

int main( int argc , char const *argv[] ) {
    
    bool running = true, polyCreation = false;
    std::vector< Vector2 > polyAux;
    Vector4 windowSize = Vector4{ 0 , 0 , 800 , 800 };
    Points * points = new Points();
    Edges * edges = new Edges();
    Polys * polys = new Polys();
    Polys * minkowskiPolys = new Polys();
    Minkowski * minkowski = new Minkowski();
    std::ofstream outFile;
    InitWindow( windowSize.z , windowSize.w , " >w< :3 :D UwU " );
    outFile.open( "log.csv" );

    //points->AddPoint( Vector2{ 400 , 400 } );
    //edges->AddEdge( Vector2{ 200 , 200 } , Vector2{ 200 , 400 } );

    polys->AddPoly( std::vector< Vector2 > { Vector2{ 300 , 300 } , Vector2{ 400 , 400 } , Vector2{ 400 , 300 } } , STD_POLY_COLOR );
    std::vector< Vector2 > robot = { Vector2{ 0 , 0 } , Vector2{ 0 , 100 } , Vector2{ 100 , 100 } , Vector2{ 100 , 0 } };

    /* static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distX(0, 800);
    std::uniform_real_distribution<float> distY(0, 800);
    auto cross = []( Vector2 a, Vector2 b , Vector2 c ) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    };

    for ( size_t i = 64; i <= 30000 ; i = i * 2 ) {
        Polys * polysAux = new Polys();
        for (size_t x = 0; x < i ; x++) {
            std::vector<Vector2> triangle = {
                {distX(rng), distY(rng)},
                {distX(rng), distY(rng)},
                {distX(rng), distY(rng)}
            };

            if (fabs(cross(triangle[0], triangle[1], triangle[2])) < 1e-6f) { continue; }
            if( cross( triangle.at( 0 ) , triangle.at( 1 ) , triangle.at( 2 ) ) > 0.0f ) {
                std::swap( triangle[1] , triangle[2] );
            }
            polysAux->AddPoly( triangle , STD_POLY_COLOR );
        }
        for (size_t x = 0; x < 15; x++) {
            ComputeAlgorithn( polysAux , minkowski , robot , minkowskiPolys , outFile );
        }
        delete polysAux;
    } */

    ComputeAlgorithn( polys , minkowski , robot , minkowskiPolys , outFile );

    while( running ) {
        if( WindowShouldClose() ) {
            running = false;
        }
        BeginDrawing( );  
        ClearBackground( BLACK );

        if( Input( points , edges , polys , polyCreation , polyAux ) ) {
            ComputeAlgorithn( polys , minkowski , robot , minkowskiPolys , outFile );
        }

        minkowskiPolys->Draw();
        polys->Draw();
        edges->Draw();
        points->Draw();

        EndDrawing();
    } 
    CloseWindow();
    outFile.close();
    return 0;
}

bool Input( Points * points , Edges * edges , Polys * polys , bool &polyCreation , std::vector< Vector2 > &polyAux ) {
    if ( !IsWindowFocused() ) {
        return false;
    }
    auto crossProduct = []( Vector2 point1 , Vector2 point2 ) {
        return point1.x * point2.y - point1.y * point2.x;
    };
    MouseButton button = MOUSE_BUTTON_EXTRA;

    if( IsKeyPressed( KEY_ONE ) ) {
        if( !polyCreation ) {
            polyCreation = true;
            std::cout << "Polygon Creating Mode" << std::endl;
        } else {
            polyCreation = false;
            if( polyAux.size() >= 3 ) {
                if( crossProduct( polyAux.at( 0 ) , polyAux.at( 1 ) ) <= 0 ) {
                    std::reverse( polyAux.begin() , polyAux.end() );
                }
                polys->AddPoly( polyAux , STD_POLY_COLOR );
                polyAux.clear();
                return true;
            }
            polyAux.clear();
        }   
    } 

    if( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) && !polyCreation ) {
        button = MOUSE_BUTTON_LEFT;
    }
    if( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) && polyCreation ) {
        polyAux.push_back( GetMousePosition() );
    }
    if( IsMouseButtonPressed( MOUSE_BUTTON_RIGHT ) ) {
        button = MOUSE_BUTTON_RIGHT;
    }

    points->InputAction( button );
    edges->InputAction( button );
    return false;
}

void ComputeAlgorithn( Polys * polys , Minkowski * minkowski , std::vector< Vector2 > robot , Polys * &minkowskiPolys , std::ofstream &outFile ) {
    std::chrono::duration<double, std::milli> computeTime;
    auto start = std::chrono::high_resolution_clock::now();
    
    delete minkowskiPolys;
    minkowskiPolys = new Polys();
    minkowski->SetData( polys->GetPolys() , robot );
    std::vector< std::vector< Vector2 > > result = minkowski->Compute();
    
    for ( size_t index = 0 ; index < result.size() ; index++ ) {
        minkowskiPolys->AddPoly( result.at( index ) , RED );
    }
    
    minkowskiPolys->AddPoly( robot , BLUE );
    
    auto end = std::chrono::high_resolution_clock::now();
    computeTime = end - start;
    size_t vertexQuantity = 0;
    for ( size_t i = 0 ; i < polys->GetPolys().size() ; i++ ) {
        vertexQuantity += polys->GetPolys().at( i ).size();
    }
    outFile << computeTime.count() << "," << vertexQuantity << "," << robot.size() << "," << polys->GetPolys().size() << std::endl;
}
