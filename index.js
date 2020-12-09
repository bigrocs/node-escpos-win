var addon = require('bindings')('addon');

const win32Escpos = function () {
    if (process.platform === 'win32') {
        return {
            GetUsbDeviceList() {
                return addon.GetUsbDeviceList();
            },
            Print() {
                return addon.Print();
            },
            Disconnect() {
                return addon.Disconnect();
            },
        }
    }
}
module.exports = win32Escpos();