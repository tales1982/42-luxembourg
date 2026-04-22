/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIManager.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:15:36 by tales             #+#    #+#             */
/*   Updated: 2025/09/01 09:15:37 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_MANAGER_HPP
#define CGI_MANAGER_HPP

#include <string>
#include <vector>
#include <map>

struct CgiResult {
    int exitStatus;            // -1 if killed/timeout
    bool timedOut;
    std::string rawHeaders;    // CGI headers
    std::string body;          // CGI body
};

class CGIManager {
public:
    // Executes CGI with timeoutMs and maxBytes limit.
    // stdinData is passed to CGI via stdin (for POST, etc.).
    static CgiResult run(const std::string& execPath,
                         const std::string& scriptPath,
                         const std::map<std::string, std::string>& env,
                         const std::string& stdinData,
                         int timeoutMs,
                         size_t maxBytes);
};

#endif
