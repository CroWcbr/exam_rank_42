 #include <unistd.h>
 #include <stdio.h>

typedef struct s_background
{
	int		width;
	int		height;
	char	type;
}t_background;

typedef struct s_rectangle
{
	char	arg;
	float	x;
	float	y;
	float	width;
	float	height;
	char	type;
}t_rectangle;

int main(int argc, char **argv)
{
	FILE	*f_open;

	if (argc != 2)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	f_open = fopen(argv[1], "r");
	if (f_open == 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}

	t_background b;
	b.width = 0;
	b.height = 0;
	b.type = '\0';
	int f_scanf;
	f_scanf = fscanf(f_open, "%d %d %c\n", &b.width, &b.height, &b.type);
	if (f_scanf != 3)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (b.width <= 0 && b.width > 300 && b.height <= 0 && b.height > 300)
	if (f_scanf != 3)
	{
		write(2, "Error\n", 6);
		return (1);
	}

	int i;
	int j;
	int draw[b.height][b.width];
	i = -1;
	while (++i < b.height)
	{
		j = -1;
		while (++j < b.width)
		{
			draw[i][j] = b.type;
		}
	}

	t_rectangle r;
	while ((f_scanf = fscanf(f_open, "%c %f %f %f %f %c\n", &r.arg, &r.x, &r.y, &r.width, &r.height, &r.type)) != -1)
	{
		if (f_scanf != 6)
		{
			write(2, "Error\n", 6);
			return (1);
		}
		if (r.arg != 'R' && r.arg != 'r')
		{
			write(2, "Error\n", 6);
			return (1);
		}	

		i = -1;
		while (++i < b.height)
		{
			j = -1;
			while (++j < b.width)
			{
				if (i >= r.y && i <= r.y + r.height && j >= r.x && j <= r.x + r.width)
				{
					if (r.arg == 'R')
						draw[i][j] = r.type;
					else
					{
						if ((i < r.y + 1 || i > r.y + r.height - 1) || (j < r.x + 1 || j > r.x + r.width - 1))
							draw[i][j] = r.type;
					}
				}
			}
		}			
	}

	i = -1;
	while (++i < b.height)
	{
		j = -1;
		while (++j < b.width)
			write(1, &draw[i][j], 1);
		write(1, "\n", 1);		
	}
	return (0);
}
