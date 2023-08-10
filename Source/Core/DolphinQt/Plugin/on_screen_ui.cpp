#include "export.h"

#include "VideoCommon/OnScreenUI.h"

EXPORT void
on_screen_ui_set_imgui_init_callback(VideoCommon::OnScreenUI::ImGuiHookCallbackFunc callback)
{
  VideoCommon::OnScreenUI::SetImGuiInitCallback(callback);
}

EXPORT void
on_screen_ui_set_imgui_render_callback(VideoCommon::OnScreenUI::ImGuiHookCallbackFunc callback)
{
  VideoCommon::OnScreenUI::SetImGuiRenderCallback(callback);
}
