/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 23:38:41 by nick              #+#    #+#             */
/*   Updated: 2022/02/15 17:01:04 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child_exec(t_prime *prime, int writefd)
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
	pipex_exit(prime, prime->argv[0], prime->cmds[0][0], prime->err_str);
}

void	middle_child_exec(
	t_prime *prime, char *const *cmd, int readfd, int writefd)
{
	char	*cmd_full_path;

	replace_stdio(prime, readfd, writefd);
	close(readfd);
	close(writefd);
	cmd_full_path = find_cmd_path(cmd[0], prime->paths);
	check_cmd(cmd_full_path, cmd[0], prime);
	execve(cmd_full_path, cmd, prime->envp);
	prime->err_str = strerror(errno);
	free(cmd_full_path);
	pipex_exit(prime, prime->argv[0], cmd[0], prime->err_str);
}

void	last_child_exec(t_prime *prime, int readfd)
{
	int			argc;
	int			writefd;
	char		*cmd_path;
	char *const	*argv;

	argv = prime->argv;
	argc = prime->argc;
	if (prime->here_doc)
		writefd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		writefd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (writefd == -1)
	{
		prime->err_str = strerror(errno);
		close(readfd);
		pipex_exit(prime, argv[0], argv[argc - 1], prime->err_str);
	}
	replace_stdio(prime, readfd, writefd);
	close(readfd);
	close(writefd);
	cmd_path = find_cmd_path(prime->cmds[prime->cmds_size -1][0], prime->paths);
	check_cmd(cmd_path, prime->cmds[prime->cmds_size - 1][0], prime);
	execve(cmd_path, prime->cmds[prime->cmds_size - 1], prime->envp);
	prime->err_str = strerror(errno);
	free(cmd_path);
	pipex_exit(prime, argv[0], argv[argc - 2], prime->err_str);
}
