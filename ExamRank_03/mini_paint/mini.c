 #include <unistd.h>
 #include <stdio.h>
#include <math.h>

typedef struct s_background
{
	int		width;
	int		height;
	char	type;
}t_background;

typedef struct s_circle
{
	char	arg;
	float	x;
	float	y;
	float	rad;
	char	type;
}t_circle;

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
	printf("w = %d, h = %d, t = %c\n", b.width, b.height, b.type);

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

	t_circle r;
	while ((f_scanf = fscanf(f_open, "%c %f %f %f %c\n", &r.arg, &r.x, &r.y, &r.rad, &r.type)) != -1)
	{
		if (f_scanf != 5)
		{
			write(2, "Error\n", 6);
			return (1);
		}
		if (r.arg != 'C' && r.arg != 'c')
		{
			write(2, "Error\n", 6);
			return (1);
		}	
		printf("a = %c, x = %f, y = %f c = %f, t = %c\n", r.arg, r.x, r.y, r.rad, r.type);

		i = -1;
		while (++i < b.height)
		{
			j = -1;
			while (++j < b.width)
			{
				if (sqrtf((j - r.x) * (j - r.x) + (i - r.y) * (i - r.y)) <= r.rad)
				{
					if (r.arg == 'C')
						draw[i][j] = r.type;
					else
					{ 
						if (sqrtf((j - r.x) * (j - r.x) + (i - r.y) * (i - r.y)) + 1 > r.rad)
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
	fclose(f_open);
	return (0);
}