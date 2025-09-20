#include "../lib/Game.hpp"
#define POINT_RADIUS 10
#define SIDE_THICKNESS 10 
#define MENU_LINE_THICKNESS 4
#define PADDING 50


Game::Game( int fps , int height , int width ) {
    this->fps = 30;
    this->height = height;
    this->width = width;
    running = true;
    selectedColor = WHITE;
}

Game::~Game(){};

void Game::SetupGame() {
    InitWindow( width + PADDING + MENU_LINE_THICKNESS * 3 , height + MENU_LINE_THICKNESS * 2 , "Game" );
    SetTargetFPS( fps );
    constrains = new Constrains;
    constrains->Set( width + MENU_LINE_THICKNESS  , height + MENU_LINE_THICKNESS , MENU_LINE_THICKNESS , MENU_LINE_THICKNESS );
    points = new Points();
    sides = new Sides();
    points->CreatePoint( Vector2{ 100 , 100 } , constrains , RED , POINT_RADIUS );
    points->CreatePoint( Vector2{ 200 , 200 } , constrains , RED , POINT_RADIUS );
    points->CreatePoint( Vector2{ 300 , 300 } , constrains , RED , POINT_RADIUS );
    points->CreatePoint( Vector2{ 400 , 400 } , constrains , RED , POINT_RADIUS );

    /*sides->CreateSide( 100 , 100 , 200 , 200 , constrains , GREEN , 3 , 2 , -2 , 3 , 5 );
    sides->CreateSide( 200 , 200 , 400 , 400 , constrains , GREEN , 3 , 2 , -2 , 3 , 5 );
    sides->CreateSide( 400 , 400 , 300 , 300 , constrains , GREEN , 3 , 2 , -2 , 3 , 5 );
    sides->CreateSide( 300 , 300 , 100 , 100 , constrains , RED , -3 , -2 , -2 , -4 , 2 );*/

    sides->CreateSide( Vector2{ 100 , 100 } , Vector2{ 200 , 100 } , constrains , GREEN , SIDE_THICKNESS );
    sides->CreateSide( Vector2{ 200 , 100 } , Vector2{ 200 , 200 } , constrains , GREEN , SIDE_THICKNESS );
    sides->CreateSide( Vector2{ 200 , 200 } , Vector2{ 100 , 200 } , constrains , GREEN , SIDE_THICKNESS );
    sides->CreateSide( Vector2{ 100 , 200 } , Vector2{ 100 , 100 } , constrains , RED , SIDE_THICKNESS );
}

void Game::Run() {
    SetupGame();

    while( running ) {
        if( WindowShouldClose() ) {
            running = false;
        }
        if( IsCursorOnScreen() ) {
            MouseInput();    
        } 
        
        BeginDrawing( );  
        ClearBackground( BLACK );
        DrawMenu();

        sides->Draw();
        points->Draw();

        EndDrawing();
    } 
    CloseWindow();
}

void Game::DrawMenu(){
    DrawLineEx( Vector2{ ( float )MENU_LINE_THICKNESS / 2, 0 } , Vector2{ ( float )MENU_LINE_THICKNESS / 2 , ( float )( MENU_LINE_THICKNESS * 3 + height ) } , MENU_LINE_THICKNESS , WHITE );
    DrawLineEx( Vector2{ ( float )(MENU_LINE_THICKNESS * 1.5 + width) , 0 } , Vector2{ ( float )( MENU_LINE_THICKNESS * 1.5 + width ) , ( float )( MENU_LINE_THICKNESS * 3 + height ) } , MENU_LINE_THICKNESS , WHITE );
    DrawLineEx( Vector2{ ( float )( width + PADDING + MENU_LINE_THICKNESS * 2.5 ) , 0 } , Vector2{ ( float )( width + PADDING + MENU_LINE_THICKNESS * 2.5 )  , ( float )( MENU_LINE_THICKNESS * 3 + height ) } , MENU_LINE_THICKNESS , WHITE );


    DrawLineEx( Vector2{ 0 , ( float )MENU_LINE_THICKNESS / 2 } , Vector2{ ( float )( MENU_LINE_THICKNESS * 3 + width + PADDING ) , ( float )MENU_LINE_THICKNESS / 2 } , MENU_LINE_THICKNESS , WHITE );
    DrawLineEx( Vector2{ 0 , ( float )(MENU_LINE_THICKNESS * 1.5 + height ) } , Vector2{ ( float )( MENU_LINE_THICKNESS * 3 + width + PADDING ) , ( float )(MENU_LINE_THICKNESS * 1.5 + height ) } , MENU_LINE_THICKNESS , WHITE );
}

void Game::MouseInput(){
    Vector2 mousePositon = GetMousePosition();
    //std::cout << mousePositon.x << " | " << mousePositon.y << "\n";
    if( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) ) {
        if( points->ClickInputAction( mousePositon , selectedColor ) ){ return; }
        if( sides->ClickInputAction( mousePositon , selectedColor ) ){ return; }
    }
    
}
 
