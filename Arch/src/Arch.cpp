#include <iostream>
#include "Arch.hpp"

MainFacade::~MainFacade()
{
    std::cout << "MainFacade destroyed" << std::endl;
}

void MainFacade::doStuff()
{
    std::cout << "doing some stuff..." << std::endl;
}
