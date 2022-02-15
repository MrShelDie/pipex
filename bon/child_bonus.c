/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 23:30:58 by nick              #+#    #+#             */
/*   Updated: 2022/02/15 02:54:07 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

pid_t	first_child(int pipefd[2], t_prime *prime)
{
	pid_t	pid;
	char	*err_str;

	if (pipe(pipefd) == -1)
		pipex_exit(prime, prime->argv[0], NULL, strerror(errno));
	pid = fork();
	if (pid == -1)
	{
		err_str = strerror(errno);
		close(pipefd[READ_END]);
		close(pipefd[WRITE_END]);
		pipex_exit(prime, prime->argv[0], NULL, err_str);
	}
	if (pid == 0)
	{
		close(pipefd[READ_END]);
		if (prime->here_doc)
			here_doc_exec(prime, pipefd[WRITE_END]);
		first_child_exec(prime, pipefd[WRITE_END]);
	}
	close(pipefd[WRITE_END]);
	return (pid);
}

pid_t	middle_child(
	char *const *cmd, int pipefd[2], int readfd, t_prime *prime)
{
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		prime->err_str = strerror(errno);
		close(readfd);
		pipex_exit(prime, prime->argv[0], NULL, prime->err_str);
	}
	pid = fork();
	if (pid == -1)
	{
		prime->err_str = strerror(errno);
		close(readfd);
		close(pipefd[READ_END]);
		close(pipefd[WRITE_END]);
		pipex_exit(prime, prime->argv[0], NULL, prime->err_str);
	}
	if (pid == 0)
	{
		close(pipefd[READ_END]);
		middle_child_exec(prime, cmd, readfd, pipefd[WRITE_END]);
	}
	close(readfd);
	close(pipefd[WRITE_END]);
	return (pid);
}

pid_t	last_child(int readfd, t_prime *prime)
{
	pid_t	pid;
	char	*err_str;

	pid = fork();
	if (pid == -1)
	{
		err_str = strerror(errno);
		close(readfd);
		pipex_exit(prime, prime->argv[0], NULL, err_str);
	}
	if (pid == 0)
		last_child_exec(prime, readfd);
	close(readfd);
	return (pid);
}
