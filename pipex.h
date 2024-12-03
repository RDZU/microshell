/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 07:22:18 by razamora          #+#    #+#             */
/*   Updated: 2024/07/31 14:16:56 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int		exec_command(char **full_cmd, char **env);
void	ft_check_command(char *cmd, char **envp);
char	*ft_find_path(char **envp);
void	ft_free_memory(char **tab);
char	*ft_get_path(char **full_cmd, char **envp);
void	ft_error_file(int *file_pipe, char *file);
int		ft_command_error(char *cmd);
void	ft_is_empty(char *cmd);

#endif