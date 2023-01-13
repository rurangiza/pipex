/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:28:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/13 13:39:20 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../src/library/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

# define READ_END 0
# define WRITE_END 1

typedef struct s_cmd {
	char	*path;
	char	**args;
} t_cmd;

typedef struct s_data {
    pid_t   pid;
    int     pipe_ends[2];
    t_cmd   cmd_1;
    t_cmd   cmd_2;
} t_data;

/* ~~~~~~~~~~ PROCESS ~~~~~~~~~ */
void    child_routine(void);
void    parent_routine(void);

/* ~~~~~~~~~ PARSING ~~~~~~~~~ */
char	*init_cmd(char **envp, char *args, t_cmd *cmd);
char	*validated_path(char **paths_list, char *args);
int     ft_count_words(char *str);

/* ~~~~~~~~~ MEMORY MGMT ~~~~~~~~~ */
int		free_prog(t_data *prog);

#endif