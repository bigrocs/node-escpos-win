var addon = require('bindings')('addon');

console.log(addon.Write()); // 'world'
const win32Escpos = function () {
    if (process.platform === 'win32') {
        console.log(123);
        
    }
    return {
        GetUsbDeviceList() {
            return addon.GetUsbDeviceList();
        },
    }
}
module.exports = win32Escpos();