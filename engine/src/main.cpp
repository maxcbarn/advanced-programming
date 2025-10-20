#include "../lib/raylib.hpp"
#include "../lib/Points.hpp"
#include "../lib/Edges.hpp"
#include "../lib/Polys.hpp"
#include <vector>

void Input( Points * points , Edges * edges );

int main( int argc , char const *argv[] )
{
    bool running = true;
    Vector4 windowSize = Vector4{ 0 , 0 , 800 , 800 };
    Points * points = new Points();
    Edges *edges = new Edges();
    Polys * polys = new Polys();

    points->AddPoint( Vector2{ 400 , 400 } );
    edges->AddEdge( Vector2{ 200 , 200 } , Vector2{ 200 , 400 } );
    polys->AddPoly( std::vector< Vector2 > { Vector2{ 600 , 600 } , Vector2{ 700 , 700 } , Vector2{ 700 , 600 } } , STD_POLY_COLOR );

    InitWindow( windowSize.z , windowSize.w , " >w< :3 :D UwU " );

    while( running ) {
        if( WindowShouldClose() ) {
            running = false;
        }
        BeginDrawing( );  
        ClearBackground( BLACK );
        
        polys->Draw();
        edges->Draw();
        points->Draw();

        Input( points , edges );

        EndDrawing();
    } 
    CloseWindow();
    return 0;
}

void Input( Points * points , Edges * edges ) {
    if ( !IsWindowFocused() ) {
        return;
    }
    MouseButton button = MOUSE_BUTTON_EXTRA;

    if( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) ) {
        button = MOUSE_BUTTON_LEFT;
    }
    if( IsMouseButtonPressed( MOUSE_BUTTON_RIGHT ) ) {
        button = MOUSE_BUTTON_RIGHT;
    }

    points->InputAction( button );
    edges->InputAction( button );
}
