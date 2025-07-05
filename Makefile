# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 13:02:42 by jcesar-s          #+#    #+#              #
#    Updated: 2025/07/04 12:18:12 by jcesar-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf
CC=cc
CFLAGS=-Wall -Wextra -Werror
LIBX=lib/minilibx
LIBXA=$(LIBX)/libmlx_linux.a
LIBFT=lib/libft
LIBFTA=$(LIBFT)/libft.a
SRC= main.c
OBJS=./objs/$(SRC:.c=.o)
ODIR=objs

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I $(LIBX) -I $(LIBFT) -g

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(LIBX)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBX) -lmlx -lXext -lX11 -lm -L $(LIBFT) -lft -o $(NAME) 

mlx:
	rm -rf $(LIBX)
	git clone git@github.com:42paris/minilibx-linux.git $(LIBX)
	rm -rf $(LIBX)/.git

libft:
	rm -rf $(LIBFT)
	git clone git@github.com:JulioSouza09/libft.git $(LIBFT)
	rm -rf $(LIBX)/.git

libclean:
	rm -rf $(LIBX) $(LIBFT)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
