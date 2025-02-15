/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 07:13:01 by razamora          #+#    #+#             */
/*   Updated: 2025/02/15 17:23:02 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
malloc, free, write, close, fork, waitpid, signal, kill,
exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp
*/
#include "pipex_bonus.h"


void	err(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int	cd(char *arg)
{
	// if (i != 2)
	// {
	// 	err("error: cd: bad arguments\n");
	// 	return (1);
	// }
	printf("inside cd::arg = %s\n", arg);
	if (chdir(arg) == -1)
	{
		err("error: cd: cannot change directory to ");
		err(arg);
		err("\n");
		return (1);
	}
	return (0);
}

pid_t	process_one(char **argv, char **envp, int *file_pipe)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		(perror("Error:"), exit(1));
	if (pid == 0)
	{
		dup2(file_pipe[1], 1);
		close(file_pipe[0]);
		close(file_pipe[1]);
		if (ft_strcmp(argv[1], "cd") == 0)
		{
				exit(cd(argv[2]));
				printf("111111111111\n");
				exit(0);
		}
		
		else
			ft_check_command(argv[1], envp);
	}
	return (pid);
}

pid_t	middle_process(char **argv, char *cmd, char **envp, int file_pipe[2])
{
	pid_t	id;
	int		middle_file[2];

	ft_putstr_fd(cmd, 1);
	if (pipe(middle_file) == -1)
		perror("Error:");
	id = fork();
	if (id == -1)
		perror("Error:");
	else if (id == 0)
	{
		dup2(file_pipe[0], STDIN_FILENO);
		dup2(middle_file[1], STDOUT_FILENO);
		close(file_pipe[1]);
		close(file_pipe[0]);
		close(middle_file[1]);
		close(middle_file[0]);
		if (ft_strcmp(cmd, "cd") == 0)
		{
				exit(cd(cmd));
				printf("22222222222222\n");
		}
		else
			ft_check_command(cmd, envp);
		
	}
	close(file_pipe[0]);
	close(middle_file[1]);
	file_pipe[0] = middle_file[0];
	return (id);
}

pid_t	process_fin(char **argv, char **envp, int argc, int *file_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		(perror("Error:"), exit(1));
	if (pid == 0)
	{
		dup2(file_pipe[0], 0);
		close(file_pipe[0]);
		close(file_pipe[1]);
		
		if (ft_strcmp(argv[argc -2], "cd") == 0)
		{
			exit(cd(argv[argc -1]));
		}
		else	
			ft_check_command(argv[argc - 1], envp);
	}
	close(file_pipe[0]);
	close(file_pipe[1]);
	return (pid);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		file_pipe[2];
	int		num_pids;
	pid_t	*pids;

	pids = malloc((argc - 1) * sizeof(pid_t));
	if (pipe(file_pipe) == -1)
		(perror("Error:"), exit(1));
	i = 2;
	num_pids = 1;

	pids[0] = process_one(argv, envp, file_pipe); // first argument
	while (i < (argc - 1))
	{
		if (ft_strcmp(argv[i], "|") == 0 || ft_strcmp(argv[i], ";") == 0)
		{
			i++;
		}
		i += ((pids[num_pids - 1] = middle_process(argv,argv[i], envp, file_pipe)), 1);
		num_pids++;
	}
	pids[num_pids - 1] = process_fin(argv, envp, argc, file_pipe);
	exit(catch_exp(argc, pids));
}
