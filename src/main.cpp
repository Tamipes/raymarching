#include <glad/glad.h>

#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "openglDebug.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "shaderClass.h"

#include "../eng/input/clb.h"

void mouseCallback(GLFWwindow* window, int button, int action, int mods){
  std::cout<<"Im from the program" << std::endl;
}

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

  GLFWwindow *window = glfwCreateWindow(1600, 900, "Demo", NULL, NULL);
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
  cms::clb::SetupCLB(window,nullptr);
  cms::clb::SetMouseButton(window,mouseCallback);
  std::cout << "after clb" << std::endl;
  
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

  VAO* vao = new VAO(); 
  VBO* vbo = new VBO(positions,12 * sizeof(float) );
  vao->LinkVBO(*vbo,0 );
  
  EBO* ebo = new EBO(indeces,sizeof(indeces));

  
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
