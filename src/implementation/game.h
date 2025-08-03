#pragma once

#include "Shader.h"
#include "Model/Model.h"
#include "Camera.h"

class Game {
public:
    Game();

    void render();
    void inputs();
    void onResize();

private:
    Shader m_shader;
    Camera m_camera;
	Model  m_model;
};
