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
  obj.Set(String::New(env, "error"), NULL);
  obj.Set(String::New(env, "list"), "list");
  obj.Set(String::New(env, "number"), 0);
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
