#version 140

in vec3 LVertexPos3D;

void main() {
    gl_Position = vec4(LVertexPos3D.x/2.0, LVertexPos3D.y/2.0, LVertexPos3D.z/2.0, 1.0);
}