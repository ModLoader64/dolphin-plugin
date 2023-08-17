#include "export.h"

#include "Core/PowerPC/JitInterface.h"
#include "Core/System.h"

static JitInterface& get_jit_interface()
{
  return Core::System::GetInstance().GetJitInterface();
}

EXPORT void jit_interface_clear_cache()
{
  get_jit_interface().ClearCache();
}

EXPORT void jit_interface_invalidate_icache(u32 address, u32 size, bool forced)
{
  get_jit_interface().InvalidateICache(address, size, forced);
}

EXPORT void jit_interface_invalidate_icache_line(u32 address)
{
  get_jit_interface().InvalidateICacheLine(address);
}

EXPORT void jit_interface_invalidate_icache_lines(u32 address, u32 count)
{
  get_jit_interface().InvalidateICacheLines(address, count);
}
