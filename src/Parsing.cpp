/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 07:50:09 by rbourgea          #+#    #+#             */
/*   Updated: 2024/01/18 07:31:31 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VulkanApp.hpp"

void VulkanApp::parseObjFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        std::exit(0);
    }

    std::vector<vec3> positions;
    std::vector<vec3> colors;
    std::vector<vec2> texCoords;

    std::string mtlFilename;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "mtllib") {
            iss >> mtlFilename;
        } else if (type == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            positions.push_back(vec3(x, y, z));
        } else if (type == "vt") {
            float u, v;
            iss >> u >> v;
            texCoords.push_back(vec2(u, v));
        } else if (type == "vc") {
            float r, g, b;
            iss >> r >> g >> b;
            colors.push_back(vec3(r, g, b));
        } else if (type == "f") {
            std::vector<int> vertexIndices;
            std::vector<int> texCoordIndices;

            int vertexIndex;
            int texCoordIndex;
            while (iss >> vertexIndex) {
                vertexIndex--;
                vertexIndices.push_back(vertexIndex);

                if (texCoords.size() > 0) {
                    iss.ignore(); // Ignore the '/'
                    iss >> texCoordIndex;
                    texCoordIndex--;
                    texCoordIndices.push_back(texCoordIndex);
                }
            }

            for (int j = 0; j < 3; ++j) {
                Vertex vertex;
                vertex.pos = positions[vertexIndices[j]];

                if (!texCoords.empty()) {
                    vertex.texCoord = texCoords[texCoordIndices[j]];
                }

                if (!colors.empty()) {
                    vertex.color = colors[vertexIndices[j]];
                } else {
                    vertex.color = vec3(0.4, 1.0, 0.4);
                }

                vertices.push_back(vertex);
                indices.push_back(static_cast<uint16_t>(vertices.size() - 1));
            }
        }
    }

    if (!mtlFilename.empty()) {
        parseMtlFile(filename, mtlFilename);
    }

    // Print vertices
    for (const auto& vertex : vertices) {
        std::cout << "Position    : " << "(" << vertex.pos.x << ", " << vertex.pos.y << ", " << vertex.pos.z << ")" << std::endl;
        std::cout << "TexCoord    : " << "(" << vertex.texCoord.x << ", " << vertex.texCoord.y << ")" << std::endl;
        std::cout << "Color       : " << "(" << vertex.color.x << ", " << vertex.color.y << ", " << vertex.color.z << ")" << std::endl;
        std::cout << "AmbientColor: " << "(" << vertex.ambientColor.x << ", " << vertex.ambientColor.y << ", " << vertex.ambientColor.z << ")" << std::endl;
        std::cout << "<==========>" << std::endl;
    }

    // Print indices
    // std::cout << "Indices:" << std::endl;
    // for (const auto& index : indices) {
    //     std::cout << index << " ";
    // }
    // std::cout << std::endl;

    file.close();
}

void VulkanApp::parseMtlFile(const std::string& objFilePath, const std::string& mtlFilename) {
    std::filesystem::path objPath(objFilePath);
    std::filesystem::path mtlPath = objPath.parent_path() / mtlFilename;

    std::ifstream file(mtlPath);
    if (!file.is_open()) {
        std::cout << "Warning: MTL file not found: " << mtlPath << std::endl;
    }

    std::string line;
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "Ka") {
            iss >> ambientColor.x >> ambientColor.y >> ambientColor.z;
        } else if (type == "Kd") {
            iss >> diffuseColor.x >> diffuseColor.y >> diffuseColor.z;
        } else if (type == "Ks") {
            iss >> specularColor.x >> specularColor.y >> specularColor.z;
        }
        // TODO: add more material properties
    }

    for (auto& vertex : vertices) {
        vertex.color = diffuseColor;
        vertex.ambientColor = ambientColor;
        vertex.specularColor = specularColor;
    }
}

std::vector<char> VulkanApp::readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file !");
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}