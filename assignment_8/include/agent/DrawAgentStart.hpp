#ifndef DRAWAGENTSTART_HPP
#define DRAWAGENTSTART_HPP

#include "raylib.hpp"
#include "Settings.hpp"
#include <vector>
#include "agent/DrawAgentDecorator.hpp"
#include "grid/GridAdapterFactory.hpp"
#include "grid/GridAdapter.hpp"
#include "agent/Agent.hpp"

class DrawAgentStart :  DrawAgentDecorator{
private:
    DrawAgentDecorator * drawAgentDecorator;
public:
    DrawAgentStart( DrawAgentDecorator * drawAgentDecorator );
    ~DrawAgentStart();
    void Draw( Agent * agent ) override;
};

#endif