/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 23:38:41 by nick              #+#    #+#             */
/*   Updated: 2022/02/09 01:39:30 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft_tools.h"

void	here_doc_exec(t_prime *prime, int writefd)
{
	char	*line;

	line = get_next_line(0);
	while (line
		&& ft_strncmp(line, prime->argv[2], ft_strlen(prime->argv[2]) + 1))
	{
		write_here_doc_line(line, prime->envp, writefd);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(writefd);
	pipex_exit(prime, NONE, prime->argv[0], NULL);
}

void	first_child_exec(t_prime *prime, int writefd)
{
	
}

void	middle_child_exec(t_prime *prime, char **cmd, int readfd, int writefd)
{

}

void	last_child_exec(t_prime *prime, int readfd)
{
	
}
