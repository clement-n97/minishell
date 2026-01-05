/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 17:04:41 by clnicola          #+#    #+#             */
/*   Updated: 2026/01/05 10:58:58 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_cmd(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_arg(t_command *cmd, char *arg)
{
	int		count;
	char	**new;
	int		i;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new = malloc(sizeof(char *) * (count + 2));
	i = 0;
	while (i < count)
	{
		new[i] = cmd->args[i];
		i++;
	}
	new[count] = arg;
	new[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new;
}

void	add_redir(t_command *cmd, int type, char *file)
{
	t_redir	*new_redir;
	t_redir	*last;

	if (!cmd || !file)
		return ;
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
	{
		free(new_redir);
		return ;
	}
	new_redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}
