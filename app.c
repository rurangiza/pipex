/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 08:31:08 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/13 08:43:39 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int pipe_fd[2];

    int pid = fork();
    pipe(pipe_fd);
    if (pid == 0)
    {
        close(pipe_fd[0]); // close read
        int nbr = 10;
        write(pipe_fd[1], &nbr, sizeof(int));
    }
    else
    {
        // close unused pipe_end 
        close(pipe_fd[1]);
        // read and save pipe content
        int nbr2;
        read(pipe_fd[0], &nbr2, sizeof(int));
        // modify content received
        nbr2 *= 3;
        // print result
        printf("number = %d", nbr2);
    }
    return (0);
}