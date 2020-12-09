var addon = require('bindings')('addon');

const iconv = require('iconv-lite');
const usb = addon.GetUsbDeviceList();
const printer = usb.list.find(item => item.service === 'usbprint' || item.name === 'USB 打印支持');
const content = iconv.encode("你好啊\n halo cpp!\n\n\n\n\n\n\n\n\n", 'GB18030');
console.log(printer); // 'world'
const res = addon.Print(printer.path, content);
console.log( res); // 'world'

// console.log(addon.Print());



const win32Escpos = function () {
    if (process.platform === 'win32') {
        console.log(123);

    }
    return {
        GetUsbDeviceList() {
            // return addon.GetUsbDeviceList();
        },
    }
}
module.exports = win32Escpos();