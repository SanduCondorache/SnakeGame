#pragma once

#include <GLFW/glfw3.h>

typedef struct {
	bool down;
	bool pressed;
	bool last;
}Key;

class Keyboard {
public:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	
	static void buttonUpdate();
	static bool key(int key);
	static bool keyWentDown(int key);
private:
	static Key keys[GLFW_KEY_LAST];
};