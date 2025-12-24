#include "agent/ActionFindCollisions.hpp"
#include "grid/GridAdapter.hpp"
#include "grid/GridAdapterFactory.hpp"
#include <iostream>
#include "Settings.hpp"

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
    cellBuff = gridAdapter->GetCell( agent->GetPosition() ); 
    if( cellBuff.size() > 1 ) {
        for ( size_t index = 0 ; index < cellBuff.size() ; index++ ) {
            cell = cellBuff[index];
            if( cell != ( Cell * ) agent && cell->GetCollisor() != nullptr && cell->GetDynamic() != nullptr ) {
                toTest.push_back( ( Agent * ) cell );
            }
        }
    }
    for ( size_t index = 0 ; index < neightburs.size() ; index++ ) {
        if( gridAdapter->GetCell( neightburs[index] ).size() == 0 ) {
            continue;
        }
        cellBuff = gridAdapter->GetCell( neightburs[index] );
        for ( size_t index = 0 ; index < cellBuff.size() ; index++ ) {
            cell = cellBuff[index];
            if( cell->GetCollisor() != nullptr && cell->GetDynamic() != nullptr ) {
                toTest.push_back( ( Agent * )cell );
            }
        }
    }

    for ( size_t index = 0 ; index < toTest.size() ; index++ ) {
        if( dist( agent->GetDynamic()->GetDynamicPosition() , toTest[index]->GetDynamic()->GetDynamicPosition() ) <= agent->GetCollisor()->GetWarningRadius() + toTest[index]->GetCollisor()->GetWarningRadius() ) {
            /* std::cout << "Possible Collision " << "(" << agent->GetDynamic()->GetDynamicPosition().x << "," << agent->GetDynamic()->GetDynamicPosition().y << ")" << " : (" <<  toTest[index]->GetDynamic()->GetDynamicPosition().x << "," << toTest[index]->GetDynamic()->GetDynamicPosition().y << ")" << std::endl; */
            Resolve( agent , toTest[index] );
        } else {
            continue;
        }
        
        if( dist( agent->GetDynamic()->GetDynamicPosition() , toTest[index]->GetDynamic()->GetDynamicPosition() ) <= agent->GetCollisor()->GetRadius() + toTest[index]->GetCollisor()->GetRadius() ) {
            std::cout << "Collision Between " << "(" << agent->GetDynamic()->GetDynamicPosition().x << "," << agent->GetDynamic()->GetDynamicPosition().y << ")" << " : (" <<  toTest[index]->GetDynamic()->GetDynamicPosition().x << "," << toTest[index]->GetDynamic()->GetDynamicPosition().y << ")" << std::endl;
        }
    }
    

    delete gridAdapter;
    ActionDecorator::Execute( agent );
}

bool ActionFindCollisions::CheckFutureCollison( [[maybe_unused]] Agent * agentToTest , [[maybe_unused]] Agent * agent , [[maybe_unused]] float distanceCheck ) {
    /* Vector2 directionAgent = agent->GetDynamic()->GetDirectionVector( agent );
    Vector2 directionAgentToTest = agent->GetDynamic()->GetDirectionVector( agentToTest ); */
    return true;
}

void ActionFindCollisions::Resolve( Agent * agent, Agent * agentTo ) {
    auto rotateDirectionCCW = []( Vector2 v ) {
        if( v.x == 0 && v.y == 0 ) {
            return v;
        }
        return Vector2{ v.y * -1 , v.x };
    };
    auto rotateDirectionCW = []( Vector2 v ) {
        if( v.x == 0 && v.y == 0 ) {
            return v;
        }
        return Vector2{ v.y , v.x * -1 };
    };
    auto angleBetweenVector = []( Vector2 a , Vector2 b ) {
        return atan2( a.x * b.y - a.y * b.x , a.x * b.x - a.y * b.y );
    };
    
    Vector2 dirToAgent = normalize( dirVector( agent->GetDynamic()->GetDynamicPosition() , agentTo->GetDynamic()->GetDynamicPosition() ) );
    double angleBetweenCCW = angleBetweenVector( dirToAgent , rotateDirectionCCW( agent->GetDynamic()->GetDirectionVector( agent ) ) );
    double angleBetweenCW = angleBetweenVector( dirToAgent , rotateDirectionCW( agent->GetDynamic()->GetDirectionVector( agent ) ) ); 
    if( angleBetweenVector( dirToAgent , agent->GetDynamic()->GetDirectionVector( agent ) ) <= 50 ) {
        if( angleBetweenCCW < angleBetweenCW ) {
            agent->GetDynamic()->SetDirection( rotateDirectionCCW( agent->GetDynamic()->GetDirectionVector( agent ) ) );
        } else {
            agent->GetDynamic()->SetDirection( rotateDirectionCW( agent->GetDynamic()->GetDirectionVector( agent ) ) );
        }
    }
}