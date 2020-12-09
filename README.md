---
```
npm install node-escpos-win --save-optional
```
---
#escpos native plugin for electron
#目前只支持 windows系统

```
// usb printer
```
    const iconv = require('iconv-lite');
    const escpos =require('node-escpos-win');
    const usb = escpos.GetUsbDeviceList();
    const printer = usb.list.find(item => item.service === 'usbprint' || item.name === 'USB 打印支持');
    const content = iconv.encode("你好啊\n bigrocs!\n\n\n\n\n\n\n\n\n", 'GB18030');
    console.log(1, printer); // 'world'
    const res = escpos.Print(printer.path, content);
    console.log(2, res); // 'world'
    const isDisConnected = escpos.Disconnect(printer.path);
    console.log(3, isDisConnected); // 'world'

```
// lpt printer
    // 暂不支持
    const iconv = require('iconv-lite');
    const escpos =require('node-escpos-win');
    const usb = escpos.GetLptDeviceList();
    const printer = usb.list.find(item => item.service === 'usbprint' || item.name === 'USB 打印支持');
    const content = iconv.encode("你好啊\n bigrocs!\n\n\n\n\n\n\n\n\n", 'GB18030');
    console.log(1, printer); // 'world'
    const res = escpos.Print(printer.path, content);
    console.log(2, res); // 'world'
    const isDisConnected = escpos.Disconnect(printer.path);
    console.log(3, isDisConnected); // 'world'
```
