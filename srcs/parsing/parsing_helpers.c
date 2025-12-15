/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:49:35 by clnicola          #+#    #+#             */
/*   Updated: 2025/12/06 16:55:18 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_operator(char *str, int *i)
{
	char	*operators;
	int		len;

	len = 1;
	if (str[*i] == '<' && str[*i + 1] == '<')
		len = 2;
	if (str[*i] == '>' && str[*i + 1] == '>')
		len = 2;
	operators = ft_substr(str, *i, len);
	*i += len;
	return (operators);
}

void	ft_add_back_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*ft_make_token(char *input, int *i, t_data *data)
{
	char	*str;
	t_token	*tok;

	if (ft_is_operator(input[*i]))
	{
		str = extract_operator(input, i);
		tok = ft_new_token(str, VOID);
	}
	else
	{
		str = extract_word(input, i, data);
		tok = ft_new_token(str, WORD);
	}
	free(str);
	return (tok);
}

void	ft_assign_token_type(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (ft_strcmp(tmp->token, "|") == 0)
			tmp->type = PIPE;
		else if (ft_strcmp(tmp->token, "<<") == 0)
			tmp->type = HEREDOC;
		else if (ft_strcmp(tmp->token, ">>") == 0)
			tmp->type = APPEND;
		else if (ft_strcmp(tmp->token, "<") == 0)
			tmp->type = INPUT;
		else if (ft_strcmp(tmp->token, ">") == 0)
			tmp->type = TRUNC;
		else if (tmp->token[0] == '$' && tmp->token[1] != '\0')
			tmp->type = VAR;
		else
			tmp->type = WORD;
		tmp = tmp->next;
	}
}
