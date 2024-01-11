#version 450

out gl_PerVertex {
    vec4 gl_Position;
};

layout(location = 0) out vec3 fragColor;

vec2 positions[3] = vec2[](
    vec2(0.0, -0.5),
    vec2(0.5, 0.5),
    vec2(-0.5, 0.5)
);

vec3 hexToVec3(in uint hexColor) {
    float r = ((hexColor >> 16) & 0xFF) / 255.0;
    float g = ((hexColor >> 8) & 0xFF) / 255.0;
    float b = (hexColor & 0xFF) / 255.0;
    return vec3(r, g, b);
}

uint hexColors[3] = uint[](
    0xFF3300,  // Hex color: #FF3300 (Reddish)
    0x00FF33,  // Hex color: #00FF33 (Greenish)
    0x0033FF   // Hex color: #0033FF (Bluish)
);

void main() {
    gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
    fragColor = hexToVec3(hexColors[gl_VertexIndex]);
}
