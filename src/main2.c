/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:21:06 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/13 12:19:50 by Arsene           ###   ########.fr       */
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
    t_data  data;

	// Check number of arguments
	if (arg_count != 5)
		return (error_msg(1, "Usage: ./pipex file1 cmd1 cmd2 file2"));

	// Save command paths
	init_cmd(envp, arg_list[2], &data.cmd_1);
	init_cmd(envp, arg_list[3], &data.cmd_2);
	if (!data.cmd_1.path || !data.cmd_2.path)
		return (free_prog(&data));
    
	// Creating a child process
	data.pid = fork();
	if (data.pid == -1)
		return (free_prog(&data));
	else if (data.pid == 0) // Child process
	{
		int file_fd = open(arg_list[1], O_RDONLY);
		dup2(file_fd, STDIN_FILENO);
		execve(data.cmd_1.path, data.cmd_1.args, NULL);
	}
	else // Parent process
	{
		int status;
		waitpid(data.pid, &status, 0);
	}
	// Exit program
	return (EXIT_SUCCESS);
}
