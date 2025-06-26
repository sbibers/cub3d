/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:55:42 by aatieh            #+#    #+#             */
/*   Updated: 2025/06/26 11:30:42 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/inc/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define PI 3.14159265358979323846
# define SPEED 4
# define ROTATE_SPEED 0.03
# define CUB_WIDTH 1280
# define CUB_HEIGHT 720
# define BLOCK 32
# define FOV 5
# define COLISION 20
# define MINI_SIZE 8.0
# define MINI_SCALE 4

typedef struct s_color
{
	uint32_t		r;
	uint32_t		g;
	uint32_t		b;
	uint32_t		a;
	uint32_t		color;
}					t_color;

typedef struct s_draw_map
{
	int		i;
	int		j;
	float	player_y;
	float	player_x;
	int		ini_i;
	int		ini_j;
}			t_draw_map;

typedef struct s_move_player
{
	float	step1_x;
	float	step1_y;
	float	step2_x;
	float	step2_y;
}			t_move_player;

typedef struct s_texture_draw
{
	float		zoom_h;
	float		zoom_w;
	uint32_t	y;
	uint32_t	x;
	int			dy;
	int			dx;
	int			pixel_index;
	t_color		cr;
}				t_texture_draw;

typedef struct s_vertival_line
{
	float			distance;
	float			corrected_distance;
	float			wall_height;
	float			projection_distance;
	float			ray_angle;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_y;
	int				tex_x;
	float			tex_pos;
	float			wall_x;
	int				pixel_index;
	float			step;
	mlx_texture_t	*texture;
}					t_vertival_line;

typedef struct s_texture
{
	mlx_texture_t	*texture;
	int				tex_x;
	float			wall_x;
	uint32_t		color;
	float			step;
	float			tex_pos;
	int				tex_y;
	int				pixel_index;
}					t_texture;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	float	angle;
	float	ray_dir_x;
	float	ray_dir_y;
}			t_ray;

typedef struct s_data_normalize
{
	char		*key;
	char		*value;
	char		*joined;
	char		*final;
	char		*tmp_key;
	char		*tmp_value;
}				t_data_normalize;

typedef struct s_data_check_colors
{
	char		**color;
	char		*temp;
	int			ij[2];
}				t_data_check_colors;

typedef struct s_file
{
	char		*all_file;
	char		**split_all_file;
	char		*complete_file;
}				t_file;

typedef struct s_bearings
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
}				t_bearings;

typedef struct s_count
{
	int			count_no;
	int			count_so;
	int			count_we;
	int			count_ea;
	int			count_floor_color;
	int			count_ceiling_color;
}				t_count;

typedef struct s_map
{
	char		**map;
	char		**copy_map;
	int			height;
	int			width;
}				t_map;

typedef struct s_mlx_cube3d
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_texture_t	*door[2];
}					t_mlx_cube3d;

typedef struct s_player
{
	char	c;
	float	x;
	float	y;
	float	angle;
	float	x_delta;
	float	fraction;
}			t_player;

typedef struct s_sprite
{
	float			x;
	float			y;
	int				frame;
	int				frame_count;
	mlx_texture_t	*f[4];
}					t_sprite;

typedef struct s_cub3d
{
	t_file			file;
	t_bearings		bearings;
	t_count			counter;
	t_map			map;
	t_player		player;
	t_mlx_cube3d	mlx_data;
	t_sprite		moon;
	char			*floor_color;
	char			*ceiling_color;
	int				bott_color[3];
	int				top_color[3];
	float			scale;
}					t_cub3d;

int				skip_spaces(char *str);
int				ft_strlen_matrix(char **str);
char			*read_map(char *map_name);
void			check_empty_read(char *map_name);
void			check_file_name(char *file_name);
char			*ft_strjoin_gnl(char *s1, char *s2);
void			parse_map(t_cub3d *data);
char			**create_2darray(t_cub3d *data);
void			ft_free_split(char **arr);
char			*ft_strndup(const char *s, int n);
void			free_and_exit(t_cub3d *data, char *error);
void			trim_config_lines(char **lines);
void			split_lines(t_cub3d *data);
void			create_map(t_cub3d *data);
void			check_map(t_cub3d *data);
void			get_poisition_of_player(t_cub3d *data);
void			check_bearings_colors(t_cub3d *data);
void			check_map_2(t_cub3d *data);
void			check_map_borders(t_cub3d *data);
void			pad_map(t_cub3d *data);
char			**ft_dup_matrix(char **m, int size, int flag);

void			determine_init_angle(t_cub3d *data);
void			move_player(t_cub3d *data);
void			move_player_extend(t_cub3d *data, t_move_player mv);
void			rotate_player(t_cub3d *data);
void			mouse_handler(double xdelta, double ydelta, void *param);

void			draw_map(t_map *map, t_mlx_cube3d *mlx_data, t_cub3d *data);
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void			draw_cube(float xy[2], int size, int color,
					t_mlx_cube3d *mlx_data);
void			draw_sprite(t_cub3d *data,
					mlx_texture_t *texture, t_sprite *sprite);

void			my_put_pixel(mlx_image_t *img, int x,
					int y, uint32_t color);
void			ft_background(uint32_t start, uint32_t color, mlx_image_t *img);
void			handle_drawing(t_mlx_cube3d *mlx_data, t_cub3d *data);
mlx_texture_t	*get_texture(t_ray *ray, t_cub3d *data);
void			free_mlx_data(t_cub3d *data);

bool			touch(t_player *player, float step_x,
					float step_y, t_cub3d *data);
void			ft_draw_loop(void *param);
void			perform_dda(t_ray *ray, t_cub3d *data);
void			draw_ray_line(t_cub3d *data, float ray_angle, int x);
void			draw_vertical_line(t_ray *ray, t_cub3d *data, int x);

void			delete_textures(t_cub3d *data);
void			pad_map(t_cub3d *data);
void			check_map_borders(t_cub3d *data);
void			flood_fill_2(t_cub3d *data, int player_y, int player_x);
void			init_data(t_cub3d *data);
void			ft_open_door(mlx_key_data_t keydata, void *param);
void			ft_map_background(uint32_t start,
					uint32_t color, mlx_image_t *img);
void	flood_fill(t_cub3d *data, int player_y, int player_x);

#endif
