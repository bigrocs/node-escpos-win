#include <napi.h>

#include <chrono>
#include <thread>
using namespace std;

class EchoWorker : public Napi::AsyncWorker {
    public:
        EchoWorker(Napi::Function& callback, string& echo)
        : AsyncWorker(callback), echo(echo) {}

        ~EchoWorker() {}
    // This code will be executed on the worker thread
    void Execute() override {
        echo = echo+"000";
        // Need to simulate cpu heavy task
        this_thread::sleep_for(chrono::seconds(1));
    }

    void OnOK() override {
        // Napi::HandleScope scope(Env());
        Callback().Call({Env().Null(), Napi::String::New(Env(), echo)});
    }

    private:
        string echo;
};

Napi::Value Echo(const Napi::CallbackInfo& info) {
    // You need to validate the arguments here.
    Napi::Function cb = info[1].As<Napi::Function>();
    std::string in = info[0].As<Napi::String>();
    EchoWorker* wk = new EchoWorker(cb, in);
    wk->Queue();
    return info.Env().Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "Echo"),
              Napi::Function::New(env, Echo));
  return exports;
}

NODE_API_MODULE(addon, Init)
