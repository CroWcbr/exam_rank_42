#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

static void ft_putchar(char c)
{
	write(1, &c, 1);
}

static void ft_putnbr(long nbr)
{
	char *base="0123456789";

	if (nbr >= 10)
		ft_putnbr(nbr / 10);
	ft_putchar(base[nbr % 10]);
}

static void ft_putnbrx(unsigned int nbr)
{
	char *base="0123456789abcdef";

	if (nbr >= 16)
		ft_putnbrx(nbr / 16);
	ft_putchar(base[nbr % 16]);
}

int ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len = 0;
	int		width;
	int		pres;
	int		pres_point;
	int		i;
	char	type;

	va_start(ap, format);
	while(*format)
	{
		if (*format != '%')
		{
			write(1, format, 1);
			format++;
			len++;
		}
		else
		{
			type = '\0';
			width = -1;
			pres = 0;
			pres_point = 0;
			format++;
			i = 0;
			while (*format && !type) 
			{
				if (*format == 's' || *format == 'd' || *format == 'x')
				{
					type = *format;
					format++;
				}
				else if (*format == '.')
				{
					pres = 0;
					pres_point = 1;
					format++;
					while (*format >= '0' && *format <='9')
					{
						pres = pres * 10 + *format - '0';
						format++;
					}
				}
				else if (*format >= '0' && *format <='9')
				{
					width = 0;
					while (*format >= '0' && *format <='9')
					{
						width = width * 10 + *format - '0';
						format++;
					}
				}
				else
					format++;
			}
			if (type == '\0')
				;
			else if (type == 's')
			{
				char *s;
				int strlen;
				int i;
				int j;

				s = va_arg(ap, char *);
				if (!s)
					s = "(null)";
				strlen = 0;
				while (*(s + strlen))
					strlen++;

				if (strlen < pres)
					pres = strlen;		
				if (!pres_point)
					pres = strlen;
				if (width < pres)
					width = pres;

				i = 0;
				while (i < width - pres)
				{
					char c = ' ';
					write(1, &c, 1);
					i++;
				}
				j = 0;
				while (i + j < width)
				{
					write(1, s + j, 1);
					j++;
				}
				len +=width;				
			}
			else if (type == 'd')
			{
				int d = va_arg(ap, int);
				long int tmp;
				long int nbr;				
				int minus = 0;
				int nbrlen = 0;

				if (d < 0)
				{
					minus = 1;
					tmp = d;
					tmp *= -1;
				}
				else
					tmp = d;

				nbr = tmp;
				if (tmp == 0)
				{
					if (pres_point && pres == 0)
						nbrlen = 0;
					else
						nbrlen = 1;
				}
				else
				{
					while (tmp != 0)
					{
						tmp /= 10;
						nbrlen++;
					}
				}

				if (nbrlen > pres)
					pres = nbrlen;		
				if (width < pres + minus)
					width = pres + minus;

				i = 0;
				while (i < width - pres - minus)
				{
					char c = ' ';
					write(1, &c, 1);
					i++;
				}
				if (minus)
				{
					char c = '-';
					write(1, &c, 1);
					i++;
				}
				while (i < width - nbrlen)
				{
					char c = '0';
					write(1, &c, 1);
					i++;
				}
				if (i < width)
					ft_putnbr(nbr);
				len += width;
			}
			else if (type == 'x')
			{
				unsigned int x = (unsigned int)va_arg(ap, int);
				unsigned int tmp = x;
				unsigned int nbr = x;				
				int nbrlen = 0;

				if (tmp == 0)
				{
					if (pres_point && pres == 0)
						nbrlen = 0;		
					else
						nbrlen = 1;
				}
				else
				{
					while (tmp != 0)
					{
						tmp /= 16;
						nbrlen++;
					}
				}

				if (nbrlen > pres)
					pres = nbrlen;		
				if (width < pres)
					width = pres ;

				i = 0;
				while (i < width - pres)
				{
					char c = ' ';
					write(1, &c, 1);
					i++;
				}
				while (i < width - nbrlen)
				{
					char c = '0';
					write(1, &c, 1);
					i++;
				}		
				if (i < width)
					ft_putnbrx(nbr);
				len +=width;
			}			
		}
	}
	return (len);
}
