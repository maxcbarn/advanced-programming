#include "../lib/Game.hpp"
#define POINT_RADIUS 6
#define SIDE_THICKNESS 16 
#define MENU_LINE_THICKNESS 4
#define PADDING 0


Game::Game( int fps , int height , int width ) {
    this->fps = 30;
    this->height = height;
    this->width = width;
    running = true;
    selectedColor = WHITE;
    log = new Log();
}

Game::~Game(){
    outFile.close();
};

void Game::SetupGame() {
    InitWindow( width + PADDING + MENU_LINE_THICKNESS * 2 , height + MENU_LINE_THICKNESS * 2 , "Game" );
    SetTargetFPS( fps );
    constrains = new Constrains;
    constrains->Set( width + MENU_LINE_THICKNESS  , height + MENU_LINE_THICKNESS , MENU_LINE_THICKNESS , MENU_LINE_THICKNESS );
    points = new Points();
    sides = new Sides();
    outFile.open( "log.csv" );
  /*points->CreatePoint( Vector2{ 100 , 100 } , constrains , RED , POINT_RADIUS );
    points->CreatePoint( Vector2{ 200 , 200 } , constrains , RED , POINT_RADIUS );
    points->CreatePoint( Vector2{ 300 , 300 } , constrains , RED , POINT_RADIUS );
    points->CreatePoint( Vector2{ 400 , 400 } , constrains , RED , POINT_RADIUS ); */

    /* sides->CreateSide( Vector2{ 100 , 100 } , Vector2{ 200 , 100 } , constrains , GREEN , SIDE_THICKNESS );
    sides->CreateSide( Vector2{ 200 , 100 } , Vector2{ 200 , 200 } , constrains , GREEN , SIDE_THICKNESS );
    sides->CreateSide( Vector2{ 200 , 200 } , Vector2{ 100 , 200 } , constrains , GREEN , SIDE_THICKNESS );
    sides->CreateSide( Vector2{ 100 , 200 } , Vector2{ 100 , 100 } , constrains , GREEN , SIDE_THICKNESS ); */
}

void Game::Run() {
    std::chrono::duration<double, std::milli> drawTime;
    std::chrono::duration<double, std::milli> actionTime;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    SetupGame();

    /* std::random_device rd;
    std::mt19937 gen(rd());
    float min_val = constrains->minXPosition;
    float max_val = constrains->maxXPosition;
    std::uniform_real_distribution<float> dist = std::uniform_real_distribution<float>(min_val, max_val);

    for (size_t i = 1024; i <= 300000; i = i * 2)
    {
        for (size_t x = 0; x < 30; x++)
        {
            sides->~Sides();
            sides = new Sides();
            points->~Points();
            points = new Points();
            for ( size_t index = 0 ; index < i ; index++ ) {
                points->CreatePoint( Vector2{ dist( gen ) , dist( gen ) } , constrains , RED , POINT_RADIUS );
            }
            std::string log = "";
            convexHull = new ConvexHull( points->GetPoints() , sides , constrains , log );
            outFile << log << std::endl;
            convexHull->~ConvexHull();
            
        }
    } */
    

    while( running ) {
        if( WindowShouldClose() ) {
            running = false;
        }
        if( IsCursorOnScreen() ) {
            start = std::chrono::high_resolution_clock::now();
            Input();    
            end = std::chrono::high_resolution_clock::now();
            actionTime = end - start;
        } else {
            actionTime = std::chrono::duration<double, std::milli>(0);
        }
        
        BeginDrawing( );  
        ClearBackground( BLACK );
        DrawMenu();

        start = std::chrono::high_resolution_clock::now();
        sides->Draw();
        points->Draw();
        end = std::chrono::high_resolution_clock::now();
        drawTime = end - start;

        EndDrawing();
        log->FormLog( GetMousePosition() , IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) , IsMouseButtonPressed( MOUSE_BUTTON_RIGHT ) , drawTime.count() , actionTime.count() , points->GetPointsQuantity() , sides->GetVertexQuantity() );
    } 
    CloseWindow();
}

