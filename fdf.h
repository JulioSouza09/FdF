#ifndef FDF_H
# define FDF_H

typedef	struct s_point
{
	int	x;
	int	y;
	int	z;
	int	x2;
	int	y2;
	int	color;
}	t_point;

typedef struct s_coord
{
	int	x;
	int	y;
	int	z;
}	t_coord;

typedef struct	s_dimension
{
	int	width;
	int	height;
}	t_dimension;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		end;
}	t_data;



void	free_matrix(t_point **matrix, int position);
t_point	**get_map(char *filename, t_dimension *dimensions);
int	count_matrix(char **matrix);
t_point	*get_line_values(char **splited_line, t_dimension *dimensions);

#endif
