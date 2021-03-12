/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbright <gbright@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 12:21:54 by gbright           #+#    #+#             */
/*   Updated: 2020/07/03 12:33:33 by gbright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

static int	my_size(char *line)
{
	int	c;

	if (line == 0)
		return (0);
	c = 0;
	while (*line)
	{
		c++;
		line++;
	}
	return (c);
}

static int	my_find_option(char **scene, char *option)
{
	int	found;
	int	k;

	found = 0;
	while (*scene)
	{
		k = 0;
		while (scene[0][k] && option[k] && scene[0][k] == option[k])
			k++;
		if (k == my_size(option) && ((scene[0][k] >= 9 &&
				scene[0][k] <= 13) || scene[0][k] == ' '))
			return (1);
		else
			scene++;
	}
	return (0);
}

void		my_res_error(char **sn)
{
	char	*temp;

	while (**sn != 'R')
		sn++;
	temp = *sn + 1;
	while (*temp == ' ' && *temp)
		temp++;
	if (*temp < '0' || *temp > '9')
		exit_status("Error\nResolution error\n");
	while ((*temp >= '0' && *temp <= '9') && *temp)
		temp++;
	if (*temp != ' ')
		exit_status("Error\nResolution error\n");
	while (*temp == ' ' && *temp)
		temp++;
	if (*temp < '0' || *temp > '9')
		exit_status("Error\nResolution error\n");
}

void		my_amb_error(char **sn, char *amb)
{
	while (**sn != 'A')
		sn++;
	amb = *sn + 1;
	amb = skip_space(amb);
	if (*amb < '0' || *amb > '9')
		exit_status("Error\nAmbient lighting error\n");
	while (*amb && ((*amb >= '0' && *amb <= '9') || *amb == '.'))
		amb++;
	if (*amb != ' ')
		exit_status("Error\nAmbient lighting error\n");
	amb = skip_space(amb);
	if (*amb < '0' || *amb > '9')
		exit_status("Error\nAmbient lighting error\n");
	amb = ft_strchr(amb, ',');
	if (!amb || *amb != ',')
		exit_status("Error\nAmbient lighting error\n");
	amb++;
	if (*amb < '0' || *amb > '9')
		exit_status("Error\nAmbient lighting error\n");
	amb = ft_strchr(amb, ',');
	if (!amb || *amb != ',')
		exit_status("Error\nAmbient lighting error\n");
	amb++;
	if (*amb < '0' || *amb > '9')
		exit_status("Error\nAmbient lighting error\n");
}

void		err_scene(char **scene)
{
	int		flag;
	char	*ptr;

	ptr = 0;
	if (!(my_find_option(scene, "R")))
		exit_status("Error\nResolution option is missed\n");
	if (!(my_find_option(scene, "A")))
		exit_status("Error\nAmbient liting option is missed\n");
	if (!(my_find_option(scene, "c")))
		exit_status("Error\nCamera option is missed\n");
	if (!(my_find_option(scene, "l")))
		exit_status("Error\nLight option is missed\n");
	flag = 0;
	flag += my_find_option(scene, "sp");
	flag += my_find_option(scene, "pl");
	flag += my_find_option(scene, "sq");
	flag += my_find_option(scene, "cy");
	flag += my_find_option(scene, "tr");
	if (flag == 0)
		exit_status("Error\nShape is missed\n");
	my_res_error(scene);
	my_amb_error(scene, ptr);
	deep_scene_error(scene);
}
