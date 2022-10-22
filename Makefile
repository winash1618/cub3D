# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaruvan <namohamm@student.42.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/06 12:06:56 by mkaruvan          #+#    #+#              #
#    Updated: 2022/10/22 16:53:38 by mkaruvan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

LIBX_DIR	=	minilibx

LIBX		=	libmlx.a

INC_DIR		=	includes

SRCS		=	cub3d.c main.c key_event.c ray_caster.c

SRC_DIR		=	srcs

PARSER		=	ft_parsing.c ft_info.c ft_map.c ft_set_info.c ft_set_map.c\
				ft_set_info_1.c ft_set_info_2.c ft_set_info_3.c ft_set_map_1.c\
				ft_set_map_2.c ft_set_map_3.c\

PARSER_DIR	=	parsing
	
#FRAMEWORK	=	-L $(LIBX_DIR) -lmlx -framework OpenGL -framework AppKit

SUBDIRS		=	libft ft_printf

OBJS		=	$(addprefix $(SRC_DIR)/, $(SRCS:%c=%o))

OBJS		+=	$(addprefix $(PARSER_DIR)/, $(PARSER:%c=%o))

CC			=	gcc

CFLAGS		=	-g3 -Wall -Werror -Wextra -Ofast 

$(SRC_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS)  -Ilibft -Ift_printf -I $(INC_DIR) -c $^ -o $@
$(PARSER_DIR)/%.o : $(PARSER_DIR)/%.c
	$(CC) $(CFLAGS)  -Ilibft -Ift_printf -I $(INC_DIR) -c $^ -o $@

$(NAME): $(OBJS)
	 for dir in $(SUBDIRS); do \
		$(MAKE) all -C $$dir; \
	done
	 $(CC) $(CFLAGS)  $(OBJS) -Lft_printf -lftprintf -Llibft -lft -o $(NAME)

# $(LIBX):
# 	make -C $(LIBX_DIR)

all: $(NAME)

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
#	make -C $(LIBX_DIR) clean
	rm -f $(SRC_DIR)/*.o
	rm -f $(PARSER_DIR)/*.o

fclean: clean
	for dir in $(SUBDIRS); do \
		$(MAKE) fclean -C $$dir; \
	done
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re
