#include <napi.h>
#include <windows.h>
#include <winioctl.h>
#include <initguid.h>
#include <setupapi.h>
#include <usbiodef.h>
#pragma comment(lib, "setupapi.lib")

Napi::Array GetUsbDeviceList(const Napi::CallbackInfo &info);
