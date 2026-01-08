#include "../include/CommandInterface.h"

void CommandInterface::printHelp()
{
    printf("TODO: USAGE\n");
}

std::vector<std::string> CommandInterface::tokenize(const std::string& input)
{
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string tmp;

    while (ss >> tmp)
    {
        tokens.push_back(tmp);
    }

    return tokens;
}

void CommandInterface::handleGet(std::vector<std::string>& tokens)
{
    std::string config = tokens[1];
    std::string value = m_camera.getConfiguration(config);

    if (value == "")
    {
        return;
    }
    Logger::Log(LogLevel::INFO, "Value for %s: %s", config, value);
}

void CommandInterface::handleSet(std::vector<std::string>& tokens)
{
    std::string config = tokens[1];
    std::string value = tokens[2];
    m_camera.setConfiguration(config, value);
}

void CommandInterface::handleCapture(std::vector<std::string>& tokens)
{
    std::string fileName = tokens[1];
    m_camera.captureImage(fileName);
}

void CommandInterface::run()
{
    
    m_running = true;
    Logger::Log(LogLevel::INFO, "Starting CLI...");
    Logger::Log(LogLevel::INFO, "Type 'help' for usage information");

    std::string input;

    while (m_running)
    {
        printf("\033[1;32m[CAMERA PROMPT]>\033[0m");
        std::getline(std::cin, input);
        
        auto tokens = tokenize(input);
        std::string cmd = tokens[0];

        if (cmd == "help")
        {
            printHelp();
        }
        else if (cmd == "exit")
        {
            m_running = false;
        }
        else if (cmd == "get")
        {
            if (tokens.size() != 2)
            {
                Logger::Log(LogLevel::ERROR, "Improper usage of 'get'. Enter 'help' for proper usage.");
                continue;
            }
            handleGet(tokens);
        }
        else if (cmd == "set")
        {
            if (tokens.size() != 3)
            {
                Logger::Log(LogLevel::ERROR, "Improper usage of 'set'. Enter 'help' for proper usage.");
                continue;
            }
            handleSet(tokens);
        }
        else if (cmd == "capture")
        {
            if (tokens.size() != 2)
            {
                Logger::Log(LogLevel::ERROR, "Improper usage of 'capture'. Enter 'help' for proper usage");
                continue;
            }
            handleCapture(tokens);
        }
        else 
        {
            Logger::Log(LogLevel::ERROR, "Please enter 'help' for a list of acceptable queries"); 
        }
    }
    
}
