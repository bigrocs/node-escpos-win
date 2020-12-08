#include <napi.h>
#include <windows.h>

using namespace Napi;

struct Result{
    BOOL success;
    DWORD err;
};

Object Write(const CallbackInfo &info);
BOOL WriteData(std::string devicePath, Result *result);