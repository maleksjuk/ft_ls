/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 08:42:28 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/17 13:55:33 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	init_list(t_info *list, int i)
{
	int	count;

	count = 0;
	while (count < 12)
		list[i].mode[count++] = '\0';
	list[i].name = NULL;
	list[i].user = NULL;
	list[i].group = NULL;
	list[i].nlink = 0;
	list[i].size = 0;
	list[i].major_num = 0;
	list[i].minor_num = 0;
	list[i].time_create = NULL;
	list[i].time_create_digit = 0;
	list[i].time_modif = NULL;
	list[i].time_modif_digit = 0;
	list[i].time_active = NULL;
	list[i].time_active_digit = 0;
	list[i].total = 0;
	list[i].total_no_all = 0;
	list[i].path_link = NULL;
	list[i].flag_link = 0;
	list[i].full_params = 0;
}

t_info	*set_info_list(int len)
{
	int		i;
	t_info	*list;

	i = 0;
	list = (t_info *)malloc(sizeof(t_info) * (len + 1));
	if (list == NULL)
		return (NULL);
	while (i < len)
		init_list(list, i++);
	return (list);
}

int		condition_sort(t_info *list, int i, t_options *options)
{
	if (!(options->time_order) || (options->time_order &&
		list[i].time_modif_digit == list[i + 1].time_modif_digit))
	{
		if (!(options->reverse))
		{
			if (ft_strcmp(list[i].name, list[i + 1].name) > 0)
				return (1);
		}
		else if (ft_strcmp(list[i].name, list[i + 1].name) < 0)
			return (1);
	}
	else
	{
		if (!(options->reverse))
		{
			if (list[i].time_modif_digit < list[i + 1].time_modif_digit)
				return (1);
		}
		else if (list[i].time_modif_digit > list[i + 1].time_modif_digit)
			return (1);
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

int		free_list(t_info *list, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(list[i].name);
		if (list[i].user)
			free(list[i].user);
		if (list[i].group)
			free(list[i].group);
		if (list[i].time_active)
			free(list[i].time_active);
		if (list[i].time_create)
			free(list[i].time_create);
		if (list[i].time_modif)
			free(list[i].time_modif);
		if (list[i].mode[0] == 'l')
			free(list[i].path_link);
		i++;
	}
	free(list);
	return (0);
}
