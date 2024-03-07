# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 16:11:02 by rvandepu          #+#    #+#              #
#    Updated: 2024/03/07 11:03:17 by rvandepu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long

FILES  := $(NAME) \
		  map_loader \
		  map_utils \
		  asset_loader \
		  entities \
		  movement \
		  hooks \
		  drawer \
		  renderer \
		  font \
		  loop \

OBJ := $(FILES:%=%.o)

CFLAGS += -Wall -Wextra -Werror

# https://github.com/remty5/libft
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

.PHONY: all clean fclean re test sprites

all: $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) -r $(LIBMLX_DIR)/build
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: CFLAGS += -g
test: re

sprites:
	ln -f -s -T /sgoinfre/goinfre/Perso/rvandepu/baba-is-you-sprites sprites

$(LIBFT_PATH):
	$(MAKE) -C $(LIBFT_DIR) $(LIBFT) -j $$(nproc)

$(LIBMLX_PATH):
	cmake -S $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build
	$(MAKE) -C $(LIBMLX_DIR)/build -j $$(nproc)

$(NAME): $(OBJ) | $(LIBFT_PATH) $(LIBMLX_PATH)
