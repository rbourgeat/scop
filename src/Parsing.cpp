/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 07:50:09 by rbourgea          #+#    #+#             */
/*   Updated: 2024/04/09 14:54:24 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VulkanApp.hpp"

void VulkanApp::parseObjFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::string mtlFilename;
    std::vector<vec3> positions;
    std::vector<vec2> texCoords;
    std::vector<vec3> colors;
    std::string line;
    std::string currentMaterial;

    float minX = std::numeric_limits<float>::max(), maxX = std::numeric_limits<float>::lowest();
    float minY = std::numeric_limits<float>::max(), maxY = std::numeric_limits<float>::lowest();
    float minZ = std::numeric_limits<float>::max(), maxZ = std::numeric_limits<float>::lowest();

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        if (!(iss >> type))
            continue;

        if (iss.eof()) {
            std::cerr << "Error: Empty " << type << " line in file: " << filename << std::endl;
            std::exit(EXIT_FAILURE);
        }

        if (type == "mtllib") {
            iss >> mtlFilename;
        } else if (type == "usemtl") {
            iss >> currentMaterial;
        } else if (type == "v") {
            float x, y, z;
            if (!(iss >> x >> y >> z)) {
                std::cerr << "Error: Bad " << type << " line in file: " << filename << std::endl;
                std::exit(EXIT_FAILURE);
            }
            vec3 pos(x, y, z);
            positions.push_back(pos);

            minX = std::min(x, minX);
            minY = std::min(y, minY);
            minZ = std::min(z, minZ);

            maxX = std::max(x, maxX);
            maxY = std::max(y, maxY);
            maxZ = std::max(z, maxZ);
        } else if (type == "vt") {
            float u, v;
            if (!(iss >> u >> v)) {
                std::cerr << "Error: Bad " << type << " line in file: " << filename << std::endl;
                std::exit(EXIT_FAILURE);
            }
            texCoords.push_back(vec2(u, v));
        } else if (type == "vc") {
            float r, g, b;
            if (!(iss >> r >> g >> b)) {
                std::cerr << "Error: Bad " << type << " line in file: " << filename << std::endl;
                std::exit(EXIT_FAILURE);
            }
            colors.push_back(vec3(r, g, b));
        } else if (type == "f") {
            std::vector<int> vertexIndices;
            std::vector<int> texCoordIndices;

            std::string vertexData;
            while (iss >> vertexData) {
                std::istringstream vertexDataStream(vertexData);
                std::string index;
                int i = 0;
                while (std::getline(vertexDataStream, index, '/')) {
                    if (i == 0 && !index.empty()) {
                        vertexIndices.push_back(std::stoi(index) - 1);
                    } else if (i == 1 && !index.empty()) {
                        texCoordIndices.push_back(std::stoi(index) - 1);
                    }
                    i++;
                } 
            }

            if (vertexIndices.size() < 3) {
                std::cerr << "Error: Bad " << type << " line in file: " << filename << std::endl;
                std::exit(EXIT_FAILURE);
            }

            for (size_t j = 0; j < vertexIndices.size() - 2; ++j) {
                std::vector<int> triangleIndices = {0, static_cast<int>(j + 1), static_cast<int>(j + 2)};

                for (int index : triangleIndices) {
                    Vertex vertex;

                    if (positions.empty())
                        continue;

                    vertex.pos = positions[vertexIndices[index]];

                    if (!texCoords.empty()) {
                        vertex.texCoord = texCoords[texCoordIndices[index]];
                    } else {
                        vertex.texCoord = vec2((vertex.pos.x - minX) / (maxX - minX), 1.0f - ((vertex.pos.y - minY) / (maxY - minY)));
                    }

                    if (!colors.empty()) {
                        vertex.color = colors[vertexIndices[index]];
                    } else {
                        vertex.color = vec3(0.65, 0.65, 0.65);
                    }

                    vertex.ambientColor = vec3(1, 1, 1);
                    vertex.dissolveFactor = 1;
                    vertex.material_name = currentMaterial;

                    vertices.push_back(vertex);
                    indices.push_back(static_cast<uint16_t>(vertices.size() - 1));
                }
            }
        }
    }

    modelCentroid = vec3((minX + maxX) / 2.f, (minY + maxY) / 2.f, (minZ + maxZ) / 2.f);

    if (!mtlFilename.empty()) {
        parseMtlFile(filename, mtlFilename);
    }

    // // Print vertices
    // for (const auto& vertex : vertices) {
    //     std::cout << "Position      : " << "(" << vertex.pos.x << ", " << vertex.pos.y << ", " << vertex.pos.z << ")" << std::endl;
    //     std::cout << "TexCoord      : " << "(" << vertex.texCoord.x << ", " << vertex.texCoord.y << ")" << std::endl;
    //     std::cout << "Color         : " << "(" << vertex.color.x << ", " << vertex.color.y << ", " << vertex.color.z << ")" << std::endl;
    //     std::cout << "AmbientColor  : " << "(" << vertex.ambientColor.x << ", " << vertex.ambientColor.y << ", " << vertex.ambientColor.z << ")" << std::endl;
    //     std::cout << "DissolveFactor: " << vertex.dissolveFactor << std::endl;
    //     std::cout << "<==========>" << std::endl;
    // }

    // // Print indices
    // std::cout << "Indices:" << std::endl;
    // for (const auto& index : indices) {
    //     std::cout << index << " ";
    // }
    // std::cout << std::endl;

    file.close();

    if (positions.empty()) {
        std::cerr << "Error: The OBJ file does not contain vertex." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (indices.empty()) {
        std::cerr << "Error: The OBJ file does not contain face." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void VulkanApp::parseMtlFile(const std::string& objFilePath, const std::string& mtlFilename) {
    std::filesystem::path objPath(objFilePath);
    std::filesystem::path mtlPath = objPath.parent_path() / mtlFilename;

    std::ifstream file(mtlPath);
    if (!file.is_open()) {
        std::cout << "Warning: MTL file not found: " << mtlPath << std::endl;
        return;
    }

    std::string line;

    std::unordered_map<std::string, Material> materials;
    auto mat = materials.end();

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "newmtl") {
            std::string name;
            iss >> name;

            auto [it, mode] = materials.insert_or_assign(name, Material{});
            mat = it;
            if (!mode) {
                std::clog << "Warning: replaced old material " << name << std::endl;
            }
        } else if (type == "Ka") {
            if (mat == materials.end()) {
                std::cerr << "Error: Material not defined before " << type << " in file: " << mtlFilename << std::endl;
                std::exit(EXIT_FAILURE);
            }
            if (!(iss >> mat->second.ambient.x >>  mat->second.ambient.y >>  mat->second.ambient.z)) {
                std::cerr << "Error: Bad " << type << " line in file: " << mtlFilename << std::endl;
                std::exit(EXIT_FAILURE);
            }
        } else if (type == "Kd") {
            if (mat == materials.end()) {
                std::cerr << "Error: Material not defined before " << type << " in file: " << mtlFilename << std::endl;
                std::exit(EXIT_FAILURE);
            }
            if (!(iss >>  mat->second.diffuse.x >>  mat->second.diffuse.y >>  mat->second.diffuse.z)) {
                std::cerr << "Error: Bad " << type << " line in file: " << mtlFilename << std::endl;
                std::exit(EXIT_FAILURE);
            }
        } else if (type == "Ks") {
            if (mat == materials.end()) {
                std::cerr << "Error: Material not defined before " << type << " in file: " << mtlFilename << std::endl;
                std::exit(EXIT_FAILURE);
            }
            if (!(iss >>  mat->second.specular.x >>  mat->second.specular.y >>  mat->second.specular.z)) {
                std::cerr << "Error: Bad " << type << " line in file: " << mtlFilename << std::endl;
                std::exit(EXIT_FAILURE);
            }
        } else if (type == "d") {
            if (mat == materials.end()) {
                std::cerr << "Error: Material not defined before " << type << " in file: " << mtlFilename << std::endl;
                std::exit(EXIT_FAILURE);
            }
            if (!(iss >>  mat->second.dissolve)) {
                std::cerr << "Error: Bad " << type << " line in file: " << mtlFilename << std::endl;
                std::exit(EXIT_FAILURE);
            }
        }
        // TODO: add more material properties
    }

    if (mat == materials.end()) {
        return;
    }
    for (auto& vertex : vertices) {
        if (!vertex.material_name.empty()) {
            try {
                const auto&[ambient, diffuse, specular, dissolve] = materials.at(vertex.material_name);

                vertex.color = diffuse;
                vertex.ambientColor = ambient;
                vertex.specularColor = specular;
                vertex.dissolveFactor = dissolve;
            } catch (const std::out_of_range&) {}
        }
    }
}

std::vector<char> VulkanApp::readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        std::exit(EXIT_FAILURE);
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}
