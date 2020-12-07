#include <napi.h>
#include <windows.h>
#include <winioctl.h>
#include <initguid.h>
#include <setupapi.h>
#include <usbiodef.h>
#define LIBRARY_NAME ("setupapi.dll")
// #pragma comment(lib, "setupapi.lib")

Napi::Object GetUsbDeviceList(const Napi::CallbackInfo &info);
