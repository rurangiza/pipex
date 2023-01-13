/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:41:01 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/13 15:43:48 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
 * WHere I try stuff
*/ 

/*

Output of ping goes to ping result

dup2(file_fd, STDOUT);




*/

// Make sur the commands are valid then save relevent info
int	index = 2;
while (index < arg_count - 1)
	init_cmd(envp, arg_list[index], &data.cmd[index - 2]);


int	main(int arg_count, char **arg_list, char **envp)
{
	pid_t	pid;
	//int		fd[2];
	char	*cmd_1;
	char	*cmd_2;

	t_data	cmd_1;
	t_data	cmd_2;

	// Check number of arguments
	if (arg_count != 5)
		return (error_msg(1, "Usage: ./pipex file1 cmd1 cmd2 file2"));

	// Save command paths
	info_msg(0, "%s", arg_list[2]);
	cmd_1 = get_cmd_path(envp, arg_list[2]);
	cmd_2 = get_cmd_path(envp, arg_list[3]);
	if (!cmd_1 || !cmd_2)
		return (free_cmd_paths(cmd_1, cmd_2));
	info_msg(0, "%s", cmd_1);
	// Creating a child process
	pid = fork();
	if (pid == -1)
		return (free_cmd_paths(cmd_1, cmd_2));
	else if (pid == 0) // Child process
	{
		char **args = ft_split(arg_list[2], ' ');

		int file_fd = open(arg_list[1], O_RDONLY);
		dup2(file_fd, STDIN_FILENO);
		execve(cmd_1, args, NULL);
	}
	else // Parent process
	{
		int status;
		waitpid(pid, &status, 0);
	}
	// Exit program
	return (EXIT_SUCCESS);
}
