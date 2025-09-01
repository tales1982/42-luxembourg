/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:15:32 by tales             #+#    #+#             */
/*   Updated: 2025/09/01 09:17:34 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "Http.hpp"
#include "Router.hpp"
#include <string>

namespace CGI {
    bool isCGI(const LocationConfig *loc, const std::string &path);
    HttpResponse run(const HttpRequest &req,
                     const RouteMatch &rm,
                     const std::string &fsPath);
}

#endif
