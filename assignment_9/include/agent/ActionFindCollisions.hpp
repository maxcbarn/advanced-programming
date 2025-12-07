#ifndef ACTIONFINDCOLLISIONS_HPP
#define ACTIONFINDCOLLISIONS_HPP

#include "agent/Agent.hpp"
#include "agent/ActionDecorator.hpp"

class ActionFindCollisions : ActionDecorator {
private:
    ActionFindCollisions * actionFindCollisions;
public:
    ActionFindCollisions( ActionDecorator * actionDecorator );
    ~ActionFindCollisions();
    void Execute( Agent * agent ) override;
    using ActionDecorator::AddEnd;
};










#endif