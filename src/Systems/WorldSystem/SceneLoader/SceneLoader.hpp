#pragma once

namespace TwilliEngine {

class Scene
{
public:
    Scene() {}
    ~Scene() {}


private:

};

class SceneLoader
{
public:
    SceneLoader() {}
    ~SceneLoader() {}

private:

    std::unique_ptr<Scene> mLoadedScene;
};

} // namespace TwilliEngine