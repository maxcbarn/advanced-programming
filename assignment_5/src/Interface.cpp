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
    delete grid;
    paths.clear();
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
        paths[index]->Draw( );
    }
    menuEdges->Draw( EDGE_MENU_COLOR );
}

void Interface::Input() {
    auto findRow = [this]( Vector2 mousePosition ) {
        if( std::abs( mousePosition.y / cellRowSize ) >= rows ) {
            return ( float ) rows - 1;
        } else {
            return std::abs( mousePosition.y / cellRowSize );
        }
    };
    auto findColumn = [this]( Vector2 mousePosition ) {
        if( std::abs( mousePosition.x / cellColumnSize ) >= columns ) {
            return ( float ) columns - 1;
        } else {
            return std::abs( mousePosition.x / cellColumnSize );
        }
    };

    if( IsKeyPressed( KEY_ONE ) ) {
        std::cout << "Type the Number of Paths: ";
        size_t quantity;
        std::cin >> quantity;
        GenerateRandomPath( quantity );
    }
    if( IsKeyPressed( KEY_TWO ) ) {
        std::cout << "Type the Number of Obstacle: ";
        size_t quantity;
        std::cin >> quantity;
        GenerateRandomObstacle( quantity );
    }

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
            CheckDeletion( findRow( GetMousePosition() ) , findColumn( GetMousePosition() ) , EMPTY );
            Recalculate();
            grid->SetCellStatus( findRow( GetMousePosition() ) , findColumn( GetMousePosition() ) , START );
        } else {
            addingPath = !addingPath;
            grid->SetCellStatus( findRow( GetMousePosition() ) , findColumn( GetMousePosition() ) , END );
            CheckDeletion( findRow( GetMousePosition() ) , findColumn( GetMousePosition() ) , EMPTY );
            Recalculate();
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

std::pair< Edges * , std::vector< size_t > > Interface::FindPath( std::pair< size_t , size_t> start , std::pair< size_t , size_t> end ) {
    Edges * path = new Edges();
    std::vector< size_t > pathRowsColumns;
    std::vector< std::vector < int > > dist =  std::vector< std::vector < int > >( rows , std::vector < int >( columns , __INT_MAX__ ) );
    std::vector< std::vector < int > > prev =  std::vector< std::vector < int > >( rows , std::vector < int >( columns , -1 ) );
    std::vector< std::vector < bool > > visited =  std::vector< std::vector < bool > >( rows , std::vector < bool >( columns , false ) );
    dist[start.first][start.second] = 0;
    dist[start.first][start.second] = true;
    prev[start.first][start.second] = start.second + rows * start.first;
    
    for ( size_t row = 0 ; row < rows ; row++ ) {
        for ( size_t column = 0 ; column < columns ; column++ ) {
            if( grid->GetCellStatus( row , column ) == OBSTACLE ) {
                visited[ row ][ column ] = true;
            }
        }
    }
    
    int indexVertex, row, column;

    for ( size_t index = 0 ; index < rows * columns ; index++ ){
        indexVertex = -1;
        for (size_t itVertex = 0 ; itVertex < rows * columns ; itVertex++ ) {
            row = itVertex / rows;
            column = itVertex % rows;
            if( !visited[ row ][ column ] && ( indexVertex == -1 || dist[ row ][ column ] < dist[ indexVertex / rows ][ indexVertex % rows ] ) ) {
                indexVertex = itVertex;
            }
        }

        if( indexVertex == -1 || dist[ indexVertex / rows ][ indexVertex % rows ] == __INT_MAX__ ) {
            break;
        }

        row = indexVertex / rows;
        column = indexVertex % rows;
        visited[ row ][ column ] = true;

        if( row <= (int)rows - 2 && ( dist[ row ][ column ] + 1 < dist[ row + 1 ][ column ] ) ) {
            dist[ row + 1 ][ column ] = dist[ row ][ column ] + 1;
            prev[ row + 1 ][ column ] = row * rows + column;
        }
        if( column <= (int)columns - 2 && ( dist[ row ][ column ] + 1 < dist[ row ][ column + 1 ] ) ) {
            dist[ row ][ column + 1 ] = dist[ row ][ column ] + 1;
            prev[ row ][ column + 1 ] = row * rows + column;
        }
        if( row > 0 && ( dist[ row ][ column ] + 1 < dist[ row - 1 ][ column ] ) ) {
            dist[ row - 1 ][ column ] = dist[ row ][ column ] + 1;
            prev[ row - 1 ][ column ] = row * rows + column;
        }
        if( column > 0 && ( dist[ row ][ column ] + 1 < dist[ row ][ column - 1 ] ) ) {
            dist[ row ][ column - 1 ] = dist[ row ][ column ] + 1;
            prev[ row ][ column - 1 ] = row * rows + column;
        }
    }
    
    if( dist[ end.first ][ end.second ] == __INT_MAX__ ) {  
        path = nullptr;
    } else {
        row = end.first;
        column = end.second;
        while ( row != (int)start.first || column != (int)start.second ) {
            pathRowsColumns.push_back( row );
            pathRowsColumns.push_back( column );
            indexVertex = prev[ row ][ column ];
            row = indexVertex / rows;
            column = indexVertex % rows;
        }
        pathRowsColumns.push_back( row );
        pathRowsColumns.push_back( column );

        Vector2 start, end; 
        for ( size_t index = 2 ; index < pathRowsColumns.size() ; index = index + 2 ) {
            start = Vector2{ pathRowsColumns[ index - 1 ] * cellRowSize + cellRowSize / 2 , pathRowsColumns[ index - 2 ] * cellColumnSize + cellColumnSize / 2 };
            end = Vector2{ pathRowsColumns[ index + 1 ] * cellRowSize + cellRowSize / 2 , pathRowsColumns[ index ] * cellColumnSize + cellColumnSize / 2 };
            path->AddEdge( start , end );
        }
    }

    return std::make_pair( path , pathRowsColumns ); 
}

void Interface::GenerateRandomPath( size_t quantity ) {
    size_t cells = rows * columns;
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<size_t> distrib(0, cells - 1);

    std::vector< bool > isUsed = std::vector< bool >( cells , false );

    for ( size_t row = 0 ; row < rows ; row++ ) {
        for ( size_t column = 0 ; column < columns ; column++ ) {
            if( grid->GetCellStatus( row , column ) != EMPTY ) {
                isUsed[ rows * row + column ] = true;
            }
        }        
    }

    std::pair< size_t , size_t > start , end;

    for ( size_t index = 0 ; index < quantity && index < cells ; index++ ) {
        auto pick = [&]() {
            size_t n;
            do { n = distrib(gen); } while (isUsed[n]);
            isUsed[n] = true;
            return std::make_pair(n / columns, n % columns);
        };

        auto start = pick();
        grid->SetCellStatus(start.first, start.second, START);

        auto end = pick();
        grid->SetCellStatus(end.first, end.second, END);

        #ifdef LOG
            paths.push_back(new Path(start, end, std::make_pair( nullptr , std::vector< size_t >( ) ) ));
        #endif
        #ifndef LOG
            paths.push_back(new Path(start, end, FindPath(start, end)));
        #endif
    }      
}

void Interface::GenerateRandomObstacle( size_t quantity ) {
    size_t cells = rows * columns;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, cells - 1);

    std::vector< bool > isUsed = std::vector< bool >( cells );

    for ( size_t row = 0 ; row < rows ; row++ ) {
        for ( size_t column = 0 ; column < columns ; column++ ) {
            if( grid->GetCellStatus( row , column ) != EMPTY ) {
                isUsed[ rows * row + column ] = true;
            }
        }        
    }

    size_t row, column;
    int number;

    for ( size_t index = 0 ; index < quantity && index < cells ; index++ ) {
        number = distrib(gen);
        while( isUsed[ number ] ) {
            number = distrib( gen );
        }
        row = number / rows;
        column = number % rows; 
        grid->SetCellStatus( row , column , OBSTACLE );
        isUsed[ number ] = true;
    }   
}

double Interface::MeanPathDistance() {
    std::vector< size_t > pathDist;
    for ( size_t i = 0 ; i < paths.size() ; i++ )
    {
        if( paths[ i ]->pathRowsColumns.size() > 0 ) {
            pathDist.push_back( paths[ i ]->pathRowsColumns.size() - 1 );
        }
    }
    double sum = 0;
    for ( size_t i = 0 ; i < pathDist.size() ; i++ ) {
        sum += pathDist[i];
    }
    return sum / pathDist.size();
}

size_t Interface::QuantityOfPathNotFound() {
    size_t sum = 0;
    for ( size_t i = 0 ; i < paths.size() ; i++ ) {
        if( paths[i]->pathRowsColumns.size() == 0 ) {
            sum++;
        }
    }
    return sum;
}

double Interface::TimeToCalculatePath() {
    std::chrono::duration<double, std::milli> computeTime;
    auto start = std::chrono::high_resolution_clock::now();
    for ( size_t i = 0 ; i < paths.size() ; i++ ) {
        paths[i]->SetPath( FindPath( paths[i]->start , paths[i]->end ) );
    }
    auto end = std::chrono::high_resolution_clock::now();
    computeTime = end - start;
    return computeTime.count();
}