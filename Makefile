# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 07:51:01 by rbourgea          #+#    #+#              #
#    Updated: 2024/01/09 10:43:16 by rbourgea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -ldl

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CXXFLAGS += -I$(VULKAN_SDK_PATH)/include
    LDFLAGS += -lglfw -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lvulkan
endif
ifeq ($(UNAME_S),Darwin)
    CXXFLAGS += -I$(VULKAN_SDK_PATH)/include -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
    LDFLAGS += -framework Cocoa -framework Metal -framework IOKit -framework CoreVideo -lglfw
endif

EXECUTABLE = scop
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)
