/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 23:38:41 by nick              #+#    #+#             */
/*   Updated: 2022/02/10 09:49:50 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft_tools.h"

static void	check_input_file(const t_prime *prime, int writefd)
{
	if (access(prime->argv[1], F_OK) == -1)
	{
		close(writefd);
		pipex_exit(prime, FILE_NOT_FOUND, prime->argv[0], prime->argv[1]);
	}
	if (access(prime->argv[1], R_OK) == -1)
	{
		close(writefd);
		pipex_exit(prime, FILE_PERM, prime->argv[0], prime->argv[1]);
	}
}

void	first_child_exec(const t_prime *prime, int writefd)
{
	int		readfd;
	char	*cmd_full_path;

	check_input_file(prime, writefd);
	readfd = open(prime->argv[1], O_RDONLY);
	if (readfd == -1)
	{
		close(writefd);
		pipex_exit(prime, FILE_OPEN, prime->argv[0], prime->argv[1]);
	}
	replace_stdio(prime, readfd, writefd);
	close(readfd);
	close(writefd);
	cmd_full_path = find_cmd_full_path(prime->cmds[0][0], prime->envp_paths);
	check_cmd(cmd_full_path, prime->cmds[0][0], prime);
	execve(cmd_full_path, prime->cmds[0], prime->envp);
	free(cmd_full_path);
	pipex_exit(prime, EXECVE, prime->argv[0], prime->argv[1]);
}

void	middle_child_exec(
	const t_prime *prime, const char *const *cmd, int readfd, int writefd)
{
	char	*cmd_full_path;

	replace_stdio(prime, readfd, write);
	close(readfd);
	close(writefd);
	cmd_full_path = find_cmd_full_path(cmd[0], prime->envp_paths);
	check_cmd(cmd_full_path, cmd[0], prime);
	execve(cmd_full_path, cmd, prime->envp);
	free(cmd_full_path);
	pipex_exit(prime, EXECVE, prime->argv[0], cmd[0]);
}

static void	check_output_file(const t_prime *prime, int readfd)
{
	if (access(prime->argv[1], F_OK) == -1)
	{
		close(readfd);
		pipex_exit(prime, FILE_NOT_FOUND,
			prime->argv[0], prime->argv[prime->argc - 1]);
	}
	if (access(prime->argv[1], R_OK) == -1)
	{
		close(readfd);
		pipex_exit(prime, FILE_PERM,
			prime->argv[0], prime->argv[prime->argc - 1]);
	}
}

void	last_child_exec(const t_prime *prime, int readfd)
{
	int		writefd;
	char	*cmd_full_path;

	check_output_file(prime, readfd);
	if (prime->here_doc)
		writefd = open(prime->argv[prime->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		writefd = open(prime->argv[prime->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (writefd == -1)
	{
		close(readfd);
		pipex_exit(prime, FILE_OPEN,
			prime->argv[0], prime->argv[prime->argc - 1]);
	}
	replace_stdio(prime, readfd, writefd);
	close(readfd);
	close(writefd);
	cmd_full_path = find_cmd_full_path(
			prime->cmds[prime->cmds_size -1][0], prime->envp_paths);
	check_cmd(cmd_full_path, prime->cmds[prime->cmds_size - 1][0], prime);
	execve(cmd_full_path, prime->cmds[prime->cmds_size - 1], prime->envp);
	free(cmd_full_path);
	pipex_exit(prime, EXECVE, prime->argv[0], prime->argv[prime->argc - 1]);
}
