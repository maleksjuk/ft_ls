/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:12:31 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/17 10:37:48 by obanshee         ###   ########.fr       */
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

int	recursive(t_options *options, char *file)
{
	char	*current_file;
	t_info	*list_rev;
	int		i;

	list_rev = rec_create_array(options, file);
	if (list_rev == NULL)
		return (error_message(file, 0));
	i = 0;
	while (i < list_rev[0].size)
	{
		update_path(options->cur_dir, file);
		set_path(options->cur_dir, list_rev[i].name);
		rec_print_current_directory(options);
		current_file = ft_strdup(options->cur_dir);
		options->count = 0;
		processing(options, current_file);
		free(current_file);
		i++;
	}
	free_list(list_rev, i);
	return (0);
}

int	ft_ls_for_dir(t_options *options)
{
	int	i;

	options->flag_current_process = 1;
	i = options->reverse ? options->len_for_array[1] : 0;
	while ((!options->reverse && i < options->len_for_array[1]) ||
		(options->reverse && i > 0))
	{
		i -= options->reverse ? 1 : 0;
		update_path(options->cur_dir, NULL);
		add_path(options->cur_dir, options->dir_array[i]);
		if (options->len_for_array[1] > 1 || options->len_for_array[0])
			ft_printf("%s%s:\n", (i > 0 || options->len_for_array[0]) ?
				"\n" : "", options->dir_array[i]);
		options->bug_ls_for_recursion = i;
		options->count = 0;
		processing(options, options->dir_array[i]);
		i += options->reverse ? 0 : 1;
	}
	return (0);
}

int	ft_ls(t_options *options)
{
	if (options->len_for_array[0])
	{
		options->flag_current_process = 0;
		update_path(options->cur_dir, NULL);
		options->count = 0;
		processing(options, NULL);
	}
	if (options->len_for_array[1])
		ft_ls_for_dir(options);
	if (!options->len_for_array[0] && !options->len_for_array[1])
	{
		options->flag_current_process = 2;
		update_path(options->cur_dir, "./\0");
		options->count = 0;
		processing(options, "./\0");
	}
	return (final_ls(options));
}
