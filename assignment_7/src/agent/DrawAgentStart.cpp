#include "agent/DrawAgentStart.hpp"

DrawAgentStart::DrawAgentStart( DrawAgentDecorator * drawAgentDecorator ) : DrawAgentDecorator ( drawAgentDecorator ) {
    this->drawAgentDecorator = drawAgentDecorator;
}

DrawAgentStart::~DrawAgentStart() {
    if( drawAgentDecorator != nullptr ) {
        delete drawAgentDecorator;
    }
}

void DrawAgentStart::Draw( Size_t2 start , Size_t2 end , std::vector< Size_t2 > path ) {
    GridAdapterFactory * gridAdapterFactory = GridAdapterFactory::GetGridAdapterFactory();
    GridAdapter * gridAdapter = gridAdapterFactory->GetAdapter();
    
    Vector2 centroid = gridAdapter->GetCentroidOfCell( start );
    float radius = gridAdapter->GetRadiusOfCell();
    
    Vector2 origin = Vector2{ centroid.x - radius , centroid.y - radius };
    Vector2 size = Vector2{ radius * 2 , radius * 2 };

    DrawRectangleV( origin , size , START_COLOR );

    if ( drawAgentDecorator != nullptr )
    {
        drawAgentDecorator->Draw( start , end , path );
    }
}