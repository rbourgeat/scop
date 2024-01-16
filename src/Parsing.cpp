/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 07:50:09 by rbourgea          #+#    #+#             */
/*   Updated: 2024/01/16 11:13:48 by rbourgea         ###   ########.fr       */
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
            for (int i = 0; i < 3; ++i) {
                int vertexIndex;
                iss >> vertexIndex;

                // Adjust indices to 0-based
                vertexIndex--;

                Vertex vertex;
                vertex.pos = positions[vertexIndex];

                if (!texCoords.empty()) {
                    vertex.texCoord = texCoords[vertexIndex];
                }

                if (!colors.empty()) {
                    vertex.color = colors[vertexIndex];
                }

                vertices.push_back(vertex);
                indices.push_back(static_cast<uint16_t>(vertices.size() - 1));
            }
        }
    }

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