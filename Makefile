# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/06 12:06:56 by mkaruvan          #+#    #+#              #
#    Updated: 2022/08/06 12:07:00 by mkaruvan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

LIBX_DIR	=	minilibx

LIBX		=	libmlx.a

INC_DIR		=	includes

SRCS		=	cub3d.c main.c key_event.c ray_caster.c

SRC_DIR		=	srcs

FRAMEWORK	=	-L $(LIBX_DIR) -lmlx -framework OpenGL -framework AppKit

SUBDIRS		=	libft ft_printf

OBJS		=	$(addprefix $(SRC_DIR)/, $(SRCS:%c=%o))

CC			=	gcc

CFLAGS		=	-g3 -Wall -Werror -Wextra -Ofast

$(SRC_DIR)/%.o : $(SRC_DIR)/%.c
	for dir in $(SUBDIRS); do \
		$(MAKE) all -C $$dir; \
	done
	$(CC) $(CFLAGS)  -Ilibft -Ift_printf -I $(INC_DIR) -c $^ -o $@

$(NAME): $(OBJS) $(LIBX)
	for dir in $(SUBDIRS); do \
		$(MAKE) all -C $$dir; \
	done
	$(CC) $(CFLAGS) -Lft_printf -lftprintf -Llibft -lft $(OBJS) $(FRAMEWORK) -o $(NAME)

$(LIBX):
	make -C $(LIBX_DIR)

all: $(NAME)

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	make -C $(LIBX_DIR) clean
	rm -f $(SRC_DIR)/*.o

fclean: clean
	for dir in $(SUBDIRS); do \
		$(MAKE) fclean -C $$dir; \
	done
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re
