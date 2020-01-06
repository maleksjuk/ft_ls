/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:34:35 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/06 17:35:09 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_list(t_info *list, int i, t_options *options)
{
	ft_printf("%s %*i %-*s  %-*s  %*d %*s %s",
		list[i].mode, 
		options->tab_len[1], list[i].nlink,
		options->tab_len[2], list[i].user,
		options->tab_len[3], list[i].group,
		options->tab_len[4], list[i].size,
		options->tab_len[5], list[i].time_modif,
		list[i].name);
	if (list[i].flag_link)
		ft_printf(" -> %s", list[i].path_link);
	ft_printf("\n");
}

int	    printing(t_info *list, t_options *options, int len)
{
	int	i;

	while (options->tab_len[6] % 8 != 0)
		options->tab_len[6]++;
	i = 0;
	if (options->list && !options->flag_list && options->count)
		ft_printf("total %lld\n", options->all ? list[0].total : list[0].total_no_all);
	while (i < len)
	{
		if (list[i].name[0] == '\0')
			break ;
		if (list[i].name[0] != '.' || (list[i].name[0] == '.' && options->all))
		{
			if (options->list)
				print_list(list, i, options);
			else
				ft_printf("%-*s", options->tab_len[6], list[i].name);
		}
		i++;
	}
	ft_printf(options->list ? "" : "\n");
	return (0);
}
