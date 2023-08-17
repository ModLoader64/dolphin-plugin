#include "dup_string.h"
#include "export.h"

#include "Core/HW/Memmap.h"
#include "Core/System.h"

static Memory::MemoryManager& get_memory_manager()
{
  return Core::System::GetInstance().GetMemory();
}

EXPORT u32 memory_get_ram_size_real()
{
  return get_memory_manager().GetRamSizeReal();
}

EXPORT u32 memory_get_ram_size()
{
  return get_memory_manager().GetRamSize();
}

EXPORT u32 memory_get_ram_mask()
{
  return get_memory_manager().GetRamMask();
}

EXPORT u32 memory_get_fake_vmem_size()
{
  return get_memory_manager().GetFakeVMemSize();
}

EXPORT u32 memory_get_fake_vmem_mask()
{
  return get_memory_manager().GetFakeVMemMask();
}

EXPORT u32 memory_get_l1_cache_size()
{
  return get_memory_manager().GetL1CacheSize();
}

EXPORT u32 memory_get_l1_cache_mask()
{
  return get_memory_manager().GetL1CacheMask();
}

EXPORT u32 memory_get_exram_size_real()
{
  return get_memory_manager().GetExRamSizeReal();
}

EXPORT u32 memory_get_exram_size()
{
  return get_memory_manager().GetExRamSize();
}

EXPORT u32 memory_get_exram_mask()
{
  return get_memory_manager().GetExRamMask();
}

EXPORT u8* memory_get_ram()
{
  return get_memory_manager().GetRAM();
}

EXPORT u8* memory_get_exram()
{
  return get_memory_manager().GetEXRAM();
}

EXPORT u8* memory_get_l1_cache()
{
  return get_memory_manager().GetL1Cache();
}

EXPORT u8* memory_get_fake_vmem()
{
  return get_memory_manager().GetFakeVMEM();
}

EXPORT u8* memory_get_pointer(u32 address)
{
  return get_memory_manager().GetPointer(address);
}

EXPORT u8* memory_get_pointer_for_range(u32 address, u32 size)
{
  return get_memory_manager().GetPointerForRange(address, size);
}

EXPORT u8 memory_read_u8(u32 address)
{
  return get_memory_manager().Read_U8(address);
}

EXPORT void memory_write_u8(u8 var, u32 address)
{
  return get_memory_manager().Write_U8(var, address);
}
