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

EXPORT void gui_main_window_set_icon_from_file(const char* path)
{
  g_main_window->setWindowIcon(QIcon{QString::fromUtf8(path)});
}

EXPORT void gui_main_window_start_game_from_file(const char* path)
{
  g_main_window->StartGame(BootParameters::GenerateFromFile(path));
}
