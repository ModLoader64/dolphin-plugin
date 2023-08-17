#include "export.h"

#include "Core/Core.h"
#include "Core/HW/ProcessorInterface.h"
#include "Core/System.h"

EXPORT double core_get_actual_emulation_speed()
{
  return Core::GetActualEmulationSpeed();
}

EXPORT bool core_is_running()
{
  return Core::IsRunning();
}

EXPORT bool core_is_running_and_started()
{
  return Core::IsRunningAndStarted();
}

EXPORT bool core_is_running_in_current_thread()
{
  return Core::IsRunningInCurrentThread();
}

EXPORT bool core_is_cpu_thread()
{
  return Core::IsCPUThread();
}

EXPORT bool core_is_gpu_thread()
{
  return Core::IsGPUThread();
}

EXPORT bool core_is_host_thread()
{
  return Core::IsHostThread();
}

EXPORT int core_get_state()
{
  return static_cast<int>(Core::GetState());
}

EXPORT void core_save_screenshot()
{
  Core::SaveScreenShot();
}

EXPORT void core_save_screenshot_as(const char* name)
{
  Core::SaveScreenShot(name);
}

EXPORT void core_display_message(const char* message, int time_in_ms)
{
  Core::DisplayMessage(message, time_in_ms);
}

using VoidCallbackFunc = void (*)();

EXPORT void core_run_as_cpu_thread(VoidCallbackFunc function)
{
  Core::RunAsCPUThread(function);
}

EXPORT void core_run_on_cpu_thread(VoidCallbackFunc function, bool wait_for_completion)
{
  Core::RunOnCPUThread(function, wait_for_completion);
}

using StateChangedCallbackFunc = void (*)(Core::State);

EXPORT int core_add_on_state_changed_callback(StateChangedCallbackFunc callback)
{
  return Core::AddOnStateChangedCallback(callback);
}

EXPORT bool core_remove_on_state_changed_callback(int* handle)
{
  return Core::RemoveOnStateChangedCallback(handle);
}

EXPORT void core_queue_host_job(VoidCallbackFunc job, bool run_during_stop)
{
  Core::QueueHostJob(job, run_during_stop);
}

EXPORT void core_host_dispatch_jobs()
{
  Core::HostDispatchJobs();
}

EXPORT void core_do_frame_step()
{
  Core::DoFrameStep();
}

EXPORT void core_set_frame_end_callback(Core::FrameEndCallbackFunc callback)
{
  Core::SetFrameEndCallback(callback);
}

EXPORT void
core_set_reset_callback(ProcessorInterface::ProcessorInterfaceManager::ResetCallbackFunc callback)
{
  Core::System::GetInstance().GetProcessorInterface().SetResetCallback(callback);
}
