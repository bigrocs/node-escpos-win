var addon = require('../index.js');


    if (process.platform === 'win32') {
        const iconv = require('iconv-lite');
        const usb = addon.GetDeviceList("USB");
        // const com = addon.GetDeviceList("COM");
        // const lpt = addon.GetDeviceList("LPT");
        // console.log(0,lpt); // 'world'
        const printer = usb.list.find(item => item.service === 'usbprint' || item.name === 'USB 打印支持');
        const content = iconv.encode("bigrocs!\n\n\n", 'GB18030');
        // console.log(1, printer); // 'world'
        // const res = addon.Print(lpt.list[0].path, content);
        console.log(printer);
        
        addon.Print(printer.path, content)
        // .then(r=>{
        //     console.log(r);
        // }).catch(error => {
        //     reject(error)
        // })
        // console.log(2, res); // 'world'
        // const isDisConnected = addon.Disconnect(printer.path);
        // console.log(3, isDisConnected); // 'world'
    }
