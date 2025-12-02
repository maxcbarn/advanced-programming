#ifndef DRAWAGENTDECORATOR_HPP
#define DRAWAGENTDECORATOR_HPP

#include "raylib.hpp"
#include "Settings.hpp"
#include <vector>

class Agent;

class DrawAgentDecorator{
private:
    DrawAgentDecorator * drawAgentDecorator;
public:
    DrawAgentDecorator( DrawAgentDecorator * drawAgentDecorator );
    virtual ~DrawAgentDecorator();
    virtual void Draw( Agent * agent );
};

#endif