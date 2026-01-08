#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include "../include/CameraHandler.h"
#include "../include/Logger.h"

const std::string ISO = "iso";
const std::string APERTURE = "aperture";
const std::string SHUTTER_SPEED = "shutterspeed";

int main(int argc, char* argv[])
{
    Logger::Log(LogLevel::INFO, "LAUNCHING MACROPHOTOGRAPHY CONTROLLER...");

    CameraHandler camera;
    int result = camera.connect();
    if (result != 0)
    {
        camera.disconnect();
        return 1;
    }

    camera.disconnect();
    return 0;
}


