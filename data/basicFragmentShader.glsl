#version 330

in vec4 vertexColor;
out vec4 color;
uniform vec4 ourColor;

void main() {
    color = ourColor;
}