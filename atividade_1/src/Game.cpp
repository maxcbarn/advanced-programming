#include "../lib/Game.hpp"

Game::Game( int fps , int height , int width ) {
    this->fps = 30;
    this->height = height;
    this->width = width;
    running = true;
}

Game::~Game(){};

void Game::SetupGame() {
    InitWindow( height , width , "Game" );
    SetTargetFPS( fps );
    constrains = new Constrains;
    constrains->Set( width , height , 0 , 0 );
    points = new Points();
    sides = new Sides();
    points->CreatePoint( 100 , 100 , constrains , RED , 10 , 5 , 5 );
    points->CreatePoint( 200 , 200 , constrains , RED , 10 , 0.01 , 3 );
    points->CreatePoint( 300 , 300 , constrains , RED , 10 , -1.2 , -3);
    points->CreatePoint( 400 , 400 , constrains , RED , 10 , 1.9 , -3.1 );

    sides->CreateSide( 100 , 100 , 200 , 200 , constrains , GREEN , 3 , 2 , -2 , 3 , 5 );
    sides->CreateSide( 200 , 200 , 400 , 400 , constrains , GREEN , 3 , 2 , -2 , 3 , 5 );
    sides->CreateSide( 400 , 400 , 100 , 100 , constrains , GREEN , 3 , 2 , -2 , 3 , 5 );
}

void Game::Run() {
    SetupGame();
    

    while( running ) {
        if( WindowShouldClose() ) {
            running = false;
        }
        BeginDrawing( );  
        ClearBackground( BLACK );

        sides->Draw();
        points->Draw();

        EndDrawing();
    } 
    CloseWindow();
}

