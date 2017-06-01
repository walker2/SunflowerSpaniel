#ifndef SUNFLOWERSPANIEL_INVENTORY_H
#define SUNFLOWERSPANIEL_INVENTORY_H


#include <ImGUI/imgui.h>
#include "../ObjectFactory/GameObject.h"
#include "../Components/DogAIComponent.h"
#include "../Components/InventoryComponent.h"
#include "../Components/HumanAIComponent.h"

class InventoryGUI
{

public:
    InventoryGUI()
    {
        position = ImVec2(832, 264);
    }

    void begin();

    void draw(std::shared_ptr<GameObject> player);

    void end();

private:
    ImVec2 position;
};


#endif
