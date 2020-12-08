#include <napi.h>
#include <windows.h>

using namespace Napi;

struct PrintResult{
    std::BOOL success;
    std::DWORD err;
};

Object Write(const CallbackInfo &info);
BOOL WriteData(std::string devicePath);