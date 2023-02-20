namespace TwilliEngine
{

template<typename T>
T* Entity::AddComponent(std::string_view name)
{
    auto it = std::find_if(mComponents.begin(), mComponents.end(),
                           [](std::unique_ptr<Component>& component)
                           { return typeid(T) == typeid(*component.get()); });

    if (it != mComponents.end()) {
        err::LogError("Attempted to add duplicate component of type ", typeid(T).name(), " in entity ", mName);
        return nullptr;
    }

    if (name == "Unnamed Component")
        mComponents.push_back(std::move(std::make_unique<T>(typeid(T).name())));
    else
        mComponents.push_back(std::move(std::make_unique<T>(name)));
    
    mComponents.back().get()->mOwner = this;
    return static_cast<T*>(mComponents.back().get());
}

template<typename T>
T* Entity::GetComponent()
{
    auto it = std::find_if(mComponents.begin(), mComponents.end(), 
                           [](std::unique_ptr<Component>& component)
                           { return typeid(T) == typeid(*component); });

    if (it == mComponents.end()) {
      //  err::LogError("Attempted to get component of type: ", typeid(T).name(), " but it doesnt exist in entity: ", mName);
        return nullptr;
    }

    return static_cast<T*>(it->get());
}
}