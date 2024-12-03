/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 07:25:06 by razamora          #+#    #+#             */
/*   Updated: 2024/08/02 20:26:16 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	ft_check_command(char *cmd, char **envp);
pid_t	process_one(char **argv, char **envp, int *file_pipe);
int		middle_process(char *cmd, char **envp, int file_pipe[2]);
pid_t	process_fin(char **argv, char **envp, int argc, int *file_pipe);
char	*ft_find_path(char **envp);
void	ft_free_memory(char **tab);
int		open_file(char *file, int type);
void	ft_check_command(char *cmd, char **envp);
int		ft_command_error(char *cmd);
void	ft_error_file(int *file_pipe, char *file);
char	*ft_get_path(char **full_cmd, char **envp);
int		ft_strcmp(char *s1, char *s2);
int		finaly_openfile(char **av, int argc);
void	ft_close_fd_final(int fd, int *file_pipe);
void	ft_is_empty(char *cmd);
void	ft_exit_here_doc(char *line, char *tmp, int *file_pipe);
int		catch_exp(int argc, pid_t *pids);

#endif