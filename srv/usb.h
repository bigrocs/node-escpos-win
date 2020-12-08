#include <napi.h>
#include <windows.h>
#include <string>
#include <winioctl.h>
#include <initguid.h>
#include <setupapi.h>
#include <usbiodef.h>
#pragma comment(lib, "setupapi.lib")

using namespace std;

struct DeviceInfo{
    string name;
    string service;
    string manufacturer;
    string location;
    string path;
};
struct Result
{
    int number;
    bool success;
    DWORD err;
};

void GetUsbDeviceList(list<DeviceInfo> &devicelist, Result &result);
string Utf8Encode(const string &str);