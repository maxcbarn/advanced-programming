#include "agent/DrawAgentStart.hpp"
#include "agent/Agent.hpp"
#include "agent/DrawAgentDecorator.hpp"

DrawAgentStart::DrawAgentStart( DrawAgentDecorator * drawAgentDecorator ) : DrawAgentDecorator ( drawAgentDecorator ) {
    this->drawAgentDecorator = drawAgentDecorator;
}

DrawAgentStart::~DrawAgentStart() {
    if( drawAgentDecorator != nullptr ) {
        delete drawAgentDecorator;
    }
}

void DrawAgentStart::Draw( Agent * agent ) {
    GridAdapterFactory * gridAdapterFactory = GridAdapterFactory::GetGridAdapterFactory();
    GridAdapter * gridAdapter = gridAdapterFactory->GetAdapter();
    gridAdapter->FillCell( START_COLOR , agent->GetStart() );
    if ( drawAgentDecorator != nullptr )
    {
        drawAgentDecorator->Draw( agent );
    }
    delete gridAdapter;
}