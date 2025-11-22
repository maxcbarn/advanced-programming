#include "raylib.hpp"
#include "grid/Grid.hpp"
#include "grid/GridAdapterFactory.hpp"
#include "grid/SquareAdapter.hpp"
#include "grid/GridAdapter.hpp"
#include "obstacle/ObstacleFactory.hpp"
#include "grid/Cell.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#include <cmath>

int main() {
    bool running = true;
    Vector4 windowSize = Vector4{ 0 , 0 , 800 , 800 };

    int option;
    TYPE_GRID typeGrid;
    std::cout << "1 - Square | 2 - Hexa" << std::endl;
    std::cin >> option;

    switch (option)
    {
        case 1:
            typeGrid = SQUARE;
            break;
        case 2:
            typeGrid = HEXA;
            break;
        default:
            return 1;
    }

    GridAdapterFactory::Initialize( typeGrid , 15 , 15 , windowSize );
    ObstacleFactory::GetObstacleFactory();
    Grid::Initialize( 15 , 15 );

    GridAdapter * gridAdapter = GridAdapterFactory::GetGridAdapterFactory()->GetAdapter();

    InitWindow( windowSize.z , windowSize.w , " >w< :3 :D UwU " );

    while( running ) {
        if( WindowShouldClose() ) {
            running = false;
        }
        if( IsWindowFocused() ) {
            if( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) ) {
                gridAdapter->Input( ADD_AGENT , GetMousePosition() );
            }
            if( IsMouseButtonDown( MOUSE_BUTTON_RIGHT ) ) {
                gridAdapter->Input( REMOVE , GetMousePosition() );
            }
            if( IsKeyDown( KEY_ONE ) ) {
                gridAdapter->Input( ADD_WALL , GetMousePosition() );
            }
            if( IsKeyDown( KEY_TWO ) ) {
                gridAdapter->Input( ADD_MUD , GetMousePosition() );
            }
        }

        BeginDrawing( );  
        ClearBackground( BLACK );
        gridAdapter->DrawGrid();

        EndDrawing();
    } 
    CloseWindow();
    return 0;
}
