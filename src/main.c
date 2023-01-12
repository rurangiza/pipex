/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:41:01 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/12 12:55:16 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

typedef struct s_data {
	pid_t	pid;
	int		fd[2];
	char	*path;
	char	*args;
	
} t_data;


int	main(int arg_count, char **arg_list, char **envp)
{
	pid_t	pid;
	int		fd[2]; // fd[0] read from, fd[1] write to
	char	*cmd1;
	char	*cmd2;
	//char	*args[] = {"file", "grep", NULL};
	

	// Check number of arguments
	if (arg_count != 5)
		return (error_msg(1, "Usage: ./pipex file1 cmd1 cmd2 file2"));

	// Save command paths
	cmd1 = get_cmd_path(envp, arg_list[2]);
	cmd2 = get_cmd_path(envp, arg_list[3]);
	if (!cmd1 || !cmd2)
		return (free_cmd_paths(cmd1, cmd1));


	
	printf()
	//execve(cmd2, args, envp);


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
	(void)pid;
	(void)fd;
}



/*
int main(void)
{
	_execl("");
	return (0);
}
*/