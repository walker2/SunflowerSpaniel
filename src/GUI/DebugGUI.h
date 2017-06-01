#ifndef SUNFLOWERSPANIEL_DEBUGGUI_H
#define SUNFLOWERSPANIEL_DEBUGGUI_H

#include <ImGUI/imgui.h>
#include <Falcon/2D/Lights/BasicLight.h>
#include <Falcon/2D/Camera/Camera2D.h>
#include <Falcon/InputOutput/InputManager.h>
#include "../ObjectFactory/GameObject.h"
#include "../ObjectFactory/ObjectFactory.h"

class DebugGUI
{
public:
    DebugGUI()
    {
        position = ImVec2(10, 10);
    }

    void begin();

    void draw(bool &renderDebug, Falcon::BasicLight &mouseLight,
              Falcon::BasicLight &playerLight, Falcon::Camera2D &camera,
              std::shared_ptr<GameObject> &currentPlayer, float m_time);

    void end();

private:

    int getRamUsage();

    int parseLine(char *line);

private:
    ImVec2 position;

};


#endif
