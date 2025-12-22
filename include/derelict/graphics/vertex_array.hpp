#pragma once
#include <memory>

namespace derelict {
struct Data {
    Data(const float *vertices, const unsigned int *indices, const uint32_t vertexCount, const uint32_t indexCount)
    : vertices(vertices), indices(indices), vertexCount(vertexCount), indexCount(indexCount)  {}

    const float *vertices;
    const unsigned int* indices;
    uint32_t vertexCount;
    uint32_t indexCount;
};

class VertexArray {
public:
    explicit VertexArray(std::shared_ptr<Data> data);
    ~VertexArray();
    // Attribute defines the data layout for the vertex array object.
    // void Attribute();

    // Bind the vertex array object.
    void Bind() const;
    // Unbind the vertex array object.
    // *Be careful in mixing this Unbind with other VAO Unbind, because of the nature of OpenGL, you may inadvertently unbind another VAO.*
    void Unbind() const;
    // Get the vertex count associated with the vertex array.
    uint32_t GetVertexCount() const {
        return data->vertexCount;
    }
    // Get the index count associated with the vertex array.
    uint32_t GetIndexCount() const {
        return data->indexCount;
    }

private:
    std::shared_ptr<Data> data;
    uint32_t vertexBuffer;
    uint32_t indexBuffer;
    uint32_t id;
};
}
