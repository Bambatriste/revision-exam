#include "get_next_line.h"

#define BUFFER_SIZE 20

int ft_strlen(char *str)
{
	int i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	*ft_memmove(void *dst, void *src, int len)
{
	char *d;
	char *s;

	d = dst;
	s = src;
	// if (dst == src)
	// return (dst);
	if (s < d)
	{
		while (len--)
		{
			*(d + len) = *(s + len);
		}
		return (dst);
	}
	while (len--)
		*d++ = *s++;
	return (dst);
}

int	gnl_has_return(char *str)
{
	int i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return(1);
		i++;
	}
	return (0);
}

char *join_str(char *s1, char *s2)
{
	int s1_len;
	int s2_len;
	int tot_len;
	char *rtn;

	if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	tot_len = s1_len + s2_len + 1;
	rtn = malloc(sizeof(char) * tot_len);
	rtn = ft_memmove(rtn, s1, s1_len);
	rtn = ft_memmove(rtn + s1_len, s2, s2_len);
	rtn[tot_len - 1] = '\0';
	free(s1);
	return (rtn);
}

char *get_line(char *str)
{
	int i = 0;
	char *rtn;

	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	rtn = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		rtn[i] = str[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

char *get_save(char *str)
{
	char *rtn;
	int i = 0;
	int j = 0;

	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	/* if (!save[i])
	{
		free(save);
		return (NULL);
	}*/
	rtn = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	i++;//passe le /n
	while (str[i])
		rtn[j++] = str[i++];
	rtn[j] = '\0';
	free(str);
	return (rtn);
}

void	update_save_line(char **buff, char ***line, char **save)
{
	free(*buff);
	**line = get_line(*save);
	*save = get_save (*save);
}

int get_next_line(char **line)
{
	char *buff;
	static char *save;
	int reader;

	reader = 1;
	if (!line || BUFFER_SIZE <=0)
		return (-1);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while ((!gnl_has_return(save)) && reader != 0)
	{
		reader = read( 0 , buff , BUFFER_SIZE);
		if (reader == -1)
		{
			free(buff);
			return (-1);
		}
		buff[reader] = '\0';
		save = join_str(save, buff);
	}
	update_save_line(&buff, &line, &save);
	if (reader == 0)
		return (0);
	return (1);
}
