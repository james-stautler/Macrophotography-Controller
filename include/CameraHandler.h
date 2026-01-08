#pragma once

extern "C"
{
    #include <gphoto2/gphoto2-camera.h>
    #include <gphoto2/gphoto2-context.h>
}

#include <string>

class CameraHandler
{

private:
    Camera* m_camera;
    GPContext* m_context;

public:
    CameraHandler();

    int connect();
    void disconnect();

    std::string getCameraMode();
    
    bool setConfiguration(const std::string& setting, const std::string& value);
};

