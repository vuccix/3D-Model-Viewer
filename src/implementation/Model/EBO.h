#pragma once

#include <glad/gl.h>
#include <vector>

class EBO {
public:
    EBO() = default;
   ~EBO();

    void init(const std::vector<GLuint>& indices);

    void bind() const;
    void unbind() const;
    void deleteEBO() const;

    GLuint getID() const { return id; }

private:
    GLuint id{};
};
