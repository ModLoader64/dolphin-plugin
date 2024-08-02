#include "export.h"

#include "Common/FileUtil.h"
#include "Common/MsgHandler.h"
#include "Core/Config/MainSettings.h"
#include "Core/Core.h"
#include "Core/DolphinAnalytics.h"
#include "DolphinQt/Host.h"
#include "DolphinQt/MainWindow.h"
#include "DolphinQt/Resources.h"
#include "DolphinQt/Settings.h"
#include "DolphinQt/Translation.h"
#include "UICommon/CommandLineParse.h"
#include "UICommon/UICommon.h"

#include <QAbstractEventDispatcher>
#include <QApplication>
#include <filesystem>

static struct
{
  QApplication* app;
  bool has_exited;
} g_app;

bool QtMsgAlertHandler(const char* caption, const char* text, bool yes_no, Common::MsgType style);

struct QuitEventFilter : QObject
{
  bool eventFilter(QObject* watched, QEvent* event) override
  {
    if (event->type() == QEvent::Quit)
    {
      g_app.has_exited = true;
      return true;
    }
    return false;
  }
};

EXPORT void gui_application_init()
{
  Core::DeclareAsHostThread();

  #ifdef __linux__
  // Qt 6.3+ has a bug which causes mouse inputs to not be registered in our XInput2 code.
  // If we define QT_XCB_NO_XI2, Qt's xcb platform plugin no longer initializes its XInput
  // code, which makes mouse inputs work again.
  // For more information: https://bugs.dolphin-emu.org/issues/12913
  #if (QT_VERSION >= QT_VERSION_CHECK(6, 3, 0))
    setenv("QT_XCB_NO_XI2", "1", true);
  #endif
  #endif

#ifdef _WIN32
    g_app.app = new QApplication(__argc, __argv);
#else
  static int argc = 1;
  static auto argv0 = (std::filesystem::current_path() / "dolphin-emu").generic_string();
  static char* argv[] = {argv0.data()};
  g_app.app = new QApplication(argc, argv);
#endif

  g_app.app->installEventFilter(new QuitEventFilter);

  UICommon::CreateDirectories();
  UICommon::Init();
  Resources::Init();
  Settings::Instance().SetBatchModeEnabled(false);
  // Hook up alerts from core
  Common::RegisterMsgAlertHandler(QtMsgAlertHandler);

  // Hook up translations
  Translation::Initialize();

  // Whenever the event loop is about to go to sleep, dispatch the jobs
  // queued in the Core first.
  QObject::connect(QAbstractEventDispatcher::instance(), &QAbstractEventDispatcher::aboutToBlock,
                   g_app.app, [] { Core::HostDispatchJobs(Core::GetSystem()); });

#if defined(USE_ANALYTICS) && USE_ANALYTICS
  if (!Config::Get(Config::MAIN_ANALYTICS_PERMISSION_ASKED))
  {
    Config::SetBase(Config::MAIN_ANALYTICS_PERMISSION_ASKED, true);
    Settings::Instance().SetAnalyticsEnabled(false);

    DolphinAnalytics::Instance().ReloadConfig();
  }
#endif
}

EXPORT void gui_application_deinit()
{
  Core::Shutdown(Core::GetSystem());
  UICommon::Shutdown();
  Host::GetInstance()->deleteLater();

  delete g_app.app;
}

EXPORT bool gui_application_has_exited()
{
  return g_app.has_exited;
}

EXPORT void gui_application_set_organization_domain(const char16_t* org_domain)
{
  QApplication::setOrganizationDomain(QString::fromUtf16(org_domain));
}

EXPORT void gui_application_set_organization_name(const char16_t* org_name)
{
  QApplication::setOrganizationName(QString::fromUtf16(org_name));
}

EXPORT void gui_application_set_application_name(const char16_t* application)
{
  QApplication::setApplicationName(QString::fromUtf16(application));
}

EXPORT void gui_application_set_application_version(const char16_t* version)
{
  QApplication::setApplicationVersion(QString::fromUtf16(version));
}

EXPORT void gui_application_set_application_display_name(const char16_t* name)
{
  QApplication::setApplicationDisplayName(QString::fromUtf16(name));
}

EXPORT void gui_application_set_desktop_filename(const char16_t* name)
{
  QApplication::setDesktopFileName(QString::fromUtf16(name));
}

EXPORT void gui_application_add_library_path(const char16_t* path)
{
  QApplication::addLibraryPath(QString::fromUtf16(path));
}

EXPORT void gui_application_set_exe_directory(const char* path)
{
  File::SetExeDirectory(path);
}

EXPORT void gui_application_set_user_directory(const char* path)
{
  UICommon::SetUserDirectory(path);
}

EXPORT int gui_application_exec()
{
  return QApplication::exec();
}

EXPORT bool gui_application_process_events()
{
  return QApplication::eventDispatcher()->processEvents(QEventLoop::AllEvents);
}

EXPORT void gui_application_quit()
{
  QApplication::quit();
}

EXPORT void gui_application_exit(int retcode)
{
  QApplication::exit(retcode);
}
