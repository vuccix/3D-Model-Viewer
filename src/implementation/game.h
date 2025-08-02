#pragma once

#include <glad/gl.h>
#include "Shader.h"
#include "Model/Model.h"
#include "Camera.h"

class Game {
public:
    Game();

    void render();
    void inputs();

private:
    Shader m_shader;
    Camera m_camera;
	Model  m_model;
};
