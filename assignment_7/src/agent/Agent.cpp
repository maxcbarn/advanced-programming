#include "agent/Agent.hpp"
#include "algorithm/Dijkstra.hpp"

Agent::Agent( Size_t2 position , Size_t2 start ) : Cell( position ) {
    this->start = start;
    drawDecorator = ( DrawAgentDecorator * ) new DrawAgentStart( nullptr );
    endState = false;
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
    CalculatePath();
}

bool Agent::GetEndState() {
    return endState;
}

void Agent::Draw() {
    drawDecorator->Draw( start , end , path );
}

void Agent::CalculatePath() {
    path = Dijkstra::GetDijkstra()->GetDijkstra()->FindPath( start , end );
}

Size_t2 Agent::GetEnd() {
    return end;
}
