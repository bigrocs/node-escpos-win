#include <napi.h>
#include "usb.h"
// #include "io.h"

using namespace Napi;

String Hello(const CallbackInfo& info) {
  Env env = info.Env();
  return String::New(env, "Hello World");
}

Object UsbDeviceList(const CallbackInfo &info)
{
  Env env = info.Env();
  Object obj = Object::New(env); // 初始化函数返回数据对象

  list<DeviceInfo> deviceList;
  ResultInfo resultInfo;
  GetUsbDeviceList(deviceList, resultInfo);

  Array list = Array::New(env);
  itor = deviceList.begin();
  obj.Set(String::New(env, "123"), itor.name);
  // while (itor != ilist.end())
  // {
  //   Object device = Object::New(env);
  //   device.Set(String::New(env, "name"), itor.name.c_str());
  //   device.Set(String::New(env, "service"), itor.service.c_str());
  //   device.Set(String::New(env, "manufacturer"), itor.manufacturer.c_str());
  //   device.Set(String::New(env, "location"), itor.location.c_str());
  //   device.Set(String::New(env, "path"), itor.path.c_str());
  //   list.Set(Number::New(env, itor), device);
  // }
  obj.Set(String::New(env, "list"), list);
  obj.Set(String::New(env, "err"), resultInfo.err);
  obj.Set(String::New(env, "number"), deviceList.size());
  obj.Set(String::New(env, "success"), resultInfo.success);
  return obj;
}

Object Init(Env env, Object exports) {
  exports.Set(String::New(env, "hello"),
              Function::New(env, Hello));
  exports.Set(String::New(env, "GetUsbDeviceList"),
              Function::New(env, UsbDeviceList));
  // exports.Set(String::New(env, "Write"),
  //             Function::New(env, Write));
  return exports;
}

NODE_API_MODULE(addon, Init)
