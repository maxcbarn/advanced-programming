#include "agent/ActionMove.hpp"
#include "grid/GridAdapterFactory.hpp"
#include "grid/GridAdapter.hpp"
#include "common/Clock.hpp"

ActionMove::ActionMove( ActionDecorator * actionDecorator ) : ActionDecorator( actionDecorator ) {

}

ActionMove::~ActionMove() {

}

void ActionMove::Execute( Agent * agent ) {
    if( agent->ReachedDestination() ) {
        return;
    }

    auto dirVector = [] ( Vector2 a , Vector2 b ) {
        return Vector2{
            b.x - a.x , b.y - a.y
        };
    };

    auto normalize = [] (Vector2 v) {
        float len = std::sqrt(v.x * v.x + v.y * v.y);
        return Vector2{
            v.x / len,
            v.y / len
        };
    };
    GridAdapter * adapter = GridAdapterFactory::GetGridAdapterFactory()->GetAdapter();
    double deltaTime = Clock::GetClock()->GetTick();
    float velocity = agent->GetDynamic()->GetVelocity() * deltaTime;
    std::vector< Size_t2 > path = agent->GetPath();
    Vector2 start = adapter->GetCentroidOfCell( path[ agent->tSpline ] );
    Vector2 end = adapter->GetCentroidOfCell( path[ agent->tSpline + 1 ] );
    Vector2 dirVec = normalize( dirVector( start , end ) );
    dirVec.x *= velocity;
    dirVec.y *= velocity;
    Vector2 position = agent->GetDynamic()->GetDynamicPosition();

    if ( std::abs( end.x - position.x ) <= std::abs( dirVec.x ) && std::abs( end.y - position.y ) <= std::abs( dirVec.y  ) ) {
        position = end;
        agent->tSpline = agent->tSpline + 1;
    } else {
        position.x += dirVec.x;
        position.y += dirVec.y;
    }
    agent->GetDynamic()->SetDynamicPosition( position );
    agent->MoveAgentInGrid( adapter->GetGridPosition( agent->GetDynamic()->GetDynamicPosition() ) );
    delete adapter;
    ActionDecorator::Execute( agent );
}