#include "agent/DrawAgentPath.hpp"
#include "agent/Agent.hpp"
#include "agent/DrawAgentDecorator.hpp"

DrawAgentPath::DrawAgentPath( DrawAgentDecorator * drawAgentDecorator ) : DrawAgentDecorator ( drawAgentDecorator ) {
    this->drawAgentDecorator = drawAgentDecorator;
}

DrawAgentPath::~DrawAgentPath() {
    if( drawAgentDecorator != nullptr ) {
        delete drawAgentDecorator;
    }
}

void DrawAgentPath::Draw( Agent * agent ) {
    GridAdapterFactory * gridAdapterFactory = GridAdapterFactory::GetGridAdapterFactory();
    GridAdapter * gridAdapter = gridAdapterFactory->GetAdapter();
    
    std::vector< Size_t2 > path = agent->GetPath();


    for ( size_t index = 1 ; index < path.size() ; index++ ) {
        DrawLineEx( gridAdapter->GetCentroidOfCell( path[index - 1] ) , gridAdapter->GetCentroidOfCell( path[index] ) , PATH_WIDTH , PATH_COLOR );
    }

    if ( drawAgentDecorator != nullptr )
    {
        drawAgentDecorator->Draw( agent );
    }
    delete gridAdapter;
}