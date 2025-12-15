/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:00:00 by clnicola          #+#    #+#             */
/*   Updated: 2025/12/15 13:10:08 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_external_cmd(char *cmd_path, t_command *cmd, char **env)
{
	if (execve(cmd_path, cmd->args, env) == -1)
	{
		ft_putstr_fd("minishell: permission denied: ", 2);
		ft_putendl_fd(cmd->args[0], 2);
		free(cmd_path);
		exit(126);
	}
	free(cmd_path);
	exit(EXIT_FAILURE);
}

static void	execute_not_found(char *cmd_name)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd_name, 2);
	exit(127);
}

void	execute_command(t_command *cmd, char **env, t_data *parent_data)
{
	char	*cmd_path;

	if (!cmd->args || !cmd->args[0])
		exit(EXIT_SUCCESS);
	if (is_builtin_cmd(cmd->args[0]))
	{
		parent_data->cmd = cmd;
		builtin_commands(parent_data);
		exit(parent_data->last_exit_status);
	}
	cmd_path = ft_get_cmd(env, cmd->args[0]);
	if (!cmd_path)
		execute_not_found(cmd->args[0]);
	execute_external_cmd(cmd_path, cmd, env);
}

void	setup_child_pipes(int prev_fd, int pipe_fd[2], t_command *cmd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

int	fork_and_execute(t_command *cmd, int prev_fd, int pipe_fd[2],
		char **env_and_data)
{
	t_fork_data	*fork_data;
	pid_t		pid;

	fork_data = (t_fork_data *)env_and_data;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_child_pipes(prev_fd, pipe_fd, cmd);
		execute_command(cmd, fork_data->env, fork_data->data);
	}
	return (pid);
}
