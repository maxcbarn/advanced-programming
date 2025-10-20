#include "../lib/raylib.hpp"
#include "../lib/Points.hpp"
#include "../lib/Edges.hpp"

void Input( Points * points , Edges * edges );

int main( int argc , char const *argv[] )
{
    bool running = true;
    Vector4 windowSize = Vector4{ 0 , 0 , 800 , 800 };
    Points * points = new Points();
    Edges *edges = new Edges();

    points->AddPoint( Vector2{ 400 , 400 } );
    edges->AddEdge( Vector2{ 200 , 200 } , Vector2{ 200 , 400 } );


    InitWindow( windowSize.z , windowSize.w , " >w< :3 :D UwU " );

    while( running ) {
        if( WindowShouldClose() ) {
            running = false;
        }
        BeginDrawing( );  
        ClearBackground( BLACK );
        
        points->Draw();
        edges->Draw();

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
