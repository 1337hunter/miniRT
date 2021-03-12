/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:26:18 by gbright           #+#    #+#             */
/*   Updated: 2020/07/03 12:28:47 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		write(2, "Error\nNot enough arguments.\n", 28);
		exit(1);
	}
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6) != 0)
	{
		write(2, "Error\nYou want to make a wrong deal.\n", 38);
		exit(1);
	}
	control(argv, argc);
	return (0);
}
