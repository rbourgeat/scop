/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 06:37:08 by rbourgea          #+#    #+#             */
/*   Updated: 2024/01/16 11:11:14 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VulkanApp.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " \"path/to/file.obj\"" << std::endl;
        return EXIT_FAILURE;
    }

    VulkanApp app;

    try {
        app.run(argv[1]);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}