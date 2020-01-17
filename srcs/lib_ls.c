/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:54:04 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/17 10:29:58 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		sort_ascii(char **array, int num)
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

intmax_t	total_counter(t_info *list, int len, int all)
{
	int			i;
	intmax_t	total;

	i = 0;
	total = 0;
	while (i < len)
	{
		if (all || list[i].name[0] != '.')
			total += list[i].total;
		i++;
	}
	return (total);
}

void		set_null_tab_len(t_options *options)
{
	options->tab_len[0] = 11;
	options->tab_len[1] = 0;
	options->tab_len[2] = 0;
	options->tab_len[3] = 0;
	options->tab_len[4] = 0;
	options->tab_len[5] = 12;
	options->tab_len[6] = 0;
}

void		update_value_tab_len_act(t_options *options, t_info *list, int i)
{
	char	*nlink;
	char	*size;

	nlink = ft_itoa(list[i].nlink);
	if ((int)ft_strlen(nlink) > options->tab_len[1])
		options->tab_len[1] = ft_strlen(nlink);
	free(nlink);
	if ((int)ft_strlen(list[i].user) > options->tab_len[2])
		options->tab_len[2] = ft_strlen(list[i].user);
	if ((int)ft_strlen(list[i].group) > options->tab_len[3])
		options->tab_len[3] = ft_strlen(list[i].group);
	if (list[i].size < 0)
	{
		if (list[i].major_num > list[i].minor_num)
			size = ft_itoa(list[i].major_num);
		else
			size = ft_itoa(list[i].minor_num);
		options->flag_spec = 1;
	}
	else
		size = ft_itoa(list[i].size);
	if ((int)ft_strlen(size) > options->tab_len[4])
		options->tab_len[4] = ft_strlen(size);
	free(size);
}

void		update_value_tab_len(t_options *options, t_info *list, int len)
{
	int		i;

	set_null_tab_len(options);
	i = 0;
	while (i < len)
	{
		if (options->all || list[i].name[0] != '.')
		{
			if (options->list)
				update_value_tab_len_act(options, list, i);
			if ((int)ft_strlen(list[i].name) > options->tab_len[6])
				options->tab_len[6] = ft_strlen(list[i].name) + 1;
		}
		i++;
	}
	list[0].total = total_counter(list, len, options->all);
}
