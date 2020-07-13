#version 140

out vec4 LFragment;

in vec4 vertexColor;

void main() {
    //LFragment = vec4( 1.0, 1.0, 1.0, 1.0 );
    LFragment = vertexColor;
}