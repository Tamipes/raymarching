#pragma once
#include <unordered_map>
#include <GLFW/glfw3.h>

class Input {
private:
	std::unordered_map<int, bool> m_keys_pressed;
	std::unordered_map<int, bool> m_mouse_buttons_pressed;
	GLFWwindow* m_window;

public:
	Input(GLFWwindow* window);

	bool IsOnlyPressed(int key);
};
