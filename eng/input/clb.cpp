#include "clb.h"

namespace cms {
namespace clb {
Input *m_input_manager;

// Copy of GLFW's implementation of callbacks for GLFWwindow class.
struct {
  GLFWwindowposfun pos;
  GLFWwindowsizefun size;
  GLFWwindowclosefun close;
  GLFWwindowrefreshfun refresh;
  GLFWwindowfocusfun focus;
  GLFWwindowiconifyfun iconify;
  GLFWwindowmaximizefun maximize;
  GLFWframebuffersizefun fbsize;
  GLFWwindowcontentscalefun scale;
  GLFWmousebuttonfun mouseButton;
  GLFWcursorposfun cursorPos;
  GLFWcursorenterfun cursorEnter;
  GLFWscrollfun scroll;
  GLFWkeyfun key;
  GLFWcharfun character;
  GLFWcharmodsfun charmods;
  GLFWdropfun drop;
} callbacks;
} // namespace clb
} // namespace cms
void cms::clb::SetupCLB(GLFWwindow *window, Input *input_manager) {
  cms::clb::m_input_manager = input_manager;
  glfwSetMouseButtonCallback(window, cms::clb::MouseButton);
  glfwSetCursorPosCallback(window, cms::clb::CursorPos);
}

void cms::clb::MouseButton(GLFWwindow *window, int button, int action,
                           int mods) {
  // ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
  // ImGuiIO io = ImGui::GetIO(); (void)io;
  // if (io.WantCaptureMouse)
  // 	return;
  /* We can handle it, GUI does not want it. */
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
  }

  /* Call developer set callback to retain functionality */
  if (cms::clb::callbacks.mouseButton)
    cms::clb::callbacks.mouseButton(window, button, action, mods);
}
void cms::clb::SetMouseButton(GLFWwindow *window, GLFWmousebuttonfun callback) {
  cms::clb::callbacks.mouseButton = callback;
}

void cms::clb::CursorPos(GLFWwindow *window, double xpos, double ypos) {
  // ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
  // ImGuiIO io = ImGui::GetIO(); (void)io;
  // if (io.WantCaptureMouse)
  // 	return;

  /* Call developer set callback to retain functionality */
  if (cms::clb::callbacks.cursorPos)
    cms::clb::callbacks.cursorPos(window, xpos, ypos);
}
void cms::clb::SetCursorPos(GLFWwindow *window, GLFWcursorposfun callback) {
  cms::clb::callbacks.cursorPos = callback;
}
