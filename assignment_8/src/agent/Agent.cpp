#include "agent/Agent.hpp"
#include "algorithm/Dijkstra.hpp"
#include "agent/DrawAgentDecorator.hpp"
#include "agent/DrawAgentStart.hpp"
#include "agent/DrawAgentEnd.hpp"
#include "agent/DrawAgentPath.hpp"
#include "agent/DrawAgent.hpp"

Agent::Agent( Size_t2 position , Size_t2 start ) : Cell( position ) {
    this->start = start;
    drawDecorator = ( DrawAgentDecorator * ) new DrawAgent( nullptr );
    drawDecorator = ( DrawAgentDecorator * ) new DrawAgentStart( drawDecorator );
    endState = false;
    step = 0;
}

Agent::~Agent() {
    path.clear();
    delete drawDecorator;
}

void Agent::SetEndPoint( Size_t2 end ) {
    endState = true;
    this->end = end;
    drawDecorator = ( DrawAgentDecorator * ) new DrawAgentEnd( drawDecorator );
    drawDecorator = ( DrawAgentDecorator * ) new DrawAgentPath( drawDecorator );
    step = 0;
    CalculatePath();
}

bool Agent::GetEndState() {
    return endState;
}

void Agent::Draw() {
    drawDecorator->Draw( this );
}

void Agent::CalculatePath() {
    path = Dijkstra::GetDijkstra()->GetDijkstra()->FindPath( start , end );
}

Size_t2 Agent::GetEnd() {
    return end;
}

Size_t2 Agent::GetStart() {
    return start;
}
    
std::vector< Size_t2 > Agent::GetPath() {
    return path;
}

void Agent::Step() {
    if( !GetEndState() ) {
        return;
    }
    step++;
    if( step == path.size() ) {
        step = 0;
    }
    position = path[step];
}
