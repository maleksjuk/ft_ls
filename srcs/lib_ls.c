/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:54:04 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/30 18:26:22 by obanshee         ###   ########.fr       */
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
	int	i;

	list = (t_info *)malloc(sizeof(t_info) * (len + 1));
	if (list == NULL)
		return (NULL);
	i = 0;
	while (i < len)
		list[i++].name = ft_strdup("\0");
	return (list);
}

void	update_value_tab_len(t_options *options, t_info *list, int len)
{
	char	*nlink;
	char	*size;
	int		i;

	i = 0;
	while (i < len)
	{
		if (options->all || list[i].name[0] != '.')
		{
			nlink = ft_itoa(list[i].nlink);
			if ((int)ft_strlen(nlink) > options->tab_len[1])
				options->tab_len[1] = ft_strlen(nlink);
			if ((int)ft_strlen(list[i].user) > options->tab_len[2])
				options->tab_len[2] = ft_strlen(list[i].user);
			if ((int)ft_strlen(list[i].group) > options->tab_len[3])
				options->tab_len[3] = ft_strlen(list[i].group);
			size = ft_itoa(list[i].size);
			if ((int)ft_strlen(size) > options->tab_len[4])
				options->tab_len[4] = ft_strlen(size);
			if ((int)ft_strlen(list[i].name) > options->tab_len[6])
				options->tab_len[6] = ft_strlen(list[i].name) + 1;
		}
		i++;
	}
}

int		condition_sort(t_info *list, int i, t_options *options)
{
	if (!(options->time_order))
	{
		if (!(options->reverse))
		{
			if (ft_strcmp(list[i].name, list[i + 1].name) > 0)
				return (1);
		}
		else
		{
			if (ft_strcmp(list[i].name, list[i + 1].name) < 0)
				return (1);
		}
	}
	else
	{
		if (!(options->reverse))
		{
			if (list[i].time_modif_digit < list[i + 1].time_modif_digit)
				return (1);
		}
		else
		{
			if (list[i].time_modif_digit > list[i + 1].time_modif_digit)
				return (1);
		}
	}
	
	return (0);
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
			if (condition_sort(list, i, options))
			{
				point = list[i];
				list[i] = list[i + 1];
				list[i + 1] = point;
			}
			i++;
		}
		j++;
	}
}

void	set_path(t_options *options, char *path, char *file)
{
	char	*tmp;

	if (path)
	{
		if (path[ft_strlen(path) - 1] != '/')
		{
			tmp = path;
			path = ft_strjoin(path, "/\0");
			free(tmp);
		}
		tmp = path;
		path = ft_strjoin(path, file);
		free(tmp);
	}
	else if (options)
	{
		if (options->cur_dir[ft_strlen(options->cur_dir) - 1] != '/')
		{
			tmp = options->cur_dir;
			options->cur_dir = ft_strjoin(options->cur_dir, "/\0");
			free(tmp);
		}
		tmp = options->cur_dir;
		options->cur_dir = ft_strjoin(options->cur_dir, file);
		free(tmp);
	}
}
