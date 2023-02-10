#pragma once

namespace TwilliEngine
{
class System
{
public:
    System() : mIsEnabled(false) {}
    virtual ~System() {};

    virtual void StartFrame() = 0;
    virtual void Update(float dt) = 0;
    virtual void EndFrame() = 0;

    void Enable(bool flag = true) { mIsEnabled = flag; }
    void Disable() { mIsEnabled = false; }
  
    bool IsEnabled() const { return mIsEnabled; }

private:
    bool mIsEnabled;
};
}