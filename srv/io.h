#include <napi.h>
#include <windows.h>

using namespace Napi;

Object Write(const CallbackInfo &info);
BOOL WriteData(Env env, String devicePath, Object *obj);