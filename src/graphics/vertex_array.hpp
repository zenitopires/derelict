#pragma once
#include <stdint.h>
#include <glad/glad.h>
#include <memory>
#include "shader.hpp"

namespace derelict {
struct Data {
    Data(const float *vertices, const unsigned int *indices, uint32_t vertexCount, uint32_t indexCount) {
        this->vertexCount = vertexCount;
        this->indexCount  = indexCount;
        this->vertexData = vertices;
        this->indexData = indices;
    }

    const float *vertexData;
    const unsigned int* indexData;
    int vertexCount;
    int indexCount;
};

class VertexArray {
public:
    explicit VertexArray(std::shared_ptr<Data> data);
    ~VertexArray();
    // Attribute defines the data layout for the vertex array object.
    void Attribute();
    // Bind binds the provided vertex array object.
    void Bind();
    // Unbind unbinds a previously bounded vertex array object.
    void Unbind();
    // GetShader returns the shader id associated with vertex array.
    uint32_t GetShaderId() {
        return shader->GetId();
    }
    int GetVertexCount() {
        return data->vertexCount;
    }
    int GetIndexCount() {
        return data->indexCount;
    }

private:
    std::shared_ptr<Data> data;
    std::shared_ptr<Shader> shader;
    uint32_t vertexBuffer;
    uint32_t indexBuffer;
    uint32_t id;
};
}
