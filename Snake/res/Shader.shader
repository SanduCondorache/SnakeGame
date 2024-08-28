#shader vertex
#version 330 core

layout (location = 0) in vec3 v_Position;

uniform float uPosition;
uniform vec2 uGrid;


void main() {
	float xPos = (mod(uPosition, uGrid.x) * (2 / uGrid.x)) - 1.0 + (1 / uGrid.x);
	float yPos = 1.0 - (1 / uGrid.y) - (floor(uPosition / uGrid.x) * (2 / uGrid.y));
	vec2 pos = vec2(xPos, yPos);
	vec2 temp = pos - (1 / uGrid) + (v_Position.xy * (2 / uGrid));
	gl_Position = vec4(temp, 0.0, 1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;

uniform vec4 uColor;

void main() {
	FragColor = uColor;
}
