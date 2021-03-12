/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:27:40 by gbright           #+#    #+#             */
/*   Updated: 2020/07/03 12:29:56 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*skip_space(char *input)
{
	while (*input == ' ' && *input)
		input++;
	return (input);
}

char	*skip_float(char *input)
{
	if (*input == '-' || *input == '+')
		input++;
	while (*input && *input >= '0' && *input <= '9')
		input++;
	if (*input == '.')
	{
		input++;
		while (*input && *input >= '0' && *input <= '9')
			input++;
	}
	return (input);
}
