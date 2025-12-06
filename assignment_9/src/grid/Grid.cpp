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

void Grid::DrawAgents() {
    for ( size_t index = 0 ; index < agents.size() ; index++ ) {
        agents[index]->DrawAgent();
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
    agents.push_back( new Agent( position , position , 60 , gridAdapter->GetRadiusOfCell() / 2 , GREEN ) );
    grid[position.x][position.y] = ( Cell* )agents.back();
    
}

void Grid::SetAgentEnd( Size_t2 position ) {
    agents.back()->SetEndPoint( position );
}

Cell * Grid::Remove( Size_t2 position ) {
    Cell * cell;
    for ( size_t index = 0 ; index < obstacles.size() ; index++ ) {
        if( obstacles[index]->GetPosition().x == position.x && obstacles[index]->GetPosition().y == position.y ) {
            cell = grid[position.x][position.y];
            obstacles.erase( obstacles.begin() + index );  
            grid[position.x][position.y] = nullptr;
            return cell;
        }
    }
    for ( size_t index = 0 ; index < agents.size() ; index++ ) {
        if( ( agents[index]->GetStart().x == position.x && agents[index]->GetStart().y == position.y ) || ( agents[index]->GetEnd().x == position.x && agents[index]->GetEnd().y == position.y ) ) {
            cell = grid[agents[index]->GetStart().x][agents[index]->GetStart().y];
            grid[agents[index]->GetStart().x][agents[index]->GetStart().y] = nullptr;
            agents.erase( agents.begin() + index );  
            return cell;
        }
    }
    return nullptr;
}

void Grid::RecalculateAgents() {
    if( agents.size() == 0 ) {
        return;
    }
    for ( size_t index = 0 ; index < agents.size() - 1 ; index++ ) {
        agents[index]->CalculatePath();
    }
    if( agents[agents.size() - 1]->GetEndState() ) {
        agents[agents.size() - 1]->CalculatePath();
    }
}

bool Grid::GetEndAgentState() {
    if( agents.size() == 0 ) {
        return true;
    }
    return agents[agents.size() - 1]->GetEndState();
}

void Grid::MoveAgents() {
    for ( size_t index = 0 ; index < agents.size() ; index++ ) {
        agents[index]->Tick();
    }
}

void Grid::MoveAgent( Size_t2 from , Size_t2 to , Agent * agent ) {
    grid[from.x][from.y] = nullptr;
    grid[to.x][to.y] = ( Cell * ) agent;
}

void Grid::ResetAgents() {
    for ( size_t index = 0 ; index < agents.size() ; index++ ) {
        agents[index]->Reset();
    }
}