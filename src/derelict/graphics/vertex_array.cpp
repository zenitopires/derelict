#include <derelict/graphics/vertex_array.hpp>
#include <derelict/logging/logger.hpp>

namespace derelict {
VertexArray::VertexArray(std::shared_ptr<Data> data) {
    logDebug("Entered VertexArray constructor.");
    this->data = std::move(data);
    auto shader = std::make_shared<Shader>("assets/shaders/defaults/vertex.vert",
        "assets/shaders/defaults/fragment.frag");
    this->shader = std::move(shader);
    // Create vertex arrays, buffers
    glGenVertexArrays(1, &id);
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &indexBuffer);
    // Switch context to vao and associate buffers and their data with it
    glBindVertexArray(id);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, this->data->vertexCount * sizeof(float), (const float*)this->data->vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->data->indexCount * sizeof(unsigned int), (const unsigned int*)this->data->indexData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    logDebug("Created vertex array object, id: {}!", id);
}

VertexArray::~VertexArray() {
    logDebug("Vertex array object deleted, id: {}!", id);
    glDeleteVertexArrays(1, &id);
    glDeleteProgram(shader->GetId());
}

void VertexArray::Attribute() {
}

void VertexArray::Bind() {
    // logDebug()
    shader->Use();
    glBindVertexArray(id);
}

void VertexArray::Unbind() {
    shader->Unuse();
    glBindVertexArray(0);
}
}
