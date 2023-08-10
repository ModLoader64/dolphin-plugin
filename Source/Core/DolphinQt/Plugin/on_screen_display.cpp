#include "export.h"

#include "VideoCommon/OnScreenDisplay.h"

EXPORT void on_screen_display_add_message(const char* message, u32 ms, u32 argb)
{
  OSD::AddMessage(message, ms, argb);
}
