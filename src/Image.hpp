/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 19:51:52 by rbourgea          #+#    #+#             */
/*   Updated: 2024/01/14 20:09:30 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <fstream>
#include <stdexcept>
#include <vector>

class Image {
public:
    static std::vector<uint8_t> loadImage(const char* filename, int& width, int& height, int& channels) {
        // Open the image file
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open image file !");
        }

        // Read the file size
        size_t fileSize = static_cast<size_t>(file.tellg());
        file.seekg(0);

        // Read the entire file into a buffer
        std::vector<uint8_t> buffer(fileSize);
        file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

        // Close the file
        file.close();

        // In this minimal example, we assume the image format is RGBA
        width = 512;  // Set your desired width
        height = 512; // Set your desired height
        channels = 4;

        return buffer;
    }
    
    static void freeImage(std::vector<uint8_t>& imageData) {
        imageData.clear();
    }
};

#endif
