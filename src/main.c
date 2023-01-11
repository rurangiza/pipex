/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:41:01 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/11 14:44:06 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int arg_count, char **argv_list, char **envp)
{
	char *cmd1_path;
	char *cmd2_path;

	if (arg_count != 5)
		return (error_msg(1, "Usage: ./pipex file1 cmd1 cmd2 file2"));
	cmd1_path = get_path(envp, argv_list[2]);
	cmd2_path = get_path(envp, argv_list[3]);
	if (!cmd1_path || !cmd2_path)
		return (free_cmd_paths(cmd1_path, cmd2_path));
	success_msg(0, "Valid commands");
}