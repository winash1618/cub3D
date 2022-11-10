# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/06 12:06:56 by mkaruvan          #+#    #+#              #
#    Updated: 2022/11/10 12:01:27 by mkaruvan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

LIBX_DIR	=	minilibx

LIBX		=	libmlx.a

INC_DIR		=	includes

SRCS		=	cub3d.c main.c key_event.c ray_caster.c ray_caster_helper.c utils.c \
				create_play.c

SRC_DIR		=	srcs

PARSER		=	ft_parsing.c ft_info.c ft_map.c ft_save_file.c ft_file.c \
				ft_clean_file.c ft_set_info.c ft_set_map.c\

PARSER_DIR	=	parsing
	
FRAMEWORK	=	-L $(LIBX_DIR) -lmlx -framework OpenGL -framework AppKit

SUBDIRS		=	libft ft_printf minilibx

OBJS		=	$(addprefix $(SRC_DIR)/, $(SRCS:%c=%o))

OBJS		+=	$(addprefix $(PARSER_DIR)/, $(PARSER:%c=%o))

CC			=	gcc
# -fsanitize=address
CFLAGS		=	-g3 -Wall -Werror -Wextra -Ofast

$(SRC_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS)  -Ilibft -Ift_printf -I $(INC_DIR) -c $^ -o $@
$(PARSER_DIR)/%.o : $(PARSER_DIR)/%.c
	$(CC) $(CFLAGS)  -Ilibft -Ift_printf -I $(INC_DIR) -c $^ -o $@

$(NAME): $(OBJS)
	 for dir in $(SUBDIRS); do \
		$(MAKE) all -C $$dir; \
	done
		$(CC) $(CFLAGS) $(OBJS)  -Lft_printf -lftprintf -Llibft -lft $(FRAMEWORK) -o $(NAME)

$(LIBX):
	make -C $(LIBX_DIR)

all: $(NAME)
	

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
#	make -C $(LIBX_DIR) clean
	rm -f $(SRC_DIR)/*.o
	rm -f $(PARSER_DIR)/*.o

fclean: clean
	make fclean -C  libft
	make fclean -C ft_printf
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re
