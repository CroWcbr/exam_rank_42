#include "get_next_line.h"

int get_next_line(char **line)
{
	int r = 1;
	char buffer[1];
	char *tmp;
	int i = 1;
	int j;

	buffer[0] = '\0';
	*line = malloc(sizeof(char) * i);
	if (!(*line))
		return (-1);
	(*line)[0] = '\0';
	while(r > 0)
	{
		r = read(0, buffer, 1);
		if (r == -1)
			return(r);
		if (r == 0 && *line == '\0')
			return(r);
		if (r == 0)
			break;
		if (buffer[0] == '\0' || buffer[0] == '\n')
			break ;
		i = 0;
		while ((*line)[i])
			i++;
		if (!(tmp = malloc(i + 2)))
			return (-1);
		i = 0;
		while ((*line)[i] != '\0')
		{
			tmp[i] = (*line)[i];
			i++;
		}
		tmp[i++] = buffer[0];
		tmp[i++] = '\0';
		free(*line);
		*line = tmp;
	}
	return (r);
}
