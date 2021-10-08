#include "utils.h"


int ft_putchar(char c)
{
	return (write(1 , &c, 1));
}

void	convert_s(data *infos, va_list ap)
{
	char *s;
	int i = 0;

	s = va_arg(ap , char*);
	if (!s)
		s = "(null)";
	while (s[i])
	{
		infos->read = infos->read + ft_putchar(s[i]);
		i++;
	}
}

unsigned int get_sign (int nbr, data *infos)
{
	unsigned int n;
	if (nbr < 0)
	{
		nbr++;
		nbr = -nbr;
		infos->nb_neg = 1;
		n = (unsigned int)nbr;
		n++;
	}
	else
		n = (unsigned int)nbr;
	return (n);
}

int get_len(unsigned int n)
{
	int i = 0;
	if (n == 0)
		i = 1;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

void print_nb(unsigned int n)
{
	if (n > 9)
		print_nb(n / 10);
	ft_putchar(n % 10 + '0');
}

void	convert_d(data *infos, va_list ap)
{
	int nbr = va_arg(ap, int);
	unsigned int n = get_sign(nbr, infos);
	int size = get_len(n);

	if (infos->nb_neg == 1)
		infos->read += ft_putchar('-');

	print_nb(n);
	infos->read += size;
}

int	 get_len_x ( unsigned int n)
{
	int i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n/16;
		i++;
	}
	return (i);
}

void	print_x(unsigned int n, const char *base)
{
	if (n > 15)
		print_x (n / 16, base);
	ft_putchar(base[n % 16]);
}

void	convert_x(data *infos , va_list ap)
{
	unsigned int n = va_arg(ap, int);
	int size = get_len_x(n);
	const char *base = "0123456789abcdef";

	print_x(n, base);
	infos->read = infos->read + size;
}

void	convert(char *fmt, data *infos, va_list ap)
{
	if (fmt[infos->i] == 's')
		convert_s(infos, ap);
	else if (fmt[infos->i] == 'd')
		convert_d(infos, ap);
	else if (fmt[infos->i] == 'x')
		convert_x(infos, ap);
	else
		infos->read += ft_putchar(fmt[infos->i]);
}

void get_infos(char *fmt, va_list ap, data *infos)
{
	while(fmt[infos->i])
	{
		infos->nb_neg = 0;
		if (fmt[infos->i] == '%')
		{
			infos->i++;
			convert(fmt, infos, ap);
		}
		else
		{
			infos->read = infos->read + ft_putchar(fmt[infos->i]);
		}
		infos->i++;
	}
}

int ft_printf(char *fmt, ...)
{
	va_list ap;
	data infos;

	infos.i = 0;
	infos.read = 0;
	va_start(ap, fmt);
	get_infos(fmt, ap, &infos);

	va_end(ap);

	return infos.read;

}
