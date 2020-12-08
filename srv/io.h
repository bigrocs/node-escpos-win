#include <napi.h>
#include <windows.h>

using namespace Napi;

class PrintDevice
{
public:
    string Port;       //串口端口号
    int BawdRate;      //波特率
    int DataBits;      //数据位
    char Parity;       //校验位
    int ReceiveBuffer; //缓冲区
    int StopBits;      //停止位
    //HANDLE DHandler;
};
struct Result
{
    BOOL success;
    DWORD err;
};

Object Write(const CallbackInfo &info);
BOOL WriteData(string devicePath, char *meg, size_t size, Result *result);