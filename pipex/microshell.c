/*

Assignment name  : microshell
Expected files   : microshell.c
Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp
--------------------------------------------------------------------------------------

Write a program that will behave like executing a shell command
- The command line to execute will be the arguments of this program
- Executable's path will be absolute or relative but your program must not build a path (from the PATH variable for example)
- You must implement "|" and ";" like in bash
	- we will never try a "|" immediately followed or preceded by nothing or "|" or ";"
- Your program must implement the built-in command cd only with a path as argument (no '-' or without parameters)
	- if cd has the wrong number of argument your program should print in STDERR "error: cd: bad arguments" followed by a '\n'
	- if cd failed your program should print in STDERR "error: cd: cannot change directory to path_to_change" followed by a '\n' with path_to_change replaced by the argument to cd
	- a cd command will never be immediately followed or preceded by a "|"
- You don't need to manage any type of wildcards (*, ~ etc...)
- You don't need to manage environment variables ($BLA ...)
- If a system call, except execve and chdir, returns an error your program should immediatly print "error: fatal" in STDERR followed by a '\n' and the program should exit
- If execve failed you should print "error: cannot execute executable_that_failed" in STDERR followed by a '\n' with executable_that_failed replaced with the path of the failed executable (It should be the first argument of execve)
- Your program should be able to manage more than hundreds of "|" even if we limit the number of "open files" to less than 30.

for example this should work:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

Hints:
Don't forget to pass the environment variable to execve

Hints:
Do not leak file descriptors!

*/


#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

void	err(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int	cd(char **argv, int i)
{
	if (i != 2)
	{
		err("error: cd: bad arguments\n");
		return (1);
	}
	if (chdir(argv[1]) == -1)
	{
		err("error: cd: cannot change directory to ");
		err(argv[1]);
		err("\n");
		return (1);
	}
	return (0);
}

void	set_pipe(int has_pipe, int *fd, int end)
{
	if (has_pipe && (dup2(fd[end], end) == -1 || close(fd[0]) == -1
			|| close(fd[1]) == -1))
	{
		err("error: fatal\n");
		exit(1);
	}
}
void ft_print(char **argv)
{
	int i = 0;
	while (argv[i])
	{
		printf("argv[%d] = %s\n", i, argv[i]);
		i++;
	}
}
int	exec(char **argv, int i, char **envp)
{
	int	has_pipe;
	int	fd[2];
	int	pid;
	int	status;

	has_pipe = argv[i] && !strcmp(argv[i], "|");
	printf("has_pipe = %d\n", has_pipe);
	if (!has_pipe && !strcmp(*argv, "cd"))
		return (cd(argv, i));
	if (has_pipe && pipe(fd) == -1)
	{
		err("error: fatal\n");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		err("error: fatal\n");
		exit(1);
	}
	// printf("  ---> execve: %s\n", *argv);
	// 	ft_print(argv);
	if (!pid)
	{
		argv[i] = 0;
		set_pipe(has_pipe, fd, 1);
		if (!strcmp(*argv, "cd"))
			exit(cd(argv, i));
		

		execve(*argv, argv, envp);
		
		err("error: cannot execute ");
		err(*argv);
		err("\n");
		exit(1);
	}
	waitpid(pid, &status, 0);
	set_pipe(has_pipe, fd, 0);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}
/*
$>./microshell  
microshell
i love my microshell
$>
*/
// $>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
/*
microshell
microshell2.c
microshell_bk.c
microshell.c
i love my microshell
c2r7s4% 
*/
int	main(int argc, char **argv, char **envp)
{
	int	status;
	int	i;

	(void)argc;
	i = 0;
	status = 0;
	while (argv[i])
	{
		argv += i + 1; // skip the previous command name program
		i = 0; // reset the index
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
		{
			//printf("dentro while argv[%d] = %s\n", i, argv[i]);
			i++;
		}
		if (i)
		{
			//printf("dentro if argv[%d] = %s\n", i, argv[i]);
			status = exec(argv, i, envp);
		}
	}
	return (status);
}