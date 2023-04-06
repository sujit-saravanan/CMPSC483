#pragma once
#define REQ_RES [&](const auto& req, auto& res)
#include "httplib.h"


struct Server{
    httplib::Server m_server;

    Server* page(const std::string &mount_point, const std::string &directory_path);
    Server* get(const std::string &pattern, std::function<void(const httplib::Request &, httplib::Response &)> handle);
    Server* post(const std::string &pattern, std::function<void(const httplib::Request &, httplib::Response &)> handle);

    void listen(const std::string &host, int32_t port);
};