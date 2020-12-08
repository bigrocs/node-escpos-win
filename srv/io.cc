#include "io.h"

Object Write(const CallbackInfo &info)
{
    Env env = info.Env();
    Object obj = Object::New(env); // 初始化函数返回数据对象
    obj.Set(String::New(env, "test"), "Hello Write Object");
    return obj;
}
