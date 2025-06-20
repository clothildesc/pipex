/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:48:19 by cscache           #+#    #+#             */
/*   Updated: 2025/06/20 11:35:49 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef enum e_state
{
	STATE_NORMAL,
	STATE_SINGLE_QUOTE,
	STATE_DOUBLE_QUOTE
}	t_state;

typedef enum e_char_type
{
	CHAR_NORMAL,
	CHAR_SPACE,
	CHAR_SINGLE_QUOTE,
	CHAR_DOUBLE_QUOTE
}	t_char_type;

typedef struct s_lexer
{
	t_state		state;
	t_list		*tmp_token;
	t_list		*lst_tokens;
	int			pos;
	const char	*input;
}	t_lexer;

void	init_struct(t_lexer *l)
{
	l->state = STATE_NORMAL;
	l->tmp_token = NULL;
	l->lst_tokens = NULL;
	l->input = NULL;
	l->pos = 0;
}

t_char_type	classify_char_type(char c)
{
	if (c == ' ')
		return (CHAR_SPACE);
	else if (c == '\'')
		return (CHAR_SINGLE_QUOTE);
	else if (c == '"')
		return (CHAR_DOUBLE_QUOTE);
	return (CHAR_NORMAL);
}

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
		return (NULL);
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

void	handle_single_quote_state(t_lexer *l)
{
	if (l->state == STATE_NORMAL)
		l->state = STATE_SINGLE_QUOTE;
	else if (l->state == STATE_SINGLE_QUOTE)
		l->state = STATE_NORMAL;
	else if (l->state == STATE_DOUBLE_QUOTE)
		add_char(&(l->tmp_token), &(l->input[l->pos]));
}

void	handle_double_quote_state(t_lexer *l)
{
	if (l->state == STATE_NORMAL)
		l->state = STATE_DOUBLE_QUOTE;
	else if (l->state == STATE_DOUBLE_QUOTE)
		l->state = STATE_NORMAL;
	else if (l->state == STATE_SINGLE_QUOTE)
		add_char(&(l->tmp_token), &(l->input[l->pos]));
}

void	handle_space_state(t_lexer *l)
{
	if (l->state == STATE_DOUBLE_QUOTE || l->state == STATE_SINGLE_QUOTE)
		add_char(&(l->tmp_token), &(l->input[l->pos]));
	else if (l->state == STATE_NORMAL)
		finish_token(&(l->tmp_token), &(l->lst_tokens));
}

void	handle_normal_state(t_lexer *l)
{
	add_char(&(l->tmp_token), &(l->input[l->pos]));
}


char	**ft_lexer(const char *input)
{
	t_lexer		lexer;
	t_char_type	type;

	init_struct(&lexer);
	lexer.input = input;
	while (lexer.input[lexer.pos])
	{
		type = classify_char_type(lexer.input[lexer.pos]);
		if (type == CHAR_SINGLE_QUOTE)
			handle_single_quote_state(&lexer);
		else if (type == CHAR_DOUBLE_QUOTE)
			handle_double_quote_state(&lexer);
		else if (type == CHAR_SPACE)
			handle_space_state(&lexer);
		else
			handle_normal_state(&lexer);
		(lexer.pos)++;
	}
	finish_token(&(lexer.tmp_token), &(lexer.lst_tokens));
	return (lst_to_array(lexer.lst_tokens));
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
