#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextCoord;

out vec2 TextCoord;

void main() {
	gl_Position = vec4(aPos, 1.0f);
	TextCoord = aTextCoord;
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 TextCoord;
uniform sampler2D u_Texture;

void main() {
	FragColor = texture(u_Texture, TextCoord);
}
