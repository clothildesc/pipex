/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:48:19 by cscache           #+#    #+#             */
/*   Updated: 2025/06/19 16:23:48 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef enum e_state
{
	STATE_NORMAL,
	STATE_SINGLE_QUOTE,
	STATE_DOUBLE_QUOTE
}	t_state;

static void	add_char(t_list **tmp_token, const char *c)
{
	t_list	*new;
	char	*new_char;

	new_char = malloc(sizeof(char));
	if (!new_char)
		return ;
	*new_char = *c;
	new = ft_lstnew(new_char);
	if (!new)
	{
		free(new_char);
		return ;
	}
	ft_lstadd_back(tmp_token, new);
}

static char	*create_token(t_list *tmp_token)
{
	char	*token;
	int		i;

	if (!tmp_token)
		return ;
	token = malloc(sizeof(char) * (ft_lstsize(tmp_token) + 1));
	if (!token)
		return (NULL);
	i = 0;
	while (tmp_token)
	{
		token[i] = *(char *)tmp_token->content;
		i++;
		tmp_token = tmp_token->next;
	}
	token[i] = 0;
	return (token);
}

static void	finish_token(t_list **tmp_token, t_list **lst_tokens)
{
	char	*token;

	if (*tmp_token)
	{
		token = create_token(*tmp_token);
		if (token)
			ft_lstadd_back(lst_tokens, ft_lstnew(token));
		ft_lstclear(tmp_token, free);
		*tmp_token = NULL;
	}
}

static char	**lst_to_array(t_list *lst_tokens)
{
	char	**tokens;
	int		i;

	tokens = malloc(sizeof(char *) * (ft_lstsize(lst_tokens) + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	while (lst_tokens)
	{
		tokens[i] = (char *)lst_tokens->content;
		i++;
		lst_tokens = lst_tokens->next;
	}
	tokens[i] = NULL;
	return (tokens);
}

char	**ft_lexer(const char *input)
{
	t_state	state;
	t_list	*tmp_token;
	t_list	*lst_tokens;
	int		i;

	i = 0;
	state = STATE_NORMAL;
	tmp_token = NULL;
	lst_tokens = NULL;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			if (state == STATE_NORMAL)
				state = STATE_SINGLE_QUOTE;
			else if (state == STATE_SINGLE_QUOTE)
				state = STATE_NORMAL;
			else if (state == STATE_DOUBLE_QUOTE)
				add_char(&tmp_token, &input[i]);
		}
		else if (input[i] == '"')
		{
			if (state == STATE_NORMAL)
				state = STATE_DOUBLE_QUOTE;
			else if (state == STATE_DOUBLE_QUOTE)
				state = STATE_NORMAL;
			else if (state == STATE_SINGLE_QUOTE)
				add_char(&tmp_token, &input[i]);
		}
		else if (input[i] == ' ')
		{
			if (state == STATE_DOUBLE_QUOTE || state == STATE_SINGLE_QUOTE)
				add_char(&tmp_token, &input[i]);
			else if (state == STATE_NORMAL && tmp_token)
			{
				token = create_token(tmp_token);
				add_token(&lst_tokens, token);
				ft_lstclear(&tmp_token, free);
				tmp_token = NULL;
				token = NULL;
			}
		}
		else
			add_char(&tmp_token, &input[i]);
		i++;
	}
	if (tmp_token)
	{
		token = create_token(tmp_token);
		add_token(&lst_tokens, token);
		ft_lstclear(&tmp_token, free);
		tmp_token = NULL;
	}
	return (lst_to_array(lst_tokens));
}
#include <stdio.h>

int	main(int ac, char *av[])
{
	char	**array;
	int		i;

	i = 0;
	if (ac == 2)
	{
		array = ft_lexer(av[1]);
		while (array[i])
		{
			printf("%s\n", array[i]);
			free(array[i]);
			i++;
		}
		free(array);
	}
	return (0);
}
