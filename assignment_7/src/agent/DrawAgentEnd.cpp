#include "agent/DrawAgentEnd.hpp"

DrawAgentEnd::DrawAgentEnd( DrawAgentDecorator * drawAgentDecorator ) : DrawAgentDecorator ( drawAgentDecorator ) {
    this->drawAgentDecorator = drawAgentDecorator;
}

DrawAgentEnd::~DrawAgentEnd() {
    if( drawAgentDecorator != nullptr ) {
        delete drawAgentDecorator;
    }
}

void DrawAgentEnd::Draw( Size_t2 start , Size_t2 end , std::vector< Size_t2 > path ) {
    GridAdapterFactory * gridAdapterFactory = GridAdapterFactory::GetGridAdapterFactory();
    GridAdapter * gridAdapter = gridAdapterFactory->GetAdapter();
    
    Vector2 centroid = gridAdapter->GetCentroidOfCell( end );
    float radius = gridAdapter->GetRadiusOfCell();
    
    Vector2 origin = Vector2{ centroid.x , centroid.y };

    DrawCircleV( origin , radius , END_COLOR );

    if ( drawAgentDecorator != nullptr )
    {
        drawAgentDecorator->Draw( start , end , path );
    }
}