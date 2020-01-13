/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:54:04 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/13 19:56:32 by obanshee         ###   ########.fr       */
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

	i = 0;
	list = (t_info *)malloc(sizeof(t_info) * (len + 1));
	if (list == NULL)
		return (NULL);
	while (i < len)
		list[i++].flag_link = 0;
	return (list);
}

void	set_null_tab_len(t_options *options)
{
	options->tab_len[0] = 11;
	options->tab_len[1] = 0;
	options->tab_len[2] = 0;
	options->tab_len[3] = 0;
	options->tab_len[4] = 0;
	options->tab_len[5] = 12;
	options->tab_len[6] = 0;
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

void	update_value_tab_len(t_options *options, t_info *list, int len)
{
	char	*nlink;
	char	*size;
	int		i;

	set_null_tab_len(options);
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
			
			if ((int)ft_strlen(list[i].name) > options->tab_len[6])
				options->tab_len[6] = ft_strlen(list[i].name) + 1;
		}
		i++;
	}
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

void	set_path(t_options *options, char *file)
{
	int	len;
	int	i;

	len = ft_strlen(options->cur_dir);
	if (len > 0 && options->cur_dir[len - 1] != '/')
	{
		options->cur_dir[len] = '/';
		len++;
	}
	i = 0;
	while (file[i])
	{
		options->cur_dir[len] = file[i];
		i++;
		len++;
	}
	options->cur_dir[len] = '\0';
}

void	update_path(t_options *options, char *path)
{
	int	i;
	int	len;

	i = 0;
	while (i < MAX_PATH)
		options->cur_dir[i++] = '\0';
	len = ft_strlen(path);
	i = 0;
	while (i < len)
	{
		options->cur_dir[i] = path[i];
		i++;
	}
	options->cur_dir[i] = '\0';
}
