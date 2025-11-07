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

    #ifdef LOG
        std::ofstream outFile;
        Interface * interfaceLog;
        outFile.open( "logDist.csv" );

        for ( size_t i = 0 ; i < 64 ; i++ ) {
            interfaceLog  = new Interface( 30 , 30 , 800 , 800 );
            interfaceLog->GenerateRandomPath( 32 );
            outFile << 32 << "," << interfaceLog->TimeToCalculatePath() << "," << interfaceLog->MeanPathDistance() << "," << interfaceLog->QuantityOfPathNotFound() << std::endl;
            delete interfaceLog;
        }
        outFile.close();
        outFile.open( "logTime.csv" );
        for ( size_t i = 16 ; i <= 128 ; i = i * 2 ) {
            interfaceLog  = new Interface( 20 , 20 , 800 , 800 );
            interfaceLog->GenerateRandomPath( i );
            for ( size_t x = 0 ; x < 15 ; x++ ) {
                outFile << i << "," << interfaceLog->TimeToCalculatePath() << "," << interfaceLog->MeanPathDistance() << "," << interfaceLog->QuantityOfPathNotFound() << std::endl;
            }   
            delete interfaceLog;
        } 
        for ( size_t i = 16 ; i <= 128 ; i = i * 2 ) {
            interfaceLog  = new Interface( 40 , 40 , 800 , 800 );
            interfaceLog->GenerateRandomPath( i );
            for ( size_t x = 0 ; x < 15 ; x++ ) {
                outFile << i << "," << interfaceLog->TimeToCalculatePath() << "," << interfaceLog->MeanPathDistance() << "," << interfaceLog->QuantityOfPathNotFound() << std::endl;
            }   
            delete interfaceLog;
        }  
       outFile.close();
       outFile.open( "logObstacle.csv" );
        for ( size_t i = 32 ; i <= 128 ; i = i * 2 ) {
            interfaceLog  = new Interface( 40 , 40 , 800 , 800 );
            interfaceLog->GenerateRandomPath( i );
            interfaceLog->GenerateRandomObstacle( i * 8 );
            for ( size_t x = 0 ; x < 15 ; x++ ) {
                outFile << i << ',' << i * 8 << "," << interfaceLog->TimeToCalculatePath() << "," << interfaceLog->MeanPathDistance() << "," << interfaceLog->QuantityOfPathNotFound() << std::endl;
            }   
            delete interfaceLog;
        } 
        outFile.close();
        return 0;
    #endif

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
