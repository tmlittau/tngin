#pragma once

#include <string>

namespace TAL {
    bool ReadFile(const char* fileName, std::string& outFile);

    void CustomFileError(const char* pFileName, unsigned int line, const char* pFileError);

    #define CUSTOM_FILE_ERROR(FileError) CustomFileError(__FILE__, __LINE__, FileError);
}