/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:21:06 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/14 11:29:56 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int arg_count, char **arg_list, char **envp)
{
    t_data  data;

	if (arg_count != 5)
		return (error_msg(1, "Usage: ./pipex file1 cmd1 cmd2 file2"));
	load_data(&data, arg_count, arg_list, envp);
	ft_pipex(&data);
	return (EXIT_SUCCESS);
}

void	load_data(t_data *data, int arg_count, char **arg_list, char **envp)
{
	data->envp = envp;
	data->arg_count = arg_count;
	data->arg_list = arg_list;
}

/*
int	main(int arg_count, char **arg_list, char **envp)
{
    char	**cmd1;
	char	**cmd2;

	// Check number of arguments
	if (arg_count != 5)
		return (error_msg(1, "Usage: ./pipex file1 cmd1 cmd2 file2"));
		
	// Load config files

	// Make sur the commands are valid then save relevent info
	init_cmd(envp, arg_list[2], &data.cmd_1);
	init_cmd(envp, arg_list[3], &data.cmd_2);
	if (!data.cmd_1.path || !data.cmd_2.path)
		return (free_prog(&data));

	// Create a pipe
	// if (pipe(data.pipe_ends) == -1)
	// {
	// 	perror("pipe");
	// 	exit (EXIT_FAILURE);
	// }
	
	ft_pipex(&data, arg_list);
	// Exit program
	return (EXIT_SUCCESS);
}
*/