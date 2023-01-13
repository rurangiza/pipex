/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:21:06 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/13 13:55:25 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int arg_count, char **arg_list, char **envp)
{
    t_data  data;

	// Check number of arguments
	if (arg_count != 5)
		return (error_msg(1, "Usage: ./pipex file1 cmd1 cmd2 file2"));

	// Make sur the commands are valid then save relevent info
	init_cmd(envp, arg_list[2], &data.cmd_1);
	init_cmd(envp, arg_list[3], &data.cmd_2);
	if (!data.cmd_1.path || !data.cmd_2.path)
		return (free_prog(&data));

	// Create a pipe
	pipe(data.pipe_ends);
	
	// Creating a child process
	info_msg(0, "forking...");
	data.pid = fork();
	if (data.pid == -1)
		return (free_prog(&data));
	// Handle routines
	else if (data.pid == 0) // Child process
	{
		close(data.pipe_ends[READ_END]);
		
		int infile_fd = open(arg_list[1], O_RDONLY); // open infile for reading
		dup2(infile_fd, STDIN_FILENO); // replace STDIN with infile
		dup2(data.pipe_ends[WRITE_END], STDOUT_FILENO); // replace STDOUT with WRITE_END of pipe
		execve(data.cmd_1.path, data.cmd_1.args, NULL); // execute cmd1 on stdin
	}
	else // Parent process
	{
		int status;
		close(data.pipe_ends[WRITE_END]);
		
		int outfile_fd = open(arg_list[4], O_WRONLY | O_CREAT | O_TRUNC, 0777); // open outfile for writing
		dup2(outfile_fd, STDOUT_FILENO); // replace stdout with outfile
		dup2(data.pipe_ends[READ_END], STDIN_FILENO); // replace stdin with READ_END of pipe
		execve(data.cmd_2.path, data.cmd_2.args, NULL);
		waitpid(data.pid, &status, 0);
	}
	// Exit program
	free_prog(&data);
	return (EXIT_SUCCESS);
}
