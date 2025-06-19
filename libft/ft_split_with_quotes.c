/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:23:51 by cscache           #+#    #+#             */
/*   Updated: 2025/06/19 12:09:31 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

static void	handle_quotes(char const *s, char c, int *i, int *in_word)
{
	char	quote_type;
	char	quote_start;

	quote_type = s[*i];
	quote_start = *i;
	*i++;
	while (s[*i] && s[*i] != quote_type)
		*i++;
	if (s[*i])
	{
		*i++;
		*in_word = 0;
		return (1);
	}
	else
	{
		*i = quote_start + 1;
		*in_word = 1;
	}
}

static int	handle_regular_char(char const *s, int *i, int *in_word, char c)
{
	if (c != s[*i] && !*in_word)
	{
		*in_word = 1;
		*i++;
		return (1);
	}
	else if (c == s[i])
	{
		in_word = 0;
		i++;
	}
	else
		i++;
}

static int	ft_count_words(char const *s, char c)
{
	int		i;
	int		count;
	int		in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			handle_quotes(s, s[i], &i, &in_word);
			count += 1;
		}
		else
		{
		
		}
	}
	return (count);
}

static char	*ft_extract_word(char const *s, int start, int end)
{
	char	*tab;
	int		i;

	i = 0;
	tab = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!tab)
		return (NULL);
	while (start < end)
	{
		tab[i] = s[start];
		i++;
		start++;
	}
	tab[i] = '\0';
	return (tab);
}

static void	ft_free(char **result, int i)
{
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
	free(result);
}

static char	**ft_split_fill(char const *s, char **result, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i] && j < ft_count_words(s, c))
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			result[j] = ft_extract_word(s, start, i);
			if (!result[j])
			{
				ft_free(result, j);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!result)
		return (NULL);
	return (ft_split_fill(s, result, c));
}

#include <stdio.h>

int	main(int ac, char *av[])
{
	if (ac == 2)
		printf("%d\n", ft_count_words(av[1], ' '));
	return (0);
}