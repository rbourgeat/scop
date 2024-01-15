/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 19:51:52 by rbourgea          #+#    #+#             */
/*   Updated: 2024/01/15 07:07:23 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <fstream>
#include <stdexcept>
#include <vector>
#include <iostream>

class Image {
public:
    static std::vector<unsigned char> loadImage(const char* filename, int& width, int& height, int& channels) {
        // Open the image file
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open image file !");
        }

        // Read the file size
        size_t fileSize = static_cast<size_t>(file.tellg());
        file.seekg(0);

        // Read the entire file into a buffer
        std::vector<unsigned char> buffer(fileSize);
        file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

        // Check for BMP header (assuming BMP format)
        if (buffer.size() >= 54 && buffer[0] == 'B' && buffer[1] == 'M') {
            // Extract width and height from BMP header
            width = *reinterpret_cast<int*>(&buffer[18]);
            height = *reinterpret_cast<int*>(&buffer[22]);
            channels = *reinterpret_cast<short*>(&buffer[28]);  // Assuming 24 or 32 bits per pixel

            // Add an alpha channel if needed (assuming 32 bits per pixel)
            if (channels == 24) {
                std::vector<unsigned char> newBuffer(width * height * 4);

                for (int i = 0; i < height; ++i) {  // Iterate over rows
                    for (int j = 0; j < width; ++j) {  // Iterate over columns
                        int inputIndex = (height - i - 1) * width + j;  // Invert Y-axis
                        int outputIndex = i * width + j;
                        newBuffer[outputIndex * 4] = buffer[inputIndex * 3 + 2];
                        newBuffer[outputIndex * 4 + 1] = buffer[inputIndex * 3 + 1];
                        newBuffer[outputIndex * 4 + 2] = buffer[inputIndex * 3];
                        newBuffer[outputIndex * 4 + 3] = 255;  // Fully opaque alpha channel
                    }
                }

                buffer = std::move(newBuffer);
                channels = 4;
            }
        } else {
            throw std::runtime_error("Unsupported image format. Only BMP is supported in this example.");
        }

        // Close the file
        file.close();

        return buffer;
    }

    static void freeImage(std::vector<unsigned char>& imageData) {
        imageData.clear();
    }
};

#endif
