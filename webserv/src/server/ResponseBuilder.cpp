/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseBuilder.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:23:18 by tales             #+#    #+#             */
/*   Updated: 2025/07/16 11:28:19 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server/ResponseBuilder.hpp"

// Lê um arquivo do disco e retorna seu conteúdo como string
std::string read_file(const std::string &path)
{
    std::ifstream file(path.c_str());
    if (!file.is_open())
        return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string get_mime_type(const std::string &path)
{
    if (path.find(".html") != std::string::npos)
        return "text/html";
    if (path.find(".jpg") != std::string::npos || path.find(".jpeg") != std::string::npos)
        return "image/jpeg";
    if (path.find(".png") != std::string::npos)
        return "image/png";
    if (path.find(".css") != std::string::npos)
        return "text/css";
    if (path.find(".js") != std::string::npos)
        return "application/javascript";
    if (path.find(".pdf") != std::string::npos)
        return "application/pdf";
    return "application/octet-stream";
}

// Gerar a pagina que vai mostra os documentos
std::string replace_placeholder(std::string source, const std::string &placeholder, const std::string &value)
{
    size_t pos = source.find(placeholder);
    if (pos != std::string::npos)
        source.replace(pos, placeholder.length(), value);
    return source;
}

std::string generate_autoindex(const std::string &dirPath, const std::string &urlPath)
{
    DIR *dir = opendir(dirPath.c_str());
    if (!dir)
        return "";

    std::ostringstream listHtml;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        std::string name = entry->d_name;
        if (name == ".")
            continue;
        listHtml << "<li><a href=\"" << name << "\">" << name << "</a></li>\n";
    }
    closedir(dir);

    // Lê o template HTML do autoindex
    std::string templateHtml = read_file("www/autoindex_template.html");

    // Substitui {{PATH}} e {{LIST}} no template
    templateHtml = replace_placeholder(templateHtml, "{{PATH}}", urlPath);
    templateHtml = replace_placeholder(templateHtml, "{{LIST}}", listHtml.str());

    return templateHtml;
}

std::string generate_all_uploads_page()
{
    std::ostringstream combinedList;
    const char *folders[] = {"./www/fotos/", "./www/pdfs/", "./www/othes/"};
    const char *routes[] = {"/fotos/", "/pdfs/", "/othes/"};

    for (int i = 0; i < 3; ++i)
    {
        DIR *dir = opendir(folders[i]);
        if (!dir)
            continue;

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            std::string name = entry->d_name;
            if (name == "." || name == "..")
                continue;
            combinedList << "<li><a href=\"" << routes[i] << name << "\">" << name << "</a></li>\n";
        }
        closedir(dir);
    }

    std::string templateHtml = read_file("www/all_uploads_template.html");
    templateHtml = replace_placeholder(templateHtml, "{{PATH}}", "/all-uploads");
    templateHtml = replace_placeholder(templateHtml, "{{LIST}}", combinedList.str());

    return templateHtml;
}