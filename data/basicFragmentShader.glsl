#version 140

out vec4 LFragment;

uniform vec4 ourColor;

void main() {
    //LFragment = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    LFragment = ourColor;
}