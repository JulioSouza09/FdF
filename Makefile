# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 13:02:42 by jcesar-s          #+#    #+#              #
#    Updated: 2025/06/26 16:47:54 by jcesar-s         ###   ########.fr        #
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
	$(CC) $(CFLAGS) -c $^ -o $@ -I $(LIBX) -g

all: $(NAME)

$(NAME): $(LIBXA) $(LIBFTA) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBX) -lmlx -lXext -lX11 -lm -L $(LIBFT) -lft -o $(NAME) -I $(LIBX) -I $(LIBFT) -g

$(LIBXA): $(LIBX)
	$(MAKE) -C $(LIBX)

$(LIBFTA): $(LIBFT)
	$(MAKE) -C $(LIBFT)

$(LIBX):
	if [ ! -d $(LIBX) ]; then\
		git clone git@github.com:42paris/minilibx-linux.git $(LIBX); rm -rf $(LIBX)/.git; fi

$(LIBFT):
	if [ ! -d $(LIBFT) ]; then\
		git clone git@github.com:JulioSouza09/libft.git $(LIBFT); rm -rf $(LIBX)/.git; fi

libclean:
	rm -rf $(LIBX) $(LIBFT)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
