#ifndef DRAWAGENTEND_HPP
#define DRAWAGENTEND_HPP

#include "raylib.hpp"
#include "Settings.hpp"
#include <vector>
#include "agent/DrawAgentDecorator.hpp"
#include "grid/GridAdapterFactory.hpp"
#include "agent/Agent.hpp"

class DrawAgentEnd : DrawAgentDecorator{
private:
    DrawAgentDecorator * drawAgentDecorator;
public:
    DrawAgentEnd( DrawAgentDecorator * drawAgentDecorator );
    ~DrawAgentEnd();
    void Draw( Agent * agent ) override;
};

#endif