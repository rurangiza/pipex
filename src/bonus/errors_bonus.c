/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:32:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/16 11:25:40 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	exit_msg(void)
{
	ft_printf("%s:%d: %s", __FILE__, __LINE__, strerror(errno));
	exit(EXIT_FAILURE);
}
