# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 13:02:42 by jcesar-s          #+#    #+#              #
#    Updated: 2025/09/01 20:00:50 by jcesar-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf
CC=cc
CFLAGS=-Wall -Wextra -Werror -O3
IDIR=include/
ODIR=obj/
CDIR=src/
LIBX=$(IDIR)minilibx
LIBXA=$(LIBX)/libmlx_Linux.a
LIBFT=$(IDIR)libft
LIBFTA=$(LIBFT)/libft.a
SRC=main.c input_handler.c map_creator.c map_utils.c utils.c init_app.c
SRC+=draw_line.c draw_utils.c renderer.c key_handler.c colors.c
SRC+=map_transformer.c events.c
_SRC=$(patsubst %.c, $(CDIR)%.c, $(SRC))
OBJS=$(patsubst %.c, $(ODIR)%.o, $(SRC))

$(ODIR)%.o: $(CDIR)%.c
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $^ -o $@ -I $(IDIR) -I $(LIBX) -I $(LIBFT)

all: $(NAME)

$(NAME): $(OBJS) $(LIBXA) $(LIBFTA)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBX) -lmlx -lXext -lX11 -L $(LIBFT) -lft -lm -o $(NAME) 

$(LIBFTA):
	make -C $(LIBFT) --no-print-directory

$(LIBXA):
	make -C $(LIBX) --no-print-directory

mlx:
	if [ ! -d $(LIBX) ]; then git clone git@github.com:42paris/minilibx-linux.git $(LIBX); fi
	rm -rf $(LIBX)/.git

libft:
	if [ ! -d $(LIBFT) ]; then git clone git@github.com:JulioSouza09/libft.git $(LIBFT); fi
	rm -rf $(LIBFT)/.git

libclean:
	rm -rf $(LIBX) $(LIBFT)

clean:
	make clean -C $(LIBFT)
	rm -rf $(ODIR)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONy: all mlx libft libclean clean fclean re
