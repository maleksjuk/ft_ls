/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:12:31 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/02 17:15:38 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	final_ls(t_options *options)
{
	int	i;

	i = 0;
	while (options->dir_array[i])
	{
//		free(options->dir_array[i]);
		i++;
	}
//	free(options->dir_array);
	free(options->cur_dir);
	free(options);
	return (0);
}

int	printing(t_info *list, t_options *options, int len)
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

int	processing(t_options *options, char *file)
{
	t_info		*list;
	struct stat	about;
	int			count;

	list = NULL;
	if (!file)
		count = processing_files(options, &list);
	else
	{
		if (!ft_strcmp(file, "./\0"))
		{
			if (stat(file, &about))
				error_message("processing stat 2");
			options->len_for_array[1] = about.st_nlink;
		}
		count = processing_dir(options, &list);
	}
	if (count < 0)
		error_message("count");
	set_null_tab_len(options);
	sort_info_list(list, count, options);
	update_value_tab_len(options, list, count);
	printing(list, options, count);
	// if (options->recursive)
	// 	recursive(options, options->cur_dir);
	return (0);
}

int	ft_ls(t_options *options)
{
	int			i;
	char		*tmp;

	if (options->len_for_array[0])		// обработка файлов
	{
		processing(options, NULL);
	}
	if (options->len_for_array[1])		// обработка директорий
	{
		i = 0;
		while (i < options->len_for_array[1])
		{
			tmp = options->cur_dir;
			options->cur_dir = ft_strdup(options->dir_array[i]);
			free(tmp);
			if (options->len_for_array[1] > 1 || options->len_for_array[0])
				ft_printf("%s%s:\n",  (i > 0 || options->len_for_array[0]) ?
					"\n" : "", options->dir_array[i]);
			processing(options, options->dir_array[i]);
			i++;
		}
	}
	if (!options->len_for_array[0] && !options->len_for_array[1])	// обработка без списка файлов и директорий
		processing(options, "./");
	return (final_ls(options));
}
