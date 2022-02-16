/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 23:30:58 by nick              #+#    #+#             */
/*   Updated: 2022/02/16 16:43:22 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_child_exec(t_prime *prime, int writefd)
{
	int		readfd;
	char	*cmd_full_path;

	readfd = open(prime->argv[1], O_RDONLY);
	if (readfd == -1)
	{
		prime->err_str = strerror(errno);
		close(writefd);
		pipex_exit(prime, prime->argv[0], prime->argv[1], prime->err_str);
	}
	replace_stdio(prime, readfd, writefd);
	close(readfd);
	close(writefd);
	cmd_full_path = find_cmd_path(prime->cmds[0][0], prime->paths);
	check_cmd(cmd_full_path, prime->cmds[0][0], prime);
	execve(cmd_full_path, prime->cmds[0], prime->envp);
	prime->err_str = strerror(errno);
	free(cmd_full_path);
	pipex_exit(prime, prime->argv[0], prime->argv[1], prime->err_str);
}

static void	last_child_exec(t_prime *prime, int readfd)
{
	int			writefd;
	char		*cmd_path;
	char *const	*argv;

	argv = prime->argv;
	writefd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (writefd == -1)
	{
		prime->err_str = strerror(errno);
		close(readfd);
		pipex_exit(prime, argv[0], argv[4], prime->err_str);
	}
	replace_stdio(prime, readfd, writefd);
	close(readfd);
	close(writefd);
	cmd_path = find_cmd_path(prime->cmds[1][0], prime->paths);
	check_cmd(cmd_path, prime->cmds[1][0], prime);
	execve(cmd_path, prime->cmds[1], prime->envp);
	prime->err_str = strerror(errno);
	free(cmd_path);
	pipex_exit(prime, argv[0], argv[3], prime->err_str);
}

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
		first_child_exec(prime, pipefd[WRITE_END]);
	}
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
