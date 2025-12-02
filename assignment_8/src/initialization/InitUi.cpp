#include "initialization/InitUi.hpp"
#include "grid/Grid.hpp"
#include "actions/Invoker.hpp"

InitUi::InitUi() : BaseHandler() {
}

InitUi::~InitUi() {

}

InicializationVariables InitUi::Execute( InicializationVariables variables ) {
    InitWindow( variables.windowSize.z , variables.windowSize.w , " >w< :3 :D UwU " );
    Invoker::GetInvoker();
    
    return BaseHandler::Execute( variables );
}

