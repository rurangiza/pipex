/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:41:01 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/11 12:02:46 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int arg_count, char **argv_list, char **envp)
{
	char **paths_list;
	char *cmd1;
	char *cmd2;
	int	i;

	// if (arg_count != 5)
	// 	return (error_msg(1, "Usage: ./pipex file1 cmd1 cmd2 file2"));

	paths_list = NULL;
	cmd1 = argv_list[2];
	cmd2 = argv_list[3];
	/* SAVE PATHS TO COMMAND EXEC FILES */
	i = 0;
	while (envp[i] != NULL)
	{
		// Select the PATH line
		if (ft_strnstr(envp[i], "PATH", 4))
		{
			// Store path list
			paths_list = ft_split_sep(envp[i] + 26, ':', '/');
			break ;
		}
		i++;
	}
	if (paths_list == NULL)
		return (error_msg(1, "couldn't save path list"));

	/* CHECK FOR VALID PATH */
	int		status[2];
	char	*path_cmd1;
	char	*path_cmd2;

	status[0] = -1;
	status[1] = -1;
	i = 0;
	while (paths_list[i] != NULL)
	{
		path_cmd1 = ft_strjoin(paths_list[i], cmd1);
		path_cmd2 = ft_strjoin(paths_list[i], cmd2);
		// Check whether if one of them exists : access(<saved_command_path + command_name>, X_OK)
		if (access(path_cmd1, X_OK) == 0)
			status[0] = 1;
		if (access(path_cmd2, X_OK) == 0)
			status[1] = 1;
		i++;
	}
	if (status[0] == 1 && status[1] == 1)
		success_msg(0, "Both commands are valid");
	ft_free_matrix(paths_list);
	free(path_cmd1);
	free(path_cmd2);
	// if so, execute with execve()
	// else, return error "command not found"
	
	(void)arg_count;
	(void)argv_list;
	return (0);
}
