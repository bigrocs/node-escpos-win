

process.on('message', ({ path, content, fu }) => { //process是一个全局变量
    var addon = require('bindings')('addon');
    const res = addon.Print(path, content);
    process.send(res);  //子进程给主进程发送消息
}) //子进程接受消息