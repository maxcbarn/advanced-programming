#include "agent/Agent.hpp"
#include "algorithm/Dijkstra.hpp"
#include "agent/ActionDecorator.hpp"
#include "agent/ActionMove.hpp"
#include "grid/GridAdapterFactory.hpp"
#include "grid/GridAdapter.hpp"
#include "agent/ActionFindCollisions.hpp"

Agent::Agent( Size_t2 position , Size_t2 start , float velocity , float radius , Color color ) : Cell( position , nullptr , nullptr ) {
    GridAdapterFactory * gridAdapterFactory = GridAdapterFactory::GetGridAdapterFactory();
    this->gridAdapter = gridAdapterFactory->GetAdapter();
    this->start = start;
    this->color = color;
    endState = false;
    GridAdapter * adpater = GridAdapterFactory::GetGridAdapterFactory()->GetAdapter();
    Dynamic * dynamic = new Dynamic( adpater->GetCentroidOfCell( position ) , velocity);
    Collisor * collisor = new Collisor( INT_MAX , false , radius );
    delete adpater;
    tSpline = 0;
    this->dynamic = dynamic;
    this->collisor = collisor;
    this->actionDecorator = ( ActionDecorator * ) new ActionMove( nullptr );
    this->actionDecorator = ( ActionDecorator * ) new ActionFindCollisions( this->actionDecorator );
    this->radius = radius;
}

Agent::~Agent() {
    pathDiscrete.clear();
    pathContinuous.clear();
    delete actionDecorator;
    delete gridAdapter;
}

void Agent::SetEndPoint( Size_t2 end ) {
    endState = true;
    this->end = end;    
}

bool Agent::GetEndState() {
    return endState;
}

void Agent::Draw() {
    gridAdapter->FillCell( color , start );
    
    if( !endState ) {
    
        return;
    }
    
    Vector2 centroid = gridAdapter->GetCentroidOfCell( end );
    float radius = gridAdapter->GetRadiusOfCell() / 1.1;
    
    Vector2 origin = Vector2{ centroid.x , centroid.y };

    DrawCircleV( origin , radius , color );

    for ( size_t index = 1 ; index < pathContinuous.size() ; index++ ) {
        DrawLineEx( pathContinuous[index - 1] , pathContinuous[index] , PATH_WIDTH , color );
    }
}

void Agent::DrawAgent() {
    Vector2 centroid = dynamic->GetDynamicPosition();
    
    Vector2 origin = Vector2{ centroid.x , centroid.y };

    DrawCircleV( origin , radius , AGENT_COLOR );
}

void Agent::MoveAgentInGrid( Size_t2 position ) {
    auto compare = []( Size_t2 a , Size_t2 b ) {
        return a.x == b.x && a.y == b.y;
    };
    if( compare( this->position , position ) ) {
        return;
    } else {
        Grid::GetGrid()->MoveAgent( this->position , position , this );
        this->position = position;
    }
}

void Agent::CalculatePath() {
    auto compare = [] ( Size_t2 a , Size_t2 b ) {
        return a.x == b.x && a.y == b.y;
    };
    Size_t2 aux;
   
    pathDiscrete = Dijkstra::GetDijkstra()->GetDijkstra()->FindPath( start , end );
    Reset();
    pathContinuous.clear();
    if( pathDiscrete[start.x][start.y] == INT_MAX ) {
        return;
    }
    aux = start;
    while ( !compare( aux , end ) ) {
        pathContinuous.push_back( gridAdapter->GetCentroidOfCell( aux ) );
        aux = LowestNeighbur( aux );
    }
    pathContinuous.push_back( gridAdapter->GetCentroidOfCell( aux ) );
}

Size_t2 Agent::LowestNeighbur( Size_t2 position ) {
    if( pathDiscrete[position.x][position.y] == 0 ) {
        return position;
    }
    Size_t2 lowest;
    size_t lowestValue = INT_MAX;
     std::vector< Size_t2 > neighburs = gridAdapter->WhoIsMyNeighburs( position );
    for ( size_t index = 0 ; index < neighburs.size() ; index++ ) {
        if( pathDiscrete[neighburs[index].x][neighburs[index].y] < lowestValue ) {
            lowestValue = pathDiscrete[neighburs[index].x][neighburs[index].y];
            lowest = neighburs[index];
        }
    }
    if( lowestValue > pathDiscrete[position.x][position.y] ) {
        return position;
    }
    return lowest;
}

void Agent::Reset( ) {
    dynamic->SetDynamicPosition( gridAdapter->GetCentroidOfCell( position ) );
    MoveAgentInGrid( start );
    tSpline = 0;
}

Size_t2 Agent::GetEnd() {
    return end;
}

Size_t2 Agent::GetStart() {
    return start;
}
    
std::vector< std::vector< size_t > > Agent::GetPathDiscrete() {
    return pathDiscrete;
}

std::vector< Vector2 > Agent::GetPathContinuous() {
    return pathContinuous;
}

bool Agent::ReachedDestination() {
    if( !endState || pathContinuous.size() == 0 ) {
        return true;
    }
/* 
    if( tSpline == path.size() ) {
        return true;
    } else {
        return false;
    }
 */
    auto compare = []( Vector2 a , Vector2 b ) {
        return std::abs( a.x - b.x ) < 0.00000004 && std::abs( a.y - b.y ) < 0.00000004;
    };

    if( compare( dynamic->GetDynamicPosition() , gridAdapter->GetCentroidOfCell( end ) ) ) {
        return true;
    } else {
        return false;
    }

}

void Agent::Tick() {
    if( !endState || ReachedDestination() ) {
        return;
    }
    actionDecorator->Execute( this );
}

float Agent::GetRadius() {
    return radius;
}