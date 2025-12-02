#include "raylib.hpp"
#include "grid/Grid.hpp"
#include "grid/GridAdapterFactory.hpp"
#include "initialization/BaseHandler.hpp"
#include "initialization/GetInfo.hpp"
#include "initialization/InitFactorys.hpp"
#include "initialization/InitGrid.hpp"
#include "initialization/InitUi.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#include <cmath>
#include "actions/Invoker.hpp"

int main() {
    bool running = true;
    BaseHandler * initialization;

    initialization = ( BaseHandler * ) new GetInfo();
    initialization->AddEnd( ( BaseHandler * ) new InitFactorys() );
    initialization->AddEnd( ( BaseHandler * ) new InitGrid() );
    initialization->AddEnd( ( BaseHandler * ) new InitUi() );
    initialization->Execute( InicializationVariables() );

    delete initialization;

    GridAdapter * gridAdapter = GridAdapterFactory::GetGridAdapterFactory()->GetAdapter();

    while( running ) {
        if( WindowShouldClose() ) {
            running = false;
        }
        if( IsWindowFocused() ) {
            Invoker::GetInvoker()->Input();
        }

        BeginDrawing( );  
        ClearBackground( BLACK );
        gridAdapter->DrawGrid();

        EndDrawing();
    } 
    CloseWindow();
    return 0;
}
