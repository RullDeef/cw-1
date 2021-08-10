#include <chrono>
#include "Builders/DefaultIDGenerator.hpp"


size_t DefaultIDGenerator::generate()
{
    auto now = std::chrono::system_clock::now();
    auto durr = now.time_since_epoch();
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(durr);

    return nanos.count();
}
