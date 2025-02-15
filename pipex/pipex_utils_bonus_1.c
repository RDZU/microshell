/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 07:18:50 by razamora          #+#    #+#             */
/*   Updated: 2025/02/04 22:03:56 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_get_path(char **full_cmd, char **envp)
{
	char	*cmd;
	char	*path;
	char	**path_split;
	int		i;
	char	*new;

	i = 0;
	path = ft_find_path(envp);
	if (path == NULL)
	{
		new = ft_strdup(full_cmd[0]);
		(ft_command_error(new));
	}
	cmd = ft_strjoin("/", full_cmd[0]);
	path_split = ft_split(path, ':');
	while (path_split[i] != NULL)
	{
		path = ft_strjoin(path_split[i], cmd);
		if (access(path, F_OK | X_OK) == 0)
			return (free(cmd), ft_free_memory(path_split), path);
		free(path);
		i++;
	}
	(free(cmd), ft_free_memory(path_split));
	return (NULL);
}

int ft_strlen_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' || str[i] != ' ')
		i++;
	return (i);
}
char *ft_space (char *str, char c)
{
	int i;
	char *s;
	
	i = ft_strlen_space(str);
	s = malloc(sizeof(char) * i + 1);
	while (*str != '\0' || *str != ' ')
	{
		*s = *str;
		s++;
		str++;
	}
	return (s);
}


int	ft_check_command(char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	ft_is_empty(cmd);
	//s_cmd = ft_space(cmd, ' ');
	s_cmd = ft_split(cmd, ' ');
	
	
		if (execve(s_cmd[0], s_cmd, envp) == -1)
			ft_command_error(s_cmd[0]);
	// }
	// 	if (execve(s_cmd[0], s_cmd, envp) == -1)
	// 		(ft_command_error(s_cmd[0])/*, ft_free_memory(s_cmd)*/);
	//if (access(s_cmd[0], F_OK | X_OK) == 0 && s_cmd[0][0] == '/')
	//{
	//	printf("s_cmd[0]");
		// if (execve(s_cmd, cmd, envp) == -1)
		// 	(ft_command_error(s_cmd)/*, ft_free_memory(s_cmd)*/);
	//}
	// if (access(s_cmd[0], F_OK | X_OK) == 0 && ft_strnstr(s_cmd[0], "./", 2))
	// {
	// 	printf("s_cmd[1]");
	// 	if (execve(s_cmd[0], s_cmd, envp) == -1)
	// 		(ft_command_error(s_cmd[0]), ft_free_memory(s_cmd));
	// }
	// else if (access(s_cmd[0], F_OK | X_OK) != 0 && ft_strchr(s_cmd[0], '/'))
	// 	(ft_command_error(s_cmd[0]), ft_free_memory(s_cmd));
	// else
	// {
	// 	printf("s_cmd[2]");
	// 	path = ft_get_path(s_cmd, envp);
	// 	if (path == NULL || execve(path, s_cmd, envp) == -1)
	// 		(ft_command_error(s_cmd[0]), ft_free_memory(s_cmd));
	// 	ft_free_memory(s_cmd);
	// 	free(path);
	// }

	return 0;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_error_file(int *file_pipe, char *file)
{
	close(file_pipe[0]);
	close(file_pipe[1]);
	perror(file);
}
