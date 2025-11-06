#include "../lib/raylib.hpp"
#include "../lib/Points.hpp"
#include "../lib/Edges.hpp"
#include "../lib/Interface.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#include <cmath>


int main( int argc , char const *argv[] ) {
    bool running = true;
    std::vector< Vector2 > polyAux;
    Vector4 windowSize = Vector4{ 0 , 0 , 800 , 800 };
    Interface * interface = new Interface( 15 , 15 , windowSize.z  , windowSize.w  );

    InitWindow( windowSize.z , windowSize.w , " >w< :3 :D UwU " );


    while( running ) {
        if( WindowShouldClose() ) {
            running = false;
        }
        if( IsWindowFocused() ) {
            interface->Input();
        }

        BeginDrawing( );  
        ClearBackground( BLACK );
        interface->DrawInterface();

        EndDrawing();
    } 
    CloseWindow();
    return 0;
}
