# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 13:02:42 by jcesar-s          #+#    #+#              #
#    Updated: 2025/09/02 13:02:25 by jcesar-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
IDIR = include/
ODIR = obj/
CDIR = src/
BDIR = $(CDIR)bonus/
LIBX = $(IDIR)minilibx
LIBXA = $(LIBX)/libmlx_Linux.a
LIBFT = $(IDIR)libft
LIBFTA = $(LIBFT)/libft.a
SRC = main.c input_handler.c map_creator.c map_utils.c utils.c init_app.c
SRC += draw_line.c draw_utils.c renderer.c key_handler.c colors.c
SRC += map_transformer.c
_SRC = $(patsubst %.c, $(CDIR)%.c, $(SRC))
OBJS = $(patsubst %.c, $(ODIR)%.o, $(SRC))

BNAME = fdf_bonus
BSRC = main_bonus.c input_handler_bonus.c map_creator_bonus.c map_utils_bonus.c
BSRC += draw_line_bonus.c draw_utils_bonus.c renderer_bonus.c key_handler_bonus.c
BSRC += map_transformer_bonus.c events_bonus.c utils_bonus.c init_app_bonus.c
BSRC += colors_bonus.c
_BSRC = $(patsubst %.c, $(BDIR)%.c, $(BSRC))
BOBJS = $(patsubst %.c, $(ODIR)%.o, $(BSRC))

$(ODIR)%.o: $(CDIR)%.c
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IDIR) -I $(LIBX) -I $(LIBFT)

$(ODIR)%.o: $(BDIR)%.c
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IDIR) -I $(LIBX) -I $(LIBFT)

all: $(NAME)

$(NAME): $(OBJS) $(LIBXA) $(LIBFTA)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBX) -lmlx -lXext -lX11 -L $(LIBFT) -lft -lm -o $(NAME) 

$(BNAME): $(BOBJS) $(LIBXA) $(LIBFTA)
	$(CC) $(CFLAGS) $(BOBJS) -L $(LIBX) -lmlx -lXext -lX11 -L $(LIBFT) -lft -lm -o $(BNAME) 

$(LIBFTA):
	make -C $(LIBFT) --no-print-directory

$(LIBXA):
	make -C $(LIBX) --no-print-directory

mlx:
	@if [ ! -d $(LIBX) ]; then git clone git@github.com:42paris/minilibx-linux.git $(LIBX); fi
	rm -rf $(LIBX)/.git
	make -C $(LIBX)

libft:
	@if [ ! -d $(LIBFT) ]; then git clone git@github.com:JulioSouza09/libft.git $(LIBFT); fi
	rm -rf $(LIBFT)/.git
	make -C $(LIBFT)

libs: mlx libft

libclean:
	rm -rf $(LIBX) $(LIBFT)

clean:
	make clean -C $(LIBFT)
	make clean -C $(LIBX)
	rm -rf $(ODIR)

fclean: clean
	make fclean -C $(LIBFT)
	make clean -C $(LIBX)
	rm -f $(NAME)
	rm -f $(BNAME)

re: fclean all 

bonus: $(BNAME)

.PHONy: all mlx libft libs libclean clean fclean re bonus
