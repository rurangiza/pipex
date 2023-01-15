/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:37:46 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/15 15:33:20 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

/*
 * Pipex
 * Recreating the UNIX mechanism known as pipe "|"
*/

int	main(int arg_count, char **arg_list, char **envp)
{
	t_data	data;

	if (arg_count != 5)
		return (error_msg(1, "Usage: ./pipex file1 cmd1 cmd2 file2"));
	load_data(&data, arg_count, arg_list, envp);
	ft_pipex(&data);
	return (EXIT_SUCCESS);
}

void	ft_pipex(t_data *data)
{
	pid_t	pid;
	int		status;
	int		pipe_ends[2];

	int index = 2;
	while (index <= data->arg_count - 2)
	{
		// create a pipe
		if (pipe(pipe_ends) == -1)
			exit_msg();
		// create a child process
		pid = fork();
		if (pid == -1)
			exit_msg();
		else if (pid == 0)
		{
			if (index == 2)
			{
				success_msg(0, "---> first_child");
				first_child(data, pipe_ends);
			}
			else if (index == data->arg_count - 2)
			{
				success_msg(0, "---> last_child");
				last_child(data);
			}
			else
			{
				success_msg(0, "---> middle_child");
				middle_child(data, pipe_ends, index);
			}
		}
		close(pipe_ends[P_WRITE]);
		info_msg(0, "index = %d, arg_count = %d", index, data->arg_count);
		if (index <= data->arg_count - 2)
		{
			dup2(pipe_ends[P_READ], STDIN_FILENO);
			close(pipe_ends[P_READ]);
		}
		else
			close(pipe_ends[P_READ]);
		waitpid(pid, &status, 0);
		index++;
	}
}
	// change I/O of child process
	// execute the command
// parent: waits for the child to terminate
