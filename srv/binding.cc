#include <napi.h>
#include <regex>
#include "usb.h"
#include "io.h"

using namespace std;

Napi::Object DeviceList(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env); // 初始化函数返回数据对象
  if (info.Length() < 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments, must be 1").ThrowAsJavaScriptException();
    return obj;
  }

  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "The first argument must be a string").ThrowAsJavaScriptException();
    return obj;
  }

  // 构建参数
  string deviceType = info[0].As<Napi::String>().Utf8Value();

  // 读取usb设备列表
  list<DeviceInfo>::iterator itor;
  list<DeviceInfo> deviceList;
  ResultInfo resultInfo;
  GetDeviceList(deviceList, deviceType, resultInfo);
  // 分配获取数据
  Napi::Array list = Napi::Array::New(env);
  itor = deviceList.begin();
  int count = 0;
  while (itor != deviceList.end())
  {
    Napi::Object device = Napi::Object::New(env);
    device.Set(Napi::String::New(env, "name"), itor->name);
    device.Set(Napi::String::New(env, "service"), itor->service);
    device.Set(Napi::String::New(env, "manufacturer"), itor->manufacturer);
    device.Set(Napi::String::New(env, "location"), itor->location);
    device.Set(Napi::String::New(env, "path"), itor->path);
    list.Set(Napi::Number::New(env, count), device);
    itor++;
    count++;
  }
  // 数据构建完成构建返回数据结构
  obj.Set(Napi::String::New(env, "list"), list);
  obj.Set(Napi::String::New(env, "err"), resultInfo.err);
  obj.Set(Napi::String::New(env, "number"), deviceList.size());
  obj.Set(Napi::String::New(env, "success"), resultInfo.success);
  return obj;
}

Napi::Object Print(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env); // 初始化函数返回数据对象
  if (info.Length() < 2)
  {
    Napi::TypeError::New(env, "Wrong number of arguments, must be 2").ThrowAsJavaScriptException();
    return obj;
  }

  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "The first argument must be a string").ThrowAsJavaScriptException();
    return obj;
  }

  if (!info[1].IsObject())
  {
    Napi::TypeError::New(env, "the second argument must be a buffer").ThrowAsJavaScriptException();
    return obj;
  }
  // 构建参数
  string devicePath = info[0].As<Napi::String>().Utf8Value();
  Napi::Buffer<char> data = info[1].As<Napi::Buffer<char>>();
  size_t bufferLength = data.Length();
  char *bufData = data.Data();
  PrintResult *printResult = (PrintResult *)malloc(sizeof(PrintResult));
  regex reg1("^LPT\\d+");
	smatch r2;
  if (regex_match(devicePath, r2, reg1))
	{
    PrintRawData(devicePath, bufData, bufferLength, printResult);
  }
	else {
		PrintRawData(devicePath, bufData, bufferLength, printResult);
	}
  obj.Set(Napi::String::New(env, "success"), printResult->success);
  obj.Set(Napi::String::New(env, "err"), printResult->err);
  // 释放内存
  free(printResult);
  return obj;
}

Napi::Boolean Disconnect(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (info.Length() < 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments, must be 1").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }

  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "The first argument must be a string").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }

  // 构建参数
  string devicePath = info[0].As<Napi::String>().Utf8Value();
  bool disconnectResult = DisConnectDevice(devicePath);
  return Napi::Boolean::New(env, disconnectResult);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "GetDeviceList"),
              Napi::Function::New(env, DeviceList));
  exports.Set(Napi::String::New(env, "Print"),
              Napi::Function::New(env, Print));
  exports.Set(Napi::String::New(env, "Disconnect"),
              Napi::Function::New(env, Disconnect));
  return exports;
}

NODE_API_MODULE(addon, Init)
