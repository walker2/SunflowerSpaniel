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
    std::shared_ptr<DialogueNode> nextNode;
    DIALOGUERESULT dialogueresult;
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

    void init(const char *objectResource)
    {
        tinyxml2::XMLDocument xmlDoc;
        tinyxml2::XMLError eResult = xmlDoc.LoadFile(objectResource);

        if (eResult != tinyxml2::XMLError::XML_SUCCESS)
        {
            printf("Failed to create object. Error: %i\n", eResult);
            return;
        }

        tinyxml2::XMLNode *pRoot = xmlDoc.FirstChild();

        if (pRoot == nullptr)
        {
            printf("Failed to find root. Error: %i\n", tinyxml2::XMLError::XML_ERROR_FILE_READ_ERROR);
            return;
        }
        tinyxml2::XMLElement *nodesNumberElement = pRoot->FirstChildElement("NodesNumber");

        if (nodesNumberElement == nullptr)
        {
            printf("Can't find a <NodesNumber>. Error: %i\n", tinyxml2::XMLError::XML_ERROR_FILE_READ_ERROR);
            return;
        }
        int numberOfNodes = 0;
        nodesNumberElement->QueryIntAttribute("n", &numberOfNodes);

        for (int i = 0; i < numberOfNodes; i++)
        {
            std::shared_ptr<DialogueNode> node = std::make_shared<DialogueNode>();
            m_dialogueNodes.push_back(node);
        }
        m_currentNode = m_dialogueNodes[0];

        for (tinyxml2::XMLElement *pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
        {
            std::string value = pNode->Value();
            if (value == "Node")
            {
                int n = 0;
                std::string nodeText;
                std::vector<std::string> options;

                pNode->QueryIntAttribute("n", &n);
                if (n > m_dialogueNodes.size())
                    return;

                for (tinyxml2::XMLElement *pChildNode = pNode->FirstChildElement(); pChildNode; pChildNode = pChildNode->NextSiblingElement())
                {
                    std::string childValue = pChildNode->Value();
                    if (childValue == "Text")
                    {
                        m_dialogueNodes[n]->text = pChildNode->GetText();
                    }
                    else if (childValue == "Option")
                    {
                        std::shared_ptr<DialogueNode> nextNode = nullptr;

                        int nextNumberOfNode = -1;
                        pChildNode->QueryIntAttribute("nextNode", &nextNumberOfNode);

                        if (nextNumberOfNode != -1)
                            nextNode = m_dialogueNodes[nextNumberOfNode];

                        DIALOGUERESULT actualResult;

                        std::string result = pChildNode->Attribute("result");
                        if (result == "continue")
                        {
                            actualResult = DIALOGUERESULT::CONTINUE;
                        } else if (result == "exit")
                        {
                            actualResult = DIALOGUERESULT::EXIT;
                        } else
                        {
                            actualResult = DIALOGUERESULT::ACCEPTQUEST;
                        }

                        m_dialogueNodes[n]->dialogueOptions.push_back(
                                DialogueOption(pChildNode->Attribute("text"),
                                               actualResult,
                                               nextNode));
                    }
                }
            }
        }



        /*std::shared_ptr<DialogueNode> node0 = std::make_shared<DialogueNode>("Hello, my friend");

        std::shared_ptr<DialogueNode> node1 = std::make_shared<DialogueNode>("After all of we've been through...");
        std::shared_ptr<DialogueNode> node2 = std::make_shared<DialogueNode>("Of course we are. Don't you remember?");
        std::shared_ptr<DialogueNode> node3 = std::make_shared<DialogueNode>("Who am I then?");
        std::shared_ptr<DialogueNode> node4 = std::make_shared<DialogueNode>("I can help you, but you can help me too before. Bring me my gun, i lost it in nearby ruins");
        std::shared_ptr<DialogueNode> node5 = std::make_shared<DialogueNode>("QUEST HAS STARTED");

        node0->dialogueOptions.push_back(DialogueOption("We are familiar?", DIALOGUERESULT::CONTINUE, node2));
        node0->dialogueOptions.push_back(DialogueOption("Get lost", DIALOGUERESULT::CONTINUE, node1));
        m_dialogueNodes.push_back(node0);

        m_currentNode = m_dialogueNodes[0];

        node1->dialogueOptions.push_back(DialogueOption("(exit dialogue)", DIALOGUERESULT::EXIT, nullptr));
        m_dialogueNodes.push_back(node1);

        node2->dialogueOptions.push_back(DialogueOption("Oh, it's you, i can see now...", DIALOGUERESULT::CONTINUE, node3));
        node2->dialogueOptions.push_back(DialogueOption("I'm sorry, but i can't remember anything", DIALOGUERESULT::CONTINUE, node4));
        m_dialogueNodes.push_back(node2);

        node3->dialogueOptions.push_back(DialogueOption("Father", DIALOGUERESULT::EXIT, nullptr));
        node3->dialogueOptions.push_back(DialogueOption("Teacher", DIALOGUERESULT::EXIT, nullptr));
        node3->dialogueOptions.push_back(DialogueOption("Uncle", DIALOGUERESULT::EXIT, nullptr));
        m_dialogueNodes.push_back(node3);

        node4->dialogueOptions.push_back(DialogueOption("Alright, i will help you", DIALOGUERESULT::ACCEPTQUEST, node5));
        node4->dialogueOptions.push_back(DialogueOption("I have a more important things to do", DIALOGUERESULT::EXIT, nullptr));
        m_dialogueNodes.push_back(node4);

        node5->dialogueOptions.push_back(DialogueOption("(exit dialogue)", DIALOGUERESULT::ACCEPTQUEST, nullptr));*/



    }

    void destroy();

    DIALOGUERESULT performDialogue()
    {
        if (m_dialogueNodes.empty())
            return DIALOGUERESULT::EXIT;

        ImGui::TextWrapped(m_currentNode->text.c_str());
        ImGui::Spacing();

        for (int i = 0; i < m_currentNode->dialogueOptions.size(); i++)
        {
            ImGui::Text("%d: ", i + 1);
            ImGui::SameLine();
            if (ImGui::Selectable(m_currentNode->dialogueOptions[i].text.c_str()))
            {
                // Check for end of the conversation
                if (m_currentNode->dialogueOptions[i].nextNode == nullptr)
                    return m_currentNode->dialogueOptions[i].dialogueresult;

                m_currentNode = m_currentNode->dialogueOptions[i].nextNode;
            }
        }

        return DIALOGUERESULT::CONTINUE;
    }

private:
    std::vector<std::shared_ptr<DialogueNode>> m_dialogueNodes;
    std::shared_ptr<DialogueNode> m_currentNode;

};

