// #include <iostream>
// #include "tami.h"
// #include "GlFW/glfw3.h"

// int main() {
//   int a = 1;
//   int b = 2;
//   int c = func(a,b);
//   std::cout << "Var is: "<<c << std::endl;
//   return 0;
// }
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
  GLFWwindow *window;
  std::cout << "modified" << std::endl;
  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    int width = 0, height = 0;

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(0, 1);
    glColor3f(0, 1, 0);
    glVertex2f(1, -1);
    glColor3f(0, 0, 1);
    glVertex2f(-1, -1);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
