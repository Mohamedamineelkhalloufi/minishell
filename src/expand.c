/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:38:45 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/06/20 18:34:44 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *expand_line(char *line, int dquote, char *plus, t_env *info)
{
    int i;
    char *line_plus;
    char *temp_plus;
    
    while (line && *line)
    {
        i = 0;
        while (line[i] && line[i] != '$')
            i = skip_quotes(line, i, &dquote);
            
        line_plus = ft_substr(line, 0, i);
        temp_plus = ft_strjoin1(plus, line_plus);
        // free(plus);
        free(line_plus);
        plus = temp_plus;
        if (line[i] == '$')
        {
            line += i;
            i = handle_dollar(&plus, line, info);
        }
        line += i;
    }
    return (plus);
}
char *expand_line1(char *line, char *plus, t_env *info)
{
    int i;
    char *line_plus;
    char *temp_plus;
    
    while (line && *line)
    {
        i = 0;
        while (line[i] && line[i] != '$')
            i++;
        line_plus = ft_substr(line, 0, i);
        temp_plus = ft_strjoin(plus, line_plus);
        free(line_plus);
        plus = temp_plus;
        if (line[i] == '$')
        {
            line += i;
            i = handle_dollar(&plus, line, info);
        }
        line += i;
    }
    return (plus);
}

int	skip_quotes(char *line, int i, int *dquote)
{
	if (line[i] == '\"')
	{
		*dquote = !(*dquote);
		i++;
	}
	else if (line[i] == '\'' && !(*dquote))
	{
		i++;
		while (line[i] && line[i] != '\'')
			i++;
		if (line[i])
			i++;
	}
	else
		i++;
	return (i);
}

int	handle_dollar(char **plus, char *line, t_env *info)
{
	int		i;
	char	*exp;

	i = 1;
	exp = expand_val(line, info);
	*plus = ft_strjoin1(*plus, exp);
	if (line[i] && (line[i] == '?' || ft_isdigit(line[i])))
	i++;
	else if (line[i] == '$')
	{
		while (line[i] == '$')
			i++;
		i--;
	}
	else
	{
		while (line[i] && ft_isalnum(line[i]))
		i++;
	}
	free(exp);
	return (i);
}

char	*expand_val(char *s, t_env *info)
{
	char	*start;
	char	*temp;
	char	*dollar;

	start = ft_strnstr(s, "$", ft_strlen(s));
	if (!start)
		return (NULL);
	if (!start[1])
		return (ft_strdup("$"));
	if (start[1] == '$')
		return (handle_dollar_case(start));
	temp = find_end(start);
	if (!temp)
		return (NULL);
	dollar = get_env_value(temp, info->my_envp);
	free(temp);
	if (dollar)
		return (dollar);
	if (start[1] && start[1] == '?')
		return (ft_itoa(g_es));
	if (start[1] && !ft_isalnum(start[1]))
		return (ft_strdup("$"));
	return (ft_strdup(""));
}	

char	*find_end(char *start)
{
	int	i;

	i = 1;
	if (start[i] && start[i] == '?')
		return (ft_substr(start + 1, 0, i));
	if (start[i] && ft_isdigit(start[i]))
		return (ft_substr(start + 1, 0, i));
	while (start[i] && ft_isalnum(start[i]))
		i++;
	return (ft_substr(start + 1, 0, i - 1));
}
