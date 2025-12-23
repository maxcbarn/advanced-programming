#ifndef ACTICONSOLVECOLLISIONDIRECT_HPP
#define ACTICONSOLVECOLLISIONDIRECT_HPP

#include "agent/ActionDecorator.hpp"

class ActionSolveCollisionDirect : ActionDecorator
{
private:
    
public:
    ActionSolveCollisionDirect( ActionDecorator * actionDecorator );
    ~ActionSolveCollisionDirect();
    void Execute( Agent * agent ) override;
};





#endif