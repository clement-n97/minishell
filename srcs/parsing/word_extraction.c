/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_extraction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 08:32:00 by clnicola          #+#    #+#             */
/*   Updated: 2025/12/15 13:13:56 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quoted_len(char *s, int *p)
{
	int		len;
	char	q;

	len = 0;
	q = s[*p];
	(*p)++;
	while (s[*p] && s[*p] != q)
	{
		len++;
		(*p)++;
	}
	return (len);
}

static int	add_len(char *s, int *p)
{
	int	len;

	len = 0;
	while (s[*p] && !ft_is_space(s[*p]) && !ft_is_operator(s[*p]))
	{
		if (s[*p] == '\'' || s[*p] == '"')
		{
			len += quoted_len(s, p);
			if (!s[*p])
				return (-1);
			(*p)++;
		}
		else
		{
			len++;
			(*p)++;
		}
	}
	return (len);
}

char	*extract_word(char *str, int *i, t_data *data)
{
	int	len;
	int	pos;

	pos = *i;
	len = add_len(str, &pos);
	if (len < 0)
	{
		ft_putstr_fd("Error: unterminated quote\n", 2);
		*i = pos;
		return (ft_strdup(""));
	}
	return (build_expanded_token(str, i, len, data));
}

char	*expand_variable(char *str, int *i, t_data *data)
{
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(data->last_exit_status));
	}
	return (get_var_value(str, i, data));
}
