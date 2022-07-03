#include "Renderer.h"

#include <iostream>

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

void GLCheckError()
{
    while(GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
    }
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    
    GLClearError();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr); //6 Refers to # of indcies
    /* Swap front and back buffers */
    GLCheckError();

}
