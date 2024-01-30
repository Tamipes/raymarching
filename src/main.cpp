#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"

int main(void)
{
  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(640, 480, "Demo", NULL, NULL);
  if (!window)
  {
    std::cout << "Failed to create GLFW window!" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  // turn off vsync
  // glfwSwapInterval(0);

  // gladLoadGL();
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // Might not need this, but ju know...

  // quad infos
  float positions[] = {
      -1.0f, -1.0f, // 0
      1.0f, -1.0f,  // 1
      1.0f, 1.0f,   // 2
      -1.0f, 1.0f   // 3
  };

  unsigned int indeces[] = {
      0, 1, 2,
      2, 3, 0};

  // shader and buffers
  Shader *shader = new Shader(RESOURCES_PATH "/shaders/quad.vert", RESOURCES_PATH "/shaders/quad.frag");

  VAO *vao = new VAO();
  vao->Bind();
  VBO *vbo = new VBO(positions, 8 * sizeof(float));
  EBO *ebo = new EBO(indeces, 6 * sizeof(unsigned int));
  vao->LinkVBO(*vbo, 0);

  glDisable(GL_DEPTH_TEST);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    int width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);

    shader->Activate();
    vao->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  delete vao;
  delete vbo;
  delete ebo;
  delete shader;

  return 0;
}