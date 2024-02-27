#pragma once

#include <string>
#include <glm/glm.hpp>

namespace TAL {
    bool ReadFile(const char* fileName, std::string& outFile);

    void CustomFileError(const char* pFileName, unsigned int line, const char* pFileError);

    void BuildCircle(std::vector<glm::vec3>& vertices, float radius, int vCount);

    #define CUSTOM_FILE_ERROR(FileError) CustomFileError(__FILE__, __LINE__, FileError);
}