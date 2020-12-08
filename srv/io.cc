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
    ArrayBuffer data = info[1].As<ArrayBuffer>();
    // char *deviceBf = (char *)malloc(devicePath->Utf8Length() + 1);

    // obj.Set(String::New(env, "deviceBf"), deviceBf);
    obj.Set(String::New(env, "devicePath"), devicePath.Utf8Value().c_str());
    obj.Set(String::New(env, "data"), data);
    obj.Set(String::New(env, "test"), "Hello Write Object");

    // DWORD dwWrite;
    HANDLE hLPT = CreateFile(devicePath.Utf8Value().c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL,
                             OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

    // if (hLPT == INVALID_HANDLE_VALUE)
    // {
    //     // SetPrintResult(result, FALSE, GetLastError());
    //     return obj;
    // }
    // BOOL b = WriteFile(
    //     hLPT,
    //     data,
    //     NULL,
    //     &dwWrite,
    //     NULL);
    // if (!b)
    // {
    //     // SetPrintResult(result, FALSE, GetLastError());
    //     return obj;
    // }
    // FlushFileBuffers(hLPT);
    // CloseHandle(hLPT);
    // SetPrintResult(result, TRUE, NULL);

    return obj;
}