class DialogueComponent : public Component
{
public:
    DialogueComponent(GameObject* obj) : Component(obj)
            {}

    void update(GameObject *obj, float deltaTime) override
    {

    }

    void init(tinyxml2::XMLNode *pNode) override
    {
        // Can be added multiple filepaths for many dialoguetrees
        tinyxml2::XMLElement *pPathElement = pNode->FirstChildElement("FilePath");

        if (pPathElement)
        {
            std::string filePath = pPathElement->GetText();
            m_dialogueTree.init(filePath.c_str());
        }
    }

    void handleMessage(const Telegram &telegram) override
    {
        if (telegram.msg == Message::PLAYER_TALKED && telegram.receiver == this->getObject()->getID())
        {
            m_shouldDraw = true;
            m_disabledPlayer = ObjectFactory::instance().getObjectFromID(ObjectFactory::instance().getCurrentPlayerID());
            m_disabledPlayer->getComponent<PlayerInputComponent>()->enable(false);
        }
    }
    void draw()
    {
        if (m_shouldDraw)
        {
            bool open = true;
            ImGui::SetNextWindowPos(ImVec2(420, 480));
            ImGui::SetNextWindowSize(ImVec2(500, 200));
            if (!ImGui::Begin("Overlay", &open, ImVec2(0, 0), 0.4f,
                              ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings))
            {
                ImGui::End();
                return;
            }

            auto result = m_dialogueTree.performDialogue();
            if (result != DIALOGUERESULT::CONTINUE)
            {
                m_shouldDraw = false;
                m_disabledPlayer->getComponent<PlayerInputComponent>()->enable(true);
            }
            ImGui::End();
        }
    }

private:
    DialogueTree m_dialogueTree;
    bool m_shouldDraw = false;
    std::shared_ptr<GameObject> m_disabledPlayer;

};


#endif
