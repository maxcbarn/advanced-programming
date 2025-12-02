#include "grid/Grid.hpp"
#include "agent/Agent.hpp"

Grid::Grid( size_t rows , size_t columns ) {
    this->rows = rows;
    this->columns = columns;
    for ( size_t row = 0 ; row < rows ; row++ ) {
        std::vector< Cell * > aux;
        for ( size_t column = 0 ; column < columns ; column++ ) {
            aux.push_back( nullptr );
        }   
        grid.push_back( aux );
        aux.clear();
    }
    gridAdapter = GridAdapterFactory::GetGridAdapterFactory()->GetAdapter();
}

Grid::~Grid() {

}

std::vector< Obstacle * > Grid::GetObstacles() {
    return obstacles;
}

Grid * Grid::GetGrid() {
    return gridptr;
}

void Grid::Initialize( size_t rows , size_t columns ) {
    gridptr = new Grid( rows , columns );
}

void Grid::Draw() {
    for ( size_t index = 0 ; index < obstacles.size() ; index++ ) {
        obstacles[index]->Draw();
    }
    for ( size_t index = 0 ; index < agents.size() ; index++ ) {
        agents[index]->Draw();
    }
}

std::vector< std::vector < Cell * > > Grid::GetBoard() {
    return grid;
}

void Grid::AddObstacle( OBSTACLE_TYPE type , Size_t2 position ) {
    Remove( position );
    obstacles.push_back( ObstacleFactory::GetObstacleFactory()->Create( type , position ) );
    grid[position.x][position.y] = ( Cell * )obstacles.back();

    RecalculateAgents();
}

void Grid::AddAgent( Size_t2 position ) {
    Remove( position );
    if( agents.size() == 0 || agents.back()->GetEndState() ) {
        agents.push_back( new Agent( position , position ) );
        grid[position.x][position.y] = ( Cell* )agents.back();
    } else {
        agents.back()->SetEndPoint( position );
    }
}

void Grid::Remove( Size_t2 position ) {
    for ( size_t index = 0 ; index < obstacles.size() ; index++ ) {
        if( obstacles[index]->GetPosition().x == position.x && obstacles[index]->GetPosition().y == position.y ) {
            delete obstacles[index];
            obstacles.erase( obstacles.begin() + index );  
            grid[position.x][position.y] = nullptr;
            RecalculateAgents();
            return;
        }
    }
    for ( size_t index = 0 ; index < agents.size() ; index++ ) {
        if( ( agents[index]->GetPosition().x == position.x && agents[index]->GetPosition().y == position.y ) || ( agents[index]->GetEnd().x == position.x && agents[index]->GetEnd().y == position.y ) ) {
            grid[agents[index]->GetPosition().x][agents[index]->GetPosition().y] = nullptr;
            delete agents[index];
            agents.erase( agents.begin() + index );  
            RecalculateAgents();
            return;
        }
    }
}

void Grid::RecalculateAgents() {
    for ( size_t index = 0 ; index < agents.size() ; index++ ) {
        agents[index]->CalculatePath();
    }
}