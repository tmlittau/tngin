#include <tngin/rendering/graphics_utils.h>

#include <iostream>
#include <fstream>
#include <assert.h>

namespace TAL {
    bool ReadFile(const char* pFileName, std::string& outFile)
    {
        std::ifstream f(pFileName);

        bool ret = false;

        if (f.is_open()) {
            std::string line;
            while (getline(f, line)) {
                outFile.append(line);
                outFile.append("\n");
            }

            f.close();

            ret = true;
        }
        else {
            CUSTOM_FILE_ERROR(pFileName);
        }

        return ret;
    }

    void CustomFileError(const char* pFileName, unsigned int line, const char* pFileError)
    {
        #ifdef _WIN32
            char msg[1000];
            _snprintf_s(msg, sizeof(msg), "%s:%d: unable to open file `%s`", pFileName, line, pFileError);
            MessageBoxA(NULL, msg, NULL, 0);
        #else
            fprintf(stderr, "%s:%d: unable to open file `%s`\n", pFileName, line, pFileError);
        #endif
    }

}