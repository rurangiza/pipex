/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:41:01 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/12 16:17:39 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
** CREATE A PIPE
** a uni-directional communication channel between two related processes
** "related" means a sibling relationship or a parent-child relationship
*/ 

int	main(int arg_count, char **arg_list, char **envp)
{
	pid_t	pid;
	int		fd[2];
	char	*cmd_1;
	char	*cmd_2;

	// Check number of arguments
	if (arg_count != 5)
		return (error_msg(1, "Usage: ./pipex file1 cmd1 cmd2 file2"));

	// Save command paths
	cmd_1 = get_cmd_path(envp, arg_list[2]);
	cmd_2 = get_cmd_path(envp, arg_list[3]);
	if (!cmd_1 || !cmd_2)
		return (free_cmd_paths(cmd_1, cmd_2));

	// Creating the pipeline
	if (pipe(fd) == -1)
		return (error_msg(1, "error while opening the pipe"));

	// Creating a child process
	pid = fork();
	if (pid == -1)
		return (free_cmd_paths(cmd_1, cmd_2));
	else if (pid == 0)
		child_routine(fd);
	else
		parent_routine(pid, fd);

	// Exit program
	return (EXIT_SUCCESS);
}

/*
int main(void)
{
	int		pipe_fd[2];
	char	*args_1[] = {"ls", "-l", NULL};
	char	*args_2[] = {"/usr/bin/grep", "file", NULL};


	if (pipe(pipe_fd) == -1)
		return (error_msg(0,"couldn't create the pipe"));

	// Create 1st child   [binary_path, argument_path]
	int	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1],STDOUT_FILENO);
		execve("/usr/local/bin/ls", args_1, NULL);
	}

	// Create 2nd child   [binary_path, argument_path]
	int pid2 = fork();
	if (pid2 <0)
		return (error_msg(1, "something went wrong with pid2"));
	if (pid2 == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		execve("/usr/bin/grep", args_2, NULL);
	}

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}*/