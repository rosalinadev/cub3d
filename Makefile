# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 16:11:02 by rvandepu          #+#    #+#              #
#    Updated: 2025/06/23 18:35:21 by rvandepu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D

SRC  := main.c \
		loop.c \
		hooks.c \
		map_loader.c \
		map_utils.c \
		player.c \
		asset_loader.c \
		sprites.c \
		debug.c \
		renderer.c \
		raycaster.c \
		\
		mlx_utils.c \
		font.c \
		type_utils.c \
		vec_utils.c \
		error.c \

SRC_DIR := src
SRC     := $(SRC:%=$(SRC_DIR)/%)
OBJ_DIR := build
OBJ     := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS += -Iinclude
CFLAGS   += -std=c23 -Wall -Wextra -Werror -Wpedantic -O3

# https://github.com/rosalinadev/libft
LIBFT_DIR	:= libft
LIBFT		:= libft.a
LIBFT_PATH	:= $(LIBFT_DIR)/$(LIBFT)
CPPFLAGS	+= -I$(LIBFT_DIR)
LDFLAGS		+= -L$(LIBFT_DIR)
LDLIBS		+= -lft

# https://github.com/codam-coding-college/MLX42
LIBMLX_DIR	:= MLX42
LIBMLX		:= libmlx42.a
LIBMLX_PATH	:= $(LIBMLX_DIR)/build/$(LIBMLX)
CPPFLAGS	+= -I$(LIBMLX_DIR)/include
CFLAGS		+= -pthread
LDFLAGS		+= -L$(LIBMLX_DIR)/build
LDLIBS		+= -lmlx42 -ldl -lglfw -lpthread -lm

.PHONY: all clean fclean re test

all: $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) fclean
	# FIXME uncomment or find way to build faster (esp. on WSL)
	#$(RM) -r $(LIBMLX_DIR)/build
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

FSANITIZE := -fsanitize=address
test: CFLAGS += -Og -g -Wno-error $(FSANITIZE)
test: LDFLAGS += $(FSANITIZE)
test: re

$(OBJ_DIR):
	mkdir -p $@

$(LIBFT_PATH):
	$(MAKE) -s -C $(LIBFT_DIR) $(LIBFT) -j $$(nproc)

$(LIBMLX_PATH):
	cmake -Wno-dev -S $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build
	$(MAKE) -C $(LIBMLX_DIR)/build -j $$(nproc)

# I hate having to do this
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(NAME): $(OBJ_DIR) $(OBJ) | $(LIBFT_PATH) $(LIBMLX_PATH)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $@
