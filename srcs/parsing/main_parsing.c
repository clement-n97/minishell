/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:19:02 by clnicola          #+#    #+#             */
/*   Updated: 2025/12/15 13:04:27 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(t_command *cmd)
{
	int	i;

	printf("Command: ");
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		printf("[%s] ", cmd->args[i]);
		i++;
	}
	printf("\n");
}

static void	print_redirects(t_redir *redir)
{
	while (redir)
	{
		printf("  Redirect: type=%d, file=[%s]\n", redir->type, redir->file);
		redir = redir->next;
	}
}

void	ft_display_commands(t_command *cmd)
{
	while (cmd)
	{
		print_args(cmd);
		if (cmd->redirs)
			print_redirects(cmd->redirs);
		cmd = cmd->next;
	}
}

t_token	*ft_word_to_token(char *input, t_data *data)
{
	t_token	*head;
	t_token	*new;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_is_space(input[i]))
		{
			i++;
			continue ;
		}
		new = ft_make_token(input, &i, data);
		ft_add_back_token(&head, new);
	}
	return (head);
}

void	ft_parsing(t_data *data, char *input)
{
	data->token = ft_word_to_token(input, data);
	ft_assign_token_type(data);
	data->cmd = ft_tokens_to_commands(data->token);
}
