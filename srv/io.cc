#include "io.h"

String Write(const CallbackInfo &info)
{
    Env env = info.Env();
    return String::New(env, "Hello Write1");
}
