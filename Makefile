# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 16:11:02 by rvandepu          #+#    #+#              #
#    Updated: 2025/03/28 02:46:47 by rvandepu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D

SRC  := main.c \
		map_loader.c \
		map_utils.c \
		asset_loader.c \
		entities.c \
		movement.c \
		hooks.c \
		drawer.c \
		renderer.c \
		font.c \
		loop.c \

SRC_DIR := src
SRC     := $(SRC:%=$(SRC_DIR)/%)
OBJ_DIR := build
OBJ     := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS += -Iinclude
CFLAGS   += -Wall -Wextra -Werror

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
	$(RM) -r $(LIBMLX_DIR)/build
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: CFLAGS += -g -Wno-error
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
