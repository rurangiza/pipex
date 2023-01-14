/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:21:06 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/14 12:05:50 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
 * Pipex
 * Recreating the UNIX mechanism known as pipe "|"
*/

int	main(int arg_count, char **arg_list, char **envp)
{
    t_data  data;

	if (arg_count != 5)
		return (error_msg(1, "Usage: ./pipex file1 cmd1 cmd2 file2"));
	load_data(&data, arg_count, arg_list, envp);
	ft_pipex(&data);
	return (EXIT_SUCCESS);
}

void	ft_pipex(t_data *data)
{
    pid_t   pid[2];
    int     pipe_ends[2];

	if (pipe(pipe_ends) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid[0] = fork();
	if (data->pid[0] == -1)
    {
        perror("fork");
		exit(EXIT_FAILURE);
    }
	else if (pid[0] == 0)
		first_child(data, pipe_ends);
    pid[1] = fork();
	if (pid[1] == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid[1] == 0)
        second_child(data, pipe_ends);
    parent_process(pid, pipe_ends);
}