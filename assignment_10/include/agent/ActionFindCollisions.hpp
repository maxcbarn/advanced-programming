#ifndef ACTIONFINDCOLLISIONS_HPP
#define ACTIONFINDCOLLISIONS_HPP

#include "agent/Agent.hpp"
#include "agent/ActionDecorator.hpp"

class ActionFindCollisions : ActionDecorator {
private:
public:
    ActionFindCollisions( ActionDecorator * actionDecorator );
    ~ActionFindCollisions();
    void Execute( Agent * agent ) override;
    using ActionDecorator::AddEnd;
    bool CheckFutureCollison( Agent * agentToTest , Agent * agent , float distanceCheck );
    void Resolve( Agent * agent, Agent * agentTo );
};










#endif