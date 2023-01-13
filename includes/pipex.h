/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:28:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/13 15:51:16 by Arsene           ###   ########.fr       */
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
void    child_process(t_data *data, char *infile);
void    parent_process(t_data *data, char *outfile);

/* ~~~~~~~~~ PARSING ~~~~~~~~~ */
char    *init_cmd(char **envp, char *args, t_cmd *cmd);

char    *validated_path(char **paths_list, char *args);
int     ft_count_words(char *str);
char    *ft_cutword(char *str);

/* ~~~~~~~~~ MEMORY MGMT ~~~~~~~~~ */
int		free_prog(t_data *prog);

#endif