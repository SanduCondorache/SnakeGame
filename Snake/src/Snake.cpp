#include "Snake.h"

#include <iostream>

Snake::Snake()
    : m_Size(0), m_Direction(Directions::NOWHERE), m_FoodPosition(0), sw(1)
{
    m_Positions.resize(GRID_X * GRID_Y);
    m_Positions[0] = (rand() % (GRID_X * GRID_Y));
    m_FoodPosition = (rand() % (GRID_X * GRID_Y));
}

void Snake::SnakeLogic() {
    if (m_Direction == Directions::NOWHERE) {
        return;
    }
    if (HitWall()) {
        m_Size = 1;
        sw = 0;
        return;
    }
    int headPosition = m_Positions[0];
    int snakeSize = m_Size;

    if (m_Direction == Directions::LEFT) {
        m_Positions[0] -= 1;
    }
    else if (m_Direction == Directions::RIGHT) {
        m_Positions[0] += 1;
    }
    else if (m_Direction == Directions::UP) {
        m_Positions[0] -= GRID_Y;
    }
    else if (m_Direction == Directions::DOWN) {
        m_Positions[0] += GRID_Y;
    }
    if (m_Positions[0] == m_FoodPosition) {
        m_Size++;
    }
    if (m_Size >= 14) {
        m_Size = 1;
    }
    if (m_Size > 2) {
        for (int i = 0; i < m_Size - 2; i++) {
            m_Positions[m_Size - 1 - i] = m_Positions[m_Size - 2 - i];
        }
    }
    if (m_Size > 1) {
        m_Positions[1] = headPosition;
    }
    for (int i = 0; i < m_Size - 1; i++) {
        if (m_Positions[0] == m_Positions[i + 1]) {
            m_Size = 1;
            sw = 0;
            return;
        }
    }
    if (m_Size != snakeSize) {
        m_FoodPosition = foodSpawn();
    }
}

int Snake::foodSpawn() {
    srand(time(NULL));
    int pos = (rand() % (GRID_X * GRID_Y));
    for (int i = 0; i < m_Size; i++) {
        if (m_Positions[i] == pos) {
            pos = (pos + 1) % (GRID_X * GRID_Y);
        }
    }
    return pos;
}

void Snake::SetFoodPosition(int food) {
    m_FoodPosition = food;
}

void Snake::SetDirection(Directions direction) {
    m_Direction = direction;
}

void Snake::SetSize(int size) {
    m_Size = size;
}

void Snake::SetHeadPosition(int coord) {
    m_Positions[0] = coord;
}

bool Snake::HitWall() const {
    if (((m_Positions[0] % GRID_X) == 0) && (m_Direction == Directions::LEFT)) {
        return true;
    }
    if (((m_Positions[0] % GRID_X) == (GRID_X - 1)) && (m_Direction == Directions::RIGHT)) {
        return true;
    }
    if (((m_Positions[0] / GRID_Y) == 0) && (m_Direction == Directions::UP)) {
        return true;
    }
    if (((m_Positions[0] / GRID_Y) == (GRID_Y - 1)) && (m_Direction == Directions::DOWN)) {
        return true;
    }
    return false;
}
