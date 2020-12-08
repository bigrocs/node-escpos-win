var addon = require('bindings')('addon');

const iconv = require('iconv-lite');
const list = addon.GetUsbDeviceList();
const printer = usblist.find(item => item.service === 'usbprint' || item.name === 'USB 打印支持');
console.log(list, addon.Write(), printer); // 'world'



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