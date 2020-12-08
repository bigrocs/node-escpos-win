#include <napi.h>
#include <windows.h>
#include <winioctl.h>
#include <initguid.h>
#include <setupapi.h>
#include <usbiodef.h>
#pragma comment(lib, "setupapi.lib")

using namespace Napi;

Object GetUsbDeviceList(const CallbackInfo &info);
std::string Utf8Encode(const std::string &str);