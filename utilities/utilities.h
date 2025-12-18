/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimend <danimend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by danimend          #+#    #+#             */
/*   Updated: 2025/12/18 00:00:00 by danimend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include <stdarg.h>

int	handle_tag_d(va_list ap);
int	handle_tag_i(va_list ap);
int	handle_tag_u(va_list ap);
int	handle_tag_c(va_list ap);
int	handle_tag_s(va_list ap);
int	handle_tag_x(va_list ap);
int	handle_tag_upper_x(va_list ap);
int	handle_tag_percent(void);

#endif
