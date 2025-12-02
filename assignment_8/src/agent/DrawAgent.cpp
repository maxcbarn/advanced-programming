#include "agent/DrawAgent.hpp"
#include "agent/Agent.hpp"
#include "agent/DrawAgentDecorator.hpp"

DrawAgent::DrawAgent( DrawAgentDecorator * drawAgentDecorator ) : DrawAgentDecorator ( drawAgentDecorator ) {
    this->drawAgentDecorator = drawAgentDecorator;
}

DrawAgent::~DrawAgent() {
    if( drawAgentDecorator != nullptr ) {
        delete drawAgentDecorator;
    }
}

void DrawAgent::Draw( Agent * agent ) {
    GridAdapterFactory * gridAdapterFactory = GridAdapterFactory::GetGridAdapterFactory();
    GridAdapter * gridAdapter = gridAdapterFactory->GetAdapter();
    
    Vector2 centroid = gridAdapter->GetCentroidOfCell( agent->GetPosition() );
    float radius = gridAdapter->GetRadiusOfCell() / 1.5f;
    
    Vector2 origin = Vector2{ centroid.x , centroid.y };

    DrawCircleV( origin , radius , AGENT_COLOR );

    if ( drawAgentDecorator != nullptr )
    {
        drawAgentDecorator->Draw( agent );
    }
    delete gridAdapter;
}