/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:32:06 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/16 15:32:58 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	first_child(t_data *data, int *outfile)
{
	int		infile;
	int		err_code;
	t_cmd	cmd;

	close(outfile[P_READ]);
	infile = open(data->arg_list[1], O_RDONLY);
	if (infile == -1)
		exit_msg();
	if (dup2(infile, STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(infile);
	dup2(outfile[P_WRITE], STDOUT_FILENO);
	init_cmd(data->envp, data->arg_list[2], &cmd);
	err_code = execve(cmd.path, cmd.args, NULL);
	if (err_code == -1)
		exit_msg();
}

void	middle_child(t_data *data, int *outfile, int arg_number)
{
	int		err_code;
	t_cmd	cmd;

	close(outfile[P_READ]);
	dup2(outfile[P_WRITE], STDOUT_FILENO);
	init_cmd(data->envp, data->arg_list[arg_number], &cmd);
	err_code = execve(cmd.path, cmd.args, NULL);
	if (err_code == -1)
		exit_msg();
}

void	last_child(t_data *data)
{
	t_cmd	cmd;
	int		outfile;
	int		outfile_index;
	int		err_code;

	outfile_index = data->arg_count - 1;
	outfile = open(data->arg_list[outfile_index],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		exit_msg();
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	init_cmd(data->envp, data->arg_list[outfile_index - 1], &cmd);
	err_code = execve(cmd.path, cmd.args, NULL);
	if (err_code == -1)
		exit_msg();
}

void	parent_process(pid_t pid, int *pipe_ends, int index, int arg_count)
{
	int	status;

	close(pipe_ends[P_WRITE]);
	if (index <= arg_count - 2)
	{
		dup2(pipe_ends[P_READ], STDIN_FILENO);
		close(pipe_ends[P_READ]);
	}
	else
		close(pipe_ends[P_READ]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGTERM)
			exit_msg();
		if (WTERMSIG(status) == SIGKILL)
			exit_msg();
	}
}
