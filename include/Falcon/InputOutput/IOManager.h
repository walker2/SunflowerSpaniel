#ifndef FALCONLATINUM_IOMANAGER_H
#define FALCONLATINUM_IOMANAGER_H

#include <vector>
#include <string>

namespace Falcon
{
    class IOManager
    {
    public:
        static bool readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer);
        static bool readFileToBuffer(std::string filePath, std::string& buffer);
    };
}

#endif
