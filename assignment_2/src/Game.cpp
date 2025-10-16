#include "../lib/Game.hpp"
#define POINT_RADIUS 4
#define SIDE_THICKNESS 14 
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

Game::~Game(){};

void Game::SetupGame() {
    InitWindow( width , height , "Game" );
    SetTargetFPS( fps );
    constrains = new Constrains;
    constrains->Set( width , height , 0 , 0 );
    points = new Points();
    sides = new Sides();
    points->CreatePoint( Vector2{ 300 , 300 } , constrains , RED , POINT_RADIUS );
    points->CreatePoint( Vector2{ 500 , 500 } , constrains , RED , POINT_RADIUS );

    CreateVoronoiDiagram();
}

void Game::Run() {
    std::chrono::duration<double, std::milli> drawTime;
    std::chrono::duration<double, std::milli> actionTime;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    SetupGame();
    

    while( running ) {
        voronoiTime = std::chrono::duration<double, std::milli>(0);
        actionTime = std::chrono::duration<double, std::milli>(0);
        drawTime = std::chrono::duration<double, std::milli>(0);
        if( WindowShouldClose() ) {
            running = false;
        }
        if( IsCursorOnScreen() ) {
            start = std::chrono::high_resolution_clock::now();
            Input();    
            end = std::chrono::high_resolution_clock::now();
            actionTime = end - start;
        }
        
        BeginDrawing( );  
        ClearBackground( BLACK );
        DrawMenu();

        start = std::chrono::high_resolution_clock::now();
        
        
        for ( size_t index = 0 ; index < voronoiResult.size() ; index++ ) {
            for ( size_t slowIndex = 0 ; slowIndex < voronoiResult.at( index ).size() ; slowIndex++ ) {
                for ( size_t fastIndex = 0 ; fastIndex < voronoiResult.at( index ).size() ; fastIndex++ ) {
                    if( fastIndex != slowIndex && fastIndex != slowIndex + 1 ) {
                        DrawTriangle( voronoiResult.at( index ).at( ( slowIndex + 1 ) % voronoiResult.at( index ).size() ) , voronoiResult.at( index ).at( slowIndex ) , voronoiResult.at( index ).at( fastIndex ) , colors.at( index ) ); 

                    }
                }   
            }
        }
        
        sides->Draw();
        points->Draw();

        end = std::chrono::high_resolution_clock::now();
        drawTime = end - start;

        EndDrawing();
        log->FormLog( GetMousePosition() , IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) , IsMouseButtonPressed( MOUSE_BUTTON_RIGHT ) , drawTime.count() , actionTime.count() , points->GetPointsQuantity() , sides->GetVertexQuantity(), voronoiTime.count() );
    } 
    CloseWindow();
}

void Game::DrawMenu(){
    //DrawLineEx( Vector2{ ( float )MENU_LINE_THICKNESS / 2, 0 } , Vector2{ ( float )MENU_LINE_THICKNESS / 2 , ( float )( MENU_LINE_THICKNESS * 3 + height ) } , MENU_LINE_THICKNESS , WHITE );
    //DrawLineEx( Vector2{ ( float )(MENU_LINE_THICKNESS * 1.5 + width) , 0 } , Vector2{ ( float )( MENU_LINE_THICKNESS * 1.5 + width ) , ( float )( MENU_LINE_THICKNESS * 3 + height ) } , MENU_LINE_THICKNESS , WHITE );
    //DrawLineEx( Vector2{ ( float )( width + PADDING + MENU_LINE_THICKNESS * 2.5 ) , 0 } , Vector2{ ( float )( width + PADDING + MENU_LINE_THICKNESS * 2.5 )  , ( float )( MENU_LINE_THICKNESS * 3 + height ) } , MENU_LINE_THICKNESS , WHITE );


    //DrawLineEx( Vector2{ 0 , ( float )MENU_LINE_THICKNESS / 2 } , Vector2{ ( float )( MENU_LINE_THICKNESS * 3 + width + PADDING ) , ( float )MENU_LINE_THICKNESS / 2 } , MENU_LINE_THICKNESS , WHITE );
    //DrawLineEx( Vector2{ 0 , ( float )(MENU_LINE_THICKNESS * 1.5 + height ) } , Vector2{ ( float )( MENU_LINE_THICKNESS * 3 + width + PADDING ) , ( float )(MENU_LINE_THICKNESS * 1.5 + height ) } , MENU_LINE_THICKNESS , WHITE );
}

void Game::Input( ){
    Vector2 mousePositon = GetMousePosition();
    //std::cout << mousePositon.x << " | " << mousePositon.y << "\n";
    if( IsMouseButtonPressed( MOUSE_BUTTON_RIGHT ) ) {
        if( !points->ClickInputAction( MOUSE_BUTTON_RIGHT , mousePositon , selectedColor ) ){ return; }
        CreateVoronoiDiagram();
    }
    if( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) ) {
        points->CreatePoint( mousePositon , constrains , RED , POINT_RADIUS );
        CreateVoronoiDiagram();
    }
} 
 
void Game::CreateVoronoiDiagram() {
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    delete sides;
    sides = new Sides();
    voronoi = new Voronoi( points->GetPoints() , sides ,  constrains ); 
    start = std::chrono::high_resolution_clock::now();
    voronoiResult = voronoi->Compute();
    end = std::chrono::high_resolution_clock::now();
    voronoiTime = end - start;
    delete voronoi;
    colors.clear();
    for ( size_t i = 0 ; i < voronoiResult.size() ; i++ ) {
        colors.push_back( static_cast<Color>( Color{ ( unsigned char )( rand() % 256 ) , ( unsigned char )( rand() % 256 ) , ( unsigned char )( rand() % 256 ) , 255 } ) );
    }
    #ifdef DEBUG
    for ( size_t i = 0 ; i < voronoiResult.size() ; i++ ) {
        std::cout << "Cell " << i + 1 << " : ";
        for ( size_t j = 0 ; j < voronoiResult.at( i ).size() ; j++ ) {
            std::cout << "(" << voronoiResult.at( i ).at( j ).x << " , " << voronoiResult.at( i ).at( j ).y << ") ";
        }
        std::cout << "\n";
    }
    #endif
}