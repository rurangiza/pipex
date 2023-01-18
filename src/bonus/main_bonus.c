/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:37:46 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/18 09:41:41 by arurangi         ###   ########.fr       */
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

	if (arg_count < 5)
		return (error_msg(1, "Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2"));
	load_data(&data, arg_count, arg_list, envp);
	ft_pipex(&data);
	return (EXIT_SUCCESS);
}

void	ft_pipex(t_data *data)
{
	pid_t	pid;
	int		pipe_ends[2];
	int		index;

	index = 2;
	while (index <= data->arg_count - 2)
	{
		if (pipe(pipe_ends) == -1)
			exit_msg();
		pid = fork();
		if (pid == -1)
			exit_msg();
		else if (pid == 0)
		{
			if (index == 2)
				first_child(data, pipe_ends);
			else if (index == data->arg_count - 2)
				last_child(data);
			else
				middle_child(data, pipe_ends, index);
		}
		parent_process(pid, pipe_ends, index, data->arg_count);
		index++;
	}
}
