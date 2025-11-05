#include "../lib/Interface.hpp"


Interface::Interface( size_t rows , size_t columns , size_t width , size_t height ) {
    this->rows = rows;
    this->columns = columns;
    this->width = width;
    this->height = height;
    grid = new Grid( rows , columns );
    cellRowSize = ( float )width / ( float )rows;
    cellColumnSize = ( float )height / ( float )columns; 
    menuEdges = new Edges();

    for ( size_t index = 0 ; index <= rows ; index++ ) {
        menuEdges->AddEdge( Vector2{ 0 , index * cellRowSize } , Vector2{ ( float )width , index * cellRowSize }  );
    }
    for ( size_t index = 0 ; index <= columns ; index++ ) {
        menuEdges->AddEdge( Vector2{ index * cellColumnSize , 0 } , Vector2{ index * cellColumnSize , ( float )height }  );
    }
}

Interface::~Interface() {
    delete menuEdges;
}

void Interface::DrawInterface() {
    Color color;
    std::vector< Vector2 > aux;
    for ( size_t row = 0 ; row < rows ; row++ ) {
        for ( size_t column = 0 ; column < columns ; column++ ) {
            switch ( grid->GetCellStatus( row , column ) ) {
                case EMPTY:
                    color = EMPTY_COLOR;
                    break;
                case OBSTACLE:
                    color = OBSTACLE_COLOR;
                    break;
                case START:
                    color = START_COLOR;
                    break;
                case END:
                    color = END_COLOR;
                    break;
            }
            aux.push_back( Vector2{ column * cellColumnSize  , row * cellRowSize } );
            aux.push_back( Vector2{ column * cellColumnSize , ( 1 + row  ) * cellRowSize } );
            aux.push_back( Vector2{ ( 1 + column  ) * cellColumnSize , ( 1 + row  ) * cellRowSize } );
            aux.push_back( Vector2{ ( 1 + column  ) * cellColumnSize , row * cellRowSize } );
            DrawTriangleFan( aux.data() , 4 , color );
            aux.clear();
        }
    }
    for ( size_t index = 0 ; index < paths.size() ; index++ ) {
        paths[index]->Draw();
    }
    menuEdges->Draw();
}

void Interface::Input() {
    auto findRow = [this]( Vector2 mousePosition ) {
        return std::abs( mousePosition.y / cellRowSize ) ; 
    };
    auto findColumn = [this]( Vector2 mousePosition ) {
        return std::abs( mousePosition.x / cellColumnSize ) ; 
    };
    if( IsMouseButtonDown( MOUSE_BUTTON_LEFT ) ) {
        grid->SetCellStatus( findRow( GetMousePosition() ) , findColumn( GetMousePosition() ) , OBSTACLE );
        CheckDeletion( findRow( GetMousePosition() ) , findColumn( GetMousePosition() ) , OBSTACLE );
        Recalculate();
        return;
    }
    if( IsMouseButtonDown( MOUSE_BUTTON_RIGHT ) ) {
        grid->SetCellStatus( findRow( GetMousePosition() ) , findColumn( GetMousePosition() ) , EMPTY );
        CheckDeletion( findRow( GetMousePosition() ) , findColumn( GetMousePosition() ) , EMPTY );
        Recalculate();
        return;
    }
    if( IsMouseButtonPressed( MOUSE_BUTTON_MIDDLE ) ) {
        if( !addingPath ) {
            start = std::make_pair< size_t , size_t >( findRow( GetMousePosition() ) , findColumn( GetMousePosition() ) );
            addingPath = !addingPath;
            grid->SetCellStatus( findRow( GetMousePosition() ) , findColumn( GetMousePosition() ) , START );
        } else {
            addingPath = !addingPath;
            grid->SetCellStatus( findRow( GetMousePosition() ) , findColumn( GetMousePosition() ) , END );
            paths.push_back( new Path( start , std::make_pair< size_t , size_t >( findRow( GetMousePosition() ) , findColumn( GetMousePosition() ) ) , FindPath( start , std::make_pair< size_t , size_t >( findRow( GetMousePosition() ) , findColumn( GetMousePosition() ) ) ) ) );
        }
    } 
}

void Interface::CheckDeletion( size_t row , size_t column , CELL_STATUS cellStatus ) {
    for ( size_t index = 0 ; index < paths.size() ; index++ ) {
        if( paths[index]->start.first == row && paths[index]->start.second == column  ) {
            grid->SetCellStatus( row , column , cellStatus );
            grid->SetCellStatus( paths[index]->end.first , paths[index]->end.second , EMPTY );
            delete paths[index];
            paths.erase( paths.begin() + index );
            break;
        }
        if( paths[index]->end.first == row && paths[index]->end.second == column ) {
            grid->SetCellStatus( row , column , cellStatus );
            grid->SetCellStatus( paths[index]->start.first , paths[index]->start.second , EMPTY );
            delete paths[index];
            paths.erase( paths.begin() + index );
            break;
        }
    }
    
}
void Interface::Recalculate() {
    for ( size_t index = 0 ; index < paths.size() ; index++ ) {
        paths[index]->SetPath( FindPath( paths[index]->start , paths[index]->end )  );
    }
}

Edges * Interface::FindPath( std::pair< size_t , size_t> start , std::pair< size_t , size_t> end ) {
    Edges * path = new Edges();


    return path;
}