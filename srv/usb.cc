#include "usb.h"  // NOLINT(build/include)
// SetupDiGetInterfaceDeviceDetail所需要的输出长度，定义足够大
#define INTERFACE_DETAIL_SIZE (1024)
#define MAX_DEVICE (10)
Napi::Array GetUsbDeviceList(const Napi::CallbackInfo &info)
{

    int i;
    char* szDevicePath[MAX_DEVICE];        // 设备路径
  
    // 分配需要的空间
    for (i = 0; i < MAX_DEVICE; i++)
    {
        szDevicePath[i] = new char[256];
    }
    int nDevice;
    // 取设备路径
    nDevice = ::GetDevicePath((LPGUID)&GUID_DEVINTERFACE_USB_DEVICE, szDevicePath);

    Napi::Env env = info.Env();
    Napi::Array arr = Napi::Array::New(env);
    int count = 1;
    for (int i = 0; i < count; i++)
    {
        Napi::Object info = Napi::Object::New(env);
        info.Set(Napi::String::New(env, "deviceName"), "name");
        info.Set(Napi::String::New(env, "manufacturer"), "desc");
        info.Set(Napi::String::New(env, "serialNumber"), "service");
        info.Set(Napi::String::New(env, "devicePath"), "path");
        info.Set(Napi::String::New(env, "deviceCont"), nDevice);
        arr.Set(Napi::Number::New(env, i), info);
    }
    return arr;
}

// 根据GUID获得设备路径
// lpGuid: GUID指针
// pszDevicePath: 设备路径指针的指针
// 返回: 成功得到的设备路径个数，可能不止1个
int GetDevicePath(LPGUID lpGuid, LPTSTR *pszDevicePath)
{
    HDEVINFO hDevInfoSet;
    SP_DEVICE_INTERFACE_DATA ifdata;
    PSP_DEVICE_INTERFACE_DETAIL_DATA pDetail;
    int nCount;
    BOOL bResult;

    // 取得一个该GUID相关的设备信息集句柄
    hDevInfoSet = ::SetupDiGetClassDevs(lpGuid,                                 // class GUID
                                        NULL,                                   // 无关键字
                                        NULL,                                   // 不指定父窗口句柄
                                        DIGCF_PRESENT | DIGCF_DEVICEINTERFACE); // 目前存在的设备

    // 失败...
    if (hDevInfoSet == INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    // 申请设备接口数据空间
    pDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)::GlobalAlloc(LMEM_ZEROINIT, INTERFACE_DETAIL_SIZE);

    pDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

    nCount = 0;
    bResult = TRUE;

    // 设备序号=0,1,2... 逐一测试设备接口，到失败为止
    while (bResult)
    {
        ifdata.cbSize = sizeof(ifdata);

        // 枚举符合该GUID的设备接口
        bResult = ::SetupDiEnumDeviceInterfaces(
            hDevInfoSet,   // 设备信息集句柄
            NULL,          // 不需额外的设备描述
            lpGuid,        // GUID
            (ULONG)nCount, // 设备信息集里的设备序号
            &ifdata);      // 设备接口信息

        if (bResult)
        {
            // 取得该设备接口的细节(设备路径)
            bResult = SetupDiGetInterfaceDeviceDetail(
                hDevInfoSet,           // 设备信息集句柄
                &ifdata,               // 设备接口信息
                pDetail,               // 设备接口细节(设备路径)
                INTERFACE_DETAIL_SIZE, // 输出缓冲区大小
                NULL,                  // 不需计算输出缓冲区大小(直接用设定值)
                NULL);                 // 不需额外的设备描述

            if (bResult)
            {
                // 复制设备路径到输出缓冲区
                ::strcpy(pszDevicePath[nCount], pDetail->DevicePath);

                // 调整计数值
                nCount++;
            }
        }
    }

    // 释放设备接口数据空间
    ::GlobalFree(pDetail);

    // 关闭设备信息集句柄
    ::SetupDiDestroyDeviceInfoList(hDevInfoSet);

    return nCount;
}