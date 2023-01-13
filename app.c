/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 08:31:08 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/13 14:47:50 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    //char buffer[5];
    //read(0, buffer, 1);
    int fd = open("README.md", O_RDONLY);
    dup2(fd, STDIN_FILENO);
    
    char buffer[1];
    //bytes_read = 1;
    while (read(fd, buffer, 1) > 0)
    {
        write(1, &buffer, 1);
    }
    return (0);
}