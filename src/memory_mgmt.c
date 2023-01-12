/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:42:14 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/11 20:24:10 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	free_cmd_paths(char *s1, char *s2)
{
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	return (EXIT_FAILURE);
}