#include <napi.h>
#include <windows.h>
#include <winioctl.h>
#include <initguid.h>
#include <setupapi.h>
#include <usbiodef.h>
#include <devpropdef.h>
#include <devpkey.h>
#pragma comment(lib, "setupapi.lib")

Napi::Object GetUsbDeviceList(const Napi::CallbackInfo &info);
std::string Utf8Encode(const std::string &str);