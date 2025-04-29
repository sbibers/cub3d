LIBFT_DIR = libft
SRC_DIR = src
OBJS_DIR = obj
LIBFT = $(LIBFT_DIR)/libft.a
LIBMLX = MLX42
MLX42_DIR = MLX42/build
MLX = $(MLX42_DIR)/libmlx42.a

SRCS = main read_map check_name_empty parse_map_1 parse_map_2 parse_map_3 parse_map_4 \
		check_colors_textures flood_fill create_map utils_1 ray_casting mlx_handle \
		player_movement draw_map check_map utils_2 check_map_2 single_ray draw_sprite
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))
SRCS := $(addsuffix .c, $(SRCS))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = cub3d

all: libmlx $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	
libmlx:
	@cmake $(LIBMLX) -B $(MLX42_DIR) && make -C $(MLX42_DIR) -j4

$(NAME): $(OBJS) inc/cub3d.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) \
	-L$(LIBFT_DIR) -lft \
	-L$(MLX42_DIR) -lmlx42 \
	-ldl -lglfw -pthread -lm -I.

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c inc/cub3d.h | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

bonus: $(LIBFT) $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)
	rm -rf $(MLX42_DIR)

fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(OBJS_DIR)
	$(RM) $(NAME)

re: fclean all

rebuild_mlx:
	rm -rf $(MLX42_DIR)
	mkdir -p $(MLX42_DIR)
	cmake $(LIBMLX) -B $(MLX42_DIR)
	make -C $(MLX42_DIR) -j4

.PHONY: all bonus clean fclean re rebuild_mlx

