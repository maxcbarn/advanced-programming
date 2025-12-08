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
    std::deque< Cell* > cellBuff;
    Cell * cell;
    if( gridAdapter->GetCell( agent->GetPosition() ).size() > 1 ) {
        
    }
    for ( size_t index = 0 ; index < neightburs.size() ; index++ ) {
        if( gridAdapter->GetCell( neightburs[index] ).size() == 0 ) {
            continue;
        }
        cellBuff = gridAdapter->GetCell( neightburs[index] );
        for ( size_t index = 0 ; index < cellBuff.size() ; index++ ) {
            cell = cellBuff[index];
            if( cell->GetCollisor() != nullptr && cell->GetDynamic() ) {
                toTest.push_back( ( Agent * )cell );
            }
        }
    }

    for ( size_t index = 0 ; index < toTest.size() ; index++ ) {
        if( dist( agent->GetDynamic()->GetDynamicPosition() , toTest[index]->GetDynamic()->GetDynamicPosition() ) <= agent->GetRadius() + toTest[index]->GetRadius() ) {
            std::cout << "Collisont Between " << "(" << agent->GetDynamic()->GetDynamicPosition().x << "," << agent->GetDynamic()->GetDynamicPosition().y << ")" << " : (" <<  toTest[index]->GetDynamic()->GetDynamicPosition().x << "," << toTest[index]->GetDynamic()->GetDynamicPosition().y << ")" << std::endl;
        }
    }
    

    delete gridAdapter;
    ActionDecorator::Execute( agent );
}