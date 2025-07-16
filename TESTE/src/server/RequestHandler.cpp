// src/server/RequestHandler.cpp
#include "../../include/server/RequestHandler.hpp"

const LocationConfig *match_location(const ServerConfig &config, const std::string &path) {
    const LocationConfig *best = NULL;
    size_t bestLen = 0;
    for (size_t i = 0; i < config.locations.size(); ++i) {
        const LocationConfig &loc = config.locations[i];
        if (path.find(loc.path) == 0 && loc.path.length() > bestLen) {
            best    = &loc;
            bestLen = loc.path.length();
        }
    }
    return best;
}

std::string get_upload_dir_by_extension(const std::string &filename) {
    if (filename.find(".jpg") != std::string::npos ||
        filename.find(".jpeg") != std::string::npos ||
        filename.find(".png") != std::string::npos) {
        return "./www/fotos/";
    }
    if (filename.find(".pdf") != std::string::npos) {
        return "./www/pdfs/";
    }
    return "./www/othes/";
}
