#include "io.h"

Object Write(const CallbackInfo &info) {
    Env env = info.Env();
    Object obj = Object::New(env); // 初始化函数返回数据对象
    if (info.Length() < 2)
    {
        TypeError::New(env, "Wrong number of arguments, must be 2").ThrowAsJavaScriptException();
        return obj;
    }

    if (!info[0].IsString())
    {
        TypeError::New(env, "The first argument must be a string").ThrowAsJavaScriptException();
        return obj;
    }

    if (!info[1].IsObject())
    {
        TypeError::New(env, "the second argument must be a buffer").ThrowAsJavaScriptException();
        return obj;
    }
    String devicePath = info[0].As<String>();
    Buffer<uint16_t> data = info[1].As<Buffer<uint16_t>>();

    obj.Set(String::New(env, "devicePath"), devicePath.Utf8Value().c_str());
    obj.Set(String::New(env, "data"), data);
    obj.Set(String::New(env, "data.length"), data.Length());
    obj.Set(String::New(env, "test"), "Hello Write Object");

    WriteData(devicePath.Utf8Value().c_str(), data, &obj);
    return obj;
}

BOOL WriteData(string devicePath, char *data, Object *obj)
{
    obj.Set(String::New(env, "WriteData"), "WriteData");
    return true;
}