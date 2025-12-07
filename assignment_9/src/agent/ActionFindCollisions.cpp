#include "agent/ActionFindCollisions.hpp"
#include "grid/GridAdapter.hpp"
#include "grid/GridAdapterFactory.hpp"
#include <iostream>

ActionFindCollisions::ActionFindCollisions( ActionDecorator * actionDecorator ) : ActionDecorator( actionDecorator ) {

}

ActionFindCollisions::~ActionFindCollisions() {
    
}

void ActionFindCollisions::Execute( Agent * agent ) {
    auto dist = [] ( Vector2 a , Vector2 b ) {
        return std::sqrtf( ( b.x - a.x ) * ( b.x - a.x ) + ( b.y - a.y ) * ( b.y - a.y ) );
    };
    
    GridAdapter * gridAdapter = GridAdapterFactory::GetGridAdapterFactory()->GetAdapter();
    std::vector< Size_t2 > neightburs  = gridAdapter->WhoIsMyNeighburs( agent->GetPosition() );
    std::vector< Agent * > toTest;
    for ( size_t index = 0 ; index < neightburs.size() ; index++ ) {
        if( gridAdapter->GetCell( neightburs[index] ) == nullptr ) {
            continue;
        }
        if( gridAdapter->GetCell( neightburs[index] )->GetCollisor() != nullptr && gridAdapter->GetCell( neightburs[index] )->GetDynamic() ) {
            toTest.push_back( ( Agent * )gridAdapter->GetCell( neightburs[index] ) );
        }
    }

    for ( size_t index = 0 ; index < toTest.size() ; index++ ) {
        std::cout << dist( agent->GetDynamic()->GetDynamicPosition() , toTest[index]->GetDynamic()->GetDynamicPosition() ) << " , " << agent->GetRadius() + toTest[index]->GetRadius() << std::endl;
        if( dist( agent->GetDynamic()->GetDynamicPosition() , toTest[index]->GetDynamic()->GetDynamicPosition() ) <= agent->GetRadius() + toTest[index]->GetRadius() ) {
            std::cout << "Collisont Between " << "(" << agent->GetDynamic()->GetDynamicPosition().x << "," << agent->GetDynamic()->GetDynamicPosition().y << ")" << " : (" <<  toTest[index]->GetDynamic()->GetDynamicPosition().x << "," << toTest[index]->GetDynamic()->GetDynamicPosition().y << ")" << std::endl;
        }
    }
    

    delete gridAdapter;
    ActionDecorator::Execute( agent );
}