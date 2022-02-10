/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 09:44:52 by nick              #+#    #+#             */
/*   Updated: 2022/02/10 09:51:05 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft_tools.h"

void	check_cmd(
	const char *cmd_full_path, const char *cmd, const t_prime *prime)
{
	if (!cmd_full_path)
		pipex_exit(prime, FILE_NOT_FOUND, prime->argv[0], cmd);
	if (access(cmd, F_OK) == -1)
	{
		free(cmd_full_path);
		pipex_exit(prime, FILE_NOT_FOUND, prime->argv[0], cmd);
	}
	if (access(prime->argv[1], R_OK) == -1)
	{
		free(cmd_full_path);
		pipex_exit(prime, FILE_PERM, prime->argv[0], cmd);
	}
}

void	replace_stdio(const t_prime *prime, int readfd, int writefd)
{
	if (dup2(readfd, STDIN_FILENO) == -1 || dup2(writefd, STDOUT_FILENO) == -1)
	{
		close(readfd);
		close(writefd);
		pipex_exit(prime, DUP, prime->argv[0], NULL);
	}
}

static char	*get_correct_path(
	const char *slash_cmd, const char *const *envp_paths)
{
	char	*last_correct_path;
	char	*new_path;

	last_correct_path = NULL;
	while (*envp_paths)
	{
		new_path = ft_strjoin(*envp_paths, slash_cmd);
		if (new_path && access(new_path, F_OK) == 0)
		{
			if (last_correct_path)
				free(last_correct_path);
			last_correct_path = new_path;
			if (access(new_path, X_OK) == 0)
				return (new_path);
		}
		else if (new_path)
			free(new_path);
		envp_paths++;
	}
	return (last_correct_path);
}

char	*find_cmd_full_path(const char *cmd, const char *const *envp_paths)
{
	char	*cmd_full_path;
	char	*slash_cmd;

	if (cmd[0] != '/' && cmd[0] != '.')
		return (ft_strdup(cmd));
	slash_cmd = ft_strjoin("/", cmd);
	if (!slash_cmd)
		return (NULL);
	cmd_full_path = get_correct_path(slash_cmd, envp_paths);
	free(slash_cmd);
	return (cmd_full_path);
}
