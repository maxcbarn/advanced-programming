#include "input/InputPublisher.hpp"
#include "grid/GridAdapterFactory.hpp"


InputPublisher::InputPublisher() {
    gridAdapter = GridAdapterFactory::GetGridAdapterFactory()->GetAdapter();
}

InputPublisher::~InputPublisher() {

}

InputPublisher * InputPublisher::GetInputPublisher() {
    if( inputPublisher == nullptr ) {
        inputPublisher = new InputPublisher();
    }
    return inputPublisher;
}

INPUT InputPublisher::GetInput() {
    return input;
}

void InputPublisher::Notify() {
    for ( size_t index = 0 ; index < subscribers.size() ; index++ ) {
        subscribers[index]->Notification();
    }
}

void InputPublisher::Input() {

    if( input == THREE ) {
        Notify();
    }

    if( !gridAdapter->IsValidMousePosition( GetMousePosition() ) ) {
        return;
    }

    if( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) ) {
        input = LEFT_CLICK;
        Notify();
        return;
    }
    if( IsMouseButtonDown( MOUSE_BUTTON_RIGHT ) ) {
        input = RIGHT_CLICK;
        Notify();
        return;
    }
    if( IsKeyDown( KEY_ONE ) ) {
        input = ONE;
        Notify();
        return; 
    }
    if( IsKeyDown( KEY_TWO ) ) {
        input = TWO;
        Notify();
        return;
    }
    if( IsKeyPressed( KEY_THREE ) ) {
        input = THREE;
        Notify();
        return;
    }
    if( IsKeyPressed( KEY_FOUR ) ) {
        input = FOUR;
        Notify();
        return;
    }
}

void InputPublisher::AddSubscriber( Subscriber * subscriber ) {
    subscribers.push_back( subscriber );
}
