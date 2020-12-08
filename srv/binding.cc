#include <napi.h>
#include <list>
#include "usb.h"
// #include "io.h"

using namespace std;

Napi::String Hello(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  return Napi::String::New(env, "Hello World");
}

Napi::Object UsbDeviceList(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env); // 初始化函数返回数据对象

  list<DeviceInfo> deviceList;
  ResultInfo resultInfo;
  GetUsbDeviceList(deviceList, resultInfo);

  Napi::Array list = Napi::Array::New(env);
  list<usb::DeviceInfo>::iterator itor = deviceList.begin();
  // while (itor != deviceList.end())
  // {

  //   obj.Set(String::New(env, "123"), itor->name);

  //   // Object device = Object::New(env);
  //   // device.Set(String::New(env, "name"), itor.name.c_str());
  //   // device.Set(String::New(env, "service"), itor.service.c_str());
  //   // device.Set(String::New(env, "manufacturer"), itor.manufacturer.c_str());
  //   // device.Set(String::New(env, "location"), itor.location.c_str());
  //   // device.Set(String::New(env, "path"), itor.path.c_str());
  //   // list.Set(Number::New(env, itor), device);
  // }
  obj.Set(Napi::String::New(env, "list"), list);
  obj.Set(Napi::String::New(env, "err"), resultInfo.err);
  obj.Set(Napi::String::New(env, "number"), deviceList.size());
  obj.Set(Napi::String::New(env, "success"), resultInfo.success);
  return obj;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "hello"),
              Napi::Function::New(env, Hello));
  exports.Set(Napi::String::New(env, "GetUsbDeviceList"),
              Napi::Function::New(env, UsbDeviceList));
  // exports.Set(Napi::String::New(env, "Write"),
  //             Napi::Function::New(env, Write));
  return exports;
}

NODE_API_MODULE(addon, Init)
