#include <napi.h>
#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;

DWORD WINAPI Fun(LPVOID lpParamter)
{
    for (int i = 0; i < 10; i++)
    {
        cout << "A Thread Fun Display!" << endl;
        Sleep(200);
    }

    return 0L;
}

Napi::Value Echo(const Napi::CallbackInfo& info) {
    // You need to validate the arguments here.
    Napi::Function cb = info[1].As<Napi::Function>();
    std::string in = info[0].As<Napi::String>();
    HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
    CloseHandle(hThread);
    for (int i = 0; i < 10; i++)
    {
        cout << "Main Thread Display!" << endl;
        Sleep(500);
    }
    return info.Env().Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "Echo"),
              Napi::Function::New(env, Echo));
  return exports;
}

NODE_API_MODULE(addon, Init)
