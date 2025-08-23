# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 13:02:42 by jcesar-s          #+#    #+#              #
#    Updated: 2025/08/23 10:34:44 by jcesar-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf
CC=cc
CFLAGS=-Wall -Wextra -Werror -O3
LIBX=lib/minilibx
LIBXA=$(LIBX)/libmlx_Linux.a
LIBFT=lib/libft
LIBFTA=$(LIBFT)/libft.a
SRC=main.c input_handler.c map_creator.c map_utils.c utils.c init_app.c
SRC+=draw_line.c draw_utils.c renderer.c key_handler.c colors.c map_transformer.c events.c
_SRC=$(patsubst %.c, srcs/%.c, $(SRC))
OBJS=$(patsubst %.c, objs/%.o, $(SRC))
ODIR=objs
CDIR=srcs
INCDIR=.

$(ODIR)/%.o: $(CDIR)/%.c
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $^ -o $@ -I $(INCDIR) -I $(LIBX) -I $(LIBFT) -g 

all: $(NAME)

$(NAME): $(OBJS) $(LIBXA) $(LIBFTA)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBX) -lmlx -lXext -lX11 -L $(LIBFT) -lft -lm -o $(NAME) 

$(LIBFTA):
	make -C $(LIBFT) --no-print-directory

$(LIBXA):
	make -C $(LIBX) --no-print-directory

mlx:
	rm -rf $(LIBX)
	git clone git@github.com:42paris/minilibx-linux.git $(LIBX)
	rm -rf $(LIBX)/.git

libft:
	rm -rf $(LIBFT)
	git clone git@github.com:JulioSouza09/libft.git $(LIBFT)
	rm -rf $(LIBFT)/.git

libclean:
	rm -rf $(LIBX) $(LIBFT)

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all
