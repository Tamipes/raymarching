#include <glad/glad.h>

#include "openglDebug.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "shaderClass.h"

int main(void)
{
  if (!glfwInit())
    return -1;

#pragma region report opengl errors to std
  // enable opengl debugging output.
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#pragma endregion

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(640, 480, "Demo", NULL, NULL);
  if (!window)
  {
    std::cout << "Failed to create GLFW window!" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGL())
  {
    std::cout << "Failed to initialize OpenGL context" << std::endl;
    return -1;
  }
  // turn off vsync
  // glfwSwapInterval(0);

#pragma region report opengl errors to std
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(glDebugOutput, 0);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr,
                        GL_TRUE);
#pragma endregion

  // quad infos
  float positions[] = {
      -1.0f, -1.0f, 0.0f, // 0
      1.0f, -1.0f, 0.0f,  // 1
      1.0f, 1.0f, 0.0f,   // 2
      -1.0f, 1.0f, 0.0f   // 3
  };

  unsigned int indeces[] = {0, 1, 2, 2, 3, 0};

  // shader and buffers
  Shader *shader = new Shader(RESOURCES_PATH "/shaders/quad.vert",
                              RESOURCES_PATH "/shaders/quad.frag");
  
  unsigned int vao;
  glGenVertexArrays(1,&vao);
  glBindVertexArray(vao);

  unsigned int vbo;
  glGenBuffers(1,&vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER,12 * sizeof(float), positions,GL_STATIC_DRAW);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),0);
  glEnableVertexAttribArray(0);

  unsigned int ibo;
  glGenBuffers(1,&ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,6* sizeof(unsigned int), indeces,GL_STATIC_DRAW);  
  
  glDisable(GL_DEPTH_TEST);
  

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    int width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);

    shader->Activate();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  delete shader;

  return 0;
}
