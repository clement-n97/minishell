/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:00:00 by clnicola          #+#    #+#             */
/*   Updated: 2026/01/05 10:59:08 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_input_file(char *file)
{
	int	file_descriptor;

	file_descriptor = open(file, O_RDONLY);
	if (file_descriptor == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	return (file_descriptor);
}

static int	open_output_file(char *file, int type)
{
	int	file_descriptor;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (type == APPEND)
		flags = flags | O_APPEND;
	else
		flags = flags | O_TRUNC;
	file_descriptor = open(file, flags, 0644);
	if (file_descriptor == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
	return (file_descriptor);
}

static int	apply_single_redir(t_redir *redir)
{
	int	file_descriptor;

	file_descriptor = -1;
	if (redir->type == INPUT)
	{
		file_descriptor = open_input_file(redir->file);
		if (file_descriptor == -1)
			return (-1);
		dup2(file_descriptor, STDIN_FILENO);
		close(file_descriptor);
	}
	else if (redir->type == TRUNC || redir->type == APPEND)
	{
		file_descriptor = open_output_file(redir->file, redir->type);
		if (file_descriptor == -1)
			return (-1);
		dup2(file_descriptor, STDOUT_FILENO);
		close(file_descriptor);
	}
	return (0);
}

int	apply_redirections(t_command *cmd)
{
	t_redir	*redir;

	if (!cmd || !cmd->redirs)
		return (0);
	redir = cmd->redirs;
	while (redir)
	{
		if (apply_single_redir(redir) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
