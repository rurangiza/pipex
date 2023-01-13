/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:21:06 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/13 16:06:41 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int arg_count, char **arg_list, char **envp)
{
    t_data  data;

	// Check number of arguments
	if (arg_count != 5)
		return (error_msg(1, "Usage: ./pipex file1 cmd1 cmd2 file2"));

	// Make sur the commands are valid then save relevent info
	init_cmd(envp, arg_list[2], &data.cmd_1);
	init_cmd(envp, arg_list[3], &data.cmd_2);
	if (!data.cmd_1.path || !data.cmd_2.path)
		return (free_prog(&data));

	// Create a pipe
	if (pipe(data.pipe_ends) == -1)
		return (error_msg(1, "an error ocured while opening the pipe"));
	
	// Create and handle processes
	data.pid = fork();
	if (data.pid == -1)
		return (free_prog(&data));
	else if (data.pid == 0)
		child_process(&data, arg_list[1]);
	else
		parent_process(&data, arg_list[4]);

	// Exit program
	return (EXIT_SUCCESS);
}
