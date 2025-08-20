/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:15:23 by tales             #+#    #+#             */
/*   Updated: 2025/07/16 11:31:20 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server/RequestHandler.hpp"

// Extrai o caminho da URL da requisição HTTP (ex: "/index.html")
std::string get_requested_path(const std::string &request)
{
    std::istringstream iss(request);
    std::string method, path;
    iss >> method >> path;
    return path;
}

// Função auxiliar para encontrar location matching
const LocationConfig *match_location(const ServerConfig &config, const std::string &path)
{
    const LocationConfig *bestMatch = NULL;
    size_t bestLength = 0;

    for (size_t i = 0; i < config.locations.size(); ++i)
    {
        const std::string &locPath = config.locations[i].path;
        if (path.find(locPath) == 0 && locPath.length() > bestLength)
        {
            bestMatch = &config.locations[i];
            bestLength = locPath.length();
        }
    }
    return bestMatch;
}

std::string get_upload_dir_by_extension(const std::string &filename)
{
    if (filename.find(".jpg") != std::string::npos || filename.find(".jpeg") != std::string::npos || filename.find(".png") != std::string::npos)
        return "./www/fotos/";
    else if (filename.find(".pdf") != std::string::npos)
        return "./www/pdfs/";
    else
        return "./www/othes/";
}