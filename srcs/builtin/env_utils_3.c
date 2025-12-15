/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:25:00 by clnicola          #+#    #+#             */
/*   Updated: 2025/12/15 15:25:46 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap_env(t_env **env, t_env *to_swap)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr && curr != to_swap)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr || !curr->next)
		return ;
	if (!prev)
	{
		*env = curr->next;
		curr->next = curr->next->next;
		(*env)->next = curr;
		return ;
	}
	prev->next = curr->next;
	curr->next = curr->next->next;
	prev->next->next = curr;
	return ;
}

int	ft_count_env_vars(t_env **env)
{
	t_env	*curr;
	int		count;

	count = 0;
	if (!env)
		return (0);
	curr = *env;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

char	*ft_build_env_string(char *name, char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

void	ft_fill_env_array(char **result, t_env **env)
{
	t_env	*curr;
	int		index;

	curr = *env;
	index = 0;
	while (curr)
	{
		result[index] = ft_build_env_string(curr->name, curr->value);
		if (!result[index])
		{
			ft_free_tabs(result);
			return ;
		}
		curr = curr->next;
		index++;
	}
	result[index] = NULL;
}
