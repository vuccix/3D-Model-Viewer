#include "Game.h"
#include <stb/stb_image.h>

#define VERTEX_PATH "../src/shaders/default.vert"
#define FRAG_PATH   "../src/shaders/default.frag"
#define IMAGE_PATH  "../src/resources/Bricks_D.jpg"

Game::Game() : shader(VERTEX_PATH, FRAG_PATH),
        texture(IMAGE_PATH, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE) {
    vao.bind();

    vbo.init(vertices, sizeof(vertices));
    ebo.init(indices, sizeof(indices));

    VAO::linkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), nullptr);
    VAO::linkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    VAO::linkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));

    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    Texture::texUnit(shader, "tex0", 0);
}

void Game::render() const {
    shader.use();
    texture.bind();
    vao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
