#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 ambientColor;
layout(location = 3) in vec3 specularColor;
layout(location = 4) in float dissolveFactor;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 ambientContrib = ambientColor;
    vec3 specularContrib = specularColor;
    vec3 textureColor = texture(texSampler, fragTexCoord).rgb;
    
    float alpha = 1.0 - dissolveFactor;

    outColor = vec4((fragColor + ambientContrib + specularContrib) * textureColor, alpha);
}
