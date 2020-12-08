#include <napi.h>
#include <windows.h>
#include <winioctl.h>
#include <initguid.h>
#include <setupapi.h>
#include <usbiodef.h>
#pragma comment(lib, "setupapi.lib")

using namespace Napi;

struct List {
    char name;
    char service;
    char manufacturer;
    char location;
    char path;
};
// struct Result
// {
//     int number;
//     bool success;
//     DWORD err;
//     List[] list;
// } result;

void GetUsbDeviceList();
string Utf8Encode(const string &str);