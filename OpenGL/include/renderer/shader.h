#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform1i(const std::string& name, int value);
    void SetUniform1f(const std::string& name, float value);
    void SetUniformMat4(const std::string& name, const glm::mat4& m);

private:
    unsigned int m_RendererID = 0;

    unsigned int CompileShader(unsigned int type, const char* source);
    int GetUniformLocation(const std::string& name) const;
};