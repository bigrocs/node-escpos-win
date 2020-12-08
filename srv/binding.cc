#include <napi.h>
#include "usb.h"
// #include "io.h"

using namespace Napi;

String Hello(const CallbackInfo& info) {
  Env env = info.Env();
  return String::New(env, "Hello World");
}


Object Init(Env env, Object exports) {
  exports.Set(String::New(env, "hello"),
              Function::New(env, Hello));
  exports.Set(String::New(env, "GetUsbDeviceList"),
              Function::New(env, GetUsbDeviceList));
  // exports.Set(String::New(env, "Write"),
  //             Function::New(env, Write));
  return exports;
}

NODE_API_MODULE(addon, Init)
