#include "renderer/shader.h"      // matches your folder/name casing
#include <glad/glad.h>            // must be before GLFW if you ever include it here
#include <iostream>
#include <unordered_map>
#include <glm/gtc/type_ptr.hpp>

namespace {
    // Small cache so repeated uniform sets don’t call glGetUniformLocation every time
    // One cache per program ID.
    struct UniformCache {
        std::unordered_map<std::string, int> locs;
    };

    // Associate a cache with each program ID
    static std::unordered_map<unsigned int, UniformCache> g_uniformCaches;
}

Shader::Shader(const char* vertexSrc, const char* fragmentSrc) {
    // 1) compile individual shaders
    unsigned int vs = CompileShader(GL_VERTEX_SHADER,   vertexSrc);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    // 2) link program
    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vs);
    glAttachShader(m_RendererID, fs);
    glLinkProgram(m_RendererID);

    int linked = 0;
    glGetProgramiv(m_RendererID, GL_LINK_STATUS, &linked);
    if (!linked) {
        char info[1024];
        glGetProgramInfoLog(m_RendererID, sizeof(info), nullptr, info);
        std::cerr << "[Shader] Link failed:\n" << info << std::endl;
        glDeleteProgram(m_RendererID);
        m_RendererID = 0;
    }

    // 3) we can delete the shader objects after linking
    glDetachShader(m_RendererID, vs);
    glDetachShader(m_RendererID, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() {
    if (m_RendererID) {
        glDeleteProgram(m_RendererID);
        g_uniformCaches.erase(m_RendererID);
    }
}

void Shader::Bind() const {
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

unsigned int Shader::CompileShader(unsigned int type, const char* source) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int compiled = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        char info[1024];
        glGetShaderInfoLog(id, sizeof(info), nullptr, info);
        std::cerr << "[Shader] Compilation failed ("
                  << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
                  << "):\n" << info << std::endl;
    }
    return id;
}

int Shader::GetUniformLocation(const std::string& name) const {
    auto& cache = g_uniformCaches[m_RendererID].locs;
    if (auto it = cache.find(name); it != cache.end())
        return it->second;

    int loc = glGetUniformLocation(m_RendererID, name.c_str());
    if (loc == -1) {
        // Not necessarily fatal—GL can optimize uniforms away if unused
        // std::cerr << "[Shader] Warning: uniform '" << name << "' not found/active\n";
    }
    cache[name] = loc;
    return loc;
}

void Shader::SetUniform1i(const std::string& name, int value) {
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value) {
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& m) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(m));
}