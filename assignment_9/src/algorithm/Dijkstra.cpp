#include "algorithm/Dijkstra.hpp"
#include "grid/Grid.hpp"
#include <queue>


Dijkstra::Dijkstra() {

}

Dijkstra::~Dijkstra() {

}

Dijkstra * Dijkstra::GetDijkstra() {
    if ( dijkstra == nullptr )
    {
        dijkstra = new Dijkstra();
    }
    return dijkstra;
}

std::vector< Size_t2 > Dijkstra::FindPath( Size_t2 start , Size_t2 end ) {
    

    std::vector< std::vector< Cell* > > board = Grid::GetGrid()->GetBoard();
    std::vector< Obstacle * > obstacles = Grid::GetGrid()->GetObstacles();
    GridAdapter * gridAdapter = GridAdapterFactory::GetGridAdapterFactory()->GetAdapter();
    std::vector< Size_t2 > neighburs;
    std::vector< Size_t2 > path;
    
    
    size_t rows = board.size();
    size_t columns = board.at(0).size();

    std::vector< std::vector < size_t > > dist =  std::vector< std::vector < size_t > >( rows , std::vector < size_t >( columns , INT_MAX ) );
    std::vector< std::vector < Size_t2 > > prev =  std::vector< std::vector < Size_t2 > >( rows , std::vector < Size_t2 >( columns , Size_t2{ INT_MAX , INT_MAX } ) );
    std::vector< std::vector < size_t > > cost = std::vector< std::vector < size_t > >( rows , std::vector < size_t >( columns , 1 ) );
    std::vector< std::vector < bool > > visited =  std::vector< std::vector < bool > >( rows , std::vector < bool >( columns , false ) );

    auto comparator = [](const pDist& a, const pDist& b) {
        return a.dist > b.dist; 
    };

    std::priority_queue< pDist , std::vector< pDist > , decltype(comparator) > pQueue( comparator );

    
    for ( size_t index = 0 ; index < obstacles.size() ; index++ ) {
        cost[obstacles[index]->GetPosition().x][obstacles[index]->GetPosition().y] = obstacles[index]->GetCost();
    }
    
    dist[start.x][start.y] = 0;
    prev[start.x][start.y] = start;
    
    pDist pDistAux;
    Size_t2 cellIndex;
    size_t costCell, costNext;

    pDistAux.row = start.x;
    pDistAux.collum = start.y;
    pDistAux.dist = dist[start.x][start.y];
    pQueue.push( pDistAux );


    for ( size_t index = 0 ; index < rows * columns ; index++) {
        cellIndex.x = INT_MAX;
        cellIndex.y = INT_MAX;

        if( pQueue.empty() ) {
            break;
        }
        pDistAux = pQueue.top();
        pQueue.pop();

        cellIndex.x = pDistAux.row;
        cellIndex.y = pDistAux.collum;

        if ( cellIndex.x == INT_MAX && cellIndex.y == INT_MAX ) {
            break;
        }   
        if ( dist[cellIndex.x][cellIndex.y] == INT_MAX ) {
            break;
        }
        
        visited[cellIndex.x][cellIndex.y] = true;
        neighburs = gridAdapter->WhoIsMyNeighburs( cellIndex );
        costCell = dist[cellIndex.x][cellIndex.y];

        for ( size_t index = 0 ; index < neighburs.size() ; index++ ) {
            if( visited[neighburs[index].x][neighburs[index].y] ) {
                continue;
            }
            if( cost[neighburs[index].x][neighburs[index].y] == INT_MAX ) {
                continue;
            }
            costNext = dist[neighburs[index].x][neighburs[index].y];
            if( costCell + cost[neighburs[index].x][neighburs[index].y] < costNext ) {
                dist[neighburs[index].x][neighburs[index].y] = costCell + cost[neighburs[index].x][neighburs[index].y];
                prev[neighburs[index].x][neighburs[index].y] = cellIndex;
                pDistAux.row = neighburs[index].x;
                pDistAux.collum = neighburs[index].y;
                pDistAux.dist = dist[neighburs[index].x][neighburs[index].y];
                pQueue.push( pDistAux );
            }  
        }
    }

    delete gridAdapter;

    if (dist[end.x][end.y] != INT_MAX) {

        Size_t2 aux = end;

        while (!(aux.x == start.x && aux.y == start.y)) {
            if (prev[aux.x][aux.y].x == INT_MAX) {
                path.clear();
                return path;
            }
            path.push_back(aux);
            aux = prev[aux.x][aux.y];
        }

        path.push_back(start);
    }
    std::reverse( path.begin() , path.end() );
    return path;
}

