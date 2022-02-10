/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 23:30:58 by nick              #+#    #+#             */
/*   Updated: 2022/02/10 12:41:00 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child(int pipefd[2], t_prime *prime)
{
	pid_t	pid;

	if (pipe(pipefd) == -1)
		pipex_exit(prime, PIPE, prime->argv[0], NULL);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[READ_END]);
		close(pipefd[WRITE_END]);
		pipex_exit(prime, FORK, prime->argv[0], NULL);
	}
	if (pid == 0)
	{
		close(pipefd[READ_END]);
		if (prime->here_doc)
			here_doc_exec(prime, pipefd[WRITE_END]);
		first_child_exec(prime, pipefd[WRITE_END]);
	}
	close(pipefd[WRITE_END]);
}

void	middle_child(
	char *const *cmd, int pipefd[2], int readfd, t_prime *prime)
{
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		close(readfd);
		pipex_exit(prime, PIPE, prime->argv[0], NULL);
	}
	pid = fork();
	if (pid == -1)
	{
		close(readfd);
		close(pipefd[READ_END]);
		close(pipefd[WRITE_END]);
		pipex_exit(prime, FORK, prime->argv[0], NULL);
	}
	if (pid == 0)
	{
		close(pipefd[READ_END]);
		middle_child_exec(prime, cmd, readfd, pipefd[WRITE_END]);
	}
	close(readfd);
	close(pipefd[WRITE_END]);
}

pid_t	last_child(int readfd, t_prime *prime)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(readfd);
		pipex_exit(prime, FORK, prime->argv[0], NULL);
	}
	if (pid == 0)
		last_child_exec(prime, readfd);
	close(readfd);
	return (pid);
}
