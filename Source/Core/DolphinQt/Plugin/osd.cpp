#include "export.h"

#include "VideoCommon/OnScreenDisplay.h"
#include "VideoCommon/OnScreenUI.h"

EXPORT void osd_add_message(const char* message, u32 ms, u32 argb)
{
  OSD::AddMessage(message, ms, argb);
}

EXPORT void osd_set_imgui_init_callback(VideoCommon::OnScreenUI::ImGuiCallbackFunc callback)
{
  VideoCommon::OnScreenUI::SetImGuiInitCallback(callback);
}

EXPORT void osd_set_imgui_render_callback(VideoCommon::OnScreenUI::ImGuiCallbackFunc callback)
{
  VideoCommon::OnScreenUI::SetImGuiRenderCallback(callback);
}
