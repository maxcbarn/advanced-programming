#include "agent/DrawAgentPath.hpp"

DrawAgentPath::DrawAgentPath( DrawAgentDecorator * drawAgentDecorator ) : DrawAgentDecorator ( drawAgentDecorator ) {
    this->drawAgentDecorator = drawAgentDecorator;
}

DrawAgentPath::~DrawAgentPath() {
    if( drawAgentDecorator != nullptr ) {
        delete drawAgentDecorator;
    }
}

void DrawAgentPath::Draw( Size_t2 start , Size_t2 end , std::vector< Size_t2 > path ) {
    GridAdapterFactory * gridAdapterFactory = GridAdapterFactory::GetGridAdapterFactory();
    GridAdapter * gridAdapter = gridAdapterFactory->GetAdapter();
    
    for ( size_t index = 1 ; index < path.size() ; index++ ) {
        DrawLineEx( gridAdapter->GetCentroidOfCell( path[index - 1] ) , gridAdapter->GetCentroidOfCell( path[index] ) , PATH_WIDTH , PATH_COLOR );
    }

    if ( drawAgentDecorator != nullptr )
    {
        drawAgentDecorator->Draw( start , end , path );
    }
    delete gridAdapter;
}