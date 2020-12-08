#include <napi.h>
#include <windows.h>

using namespace Napi;

struct PrintResult{
    BOOL success;
    DWORD err;
};

Object Write(const CallbackInfo &info);
BOOL WriteData(std::string devicePath);