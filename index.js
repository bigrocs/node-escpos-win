const win32Escpos = function () {
    if (process.platform === 'win32') {
        var addon = require('bindings')('addon');
        return {
            GetUsbDeviceList() {
                return addon.GetUsbDeviceList();
            },
            Print(path, content) {
                return addon.Print(path, content);
            },
            Disconnect(path) {
                return addon.Disconnect(path);
            },
        }
    }else{
        return {
            GetUsbDeviceList() {
                console.log("Only supports Windows system");
                
            },
            Print(path, content) {
                console.log("Only supports Windows system");
                
            },
            Disconnect(path) {
                console.log("Only supports Windows system");
                
            },
        }
    }
}
module.exports = win32Escpos();