#pragma once

#include "CameraHandler.h"
#include "Logger.h"
#include <string>
#include <vector>
#include <map>

class CommandInterface
{
private:
    CameraHandler& m_camera;
    bool m_running;

    void printHelp();
    std::vector<std::string> tokenize(const std::string& input);

    void handleGet(std::vector<std::string>& tokens);
    void handleSet(std::vector<std::string>& tokens);

public:
    CommandInterface(CameraHandler& camera) : m_camera(camera), m_running(false) {};
    void run();

};
