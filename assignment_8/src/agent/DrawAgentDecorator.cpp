#include "agent/DrawAgentDecorator.hpp"
#include "agent/Agent.hpp"

DrawAgentDecorator::DrawAgentDecorator( DrawAgentDecorator * drawAgentDecorator ) {
    this->drawAgentDecorator = drawAgentDecorator;
}

DrawAgentDecorator::~DrawAgentDecorator() {
    
}

void DrawAgentDecorator::Draw( [[maybe_unused]] Agent * agent ) {

}