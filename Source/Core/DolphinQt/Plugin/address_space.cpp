#include "export.h"

#include "Core/Core.h"
#include "Core/HW/AddressSpace.h"
#include "Core/System.h"

EXPORT AddressSpace::Accessors* address_space_get_accessors(int address_space)
{
  return AddressSpace::GetAccessors(static_cast<AddressSpace::Type>(address_space));
}

EXPORT bool address_space_accessors_is_valid_address(AddressSpace::Accessors* accessors,
                                                     u32 address)
{
  Core::CPUThreadGuard guard{Core::System::GetInstance()};
  return accessors->IsValidAddress(guard, address);
}

EXPORT u8 address_space_accessors_read_u8(AddressSpace::Accessors* accessors, u32 address)
{
  Core::CPUThreadGuard guard{Core::System::GetInstance()};
  return accessors->ReadU8(guard, address);
}

EXPORT void address_space_accessors_write_u8(AddressSpace::Accessors* accessors, u32 address,
                                             u8 value)
{
  Core::CPUThreadGuard guard{Core::System::GetInstance()};
  return accessors->WriteU8(guard, address, value);
}

EXPORT AddressSpace::Accessors::iterator
address_space_accessors_begin(AddressSpace::Accessors* accessors)
{
  return accessors->begin();
}

EXPORT AddressSpace::Accessors::iterator
address_space_accessors_end(AddressSpace::Accessors* accessors)
{
  return accessors->end();
}

EXPORT u32 address_space_accessors_get_size(AddressSpace::Accessors* accessors)
{
  return static_cast<u32>(accessors->end() - accessors->begin());
}

EXPORT u32 address_space_accessors_search(AddressSpace::Accessors* accessors, u32 haystack_offset,
                                          const u8* needle_start, u32 needle_size, bool forward,
                                          bool* ok)
{
  Core::CPUThreadGuard guard{Core::System::GetInstance()};
  const auto res = accessors->Search(guard, haystack_offset, needle_start, needle_size, forward);
  *ok = res.has_value();
  return res.value_or(0);
}
