var addon = require('bindings')('addon');

const win32Escpos = function () {
    if (process.platform === 'win32') {
        return {
            GetUsbDeviceList() {
                return addon.GetUsbDeviceList();
            },
            Print(path, content) {
                return addon.Print(path, content);
            },
            Disconnect() {
                return addon.Disconnect(path);
            },
        }
    }
}
module.exports = win32Escpos();