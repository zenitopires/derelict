#include <derelict/graphics/vertex_array.hpp>
#include <derelict/logging/logger.hpp>
#include <glad/glad.h>

namespace derelict {
VertexArray::VertexArray(std::shared_ptr<Data> data) {
    logDebug("Entered VertexArray constructor.");
    this->data = std::move(data);
    // Create vertex arrays, buffers
    glGenVertexArrays(1, &id);
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &indexBuffer);
    // Switch context to vao and associate buffers and their data with it
    glBindVertexArray(id);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(this->data->vertexCount * sizeof(float)), this->data->vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(this->data->indexCount * sizeof(unsigned int)), this->data->indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    logDebug("Created vertex array object, id: {}!", id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);
}

// void VertexArray::Attribute() {
// }

void VertexArray::Bind() const {
    // logDebug()
    glBindVertexArray(id);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}
}
