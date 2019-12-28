/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:10:54 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/28 16:48:15 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	init_options(t_options *options, int ac)
{
	options->list = 0;
	options->recursive = 0;
	options->all = 0;
	options->reverse = 0;
	options->time_order = 0;
	options->illegal = 0;
	options->dir_array = (char **)malloc(sizeof(char *) * ac);
	if (options->dir_array == NULL)
		exit(1);
	options->dir_array[ac - 1] = NULL;
	options->flag = 0;
	options->cur_dir = ft_strdup(".\0");
	set_null_tab_len(options);
	options->flag_list = 0;
	options->count = 0;
}

int		input_options(t_options *options, char *params)
{
	int	i;

	i = 1;
	while (params[i])
	{
		if (params[i] == 'R')
			options->recursive = 1;
		else if (params[i] == 'l')
			options->list = 1;
		else if (params[i] == 'a')
			options->all = 1;
		else if (params[i] == 'r')
			options->reverse = 1;
		else if (params[i] == 't')
			options->time_order = 1;
		else
		{
			options->illegal = params[i];
			return (0);
		}
		i++;
	}
	if (i == 1)
		return (1);
	return (2);
}
