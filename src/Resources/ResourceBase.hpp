#pragma once
#include "ResourceID.h"

// NOTE:
// Consider making every resource bindable, buildable, and check if built.
// TODO: Exception throwing for when resource creation fails

namespace TwilliEngine
{
// Base class for resources. Statically contains templated container.
///////////////////////////////////////////////////////////////////////
template <typename T>
class ResourceBase
{
public:
    ResourceBase() : mIsBuilt(false), mName("Unnamed Resource") {}
    ResourceBase(std::string_view name) : mIsBuilt(false), mName(name) {}
    virtual ~ResourceBase() {}

    bool IsBuilt() { return mIsBuilt; }

    class Key
    {
    public:
        Key() : mID() {}
        Key(const ResourceID &id) : mID(id) {}
        Key(const Key &rhs) : mID(rhs.mID) {}

        Key& operator=(const Key& rhs) { mID = rhs.mID; return *this; }
    
        operator ResourceID() const { return mID; }

        operator bool() const { return T::Get(mID) ? true : false; }
        bool IsValid() const { return T::Get(mID) ? true : false; }

        T* operator->() { return T::Get(mID); }

        void Destroy() { T::sResources.erase(mID); }

    private:
        ResourceID mID;
    };

    template <typename... Args>
    static ResourceID Create(Args&&...args);

    static std::unordered_map<ResourceID, std::unique_ptr<T>>&
    GetResources() { return sResources; }

    static Key GetResourceWithName(std::string_view name);

    static const Key NullKey;

    ResourceID mID;
    std::string mName;

protected:
    inline static T* Get(ResourceID id);
    static std::unordered_map<ResourceID, std::unique_ptr<T>> sResources;

    bool mIsBuilt;
    
private:
};

} // namespace TwilliEngine

#include "ResourceBase.inl"