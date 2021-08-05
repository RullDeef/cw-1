#ifndef LOADMANAGERIMP_HPP
#define LOADMANAGERIMP_HPP

#include "Managers/LoadManager.hpp"


template<typename T>
void LoadManager::loadObject()
{
    std::string filename = requestFilename();
    std::shared_ptr<IObject> object = loader->loadObject<T>();

    /// may be error here (SceneManager doesnt imported)
    getFactory()->getSceneManager()->addObject(object);

    onObjectLoad(object);
}

#endif // LOADMANAGERIMP_HPP
