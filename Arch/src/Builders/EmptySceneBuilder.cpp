#include "Builders/EmptySceneBuidler.hpp"


std::unique_ptr<Scene> EmptySceneBuilder::build()
{
    return std::make_unique<Scene>();
}
