#include "../../lib/path/PathFactory.hpp"

PathFactory::PathFactory() {

}
PathFactory::~PathFactory() {

}

Path * PathFactory::Create( std::pair< size_t , size_t> start , std::pair< size_t , size_t > end ) {
    return ( Path * ) new ExactPath( start , end );
}