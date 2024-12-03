/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:08:19 by razamora          #+#    #+#             */
/*   Updated: 2024/07/26 17:30:34 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_line(char *str)
{
	size_t	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str [i] == '\n')
		i++;
	return (i);
}

static char	*ft_cut_line(char *str)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	if (!*str)
		return (free(str), NULL);
	j = size_line(str);
	new = (char *)malloc((strlen_gnl(str) - j) * sizeof(char) + 1);
	if (!new)
		return (free(new), NULL);
	while (str[j] != '\0')
		new[i++] = str[j++];
	new[i] = '\0';
	if (!*new)
		return (free(str), free(new), NULL);
	free(str);
	return (new);
}

static char	*ft_extract_line(char *str)
{
	size_t	i;
	char	*new;

	if (!str || str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	i = size_line(str);
	new = (char *) malloc(i * sizeof(char) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char	*read_file(char *memory_line, int fd)
{
	int		num_bytes;
	char	*buffer;

	num_bytes = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr_gnl(memory_line, '\n'))
	{
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if (!num_bytes)
			break ;
		if (num_bytes < 0)
		{
			free(buffer);
			(free(memory_line), memory_line = NULL);
			return (NULL);
		}
		buffer[num_bytes] = '\0';
		memory_line = ft_strjoin_gnl(memory_line, buffer);
	}
	return (free(buffer), memory_line);
}

char	*get_next_line(int fd)
{
	static char	*memory_line[FD_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	memory_line[fd] = read_file(memory_line[fd], fd);
	line = ft_extract_line(memory_line[fd]);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	memory_line[fd] = ft_cut_line(memory_line[fd]);
	return (line);
}
