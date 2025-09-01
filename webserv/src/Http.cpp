/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Http.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:20:44 by tales             #+#    #+#             */
/*   Updated: 2025/09/01 09:20:45 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Http.hpp"
#include "Utils.hpp"
#include <sstream>
#include <cstdlib>

HttpParser::HttpParser(): _state(REQ_LINE), _needBody(0) {}

bool HttpParser::parse(const std::string &data, size_t &consumed, HttpRequest &req, size_t contentLimit) {
	_buffer += data;
	consumed = data.size();
	if (_state == REQ_LINE) {
		size_t pos = _buffer.find("\r\n");
		if (pos == std::string::npos) return false;
		std::string line = _buffer.substr(0, pos);
		_buffer.erase(0, pos+2);
		std::istringstream is(line);
		is >> req.method >> req.uri >> req.version;
		_state = HEADERS;
	}
	if (_state == HEADERS) {
		while (true) {
			size_t pos = _buffer.find("\r\n");
			if (pos == std::string::npos) return false;
			if (pos == 0) { // end of headers
				_buffer.erase(0, 2);
				std::map<std::string,std::string>::iterator it = req.headers.find("Content-Length");
				_needBody = 0;
				if (it != req.headers.end()) {
					_needBody = (size_t)std::atoi(it->second.c_str());
					if (_needBody > contentLimit) _needBody = contentLimit + 1;
				}
				_state = (_needBody ? BODY : DONE);
				break;
			}
			std::string line = _buffer.substr(0, pos);
			_buffer.erase(0, pos+2);
			size_t colon = line.find(':');
			if (colon != std::string::npos) {
				std::string k = line.substr(0, colon);
				std::string v = Utils::trim(line.substr(colon+1));
				if (req.headers.count(k)) req.headers[k] += ", " + v;
				else req.headers[k] = v;
			}
		}
	}
	if (_state == BODY) {
		if (_buffer.size() < _needBody) return false;
		req.body = _buffer.substr(0, _needBody);
		_buffer.erase(0, _needBody);
		_state = DONE;
	}
	return _state == DONE;
}

std::string httpStatusReason(int code) {
	switch (code) {
		case 200: return "OK";
		case 201: return "Created";
		case 204: return "No Content";
		case 301: return "Moved Permanently";
		case 302: return "Found";
		case 400: return "Bad Request";
		case 403: return "Forbidden";
		case 404: return "Not Found";
		case 405: return "Method Not Allowed";
		case 413: return "Payload Too Large";
		case 500: return "Internal Server Error";
		case 502: return "Bad Gateway";      
		case 504: return "Gateway Timeout";  
		default: return "OK";
	}
}
