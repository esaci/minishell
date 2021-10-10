#include "../../lib/libmin.h"

int	compatibility_arg(TOKENTYPE type)
{
	if (type == CHAR_INUT || type == CHAR_TIRET)
		return (1);
	if (type == CHAR_ARG || type == CHAR_TIRET)
		return (1);
	if (type == CHAR_APO || type == CHAR_GUILL)
		return (1);
	if (type == CHAR_SPACE)
		return (1);
	return (0);
}

void	remove_for_arg(char *str)
{
	int	count;

	count = 0;
	while (str[count + 1])
	{
		str[count] = str[count + 1];
		count++;
	}
	str[count - 1] = '\0';
}

void	check_for_arg(char **str, t_lexer *l)
{
	int	count;

	count = 0;
	while (str && str[count])
	{
		if (str[count][0] == '\'' || str[count][0] == '\"')
		{
			if (ft_strlen(str[count]) > 2)
			{
				get_token_buffer(l, str[count])->type = CHAR_INUT;
				if (str[count][0] == str[count][ft_strlen(str[count]) - 1])
				{
					remove_for_arg(str[count]);
					if (join_close_token(l, str, count))
						exit(print_custom("Malloc during token arg", 2, 1, 1));
				}
			}
		}
		count++;
	}

}

void	correct_name(t_lexer *l, char *str)
{
	int	count;

	return ;
	(void)l;
	(void)str;
	(void)count;
    /* if (str[0] != '/')
		return ;
	count = 0;
	while (str[count])
	{
		if ()
	} */
}