var addon = require('bindings')('addon');

if (process.platform === 'win32') {
    const iconv = require('iconv-lite');
    const usb = addon.GetUsbDeviceList();
    const printer = usb.list.find(item => item.service === 'usbprint' || item.name === 'USB 打印支持');
    const content = iconv.encode("你好\n bigrocs!\n\n", 'GB18030');
    console.log(1, printer); // 'world'
    const res = addon.Print(printer.path, content);
    console.log(2, res); // 'world'
    const isDisConnected = addon.Disconnect(printer.path);
    console.log(3, isDisConnected); // 'world'
}