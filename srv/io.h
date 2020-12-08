#include <napi.h>
#include <windows.h>

using namespace Napi;

Object Write(const CallbackInfo &info);
BOOL WriteData(std::string devicePath);