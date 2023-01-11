/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:41:01 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/11 20:33:09 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int arg_count, char **argv_list, char **envp)
{
	pid_t	pid;
	char	*cmd1;
	char	*cmd2;

	// Check number of arguments
	if (arg_count != 5)
		return (error_msg(1, "Usage: ./pipex file1 cmd1 cmd2 file2"));
	// Save command paths
	cmd1 = get_cmd_path(envp, argv_list[2]);
	cmd2 = get_cmd_path(envp, argv_list[3]);
	if (!cmd1 || !cmd2)
		return (free_cmd_paths(cmd1, cmd2));
	// Create child process
	pid = fork();
	if (pid == -1)
		return (free_cmd_paths(cmd1, cmd2));
	if (pid == 0)
		child_process(pid);
	else
		parent_process(pid);
	// Exit program
	//return (EXIT_FAILURE);
}
