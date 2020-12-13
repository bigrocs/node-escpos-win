#include <napi.h>
#include <windows.h>
#include <string>
#include <list>
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
struct ResultInfo
{
    int number;
    bool success;
    string err;
};

void GetDeviceList(list<DeviceInfo> &devicelist, string deviceType, ResultInfo &resultInfo);
string Utf8Encode(const string &str);