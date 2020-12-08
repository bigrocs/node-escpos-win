#include <napi.h>
#include <windows.h>

using namespace Napi;

Object Write(const CallbackInfo &info);
BOOL WriteData(String devicePath, Buffer<uint16_t> *data, Object *obj);