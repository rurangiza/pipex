/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:28:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/11 20:04:59 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../src/library/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

/* ~~~~~~~~~~ PROCESS ~~~~~~~~~ */
void    child_process(pid_t pid);
void    parent_process(pid_t pid);

/* ~~~~~~~~~ PARSING ~~~~~~~~~ */
char	*get_cmd_path(char **envp, char *cmd);
char	*validated_path(char **paths_list, char *cmd);

/* ~~~~~~~~~ MEMORY MGMT ~~~~~~~~~ */
int		free_cmd_paths(char *s1, char *s2);

#endif