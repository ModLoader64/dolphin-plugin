#include "export.h"

#include "Core/State.h"

#include <cstring>

EXPORT void state_save(int slot, bool wait)
{
  State::Save(slot, wait);
}

EXPORT void state_load(int slot)
{
  State::Load(slot);
}

EXPORT void state_save_as(const char* filename, bool wait)
{
  State::SaveAs(filename, wait);
}

EXPORT void state_load_as(const char* filename)
{
  State::LoadAs(filename);
}

EXPORT void state_save_to_buffer(u8** data, u64* size)
{
  std::vector<u8> buffer;
  State::SaveToBuffer(buffer);
  *data = static_cast<u8*>(malloc(buffer.size()));
  memcpy(*data, buffer.data(), buffer.size());
  *size = buffer.size();
}

EXPORT void state_load_from_buffer(u8* data, u64 size)
{
  std::vector<u8> buffer(size);
  memcpy(buffer.data(), data, size);
  State::LoadFromBuffer(buffer);
}

EXPORT void state_free_buffer_data(u8* data)
{
  free(data);
}
