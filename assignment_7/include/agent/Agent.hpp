#ifndef AGENT_HPP
#define AGENT_HPP

#include "raylib.hpp"
#include "grid/Cell.hpp"
#include "Settings.hpp"
#include <vector>
#include "agent/DrawAgentDecorator.hpp"
#include "agent/DrawAgentEnd.hpp"
#include "agent/DrawAgentPath.hpp"
#include "agent/DrawAgentStart.hpp" 


class Agent : Cell
{
protected:
    Size_t2 start , end;
    std::vector< Size_t2 > path;
    DrawAgentDecorator * drawDecorator;
    bool endState;
public:
    Agent( Size_t2 position , Size_t2 start );
    ~Agent();
    void SetEndPoint( Size_t2 end );
    void CalculatePath();
    void Draw() override;
    bool GetEndState();
    using Cell::GetPosition;
    Size_t2 GetEnd();
};

#endif