#ifndef SCENE_HPP
#define SCENE_HPP

class Scene
{
public:
    Scene() {}
    virtual ~Scene() {}
    
    virtual void init() = 0;
    virtual void render() = 0;
    virtual void update() = 0;
    virtual void fixedUpdate(float dt) = 0;
    virtual void erase() = 0;
};

#endif
