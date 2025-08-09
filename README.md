# 3D Model Viewer

A real-time GLTF model viewer built with modern C++ and OpenGL.
This project focuses on loading and displaying 3D models with physically plausible shading and interactive camera controls, ideal for inspecting GLTF assets.

## Features

- **GLTF 2.0 model loading**
- **Full texture support**
  - Diffuse (albedo) map
  - Specular map (Phong reflectance model)
  - Normal mapping
  - Ambient Occlusion (AO) textures
- **Basic Phong shading for realistic lighting**
- **Free-fly camera controls:**
  - <kbd>WASD</kbd> movement
  - Mouse look (when holding the right mouse button)

## TODO

- Add a simple GUI
- Replace Phong with PBR shader (metallic-roughness workflow)
- Delta time-based movement (fix movement speed across framerates)
- Add a material system (organized data structure for shaders/textures/uniforms)
- ...

## Dependencies

- C++20 (or later)
- OpenGL 3.3
- CMake 3.20+
- [GLAD](https://github.com/Dav1dde/glad)
- [GLFW](https://github.com/glfw/glfw)
- [GLM](https://github.com/g-truc/glm)
- [stb_image](https://github.com/nothings/stb)
- [cgltf](https://github.com/jkuhlmann/cgltf)

[//]: # (- ImGui)
