#include <string>

#include <GL/glew.h>


namespace TAL {
    class Texture {
        public:
            Texture(GLenum TextureTarget, const std::string& FileName);

            bool Load();

            void Bind(GLenum TextureUnit);

        private:
            std::string _fileName;
            GLenum _textureTarget;
            GLuint _textureObj;
    };
}