#include <napi.h>
#include <windows.h>
#include <winioctl.h>
#include <initguid.h>
#include <setupapi.h>
#pragma comment(lib, "setupapi.lib")

Napi::Array GetUsbDeviceList(const Napi::CallbackInfo &info);
int GetDevicePath(LPGUID lpGuid, LPTSTR *pszDevicePath);
