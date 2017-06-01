#include "DialogueComponent.h"

void DialogueTree::init(const char *objectResource)
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
            if (n > (int) m_dialogueNodes.size())
                return;

            for (tinyxml2::XMLElement *pChildNode = pNode->FirstChildElement(); pChildNode; pChildNode = pChildNode->NextSiblingElement())
            {
                std::string childValue = pChildNode->Value();
                if (childValue == "Text")
                {
                    m_dialogueNodes[n]->text = pChildNode->GetText();
                } else if (childValue == "Option")
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
}

DIALOGUERESULT DialogueTree::performDialogue()
{
    if (m_dialogueNodes.empty())
        return DIALOGUERESULT::EXIT;

    ImGui::TextWrapped(m_currentNode->text.c_str());
    ImGui::Spacing();

    for (unsigned int i = 0; i < m_currentNode->dialogueOptions.size(); i++)
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

void DialogueComponent::init(tinyxml2::XMLNode *pNode)
{
    // Can be added multiple filepaths for many dialoguetrees
    tinyxml2::XMLElement *pPathElement = pNode->FirstChildElement("FilePath");

    if (pPathElement)
    {
        std::string filePath = pPathElement->GetText();
        m_dialogueTree.init(filePath.c_str());
    }
}

void DialogueComponent::handleMessage(const Telegram &telegram)
{
    if (telegram.msg == Message::PLAYER_TALKED && telegram.receiver == this->getObject()->getID())
    {
        m_shouldDraw = true;
        m_disabledPlayer = ObjectFactory::instance().getObjectFromID(ObjectFactory::instance().getCurrentPlayerID());
        m_disabledPlayer->getComponent<PlayerInputComponent>()->enable(false);
    }
}

void DialogueComponent::draw()
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
