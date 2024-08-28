#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Camera.h"
#include "Keyboard.h"
#include "Snake.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

int Width = 800, Height = 800;
const int speed = 10;

float timeNow, timeLast, delta, timeTotal;

float fps_currentTime = 0.0f;
float fps_lastTime = 0.0f;
int nbFrames = 0;

Snake snake;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Width = width;
    Height = height;
}

static void processInput(GLFWwindow* window) {
    
    Keyboard::buttonUpdate();
    Directions lastDirection = snake.GetDirection();
    
    if (Keyboard::keyWentDown(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }

    if (Keyboard::key(GLFW_KEY_W)) {
        if ((snake.GetDirection() != Directions::DOWN)) {
            snake.SetDirection(Directions::UP);
        }
    }
    else if (Keyboard::key(GLFW_KEY_S)) {
        if ((snake.GetDirection() != Directions::UP)) {
            snake.SetDirection(Directions::DOWN);
        }
    }
    else if (Keyboard::key(GLFW_KEY_D)) {
        if ((snake.GetDirection() != Directions::LEFT)) {
            snake.SetDirection(Directions::RIGHT);
        }
    }
    else if (Keyboard::key(GLFW_KEY_A)) {
        if ((snake.GetDirection() != Directions::RIGHT)) {
            snake.SetDirection(Directions::LEFT);
        }
    }
    if (snake.GetDirection() != lastDirection) {
        snake.SnakeLogic();
        if (snake.StopGame()) {
            glfwSetWindowShouldClose(window, true);
        }
        timeTotal = 0.0f;
    }
}

static void showScore(GLFWwindow* window) {
        std::stringstream ss;
        ss << "Score: " << snake.GetSize();
        glfwSetWindowTitle(window, ss.str().c_str());
}

int main(void) {
    srand(time(NULL));
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(Width, Height, "Loh", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, Keyboard::keyCallback);
    glfwSwapInterval(5);
    {
        Renderer renderer;

        VertexBuffer vb(vertices, sizeof(vertices));
        VertexArray va;
        IndexBuffer ib(indeces, 6);

        VertexBufferLayout layout;
        layout.Push<float>(3);
        va.AddBuffer(vb, layout);

        Shader shader("res/Shader.shader");
        shader.Bind();

        snake.SetDirection(Directions::NOWHERE);
        snake.SetSize(1);
        snake.SetHeadPosition((rand() % (GRID_X * GRID_Y)));
        snake.SetFoodPosition((rand() % (GRID_X * GRID_Y)));

        timeNow = static_cast<float>(glfwGetTime());
        timeLast = timeNow;
        delta = 0.0f;
        timeTotal = 0.0f;

        glm::vec2 grid = glm::vec2((float)GRID_X, (float)GRID_Y);

        while (!glfwWindowShouldClose(window)) {
            renderer.Clear();
            processInput(window);

            showScore(window);

            timeNow = static_cast<float>(glfwGetTime());
            delta = timeNow - timeLast;
            timeLast = timeNow;
            timeTotal += delta;

            if (timeTotal >= 1.0 / speed) {
                snake.SnakeLogic();
                timeTotal = 0.0f;
            }

            va.Bind();
            ib.Bind();
            shader.SetUniform2f("uGrid", grid);
            float t = 0.0f;
            shader.SetUniform1f("uPosition", t);
            shader.SetUniform4f("uColor", 0.0f, 1.0f, 0.0f, 1.0f);
            glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
            for (int i = 0; i < snake.GetSize(); i++) {
                shader.SetUniform1f("uPosition", (float)snake.GetPosition(i));
                if (i == 0) {
                    shader.SetUniform4f("uColor", 0.0f, 0.0f, 0.0f, 1.0f);
                }
                else {
                    shader.SetUniform4f("uColor", 0.0f, 0.0f, 0.0f, 1.0f);
                }
                glDrawElements(GL_TRIANGLES, ib.GetCount() , GL_UNSIGNED_INT, 0);
            }

            shader.SetUniform1f("uPosition", (float)snake.GetFoodPosition());
            shader.SetUniform4f("uColor", 1.0f, 0.0f, 0.0f, 1.0f);
            glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
            
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}