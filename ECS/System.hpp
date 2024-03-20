#pragma once

#include "Component.hpp"
#include "Entity.hpp"


#include <vector>

class World;

class SystemBase
{
public:
    SystemBase() = default;
    virtual ~SystemBase() = default;
    SystemBase(const SystemBase &) = default;
    SystemBase &operator=(const SystemBase &) = default;
    SystemBase(SystemBase &&) = default;
    SystemBase &operator=(SystemBase &&) = default;

    // Executed once at the start of the application
    virtual void Init() = 0;

    // Executed once per frame
    virtual void Update() = 0;

    // Executed once per frame
    virtual void Render() = 0;

    void RegisterWorld(World *world) { world = world; }

    void RegisterEntity(EID_TYPE const &entity_id) { m_entities.push_back(entity_id); }

    void UnregisterEntity(EID_TYPE const &entity_id)
    {
        auto it = std::find(m_entities.begin(), m_entities.end(), entity_id);
        if (it != m_entities.end())
        {
            m_entities.erase(it);
        }
    }

    Signature GetSignature() const { return m_signature; }

protected:
    std::vector<EID_TYPE> m_entities;
    Signature m_signature;
    World *m_world;
};

template<typename ... ComponentType>
class System : public SystemBase
{
public:
    System() : SystemBase()
    {
        (m_signature.set(GetComponentType<ComponentType>()), ...);
    }
};