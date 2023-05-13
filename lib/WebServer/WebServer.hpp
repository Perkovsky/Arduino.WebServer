#pragma once

#include <String.h>
#include "LoggerFactory.hpp"

class WebServer {
private:
    LoggerFactory& _logger;

public:
    WebServer(LoggerFactory& logger) : _logger(logger) {}

    // void bebin(uint16_t port) {
    //     _server = new AsyncServer(port);
        
    //     _server->onClient([](void* arg, AsyncClient* newClient) {
    //         TcpServer* server = reinterpret_cast<TcpServer*>(arg);
    //         server->onClientConnect(newClient);
    //     }, this);
        
    //     _server->begin();
    //     _logger.logInfo("TCP Server has been started");
    // }

    // void end() {
    //     _server->end();
    //     _logger.logInfo("TCP Server has been ended");
    // }
};