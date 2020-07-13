#version 140

in vec3 LVertexPos3D;

out vec4 vertexColor;

void main() {
    gl_Position = vec4(LVertexPos3D.x/2.0, LVertexPos3D.y/2.0, LVertexPos3D.z/2.0, 1.0);
    vertexColor = vec4(LVertexPos3D.x, LVertexPos3D.y, LVertexPos3D.z, 1.0);
}