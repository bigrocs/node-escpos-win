const win32Escpos = function () {
    if (process.platform === 'win32') {
        var addon = require('bindings')('addon');
        return {
            GetDeviceList(type) {
                return addon.GetDeviceList(type);
            },
            Print(path, content) {
                return addon.Print(path, content);
            },
            asyncPrint(path, content) {
                return new Promise((resolve, reject) => {
                    try {
                        const cp = require('child_process')  //控制子进程的调度
                        const child_process = cp.fork('./print.js');  //创建子进程，参数是子进程入口js
                        child_process.send({ path, content }); //给子进程发送消息
                        child_process.on('message', (res) => {
                            resolve(res)
                        })
                        child_process.disconnect()
                    } catch (error) {
                        reject(error)
                    }
                })
            },
            Disconnect(path) {
                return addon.Disconnect(path);
            },
        }
    }else{
        const err = {
            list : [                             
            ],
            number : 0, //设备数量
            error:'This operating system is not supported by this application' // 错误提示,
        }
        return {
            GetDeviceList(type) {
                return err;
            },
            Print(path, content) {
                return err;
            }, 
            asyncPrint(path, content) {
                return err;
            },
            Disconnect(path) {
                return err;
            },
        }
    }
}
module.exports = win32Escpos();