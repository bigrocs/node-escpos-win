#include "usb.h"  // NOLINT(build/include)
#define INTERFACE_DETAIL_SIZE (1024)    // SetupDiGetInterfaceDeviceDetail所需要的输出长度，定义足够大
/*
    GetUsbDeviceList
    返回的json数据
    Napi::Object {
        list : [                             // 设备列表
            {
                name : 'USB  打印支持',      // 设备名称
                service : '服务名称',        // 服务名称
                desc : '设备描述',           // 设备描述
                manufacturer : '设备制造商', // 设备制造商
                vid : 'vid',                // vendorId
                pid : 'pid',                // productId
                path : '设备路径',           // 设备路径
            }
        ],
        number : 1, //设备数量
        error:'This operating system is not supported by this application' // 错误提示,
    }
*/
Napi::Object GetUsbDeviceList(const Napi::CallbackInfo &info)
{
    HDEVINFO hDevInfoSet;
    PSP_DEVICE_INTERFACE_DETAIL_DATA pDetail;
    SP_DEVICE_INTERFACE_DATA ifdata;

    Napi::Env env = info.Env();
    Napi::Object obj = Napi::Object::New(env); // 初始化函数返回数据对象
    // 取得一个该GUID相关的设备信息集句柄
    hDevInfoSet = ::SetupDiGetClassDevs((LPGUID)&GUID_DEVINTERFACE_USB_DEVICE,  // class GUID USB
                                        NULL,                                   // 无关键字
                                        NULL,                                   // 不指定父窗口句柄
                                        DIGCF_PRESENT | DIGCF_DEVICEINTERFACE); // 目前存在的设备
    // 获取设备信息失败
    if (hDevInfoSet == INVALID_HANDLE_VALUE)
    {
        obj.Set(Napi::String::New(env, "error"), "Failed to get device information");
    }

    // 申请设备接口数据空间
    pDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)::GlobalAlloc(LMEM_ZEROINIT, INTERFACE_DETAIL_SIZE);
    pDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

    int nCount = 0;
    BOOL bResult = true;
    Napi::Array list = Napi::Array::New(env);
    // 设备序号=0,1,2... 逐一测试设备接口，到失败为止
    while (bResult)
    {
        Napi::Object device = Napi::Object::New(env);
        ifdata.cbSize = sizeof(ifdata);
        // 枚举符合该GUID的设备接口
        bResult = ::SetupDiEnumDeviceInterfaces(hDevInfoSet,                             // 设备信息集句柄
                                                NULL,                                    // 不需额外的设备描述
                                                (LPGUID)&GUID_DEVINTERFACE_USB_DEVICE,   // GUID
                                                (ULONG)nCount,                           // 设备信息集里的设备序号
                                                &ifdata);                                // 设备接口信息
        obj.Set(Napi::String::New(env, "bResult1"), bResult);
        if (bResult)
        {
            // 取得该设备接口的细节(设备路径)
            bResult = SetupDiGetInterfaceDeviceDetail(hDevInfoSet,           // 设备信息集句柄
                                                        &ifdata,               // 设备接口信息
                                                        pDetail,               // 设备接口细节(设备路径)
                                                        INTERFACE_DETAIL_SIZE, // 输出缓冲区大小
                                                        NULL,                  // 不需计算输出缓冲区大小(直接用设定值)
                                                        NULL);                 // 不需额外的设备描述
            obj.Set(Napi::String::New(env, "bResult2"), bResult);
            if (bResult)
            {
                device.Set(Napi::String::New(env, "path"), pDetail->DevicePath);    // 复制设备路径到Napi对象
                nCount++; // 调整计数值
            }
        }
        list.Set(Napi::Number::New(env, nCount), device);
    }
    ::GlobalFree(pDetail); // 释放设备接口数据空间
    ::SetupDiDestroyDeviceInfoList(hDevInfoSet); // 关闭设备信息集句柄

    obj.Set(Napi::String::New(env, "number"), nCount);
    return obj;
}