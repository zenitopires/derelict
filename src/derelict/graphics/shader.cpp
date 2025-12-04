#include <derelict/graphics/shader.hpp>
#include <fstream>
#include <glad/glad.h>
#include <derelict/logging/logger.hpp>

namespace derelict {
    Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
        uint32_t vertexShader = createShader(vertexShaderPath, ShaderType::VertexShader);
        uint32_t fragmentShader = createShader(fragmentShaderPath, ShaderType::FragmentShader);
        uint32_t shader = glCreateProgram();
        glAttachShader(shader, vertexShader);
        glAttachShader(shader, fragmentShader);
        glLinkProgram(shader);
        int program_linked;
        glGetProgramiv(shader, GL_LINK_STATUS, &program_linked);
        if (program_linked != GL_TRUE)
        {
            GLsizei log_length = 0;
            GLchar message[1024];
            glGetProgramInfoLog(shader, 1024, &log_length, message);
            logError("Error: %s", message);
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        logDebug("Created shader program, id: {}", shader);
        id = shader;
    }

    Shader::~Shader() {
        logDebug("Shader deleted!");
        glDeleteProgram(id);
    }

    void Shader::Use() {
        glUseProgram(id);
    }

    void Shader::Unuse() {
        glUseProgram(0);
    }

    uint32_t Shader::GetId() {
        return id;
    }

    uint32_t Shader::createShader(const std::string& shaderSrcPath, ShaderType shaderType) {
        logDebug("Entered createShader.");
        logDebug("Attempting to open shader file at {}.", shaderSrcPath.c_str());

        std::ifstream file(shaderSrcPath);
        if (!file.is_open()) {
            logError("Failed to open shader file: {}", shaderSrcPath.c_str());
            return 0;
        }

        std::string source((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        file.close();

        if (source.empty()) {
            logError("Shader file was empty: {}", shaderSrcPath.c_str());
            return 0;
        }

        GLenum glType;
        switch (shaderType) {
            case ShaderType::VertexShader:
                glType = GL_VERTEX_SHADER;
                break;
            case ShaderType::FragmentShader:
                glType = GL_FRAGMENT_SHADER;
                break;
            default:
                logError("Shader type not supported!");
                return 0;
        }

        uint32_t shader = glCreateShader(glType);
        const char* src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
            logError("Shader compile error ({}): {}", shaderSrcPath.c_str(), infoLog);
            glDeleteShader(shader);
            return 0;
        }
        return shader;
    }
}
