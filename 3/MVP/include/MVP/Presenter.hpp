#ifndef PRESENTER_HPP
#define PRESENTER_HPP

#include <Memory/IManager.hpp>

namespace MVPNameSpace {

using namespace MemoryNameSpace;

class Presenter final {
private:
    IManager& manager_;

public:
    Presenter(IManager& manager) : manager_(manager) {}
    
};

}

#endif