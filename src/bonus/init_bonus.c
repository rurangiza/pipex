/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:53:36 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/15 13:46:25 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * setup my environment before doing somework
*/

#include "../../includes/pipex.h"

void	load_data(t_data *data, int arg_count, char **arg_list, char **envp)
{
	data->envp = envp;
	data->arg_count = arg_count;
	data->arg_list = arg_list;
}
