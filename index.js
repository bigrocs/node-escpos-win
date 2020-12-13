const win32Escpos = function () {
    if (process.platform === 'win32') {
        var addon = require('bindings')('addon');
        return {
            GeteviceList(type) {
                return addon.GeteviceList(type);
            },
            Print(path, content) {
                return addon.Print(path, content);
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
            GeteviceList(type) {
                return err;
            },
            Print(path, content) {
                return err;
            },
            Disconnect(path) {
                return err;
            },
        }
    }
}
module.exports = win32Escpos();