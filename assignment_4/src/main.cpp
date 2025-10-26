#include "../lib/raylib.hpp"
#include "../lib/Points.hpp"
#include "../lib/Edges.hpp"
#include "../lib/Polys.hpp"
#include "../lib/Minkowski.hpp"
#include <vector>
#include <iostream>

bool Input( Points * points , Edges * edges , Polys * polys , bool &polyCreation , std::vector< Vector2 > &polyAux );
void ComputeAlgorithn( Polys * polys , Minkowski * minkowski , std::vector< Vector2 > robot , Polys * &minkowskiPolys );

int main( int argc , char const *argv[] )
{
    bool running = true, polyCreation = false;
    std::vector< Vector2 > polyAux;
    Vector4 windowSize = Vector4{ 0 , 0 , 800 , 800 };
    Points * points = new Points();
    Edges * edges = new Edges();
    Polys * polys = new Polys();
    Polys * minkowskiPolys = new Polys();
    Minkowski * minkowski = new Minkowski();
    InitWindow( windowSize.z , windowSize.w , " >w< :3 :D UwU " );
    
    //points->AddPoint( Vector2{ 400 , 400 } );
    //edges->AddEdge( Vector2{ 200 , 200 } , Vector2{ 200 , 400 } );

    polys->AddPoly( std::vector< Vector2 > { Vector2{ 300 , 300 } , Vector2{ 400 , 400 } , Vector2{ 400 , 300 } } , STD_POLY_COLOR );
    std::vector< Vector2 > robot = { Vector2{ 0 , 0 } , Vector2{ 0 , 100 } , Vector2{ 100 , 100 } , Vector2{ 100 , 0 } };

    ComputeAlgorithn( polys , minkowski , robot , minkowskiPolys );

    while( running ) {
        if( WindowShouldClose() ) {
            running = false;
        }
        BeginDrawing( );  
        ClearBackground( BLACK );

        if( Input( points , edges , polys , polyCreation , polyAux ) ) {
            ComputeAlgorithn( polys , minkowski , robot , minkowskiPolys );
        }

        minkowskiPolys->Draw();
        polys->Draw();
        edges->Draw();
        points->Draw();

        EndDrawing();
    } 
    CloseWindow();
    return 0;
}

bool Input( Points * points , Edges * edges , Polys * polys , bool &polyCreation , std::vector< Vector2 > &polyAux ) {
    if ( !IsWindowFocused() ) {
        return false;
    }
    MouseButton button = MOUSE_BUTTON_EXTRA;

    if( IsKeyPressed( KEY_ONE ) ) {
        if( !polyCreation ) {
            polyCreation = true;
            std::cout << "Polygon Creating Mode" << std::endl;
        } else {
            polyCreation = false;
            if( polyAux.size() >= 3 ) {
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

void ComputeAlgorithn( Polys * polys , Minkowski * minkowski , std::vector< Vector2 > robot , Polys * &minkowskiPolys ) {
    minkowskiPolys = nullptr;
    minkowskiPolys = new Polys();
    minkowski->SetData( polys->GetPolys() , robot );
    std::vector< std::vector< Vector2 > > result = minkowski->Compute();

    for ( size_t index = 0 ; index < result.size() ; index++ ) {
        minkowskiPolys->AddPoly( result.at( index ) , RED );
    }

    minkowskiPolys->AddPoly( robot , BLUE );
}
