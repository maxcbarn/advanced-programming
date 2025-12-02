#include "agent/DrawAgentEnd.hpp"
#include "agent/DrawAgentDecorator.hpp"
#include "agent/Agent.hpp"

DrawAgentEnd::DrawAgentEnd( DrawAgentDecorator * drawAgentDecorator ) : DrawAgentDecorator ( drawAgentDecorator ) {
    this->drawAgentDecorator = drawAgentDecorator;
}

DrawAgentEnd::~DrawAgentEnd() {
    if( drawAgentDecorator != nullptr ) {
        delete drawAgentDecorator;
    }
}

void DrawAgentEnd::Draw( Agent * agent ) {
    GridAdapterFactory * gridAdapterFactory = GridAdapterFactory::GetGridAdapterFactory();
    GridAdapter * gridAdapter = gridAdapterFactory->GetAdapter();
    
    Vector2 centroid = gridAdapter->GetCentroidOfCell( agent->GetEnd() );
    float radius = gridAdapter->GetRadiusOfCell();
    
    Vector2 origin = Vector2{ centroid.x , centroid.y };

    DrawCircleV( origin , radius , END_COLOR );

    if ( drawAgentDecorator != nullptr )
    {
        drawAgentDecorator->Draw( agent );
    }
    delete gridAdapter;
}