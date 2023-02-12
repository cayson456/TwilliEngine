namespace TwilliEngine
{
template <typename T>
std::unique_ptr<T> Singleton<T>::sInstance = nullptr;

template <typename T>
template <typename ...Args>
inline void Singleton<T>::Initialize(Args&& ...args)
{
    if (sInstance)
        err::LogError("WARNING: Attempted to initialize an already instantiated singleton!");
    else
        sInstance = std::make_unique<T>(args...);
}

template <typename T>
void Singleton<T>::Shutdown()
{
    if (!sInstance)
        err::LogError("WARNING: Attempted to an destroy an uninitialized singleton!");

    sInstance.reset(nullptr);
}

template <typename T>
T* Singleton<T>::GetInstance()
{
    return sInstance.get();
}

}