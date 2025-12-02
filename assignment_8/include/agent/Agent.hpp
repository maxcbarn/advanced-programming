#ifndef AGENT_HPP
#define AGENT_HPP

#include "raylib.hpp"
#include "grid/Cell.hpp"
#include "Settings.hpp"
#include <vector>
#include "agent/DrawAgentDecorator.hpp"


class Agent : Cell
{
protected:
    Size_t2 start , end;
    std::vector< Size_t2 > path;
    DrawAgentDecorator * drawDecorator;
    size_t step;
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
    Size_t2 GetStart();
    std::vector< Size_t2 > GetPath();
    void Step();
};

#endif