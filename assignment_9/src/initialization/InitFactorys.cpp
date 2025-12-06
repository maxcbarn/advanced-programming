#include "initialization/InitFactorys.hpp"
#include "grid/GridAdapterFactory.hpp"
#include "obstacle/ObstacleFactory.hpp"

InitFactorys::InitFactorys() : BaseHandler() {
}

InitFactorys::~InitFactorys() {

}

InicializationVariables InitFactorys::Execute( InicializationVariables variables ) {
    GridAdapterFactory::Initialize( variables.typeGrid , variables.rows , variables.columns , variables.windowSize );
    ObstacleFactory::GetObstacleFactory();

    return BaseHandler::Execute( variables );
}

