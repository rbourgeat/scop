/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 19:51:52 by rbourgea          #+#    #+#             */
/*   Updated: 2024/01/15 10:45:56 by rbourgea         ###   ########.fr       */
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
            channels = *reinterpret_cast<short*>(&buffer[28]);

            if (channels == 24 || channels == 32) {
                // Handle 24-bit and 32-bit images
                int bytesPerPixel = channels / 8;
                int padding = (4 - (width * bytesPerPixel) % 4) % 4;

                std::vector<unsigned char> newBuffer(width * height * 4);

                for (int i = 0; i < height; ++i) {
                    for (int j = 0; j < width; ++j) {
                        int inputIndex = (height - i - 1) * (width * bytesPerPixel + padding) + j * bytesPerPixel;
                        int outputIndex = i * width + j;

                        newBuffer[outputIndex * 4] = buffer[inputIndex + 2];
                        newBuffer[outputIndex * 4 + 1] = buffer[inputIndex + 1];
                        newBuffer[outputIndex * 4 + 2] = buffer[inputIndex];
                        newBuffer[outputIndex * 4 + 3] = (channels == 24) ? 255 : buffer[inputIndex + 3];
                    }
                }

                buffer = std::move(newBuffer);
                channels = 4;
            } else {
                throw std::runtime_error("Unsupported image channel count. Only 24-bit and 32-bit images are supported.");
            }
        } else {
            throw std::runtime_error("Unsupported image format. Only BMP is supported.");
        }

        file.close();

        return buffer;
    }

    static void freeImage(std::vector<unsigned char>& imageData) {
        imageData.clear();
    }
};

#endif
