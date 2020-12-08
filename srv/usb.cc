#include "usb.h"  // NOLINT(build/include)
#define INTERFACE_DETAIL_SIZE (1024)    // SetupDiGetInterfaceDeviceDetail所需要的输出长度，定义足够大
// /*
//     GetUsbDeviceList
//     返回的json数据
//     Object {
//         list : [                             // 设备列表
//             {
//                 name : 'USB  打印支持',      // 设备名称
//                 service : '服务名称',        // 服务名称
//                 manufacturer : '设备制造商', // 设备制造商
//                 location : 'location',      // 位置
//                 path : '设备路径',           // 设备路径
//                 count: 0               // 计数
//             }
//         ],
//         number : 1, //设备数量
//         error:'This operating system is not supported by this application' // 错误提示,
//     }
// */
// void GetUsbDeviceList()
// {
//     HDEVINFO hDevInfoSet;
//     SP_DEVINFO_DATA spDevInfoData;

//     PSP_DEVICE_INTERFACE_DETAIL_DATA pDetail;
//     SP_DEVICE_INTERFACE_DATA ifdata;

//     Env env = info.Env();
//     Object obj = Object::New(env); // 初始化函数返回数据对象
//     // 取得一个该GUID相关的设备信息集句柄
//     hDevInfoSet = ::SetupDiGetClassDevs((LPGUID)&GUID_DEVINTERFACE_USB_DEVICE,  // class GUID USB
//                                         NULL,                                   // 无关键字
//                                         NULL,                                   // 不指定父窗口句柄
//                                         DIGCF_PRESENT | DIGCF_DEVICEINTERFACE); // 目前存在的设备
//     // 获取设备信息失败
//     if (hDevInfoSet == INVALID_HANDLE_VALUE)
//     {
//         obj.Set(String::New(env, "error"), "Failed to get device information");
//     }

//     // 申请设备接口数据空间
//     pDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)::GlobalAlloc(LMEM_ZEROINIT, INTERFACE_DETAIL_SIZE);
//     pDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

//     int nCount = 0;
//     BOOL bResult = true;
//     Array list = Array::New(env);
//     // 设备序号=0,1,2... 逐一测试设备接口，到失败为止
//     while (bResult)
//     {
//         Object device = Object::New(env);
//         // 枚举符合该GUID的设备接口
//         spDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
//         bResult = ::SetupDiEnumDeviceInfo(hDevInfoSet,     // 设备信息集句柄
//                                           (ULONG)nCount,   // 设备信息集里的设备序号
//                                           &spDevInfoData); // 设备接口信息
//         if (bResult){
//             DWORD DataT;
//             char buf[MAX_PATH];
//             // char serviceBuf[MAX_PATH];
//             // char manufacturerBuf[MAX_PATH];
//             DWORD nSize = 0;
//             if (SetupDiGetDeviceRegistryProperty(hDevInfoSet, &spDevInfoData, SPDRP_DEVICEDESC, &DataT, (PBYTE)buf, sizeof(buf), &nSize))
//             {
//                 device.Set(String::New(env, "name"), Utf8Encode(buf).c_str());
//             }
//             else if (SetupDiGetDeviceRegistryProperty(hDevInfoSet, &spDevInfoData, SPDRP_FRIENDLYNAME, &DataT, (PBYTE)buf, sizeof(buf), &nSize))
//             {
//                 device.Set(String::New(env, "name"), Utf8Encode(buf).c_str());
//             }
//             if (SetupDiGetDeviceRegistryProperty(hDevInfoSet, &spDevInfoData,  SPDRP_SERVICE, &DataT, (PBYTE)buf, sizeof(buf), &nSize))
//             {
//                 device.Set(String::New(env, "service"), Utf8Encode(buf).c_str());
//             }
//             if (SetupDiGetDeviceRegistryProperty(hDevInfoSet, &spDevInfoData, SPDRP_MFG, &DataT, (PBYTE)buf, sizeof(buf), &nSize))
//             {
//                 device.Set(String::New(env, "manufacturer"), Utf8Encode(buf).c_str());
//             }
//             if (SetupDiGetDeviceRegistryProperty(hDevInfoSet, &spDevInfoData, SPDRP_LOCATION_PATHS, &DataT, (PBYTE)buf, sizeof(buf), &nSize))
//             {
//                 device.Set(String::New(env, "location"), Utf8Encode(buf).c_str());
//             }
//         }

//         // 开始获取设备路径
//         ifdata.cbSize = sizeof(ifdata);
//         // 枚举符合该GUID的设备接口
//         bResult = ::SetupDiEnumDeviceInterfaces(hDevInfoSet,                             // 设备信息集句柄
//                                                 NULL,                                    // 不需额外的设备描述
//                                                 (LPGUID)&GUID_DEVINTERFACE_USB_DEVICE,   // GUID
//                                                 (ULONG)nCount,                           // 设备信息集里的设备序号
//                                                 &ifdata);                                // 设备接口信息
//         if (bResult)
//         {
//             // 取得该设备接口的细节(设备路径)
//             bResult = SetupDiGetInterfaceDeviceDetail(hDevInfoSet,           // 设备信息集句柄
//                                                         &ifdata,               // 设备接口信息
//                                                         pDetail,               // 设备接口细节(设备路径)
//                                                         INTERFACE_DETAIL_SIZE, // 输出缓冲区大小
//                                                         NULL,                  // 不需计算输出缓冲区大小(直接用设定值)
//                                                         NULL);                 // 不需额外的设备描述
//             if (bResult)
//             {
//                 device.Set(String::New(env, "path"), pDetail->DevicePath); // 复制设备路径到Napi对象
//                 list.Set(Number::New(env, nCount), device);
//                 nCount++;                                                        // 调整计数值
//             }
//         }
//     }
//     ::GlobalFree(pDetail); // 释放设备接口数据空间
//     ::SetupDiDestroyDeviceInfoList(hDevInfoSet); // 关闭设备信息集句柄
//     obj.Set(String::New(env, "list"), list);
//     obj.Set(String::New(env, "number"), nCount);
//     return obj;
// }

// string Utf8Encode(const string &str) {
//     if (str.empty())
//     {
//         return std::string();
//     }

//     //System default code page to wide character
//     int wstr_size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
//     std::wstring wstr_tmp(wstr_size, 0);
//     MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wstr_tmp[0], wstr_size);

//     //Wide character to Utf8
//     int str_size = WideCharToMultiByte(CP_UTF8, 0, &wstr_tmp[0], (int)wstr_tmp.size(), NULL, 0, NULL, NULL);
//     std::string str_utf8(str_size, 0);
//     WideCharToMultiByte(CP_UTF8, 0, &wstr_tmp[0], (int)wstr_tmp.size(), &str_utf8[0], str_size, NULL, NULL);

//     return str_utf8;
// }