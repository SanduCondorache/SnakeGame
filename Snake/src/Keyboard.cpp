#include "Keyboard.h"

Key Keyboard::keys[GLFW_KEY_LAST] = { {0, 0, 0} };


void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (action == GLFW_RELEASE) {
		keys[key].down = false;
	}

	if (action == GLFW_PRESS) {
		keys[key].down = true;
	}
}

void Keyboard::buttonUpdate() {
	for (int i = 0; i < GLFW_KEY_LAST; i++) {
		keys[i].pressed = keys[i].down && !keys[i].last;
		keys[i].last = keys[i].down;
	}
}

bool Keyboard::key(int key) {
	return keys[key].pressed;
}

bool Keyboard::keyWentDown(int key) {
	return keys[key].down;
}

