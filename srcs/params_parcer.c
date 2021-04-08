
#include "cub3d.h"

int		get_res(char *line, t_args *s_args)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_isalnum(line[i]) && line[i] != ' ')
			return (-1);
		++i;
	}
	skip_spaces(&line);
	if (!ft_isalnum(*line))
		return (-1);
	s_args->win_w = ft_atoi(line);
	skip_numbers(&line);
	skip_spaces(&line);
	if (!ft_isalnum(*line))
		return (-1);
	s_args->win_h = ft_atoi(line);
	return (1);
}

int		get_path(char **path, char *line)
{
	int i;

	skip_spaces(&line);
	i = 0;
	while (line[i])
		if (ft_isspace(line[i++]))
			return (-1);
	if ((*path = ft_strdup(line)) == NULL)
	{
		perror("Malloc error.\n");
		return (-1);
	}
	return (1);
}

int		get_color(char *line, unsigned int *color)
{
	skip_spaces(&line);
	if (!ft_isalnum(*line))
		return (-1);
	*color += ft_atoi(line) << 16;
	skip_numbers(&line);
	if ((line = ft_strnstr(line, ",", 1)) == NULL)
		return (-1);
	++line;
	skip_spaces(&line);
	if (!ft_isalnum(*line))
		return (-1);
	*color += ft_atoi(line) << 8;
	skip_numbers(&line);
	if ((line = ft_strnstr(line, ",", 1)) == NULL)
		return (-1);
	++line;
	skip_spaces(&line);
	if (!ft_isalnum(*line))
		return (-1);
	*color += ft_atoi(line);
	return (1);
}