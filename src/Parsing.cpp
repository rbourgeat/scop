/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 07:50:09 by rbourgea          #+#    #+#             */
/*   Updated: 2024/01/17 11:20:36 by rbourgea         ###   ########.fr       */
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

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
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

            // Parse vertex and optional texture coordinate indices
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
                // } else {
                //     vertex.color = vec3(1.0f, 0.0f, 0.0f);
                } else {
                    if (j == 0) {
                        vertex.color = vec3(1.0f, 0.0f, 0.0f);
                    } else if (j == 1) {
                        vertex.color = vec3(0.0f, 1.0f, 0.0f);
                    } else {
                        vertex.color = vec3(0.0f, 0.0f, 1.0f);  
                    }
                }

                vertices.push_back(vertex);
                indices.push_back(static_cast<uint16_t>(vertices.size() - 1));
            }
        }
    }

    // Print vertices
    std::cout << "Vertices:" << std::endl;
    for (const auto& vertex : vertices) {
        std::cout << "Pos: (" << vertex.pos.x << ", " << vertex.pos.y << ", " << vertex.pos.z << ")";
        std::cout << " TexCoord: (" << vertex.texCoord.x << ", " << vertex.texCoord.y << ")";
        std::cout << " Color: (" << vertex.color.x << ", " << vertex.color.y << ", " << vertex.color.z << ")";
        std::cout << std::endl;
    }

    // Print indices
    std::cout << "Indices:" << std::endl;
    for (const auto& index : indices) {
        std::cout << index << " ";
    }
    std::cout << std::endl;

    // vertices = {
    //     {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    //     {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    //     {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    //     {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
    // };

    // indices = {
    //     0, 1, 2, 2, 3, 0
    // };

    file.close();
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