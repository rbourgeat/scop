#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 ambientColor;
layout(location = 3) in vec3 specularColor;
layout(location = 4) in float dissolveFactor;
layout(location = 5) in float dissolveTextureFactor;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 diffuseContrib = fragColor;
    vec3 ambientContrib = ambientColor;
    vec3 specularContrib = specularColor;

    float alpha = dissolveFactor;

    vec3 textureColor = texture(texSampler, fragTexCoord).rgb;

    vec3 finalColor = (diffuseContrib + textureColor * dissolveTextureFactor) / 2;
    if (ambientColor.r != 0 || ambientColor.g != 0 || ambientColor.b != 0) {
        finalColor *= ambientColor;
    }
    if (specularColor.r != 0 || specularColor.g != 0 || specularColor.b != 0) {
        finalColor *= specularColor;
    }

    outColor = vec4(finalColor, alpha);
}
