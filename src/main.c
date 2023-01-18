/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:21:06 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/18 12:58:11 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
			else
				last_child(data);
		}
		parent_process(pid, pipe_ends, index, data->arg_count);
		index++;
	}
}

// void	ft_pipex(t_data *data)
// {
// 	pid_t	pid[2];
// 	int		pipe_ends[2];

// 	if (pipe(pipe_ends) == -1)
// 		exit_msg(0, "pipe");
// 	pid[0] = fork();
// 	if (pid[0] == -1)
// 		exit_msg(0, "fork");
// 	else if (pid[0] == 0)
// 		first_child(data, pipe_ends);
// 	pid[1] = fork();
// 	if (pid[1] == -1)
// 		exit_msg(0, "2nd fork");
// 	else if (pid[1] == 0)
// 		second_child(data, pipe_ends);
// 	parent_process(pid, pipe_ends);
// }
