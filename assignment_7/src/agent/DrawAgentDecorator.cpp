#include "agent/DrawAgentDecorator.hpp"


DrawAgentDecorator::DrawAgentDecorator( DrawAgentDecorator * drawAgentDecorator ) {
    this->drawAgentDecorator = drawAgentDecorator;
}

DrawAgentDecorator::~DrawAgentDecorator() {
    
}

void DrawAgentDecorator::Draw( [[maybe_unused]] Size_t2 start , [[maybe_unused]] Size_t2 end , [[maybe_unused]] std::vector< Size_t2 > path ) {

}