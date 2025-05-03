#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos; // Camera/view position in world space

void emitEdge(int i, int j) {
    gl_Position = projection * view * model * gl_in[i].gl_Position;
    EmitVertex();
    gl_Position = projection * view * model * gl_in[j].gl_Position;
    EmitVertex();
    EndPrimitive();
}

vec3 getNormal(vec3 v0, vec3 v1, vec3 v2) {
    vec3 edge1 = v1 - v0;
    vec3 edge2 = v2 - v0;
    return normalize(cross(edge1, edge2));
}

void main() {
    vec3 v0 = vec3(model * gl_in[0].gl_Position);
    vec3 v1 = vec3(model * gl_in[1].gl_Position);
    vec3 v2 = vec3(model * gl_in[2].gl_Position);

    vec3 faceNormal = getNormal(v0, v1, v2);
    vec3 viewDir = normalize(v0 + v1 + v2) / 3.0 - viewPos;

    // If normal is nearly perpendicular to view direction → silhouette
    if (abs(dot(faceNormal, viewDir)) < 0.3) {
        emitEdge(0, 1);
        emitEdge(1, 2);
        emitEdge(2, 0);
    }
}
