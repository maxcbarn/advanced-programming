#ifndef DRAWAGENT_HPP
#define DRAWAGENT_HPP

#include "raylib.hpp"
#include "Settings.hpp"
#include <vector>
#include "agent/DrawAgentDecorator.hpp"
#include "grid/GridAdapterFactory.hpp"
#include "agent/Agent.hpp"

class DrawAgent : DrawAgentDecorator{
private:
    DrawAgentDecorator * drawAgentDecorator;
public:
    DrawAgent( DrawAgentDecorator * drawAgentDecorator );
    ~DrawAgent();
    void Draw( Agent * agent ) override;
};

#endif