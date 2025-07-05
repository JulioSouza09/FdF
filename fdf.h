#ifndef FDF_H
# define FDF_H

typedef	struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		end;
}	t_data;



void	free_matrix(t_point **matrix, int position);
t_point	**get_map(int n_lines, int fd, int *w);
int	count_matrix(char **matrix);
t_point	*get_line_values(char **splited_line);

#endif
