#include <napi.h>
#include <windows.h>

using namespace Napi;

class PrintDevice
{
public:
    std::string Port;         //串口端口号
    std::int BawdRate;      //波特率
    std::int DataBits;      //数据位
    std::char Parity;       //校验位
    std::int ReceiveBuffer; //缓冲区
    std::int StopBits;      //停止位
    //HANDLE DHandler;
};
struct Result
{
    std::BOOL success;
    std::DWORD err;
};

Object Write(const CallbackInfo &info);
BOOL WriteData(string devicePath, char *meg, size_t size, Result *result);