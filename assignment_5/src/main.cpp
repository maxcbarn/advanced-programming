#include "../lib/raylib.hpp"
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
    Vector4 windowSize = Vector4{ 0 , 0 , 800 , 800 };

    std::ofstream outFile;
    Interface * interfaceLog;
    outFile.open( "log.csv" );
    for ( size_t i = 64 ; i <= 64 ; i = i * 2 ) {
        for ( size_t x = 0 ; x < 2 ; x++ ) {
            interfaceLog  = new Interface( 50 , 50 , 800 , 800 );
            interfaceLog->GenerateRandomPath( i );
            outFile << interfaceLog->TimeToCalculatePath() << "," << interfaceLog->MeanPathDistance() << "," << interfaceLog->QuantityOfPathNotFound() << "," << std::endl;
            delete interfaceLog;
        }   
    } 
    outFile.close();

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
