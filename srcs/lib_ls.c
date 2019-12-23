/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:54:04 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/23 19:19:40 by obanshee         ###   ########.fr       */
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

void	update_value_tab_len(t_options *options, t_info list)
{
	char	*nlink;
	char	*size;

	nlink = ft_itoa(list.nlink);
	if ((int)ft_strlen(nlink) > options->tab_len[1])
		options->tab_len[1] = ft_strlen(nlink) + 1;
	if ((int)ft_strlen(list.user) > options->tab_len[2])
		options->tab_len[2] = ft_strlen(list.user) + 1;
	if ((int)ft_strlen(list.group) > options->tab_len[3])
		options->tab_len[3] = ft_strlen(list.group) + 1;
	size = ft_itoa(list.size);
	if ((int)ft_strlen(size) > options->tab_len[4])
		options->tab_len[4] = ft_strlen(size) + 1;
	if ((int)ft_strlen(list.name) > options->tab_len[6])
		options->tab_len[6] = ft_strlen(list.name) + 1;
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
		// if ((int)ft_strlen(list[j].name) > options->tab_len)
		// 	options->tab_len = ft_strlen(list[j].name) + 1;
		if (options->all || list[j].name[0] != '.')
			update_value_tab_len(options, list[j]);
		j++;
	}
}

void	set_path(t_options *options, char *path, char *file)
{
	char	*tmp;

	if (path)
	{
		tmp = path;
		path = ft_strjoin(path, "/\0");
		free(tmp);
		tmp = path;
		path = ft_strjoin(path, file);
		free(tmp);
	}
	else if (options)
	{
		tmp = options->cur_dir;
		options->cur_dir = ft_strjoin(options->cur_dir, "/\0");
		free(tmp);
		tmp = options->cur_dir;
		options->cur_dir = ft_strjoin(options->cur_dir, file);
		free(tmp);
	}
}

void	set_null_tab_len(t_options *options)
{
	options->tab_len[0] = 10;
	options->tab_len[1] = 0;
	options->tab_len[2] = 0;
	options->tab_len[3] = 0;
	options->tab_len[4] = 0;
	options->tab_len[5] = 12;
	options->tab_len[6] = 0;
}
