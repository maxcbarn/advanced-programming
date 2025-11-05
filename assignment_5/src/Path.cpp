#include "../lib/Path.hpp"

Path::Path( std::pair< size_t , size_t> start , std::pair< size_t , size_t > end , Edges * path ) {
    this->start = start;
    this->end = end;
    this->path = path;
}

Path::~Path() {
    delete path;
}

void Path::Draw() {
    if( path == nullptr ) {
        return;
    }
    path->Draw();
}

void Path::SetPath( Edges * path ) {
    delete this->path;
    this->path = path;
}