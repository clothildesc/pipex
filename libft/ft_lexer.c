/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:48:19 by cscache           #+#    #+#             */
/*   Updated: 2025/06/19 15:07:19 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef enum e_state
{
	STATE_NORMAL,
	STATE_SINGLE_QUOTE,
	STATE_DOUBLE_QUOTE
}	t_state;

static int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}
void	add_char(t_list **tmp_token, char c)
{
	t_list	*new;

	new = ft_lstnew((char)c);
	ft_lstadd_back(tmp_token, new);
}

char	*create_token(t_list *tmp_token)
{
	char	*token;
	int		i;

	token = malloc(sizeof(char) * (ft_lstsize(tmp_token) + 1));
	if (!token)
		return (NULL);
	i = 0;
	while (tmp_token)
	{
		token[i] = (char)tmp_token->content;
		i++;
		tmp_token = tmp_token->next;
	}
	token[i] = '\0';
	return (token);
}

void	add_token(t_list **tokens, char *token)
{
	t_list	*new;

	new = ft_lstnew((char *)token);
	ft_lstadd_back(tokens, new);
}

char	**lst_to_array(t_list *tokens)

char	**lexer(const char *input)
{
	char	*token;
	int		i;
	t_state	state;
	t_list	*tmp_token;
	t_list	*tokens;

	i = 0;
	token = NULL;
	state = STATE_NORMAL;
	tmp_token = NULL;
	tokens = NULL;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			if (state == STATE_NORMAL)
				state = STATE_SINGLE_QUOTE;
			else if (state == STATE_SINGLE_QUOTE)
				state = STATE_NORMAL;
			else if (state == STATE_DOUBLE_QUOTE)
				add_char(&tmp_token, input[i]);
		}
		else if (input[i] == '"')
		{
			if (state == STATE_NORMAL)
				state = STATE_DOUBLE_QUOTE;
			else if (state == STATE_DOUBLE_QUOTE)
				state = STATE_NORMAL;
			else if (state == STATE_SINGLE_QUOTE)
				add_char(&tmp_token, input[i]);
		}
		else if (input[i] == ' ')
		{
			if (state == STATE_DOUBLE_QUOTE || state == STATE_SINGLE_QUOTE)
				add_char(&tmp_token, input[i]);
			else if (state == STATE_NORMAL && !tmp_token)
			{
					token = create_token(tmp_token);
					add_token(&tokens, token);
					token = NULL;
			}
		}
		else
			add_char(&tmp_token, input[i]);
		i++;
	}
	if (input[i])
	{
		token = create_token(tmp_token);
		add_token(&tokens, token);
	}
}

