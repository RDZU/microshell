/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:12:05 by razamora          #+#    #+#             */
/*   Updated: 2024/07/26 17:28:14 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*s != '\0')
	{
		s++;
		i++;
	}
	return (i);
}

char	*ft_strchr_gnl(const char *s1, int ch)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] != '\0')
	{
		if (s1[i] == (char)ch)
			return ((char *)&s1[i]);
		i++;
	}
	if ((char)ch == '\0')
		return ((char *)&s1[i]);
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!s1 & !s2)
		return (NULL);
	i = 0;
	j = 0;
	new = (char *)malloc((strlen_gnl(s1) + strlen_gnl(s2) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	if (s1)
	{
		while (s1[j] != '\0')
			new[i++] = s1[j++];
	}
	j = 0;
	if (s2)
	{
		while (s2[j] != '\0')
			new[i++] = s2[j++];
	}
	new[i] = '\0';
	free(s1);
	return (new);
}
