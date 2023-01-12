/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:28:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/12 16:37:36 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../src/library/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

# define READ_END 0
# define WRITE_END 1

// typedef struct s_data {
// 	pid_t	pid;
// 	int		fd[2];
// 	char	*path;
// 	char	*args;
// } t_data;

/* ~~~~~~~~~~ PROCESS ~~~~~~~~~ */
void    child_routine(int *pipe_fd);
void    parent_routine(pid_t pid, int *pipe_fd);

/* ~~~~~~~~~ PARSING ~~~~~~~~~ */
char	*get_cmd_path(char **envp, char *cmd);
char	*validated_path(char **paths_list, char *cmd);

/* ~~~~~~~~~ MEMORY MGMT ~~~~~~~~~ */
int		free_cmd_paths(char *s1, char *s2);

#endif