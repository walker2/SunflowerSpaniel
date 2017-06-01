#ifndef SUNFLOWERSPANIEL_DIALOGUECOMPONENT_H
#define SUNFLOWERSPANIEL_DIALOGUECOMPONENT_H

#include <vector>
#include <string>
#include <ImGUI/imgui.h>
#include "Component.h"
#include "../Messaging/Messages.h"
#include "../ObjectFactory/GameObject.h"
#include "../ObjectFactory/ObjectFactory.h"

enum DIALOGUERESULT
{
    EXIT = 0, CONTINUE, ACCEPTQUEST
};

class DialogueNode;

class DialogueOption
{
public:
    DialogueOption(std::string _text, DIALOGUERESULT _dialogueresult, std::shared_ptr<DialogueNode> _nextNode)
            : text(_text), dialogueresult(_dialogueresult), nextNode(_nextNode)
    {}

    std::string text;
    DIALOGUERESULT dialogueresult;
    std::shared_ptr<DialogueNode> nextNode;
};

class DialogueNode
{
public:
    DialogueNode()
    {}

    DialogueNode(std::string _text)
            : text(_text)
    {}

    std::string text;
    std::vector<DialogueOption> dialogueOptions;
};

class DialogueTree
{
public:
    DialogueTree()
    {}

    void init(const char *objectResource);

    void destroy();

    DIALOGUERESULT performDialogue();

private:
    std::vector<std::shared_ptr<DialogueNode>> m_dialogueNodes;
    std::shared_ptr<DialogueNode> m_currentNode;

};

class DialogueComponent : public Component
{
public:
    DialogueComponent(GameObject *obj) : Component(obj)
    {}

    void update(GameObject */*obj*/, float /*deltaTime*/) override
    {}

    void init(tinyxml2::XMLNode *pNode) override;

    void handleMessage(const Telegram &telegram) override;

    void draw();

private:
    DialogueTree m_dialogueTree;
    bool m_shouldDraw = false;
    std::shared_ptr<GameObject> m_disabledPlayer;

};


#endif
