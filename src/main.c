/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:41:01 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/12 11:33:39 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int arg_count, char **argv_list, char **envp)
{
	pid_t	pid;
	int		fd[2]; // fd[0] read from, fd[1] write to
	char	*cmd1;
	char	*cmd2;

	// Check number of arguments
	if (arg_count != 5)
		return (error_msg(1, "Usage: ./pipex file1 cmd1 cmd2 file2"));

	// Save command paths
	cmd1 = get_cmd_path(envp, argv_list[2]);
	cmd2 = get_cmd_path(envp, argv_list[3]);
	if (!cmd1 || !cmd2)
		return (free_cmd_paths(cmd1, cmd2));

	// Data
	int data[10];
	printf("Add number: ");
	for (int i = 0; i < 10; i++)
	{
		scanf("%d", &data[i]);
	}

	// Creating the pipeline
	if (pipe(fd) == -1)
		return (error_msg(1, "error while opening the pipe"));

	// Creating a child process
	pid = fork();
	if (pid == -1)
		return (free_cmd_paths(cmd1, cmd2));
	if (pid == 0)
		child_routine(pid, fd, data);
	else
		parent_routine(pid, fd, data);

	// Exit program
	return (EXIT_SUCCESS);
}

/*
int main(void)
{
	pid_t	pid;
	int		fd[2];
	// fd[0] - read from
	// fd[1] - write to

	// Connect two programs together
	if (pipe(fd) == -1)
		return (error_msg(1, "error while opening the pipe"));
	
	// Create child process
	pid = fork();
	if (pid == 0) // We're in the CHILD process
	{
		close(fd[0]);
		int x;
		printf("Input a number: ");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int)); // Writing to the pipe
		close(fd[1]);
	}
	else // We're in the PARENT process
	{
		close(fd[1]);
		int y;
		read(fd[0], &y, sizeof(int)); // Reading from the pipe
		close(fd[0]);
		y *= 3;
		printf("Got from child process %d\n", y);
	}
		
	return (0);
}
*/