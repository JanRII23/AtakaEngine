#include <DX3D/Core/InputSystem.h> 
#include <DX3D/Core/InputListener.h>
#include <Windows.h>

dx3d::InputSystem::InputSystem()
{
}

dx3d::InputSystem::~InputSystem()
{
}

void dx3d::InputSystem::update()
{
    if (::GetKeyboardState(m_keys_state))
    {
        for (ui32 i = 0; i < 256; i++)
        {
            //NOTE: KEY IS DOWN
            if (m_keys_state[i] & 0x80)
            {
                std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.begin();

                while (it != m_map_listeners.end())
                {
                    it->second->onKeyDown(i);
                    ++it;
                }
            }
            //NOTE: KEY IS UP
            else
            {
                if (m_keys_state[i] != m_old_keys_state[i])
                {
                    std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.begin();

                    while (it != m_map_listeners.end())
                    {
                        it->second->onKeyUp(i);
                        ++it;
                    }
                }
            }
        }
        //NOTE: stores current keys state to old keys state buffer
        ::memcpy(m_old_keys_state, m_keys_state, sizeof(uc8) * 256);
    }
}

void dx3d::InputSystem::addListener(InputListener* listener)
{
    m_map_listeners.insert(std::make_pair<InputListener*, InputListener*>
        (std::forward<InputListener*>(listener), std::forward<InputListener*>(listener)));
}

void dx3d::InputSystem::removeListener(InputListener* listener)
{
    std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.find(listener);

    if (it != m_map_listeners.end())
    {
        m_map_listeners.erase(it);
    }
}

dx3d::InputSystem* dx3d::InputSystem::get()
{
    static InputSystem system;
    return &system;
}
