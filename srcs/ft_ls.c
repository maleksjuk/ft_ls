/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:12:31 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/06 19:43:23 by obanshee         ###   ########.fr       */
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

int	processing(t_options *options, char *file)
{
	t_info		*list;
	struct stat	about;
	int			count;

	list = NULL;
	if (!file)			//  обработка файлов
	{
		if ((list = set_info_list(list, options->len_for_array[0])) == NULL)
			error_message("processing list error 1");
		count = processing_files(options, list);
	}
	else				//	обработка директорий
	{
		if (stat(file, &about))
			error_message("processing stat");
		if ((list = set_info_list(list, about.st_nlink)) == NULL)
			error_message("processing_files list error 3");
		count = processing_dir(options, list, file);
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
