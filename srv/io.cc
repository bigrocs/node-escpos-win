#include "io.h"

Object Write(const CallbackInfo &info) {
    Env env = info.Env();
    if (info.Length() < 2)
    {
        TypeError::New(env, "Wrong number of arguments, must be 2")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString())
    {
        TypeError::New(env, "The first argument must be a string").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[1].IsObject())
    {
        TypeError::New(env, "the second argument must be a buffer").ThrowAsJavaScriptException();
        return env.Null();
    }
    String arg0 = info[0].As<String>().Utf8Value();
    ArrayBuffer arg1 = info[1].As<ArrayBuffer>();

    Object obj = Object::New(env); // 初始化函数返回数据对象
    obj.Set(String::New(env, "arg0"), arg0);
    obj.Set(String::New(env, "arg1"), arg1);
    obj.Set(String::New(env, "test"), "Hello Write Object");
    return obj;
}
