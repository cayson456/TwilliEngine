#include "ResourceBase.hpp"

namespace TwilliEngine
{
template <typename T> std::unordered_map<ResourceID, std::unique_ptr<T>>
  ResourceBase<T>::sResources = std::unordered_map<ResourceID, std::unique_ptr<T>>();

template <typename T>
template <typename... Args>
inline ResourceID ResourceBase<T>::Create(Args&&... args)
{
    ResourceID resource_id;
    resource_id.GenerateNewID();

    sResources.emplace(resource_id, std::make_unique<T>(args...));
    
    auto it = sResources.find(resource_id);
    if (it != sResources.end())
        it->second.get()->mID = resource_id;
    
    return resource_id;
}

template <typename T>
inline T* ResourceBase<T>::Get(ResourceID id)
{
    auto res = sResources.find(id);

    if (res != sResources.end())
        return res->second.get();
    else
        return nullptr;
}
}