#include "../../lib/path/Path.hpp"

Path::Path( std::pair< size_t , size_t> start , std::pair< size_t , size_t > end ) {
    this->start = start;
    this->end = end;
}

std::pair< size_t , size_t> Path::GetStart() {
    return start;
}

std::pair< size_t , size_t> Path::GetEnd() {
    return end;
} 

std::vector< size_t > Path::GetPath() {
    return pathRowsColumns;
}