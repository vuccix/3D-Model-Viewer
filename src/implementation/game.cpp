#include "Game.h"
#include <iostream>

#define VERTEX_PATH "../src/shaders/default.vert"
#define FRAG_PATH   "../src/shaders/default.frag"

Game::Game() : shader(VERTEX_PATH, FRAG_PATH) {
    std::cout << "init\n";
    vao.bind();

    vbo.init(vertices, sizeof(vertices));
    ebo.init(indices, sizeof(indices));

    vao.linkVBO(vbo, 0);

    vao.unbind();
    vbo.unbind();
    ebo.unbind();
}

void Game::render() const {
    shader.use();
    vao.bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);
}
