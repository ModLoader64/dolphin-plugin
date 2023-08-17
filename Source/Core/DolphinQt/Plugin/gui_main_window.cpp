#include "export.h"

#include "DolphinQt/MainWindow.h"
#include "DolphinQt/Settings.h"

static MainWindow* g_main_window;

EXPORT void gui_main_window_create()
{
  auto& settings = Settings::Instance();
  settings.InitDefaultPalette();
  settings.UpdateSystemDark();
  settings.SetCurrentUserStyle(settings.GetCurrentUserStyle());

  g_main_window = new MainWindow({}, {});
}

EXPORT void gui_main_window_destroy()
{
  delete g_main_window;
}

EXPORT void gui_main_window_show()
{
  g_main_window->Show();
}
