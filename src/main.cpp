#include "../include/CameraHandler.h"
#include "../include/Logger.h"
#include "../include/CommandInterface.h"

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

    CommandInterface cli(camera);
    cli.run();

    camera.disconnect();
    return 0;
}