void Game::DrawMenu(){
    /* DrawLineEx( Vector2{ ( float )MENU_LINE_THICKNESS / 2, 0 } , Vector2{ ( float )MENU_LINE_THICKNESS / 2 , ( float )( MENU_LINE_THICKNESS * 3 + height ) } , MENU_LINE_THICKNESS , WHITE );
    DrawLineEx( Vector2{ ( float )(MENU_LINE_THICKNESS * 1.5 + width) , 0 } , Vector2{ ( float )( MENU_LINE_THICKNESS * 1.5 + width ) , ( float )( MENU_LINE_THICKNESS * 3 + height ) } , MENU_LINE_THICKNESS , WHITE );
    //DrawLineEx( Vector2{ ( float )( width + PADDING + MENU_LINE_THICKNESS * 2.5 ) , 0 } , Vector2{ ( float )( width + PADDING + MENU_LINE_THICKNESS * 2.5 )  , ( float )( MENU_LINE_THICKNESS * 3 + height ) } , MENU_LINE_THICKNESS , WHITE );


    DrawLineEx( Vector2{ 0 , ( float )MENU_LINE_THICKNESS / 2 } , Vector2{ ( float )( MENU_LINE_THICKNESS * 3 + width + PADDING ) , ( float )MENU_LINE_THICKNESS / 2 } , MENU_LINE_THICKNESS , WHITE );
    DrawLineEx( Vector2{ 0 , ( float )(MENU_LINE_THICKNESS * 1.5 + height ) } , Vector2{ ( float )( MENU_LINE_THICKNESS * 3 + width + PADDING ) , ( float )(MENU_LINE_THICKNESS * 1.5 + height ) } , MENU_LINE_THICKNESS , WHITE ); */
}

void Game::Input(){
    Vector2 mousePositon = GetMousePosition();
    bool flag = false;
    //std::cout << mousePositon.x << " | " << mousePositon.y << "\n";
    if( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) ) {
        points->CreatePoint( mousePositon , constrains , RED , POINT_RADIUS );
        flag = true;
    }
    if( IsMouseButtonPressed( MOUSE_BUTTON_RIGHT ) ) {
        points->ClickInputAction( MOUSE_BUTTON_RIGHT , mousePositon , selectedColor );
        flag = true;
    }
    if( IsKeyPressed( KEY_ONE ) ) {
        flag = true;
        size_t quantity, option;
        std::random_device rd;
        std::mt19937 gen(rd());
        float min_val, max_val, radius, value;
        std::uniform_real_distribution<float> dist;
        std::cout << "Type The Quantity of Points: ";
        std::cin >> quantity;
        std::cout << "Type Pattern of The Points \t1-Random\t2-Circle\t3-Square \n";
        std::cin >> option;
        switch ( option )
        {
            case 1:
                min_val = constrains->minXPosition;
                max_val = constrains->maxXPosition;
                dist = std::uniform_real_distribution<float>(min_val, max_val);
                for ( size_t index = 0 ; index < quantity ; index++ ) {
                    points->CreatePoint( Vector2{ dist( gen ) , dist( gen ) } , constrains , RED , POINT_RADIUS );
                }
                break;
            case 2:
                min_val = 0.0f;
                max_val = 2 * PI;
                radius = 200.0f;
                dist = std::uniform_real_distribution<float>(min_val, max_val);
                for ( size_t index = 0 ; index < quantity ; index++ ) {
                    value = dist( gen );
                    points->CreatePoint( Vector2{ std::cos( value ) * radius + 400, std::sin( value ) * radius + 400 } , constrains , RED , POINT_RADIUS );
                }
                break;
            case 3:
                min_val = 200;
                max_val = 600;
                dist = std::uniform_real_distribution<float>(min_val, max_val);

                for ( size_t i = 1 ; i < quantity + 1 ; i++ ) {
                    if( i % 4 == 1 % 4 ) {
                        points->CreatePoint( Vector2{ min_val , dist( gen ) } , constrains , RED , POINT_RADIUS );
                        continue;
                    }
                    if( i % 4 == 2 % 4 ) {
                        points->CreatePoint( Vector2{ max_val , dist( gen ) } , constrains , RED , POINT_RADIUS );
                        continue;
                    }
                    if( i % 4 == 3 % 4 ) {
                        points->CreatePoint( Vector2{ dist( gen ) , min_val } , constrains , RED , POINT_RADIUS );
                        continue;
                    }
                    if( i % 4 == 4 % 4 ) {
                        points->CreatePoint( Vector2{ dist( gen ) , max_val } , constrains , RED , POINT_RADIUS );
                        continue;
                    }
                }
                break;
        }
    }
    if( flag ) {
        sides = nullptr;
        sides = new Sides();
        std::string log = "";
        convexHull = new ConvexHull( points->GetPoints() , sides , constrains , log );
        outFile << log << std::endl;
        convexHull = nullptr;
    }
} 
 
