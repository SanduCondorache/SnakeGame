#pragma once

#include <time.h>
#include <vector>

#include "Renderer.h"

enum class Directions {
	NOWHERE = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 4,
	DOWN = 8,
};

class Snake {
public:
	Snake();
	void SnakeLogic();
	inline Directions GetDirection() const { return m_Direction; }
	inline int GetSize() const { return m_Size; }
	inline int GetPosition(int i) const { return m_Positions[i]; }
	inline int GetFoodPosition() const { return m_FoodPosition; }
	inline int StopGame() const { return !sw; }
	void SetDirection(Directions direction);
	void SetSize(int size);
	void SetHeadPosition(int coord);
	int foodSpawn();
	void SetFoodPosition(int food);

private:
	int m_Size;
	std::vector<int> m_Positions;
	std::vector<int> m_Walls;
	Directions m_Direction;
	int m_FoodPosition;
	int sw;

private:
	bool HitWall() const;
};