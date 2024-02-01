#pragma once

#include "input.h"

namespace cms {
	namespace clb {
		//(clb == callback)

		// This sets up our custom GLFW callbacks "injection"
		void SetupCLB(GLFWwindow* window, Input* input_manager);


		// Our Custom callback for injecting into GLFW's callaback and doing stuff for the engine,
		// but we retain functionality using:
		// cms::clb::Set************
		void MouseButton(GLFWwindow* window, int button, int action, int mods);
		// Our Custom callback for injecting into GLFW's callaback and doing stuff for the engine,
		// but we retain functionality using:
		// cms::clb::Set************
		void CursorPos(GLFWwindow* window, double xpos, double ypos);

		// Our custom way of setting glfw callbacks, but this will also run engine code as well.
		void SetMouseButton(GLFWwindow* window, GLFWmousebuttonfun callback);
		// Our custom way of setting glfw callbacks, but this will also run engine code as well.
		void SetCursorPos(GLFWwindow* window, GLFWcursorposfun callback);
	};
}
