//
// Created by walker2 on 5/4/17.
//

#include "DebugGUI.h"

void DebugGUI::begin()
{
    bool open = true;
    ImGui::SetNextWindowPos(position);
    if (!ImGui::Begin("Fixed Overlay", &open, ImVec2(0, 0), 0.3f,
                      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                      ImGuiWindowFlags_NoSavedSettings))
    {
        ImGui::End();
        return;
    }
}

void DebugGUI::draw(bool &renderDebug, Falcon::BasicLight &mouseLight, Falcon::BasicLight &playerLight,
                    Falcon::Camera2D &camera, std::shared_ptr<GameObject> &currentPlayer, float m_time)
{
    if (ImGui::Button("Debug mode"))
    {
        renderDebug = !renderDebug;
    }

    ImGui::SameLine();

    if (ImGui::Button("Random mouse color"))
    {
        std::mt19937 rng(time(0));
        std::uniform_int_distribution<int> color(0, 255);
        mouseLight.color.r = static_cast<GLubyte>(color(rng));
        mouseLight.color.g = static_cast<GLubyte>(color(rng));
        mouseLight.color.b = static_cast<GLubyte>(color(rng));
    }
    ImGui::Separator();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
    ImGui::Text("Mouse position (%.2f, %.2f)",
                camera.screenToWorld(Falcon::InputManager::instance().getMouseCoords()).x,
                camera.screenToWorld(Falcon::InputManager::instance().getMouseCoords()).y);
    ImGui::Text("Player position (%.2f, %.2f)", currentPlayer->getComponent<BodyComponent>()->getPosition().x,
                currentPlayer->getComponent<BodyComponent>()->getPosition().y);
    ImGui::Text("Time %.5f", m_time);
    ImGui::Text("Player light alpha %i", playerLight.color.a);
    ImGui::Text("Number of objects in world %li", ObjectFactory::instance().getNumberOfGameObjects());
    ImGui::Text("RAM usage by app %i kbytes", getRamUsage());

}

void DebugGUI::end()
{
    ImGui::End();
}

int DebugGUI::getRamUsage()
{ //Note: this value is in KB!
    FILE *file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL)
    {
        if (strncmp(line, "VmRSS:", 6) == 0)
        {
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int DebugGUI::parseLine(char *line)
{
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = (int) strlen(line);
    const char *p = line;
    while (*p < '0' || *p > '9') p++;
    line[i - 3] = '\0';
    i = atoi(p);
    return i;
}
