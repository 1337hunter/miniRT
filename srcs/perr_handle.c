/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perr_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:26:37 by gbright           #+#    #+#             */
/*   Updated: 2020/07/03 12:26:43 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int		perr_handle(void)
{
	perror("Error");
	exit(1);
	return (-1);
}

void	exit_status(char *errline)
{
	while (*errline)
		write(1, errline++, 1);
	exit(1);
}
