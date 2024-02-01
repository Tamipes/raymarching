#include "input.h"
#include "clb.h"

Input::Input(GLFWwindow* window) : m_window(window)
{
	cms::clb::SetupCLB(window, this);
}

bool Input::IsOnlyPressed(int key)
{
	if (glfwGetKey(m_window, key) == GLFW_PRESS)
	{
		if (!m_keys_pressed[key]) {
			m_keys_pressed[key] = true;
			return true;
		}
		return false;
	}
	else
	{
		m_keys_pressed[key] = false;
		return false;
	}

}
