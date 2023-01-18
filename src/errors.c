/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:32:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/18 11:07:56 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exit_nofile_msg(char *filename)
{
	write(2, "bash: no such file or directory: ", 33);
	write(2, filename, ft_strlen(filename));
	write(2, "\n", 1);
	exit(errno);
}

void	exit_msg(int error_number, char *title)
{
	perror(title);
	exit(error_number);
}
