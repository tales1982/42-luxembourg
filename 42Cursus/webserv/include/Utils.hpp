/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:16:17 by tales             #+#    #+#             */
/*   Updated: 2025/09/01 09:16:18 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <map>
#include <cctype>

namespace Utils {
	std::string trim(const std::string &s);
	std::vector<std::string> split(const std::string &s, char delim);
	std::string toLower(const std::string &s);
	std::string urlDecode(const std::string &s);
	std::string getTimeRfc1123();
	std::string guessMime(const std::string &path);
	bool startsWith(const std::string &s, const std::string &prefix);
	bool endsWith(const std::string &s, const std::string &suffix);
	std::string joinPath(const std::string &a, const std::string &b);
	std::string safePathJoin(const std::string &root, const std::string &rel);
	std::string readFile(const std::string &path);
	bool fileExists(const std::string &path);
	bool isDir(const std::string &path);
	size_t fileSize(const std::string &path);
	std::string itoa(int v);
	std::string utoa(size_t v);
	std::string toUpper(const std::string &s);
}

#endif
