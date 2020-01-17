/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:34:35 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/17 08:38:25 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_list(t_info *list, int i, t_options *options)
{
	ft_printf("%s %*i %-*s  %-*s",
		list[i].mode,
		options->tab_len[1], list[i].nlink,
		options->tab_len[2], list[i].user,
		options->tab_len[3], list[i].group);
	if (list[i].size < 0)
		ft_printf("  %*d, %*d",
		options->tab_len[4], list[i].major_num,
		options->tab_len[4], list[i].minor_num);
	else
		ft_printf("  %*lld", options->flag_spec ?
		(options->tab_len[4] * 2 + 2) : options->tab_len[4], list[i].size);
	ft_printf(" %*s %s",
		options->tab_len[5], list[i].time_modif,
		list[i].name);
	if (list[i].flag_link)
		ft_printf(" -> %s", list[i].path_link);
	ft_printf("\n");
}

int		printing(t_info *list, t_options *options, int len)
{
	int	i;

	while (options->tab_len[6] % 8 != 0)
		options->tab_len[6]++;
	i = 0;
	if (options->list && !options->list_files && options->count)
		ft_printf("total %lld\n", list[0].total);
	while (list && i < len)
	{
		if (list[i].name[0] == '\0')
			break ;
		if (list[i].name[0] != '.' || ft_strnequ(list[i].name, "./", 2) ||
			ft_strnequ(list[i].name, "../", 3) || options->all ||
			options->list_files)
		{
			if (options->list)
				print_list(list, i, options);
			else
				ft_printf("%-*s", options->tab_len[6], list[i].name);
		}
		i++;
	}
	ft_printf("%s", options->list ? "" : "\n");
	return (0);
}
