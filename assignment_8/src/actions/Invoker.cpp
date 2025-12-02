#include "actions/Invoker.hpp"
#include "raylib.hpp"
#include "actions/RemoveCell.hpp"
#include "actions/AddAgent.hpp"
#include "actions/AddEndAgent.hpp"
#include "actions/AddObstacle.hpp"
#include "grid/GridAdapterFactory.hpp"
#include "actions/MoveAgents.hpp"

Invoker::Invoker() {
    gridAdapter = GridAdapterFactory::GetGridAdapterFactory()->GetAdapter();
}

Invoker::~Invoker() {
    for ( size_t i = 0 ; i < actionList.size() ; i++ ) {
        delete actionList[i];
    }
    actionList.clear();
    delete gridAdapter;
}

Invoker * Invoker::GetInvoker() {
    if( invoker == nullptr ) {
        invoker = new Invoker();
    }
    return invoker;
}

Command * Invoker::GetCommand() {
    if( !gridAdapter->IsValidMousePosition( GetMousePosition() ) ) {
        return nullptr;
    }

    if( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) ) {
        if( gridAdapter->GetEndAgentState() ) {
            return ( Command * ) new AddAgent();
        } else {
            return ( Command * ) new AddEndAgent();
        }
    }
    if( IsMouseButtonDown( MOUSE_BUTTON_RIGHT ) ) {
        return ( Command * ) new RemoveCell();
    }
    if( IsKeyDown( KEY_ONE ) ) {
        return ( Command * ) new AddObstacle( MUD );
    }
    if( IsKeyDown( KEY_TWO ) ) {
        return ( Command * ) new AddObstacle( WALL );
    }
    if( IsKeyPressed( KEY_THREE ) ) {
        return ( Command * ) new MoveAgents();
    }
    return nullptr;
}

void Invoker::Input() {
    Command * command = GetCommand();
    
    if( command != nullptr ) {
        command->Execute();
        actionList.push_back( command );
    }
}