/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:42:14 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/13 12:07:30 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	free_prog(t_data *prog)
{
	if (prog->cmd_1.path != NULL)
		free(prog->cmd_1.path);
	if (prog->cmd_2.path != NULL)
		free(prog->cmd_1.path);
	return (EXIT_FAILURE);
}