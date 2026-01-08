#include "../include/CameraHandler.h"
#include "../include/Logger.h"
#include <gphoto2/gphoto2-widget.h>

CameraHandler::CameraHandler()
{
    m_camera = nullptr;
    m_context = gp_context_new();
}

int CameraHandler::connect()
{
    int res = 0;

    gp_camera_new(&m_camera);
    res = gp_camera_init(m_camera, m_context);

    if (res < GP_OK)
    {
        Logger::Log(LogLevel::ERROR, "Could not connect to camera. Code: %d", res);
        gp_camera_free(m_camera);
        m_camera = nullptr;
        return res;
    }

    Logger::Log(LogLevel::INFO, "Successfully connected to camera!");
    return res;
}

void CameraHandler::disconnect()
{
    if (m_camera)
    {
        gp_camera_exit(m_camera, m_context);
        gp_camera_free(m_camera);
    }
    gp_context_unref(m_context);
}

std::string CameraHandler::getCameraMode()
{
    CameraWidget* root_config = nullptr;
    CameraWidget* child_widget = nullptr;
    char* current_mode = nullptr;

    gp_camera_get_config(m_camera, &root_config, m_context);
    if (gp_widget_get_child_by_name(root_config, "autoexposuremode", &child_widget) == GP_OK)
    {
        gp_widget_get_value(child_widget, &current_mode);
        std::string mode(current_mode);
        gp_widget_free(root_config);
        return mode;
    }

    gp_widget_free(root_config);
    return "Unknown";
}

bool CameraHandler::setConfiguration(const std::string& setting, const std::string& value)
{
    CameraWidget* root_config = nullptr;
    CameraWidget* child_widget = nullptr;
    bool found = false;

    gp_camera_get_config(m_camera, &root_config, m_context);
    if (gp_widget_get_child_by_name(root_config, setting.c_str(), &child_widget) == GP_OK)
    {
        int count = gp_widget_count_choices(child_widget);

        for (int i = 0; i < count; i++)
        {
            const char* choice;
            gp_widget_get_choice(child_widget, i, &choice);

            if (value == choice)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            Logger::Log(LogLevel::ERROR, "%s not valid for %s on this camera", value, setting);
            gp_widget_free(root_config);
            return false;
        }
    }

    if (!found)
    {
        Logger::Log(LogLevel::ERROR, "%s is not a valid configuration option for the camera", setting);
        gp_widget_free(root_config);
        return false;
    }

    int res = gp_widget_set_value(child_widget, value.c_str());
    if (res != GP_OK)
    {
        Logger::Log(LogLevel::ERROR, "Widget update failed for %s. Error Code: %d", setting, res);
        gp_widget_free(root_config);
        return false;
    }
    gp_camera_set_config(m_camera, root_config, m_context);
    Logger::Log(LogLevel::INFO, "Successfully set %s to %s", setting, value);

    gp_widget_free(root_config);
    return true;

}

std::string CameraHandler::getConfiguration(const std::string& setting)
{
    CameraWidget* root_config = nullptr;
    CameraWidget* child_widget = nullptr;
    char* val = nullptr;
    std::string result = "";

    if (gp_camera_get_config(m_camera, &root_config, m_context) != GP_OK)
    {
        Logger::Log(LogLevel::ERROR, "Failed to retrieve config tree for %s", setting.c_str());
        return result;
    }

    if (gp_widget_get_child_by_name(root_config, setting.c_str(), &child_widget) == GP_OK)
    {
        gp_widget_get_value(child_widget, &val);
        if (val)
        {
            result = std::string(val);
        }
    }
    else 
    {
        Logger::Log(LogLevel::ERROR, "%s is not a valid configuration option", setting);
    }

    gp_widget_free(root_config);
    return result;
}


