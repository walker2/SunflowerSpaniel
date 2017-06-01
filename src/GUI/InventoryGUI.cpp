//
// Created by walker2 on 5/4/17.
//

#include "InventoryGUI.h"

void InventoryGUI::begin()
{
    bool open = true;
    ImGui::SetNextWindowPos(position);
    if (!ImGui::Begin("Overlay", &open, ImVec2(0, 0), 0.4f,
                      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize |
                      ImGuiWindowFlags_NoSavedSettings))
    {
        ImGui::End();
        return;
    }
}

void InventoryGUI::draw(std::shared_ptr<GameObject> player)
{
    std::shared_ptr<NeedsComponent> needs = player->getComponent<DogAIComponent>();
    if (!needs)
    {
        needs = player->getComponent<HumanAIComponent>();
    }

    auto inventory = player->getComponent<InventoryComponent>();

    ImGui::Text("INVENTORY");
    ImGui::Separator();

    ImGui::Text("Thirst");
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    static float progressThirst = 0.0f;
    progressThirst = 1 - needs->getThirst();
    ImGui::ProgressBar(progressThirst, ImVec2(0.0f,0.0f));

    ImGui::Text("Hunger");
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    static float progressHunger = 0.0f;
    progressHunger = 1 - needs->getHunger();
    ImGui::ProgressBar(progressHunger, ImVec2(0.0f,0.0f));

    ImGui::Text("Fatigue");
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    static float progressFatigue = 0.0f;
    progressFatigue = 1 - needs->getFatigue();
    ImGui::ProgressBar(progressFatigue, ImVec2(0.0f,0.0f));

    ImGui::Separator();
    ImGui::Text("Items");
    static std::string nodeName = "NODE";
    auto items = inventory->getItems();

    static bool selected[16] = { false };
    int i = 0;
    for (auto item : items)
    {
        ImGui::PushID(i++);
        nodeName = item.first;

        ImGui::Selectable(nodeName.c_str(), &selected[i]);

        if (ImGui::BeginPopupContextItem("item context menu"))
        {
            if (ImGui::Selectable("Use"))
            {
                //SHOULD BE ASKED FROM THE OBJECT
                inventory->removeItem(item.first);
                needs->decreaseThirst(0.3f);
                needs->decreaseHunger(0.05f);
            }
            if (ImGui::Selectable("Drop"))
            {
                inventory->removeItem(item.first);
            }
            ImGui::EndPopup();
        }
        ImGui::SameLine(300);
        ImGui::Text("total: %d", item.second);

        ImGui::PopID();
    }

}

void InventoryGUI::end()
{
    ImGui::End();
}
