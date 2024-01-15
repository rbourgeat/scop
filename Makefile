# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 07:51:01 by rbourgea          #+#    #+#              #
#    Updated: 2024/01/15 06:42:55 by rbourgea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TIME = $(shell date +%s.%N)

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g
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

RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
NC=\033[0m
BOLD=\033[1m

EMOJI_DONE=✅
EMOJI_BUILD=🚀
EMOJI_LINK=🔗
EMOJI_CLEAN=🚽
EMOJI_ERROR=❌

LINE_SEPARATOR=$(BOLD)$(PURPLE)<====================================>$(NC)

all: shaders $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	@echo "$(YELLOW)$(EMOJI_LINK) Linking $(BOLD)$(EXECUTABLE)$(NC)"
	@$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "$(GREEN)$(BOLD)$(EMOJI_DONE) Build successful !$(NC)"
	@TIME_DIFF=$$(echo $$(date +%s.%N) - $(TIME) | bc); \
	echo "$(BLUE)⏰ Build completed in $(BOLD)$${TIME_DIFF}$(NC) $(BLUE)seconds$(NC)"
	@echo "$(LINE_SEPARATOR)"

-include $(DEPS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "$(YELLOW)$(EMOJI_BUILD) Compiling $(BOLD)$<$(NC)"
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

shaders:
	@echo "$(LINE_SEPARATOR)"
	@echo "$(YELLOW)$(EMOJI_BUILD) Compiling shaders...$(NC)"
	@cd shaders && bash compile.sh && echo "$(GREEN)$(EMOJI_DONE) Shaders compiled successfully!$(NC)" || echo "$(RED)$(EMOJI_ERROR) Error compiling shaders.$(NC)"
	@echo "$(LINE_SEPARATOR)"

clean:
	@echo "$(LINE_SEPARATOR)"
	@echo "$(YELLOW)$(EMOJI_CLEAN) Cleaning...$(NC)"
	@rm -f $(EXECUTABLE) $(OBJ_FILES) $(DEPS)
	@rm -rf shaders/*.spv
	@echo "$(GREEN)$(EMOJI_DONE) Cleaned !$(NC)"

re: clean shaders all

debug: CXXFLAGS += -DDEBUG
debug: re
	@echo "$(YELLOW)$(EMOJI_DONE) Debug mode activated:\n"

.PHONY: all clean shaders