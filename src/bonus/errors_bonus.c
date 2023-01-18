/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:32:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/18 12:36:29 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	exit_msg(void)
{
	perror("pipex");
	exit(EXIT_FAILURE);
}

void	exit_wrongcmd_msg(char *cmd, int error_code)
{
	write(2, "zsh: command not found: ", 24);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(error_code);
}

void	exit_nofile_msg(char *filename)
{
	write(2, "bash: no such file or directory: ", 33);
	write(2, filename, ft_strlen(filename));
	write(2, "\n", 1);
	exit(0);
}