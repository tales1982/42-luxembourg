/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Http.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:16:04 by tales             #+#    #+#             */
/*   Updated: 2025/09/01 09:16:05 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_HPP
#define HTTP_HPP

#include <string>
#include <map>
#include <vector>

struct HttpRequest {
	std::string method;
	std::string uri;
	std::string version;
	std::map<std::string, std::string> headers;
	std::string body;
};

struct HttpResponse {
	int status;
	std::string reason;
	std::map<std::string, std::string> headers;
	std::string body;
};

class HttpParser {
public:
	HttpParser();
	bool parse(const std::string &data, size_t &consumed, HttpRequest &req, size_t contentLimit);
private:
	enum State { REQ_LINE, HEADERS, BODY, DONE };
	State _state;
	size_t _needBody;
	std::string _buffer;
};

std::string httpStatusReason(int code);

#endif
