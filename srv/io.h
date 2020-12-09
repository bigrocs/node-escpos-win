#include <napi.h>
#include <string>
#include <windows.h>
#include <map>

using namespace std;

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
struct PrintResult
{
    BOOL success;
    DWORD err;
};

BOOL PrintRawData(string devicePath, char *meg, size_t size, PrintResult *result);

int WriteRawData(const char *str, HANDLE hPort, size_t size);
void InitializeDevicePar(PrintDevice &device);
HANDLE InitPort(PrintDevice &device);
void SetPrintResult(PrintResult *result, BOOL success, DWORD errCode);