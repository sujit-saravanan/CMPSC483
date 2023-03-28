#include "server.h"
#include "logger.h"

// adds a page with contents located in directory_path at address/mount_point
Server *Server::page(const std::string &mount_point, const std::string &directory_path) {
    auto ret = m_server.set_mount_point(mount_point, directory_path);
    ASSERT(ret, INFO("MOUNTED \"%s\" : \"%s\"", mount_point.c_str(), directory_path.c_str()), FATAL("FAILED TO MOUNT %s", directory_path.c_str()));
    return this;
}

// makes the server start listening to requests on host:port
void Server::listen(const std::string &host, int32_t port) {
    INFO("Starting server... Listening on %s:%d", host.c_str(), port);
    m_server.listen(host, port);
}

// sets up a get request handler
Server* Server::get(const std::string &pattern, std::function<void(const httplib::Request &, httplib::Response &)> handle) {
    m_server.Get(pattern, std::move(handle));
    return this;
}

// sets up a post request handler
Server* Server::post(const std::string &pattern, std::function<void(const httplib::Request &, httplib::Response &)> handle) {
    m_server.Post(pattern, std::move(handle));
    return this;
}
