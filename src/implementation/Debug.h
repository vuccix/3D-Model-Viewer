#pragma once

#include <glad/gl.h>
#include <iostream>

inline const char* glErrorToString(const GLenum err) {
    switch (err) {
        case GL_NO_ERROR:
            return "GL_NO_ERROR";
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";
        default:
            return "Unknown OpenGL error.";
    }
}

inline void checkGLError(const char* txt) {
    if (const GLenum e = glGetError(); e != GL_NO_ERROR)
        std::cerr << "Error after " << txt << ": " << glErrorToString(e) << '\n';
}
