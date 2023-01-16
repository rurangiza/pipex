/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:38:15 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/16 11:24:53 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../src/library/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>

# define P_READ 0
# define P_WRITE 1

typedef struct s_cmd {
	char	*path;
	char	**args;
}	t_cmd;

typedef struct s_data {
	int		arg_count;
	char	**arg_list;
	char	**envp;
}	t_data;

void	ft_pipex(t_data *data);

/* ~~~~~~ INITTIALIZTION ~~~~~~~ */
void	load_data(t_data *data, int arg_count, char **arg_list, char **envp);

/* ~~~~~~~~~~ PROCESS ~~~~~~~~~ */
void	first_child(t_data *data, int *outfile);
void	middle_child(t_data *data, int *outfile, int arg_number);
void	last_child(t_data *data);
void	parent_process(pid_t pid, int *pipe_ends, int index, int arg_count);

/* ~~~~~~~~~ PARSING ~~~~~~~~~ */
char	*init_cmd(char **envp, char *args, t_cmd *cmd);

char	*validated_path(char **paths_list, char *args);
int		count_words(char *str);
char	*cut_first_word(char *str);

/* ~~~~~~~~ ERROR HANDLING ~~~~~~ */
void	exit_msg(void);

#endif