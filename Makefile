# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 07:51:01 by rbourgea          #+#    #+#              #
#    Updated: 2024/01/10 08:31:59 by rbourgea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -ldl

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LDFLAGS += -lglfw -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lvulkan
endif
ifeq ($(UNAME_S),Darwin)
    GLFW_PATH = $(shell brew --prefix glfw)
    CXXFLAGS += -I$(GLFW_PATH)/include
    LDFLAGS += -L$(GLFW_PATH)/lib -lglfw -framework Cocoa -framework Metal -framework IOKit -framework CoreVideo -lvulkan
endif

EXECUTABLE = scop
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)
DEPS = $(OBJ_FILES:.o=.d)

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $^ -o $@ $(LDFLAGS)

-include $(DEPS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJ_FILES) $(DEPS)

re: clean all

debug: CXXFLAGS += -DDEBUG
debug: re
