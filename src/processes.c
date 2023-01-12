/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/12 11:23:24 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    child_routine(pid_t pid, int *fd, int *data)
{
    close(fd[0]);

    
    int sum = 0;
    for (int i = 0; i < 5; i++)
        sum += data[i];
    write(fd[1], &sum, sizeof(int)); // Writing to the pipe
    close(fd[1]);
    success_msg(0, "child_sum : %d", sum);
    // others
    (void)pid;
    exit(0);
}

void    parent_routine(pid_t pid, int *fd, int *data)
{
    int status;

    close(fd[1]);
    int sum_child;
    int sum_parent;

    sum_parent = 0;
    // Read input and save it into variable {y}
    read(fd[0], &sum_child, sizeof(int)); 
    close(fd[0]);
    for (int i = 5; i < 10; i++)
        sum_parent += data[i];
    // Modify my input
    
    // Print result
    success_msg(0, "parent_sum: %d", sum_parent);
    printf("sum = %d\n", sum_child + sum_parent);
    waitpid(pid, &status, 0);
}
