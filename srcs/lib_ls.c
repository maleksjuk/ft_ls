/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:54:04 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/18 16:31:34 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	sort_ascii(char **array, int num)
{
	char	*point;
	int		i;
	int		j;

	j = 0;
	while (j < num)
	{
		i = 0;
		while (i < num - 1)
		{
			if (ft_strcmp(array[i], array[i + 1]) > 0)
			{
				point = array[i];
				array[i] = array[i + 1];
				array[i + 1] = point;
			}
			i++;
		}
		j++;
	}
}

t_info	*set_info_list(t_info *list, int len)
{
	list = (t_info *)malloc(sizeof(t_info) * (len + 1));
	if (list == NULL)
		return (NULL);
	return (list);
}

void	sort_info_list(t_info *list, int len, t_options *options)
{
	t_info	point;
	int		i;
	int		j;

	j = 0;
	while (j < len)
	{
		i = 0;
		while (i < len - 1)
		{
			// НАДО СДЕЛАТЬ ОТДЕЛЬНУЮ ФУНКЦИЮ ДЛЯ СОРТИРОВОК
			if ((ft_strcmp(list[i].name, list[i + 1].name) > 0 &&
				!(options->reverse)) || (ft_strcmp(list[i].name,
				list[i + 1].name) < 0 && options->reverse))
			{
				point = list[i];
				list[i] = list[i + 1];
				list[i + 1] = point;
			}
			i++;
		}
		if ((int)ft_strlen(list[j].name) > options->tab_len)
			options->tab_len = ft_strlen(list[j].name) + 1;
		j++;
	}
}

void	set_path(t_options *options, char *path)
{
	char	*tmp;

	tmp = options->cur_dir;
	options->cur_dir = ft_strjoin(options->cur_dir, "/\0");
	free(tmp);
	tmp = options->cur_dir;
	options->cur_dir = ft_strjoin(options->cur_dir, path);
	free(tmp);
}
