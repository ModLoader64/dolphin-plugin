#include "dup_string.h"
#include "export.h"

char* dup_std_string(const std::string& str)
{
  auto dst = malloc(str.size() + 1);
  memcpy(dst, str.c_str(), str.size() + 1);
  return static_cast<char*>(dst);
}

char* dup_qstring(const QString& str)
{
  return dup_std_string(str.toStdString());
}

EXPORT void dup_free(char* str)
{
  free(str);
}
