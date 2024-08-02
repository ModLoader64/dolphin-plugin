#include "export.h"

#include "DolphinQt/MainWindow.h"
#include "DolphinQt/Settings.h"

static MainWindow* g_main_window;

EXPORT void gui_main_window_create()
{
  g_main_window = new MainWindow({}, {});
  Settings::Instance().InitDefaultPalette();
  Settings::Instance().UpdateSystemDark();
  Settings::Instance().ApplyStyle();
}

EXPORT void gui_main_window_destroy()
{
  delete g_main_window;
}

EXPORT void gui_main_window_show()
{
  g_main_window->Show();
}
