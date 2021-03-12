# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/29 22:01:11 by gbright           #+#    #+#              #
#    Updated: 2020/07/06 13:35:10 by student          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

FLAGS = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit -o
SRCS_DIR = ./srcs/
SRCS_FILES = main.c control.c get_next_line.c hooksf.c make_window_n_img.c \
			 err_scene.c \
			 get_scene.c perr_handle.c save_bmp.c skip_space.c \
			 parse_scene.c get_amb_light.c get_sp_pl.c get_sq_cy.c get_tr.c \
			 rendering.c intersect_sp_pl.c vector.c color_deal.c light_deal.c \
			 shadow_deal.c vector2.c intersect_sq_tr_cy.c shadow_cy.c \
			 deep_scene_error.c error_sq_cy_tr.c get_effects.c
LIBFT_FILES = ./libft/ft_atoi.c ./libft/ft_memset.c ./libft/ft_strncmp.c \
			  ./libft/ft_bzero.c ./libft/ft_atod.c ./libft/ft_strchr.c \
			  ./libft/ft_memcpy.c
FILES = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJ = $(FILES:.c=.o)
INC = ./includes/

all: $(NAME)

%o: %c
	gcc -Wall -Wextra -Werror -c -I$(INC) $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	cd ./minilibx && make
	gcc $(FLAGS) $(NAME) -I$(INC) $(FILES) $(LIBFT_FILES)

bonus: all

clean:
	cd ./minilibx && make clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
