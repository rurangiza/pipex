/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:28:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/11 14:45:09 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../src/library/libft.h"
# include <stdio.h>
# include <unistd.h>

/* ~~~~~~~~~ PARSING ~~~~~~~~~ */
char	*get_path(char **envp, char *cmd);
char	*validated_path(char **paths_list, char *cmd);
/* ~~~~~~~~~ MEMORY MGMT ~~~~~~~~~ */
int		free_cmd_paths(char *s1, char *s2);

#endif