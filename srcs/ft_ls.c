/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:12:31 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/10 18:24:58 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	final_ls(t_options *options)
{
	int	i;

	i = 0;
	while (i < options->len_for_array[0])
	{
		free(options->dir_array[i]);
		i++;
	}
	i = 0;
	while (i < options->len_for_array[1])
	{
		free(options->files_array[i]);
		i++;
	}
	free(options->dir_array);
	free(options->files_array);
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
			error_message("processing list error 1", 1);
		count = processing_files(options, list);
	}
	else				//	обработка директорий
	{
		if (stat(file, &about))
			error_message("processing stat", 1);
		if ((list = set_info_list(list, about.st_nlink)) == NULL)
			error_message("processing_files list error 3", 1);
		count = processing_dir(options, list, file);
	}
	if (count < 0)
		error_message("count", 1);
	sort_info_list(list, count, options);
	update_value_tab_len(options, list, count);
	printing(list, options, count);
	if (file && options->recursive)
		recursive(options, file);
	return (0);
}

int	ft_ls(t_options *options)
{
	int	i;

	if (options->len_for_array[0])		// обработка файлов
	{
		update_path(options, "\0");
		processing(options, NULL);
	}
	if (options->len_for_array[1])		// обработка директорий
	{
		i = 0;
		while (i < options->len_for_array[1])
		{
			update_path(options, options->dir_array[i]);
			if (options->len_for_array[1] > 1 || options->len_for_array[0])
				ft_printf("%s%s:\n",  (i > 0 || options->len_for_array[0]) ?
					"\n" : "", options->dir_array[i]);
			processing(options, options->dir_array[i]);
			i++;
		}
	}
	if (!options->len_for_array[0] && !options->len_for_array[1])	// обработка без списка файлов и директорий
	{
		update_path(options, "./\0");
		processing(options, "./\0");
	}
	return (final_ls(options));
}
