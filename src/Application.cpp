//  main.cpp
//  pong3
//
//  Created by Xander on 10/8/20.
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"

int main(void)
{
    
    
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //FOR MAC
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //PREVENTS RESIZING
    
    
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    
    int screenWidth, screenHeight; // FOR MAC
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight); // FOR MAC
    
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
        std::cout << "ERRORs" << std::endl;
    
    glViewport(0, 0, screenWidth, screenHeight); // FOR HIGH DENISTY SCREEN MAC
    
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
    float positions[] = {
       -0.5f,  -0.5f,
        0.5f,  -0.5f,
        0.5f,   0.5f,
       -0.5f,   0.5f,
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    //unsigned int vertexArrayID; //LINUX MAC START
    //glGenVertexArrays(1, &vertexArrayID);
    //glBindVertexArray(vertexArrayID); //LINUX MAC END
    
  
    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        
    VertexBufferLayout layout;
    layout.Push<float>(2);
        va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);
    
        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    
    va.UnBind();
    shader.Unbind();
    vb.Unbind();
    ib.Unbind();
    
        Renderer renderer;
        
    float r = 0.0f;
    float increment = 0.05f;
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        
        renderer.Clear();
        
        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f); // must be called after shader glUseProgram is called
        
        renderer.Draw(va, ib, shader);
        
        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;
        
        r += increment;
        
        
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        

    }

    }
    
    glfwTerminate();
    return 0;
}
