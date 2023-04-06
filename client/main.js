const {app, BrowserWindow, ipcMain} = require('electron');
const path = require('path');
const net  = require('net');

let connect_win;
let main_win;

let client;

//const primary_screen     = screen.getPrimaryDisplay();
//const dimensions         = primary_screen.size;

const create_connect_win = () => {
  const connect_win_width  = 0.5 * 1920;
  const conenct_win_height = 0.7 * 1080;
  connect_win = new BrowserWindow({
    webPreferences: {
      preload: path.join(__dirname, 'preload.js')
    },
    width: connect_win_width,
    height: conenct_win_height,
    //autoHideMenuBar: true,
  });

  ipcMain.on('app: connect_to_server', function(event, socket_info) {
    console.log(socket_info);
    connect_to_server(socket_info.ip, socket_info.port);
  });

  connect_win.loadFile('src/components/connect/index.html')
}

app.whenReady().then(() => {
  create_connect_win();

    app.on('activate', () => {
        if (BrowserWindow.getAllWindows().length === 0)
         create_connect_win()
    });

})

function connect_to_server(ip, port)
{
  if (connected_to_server(ip, port) === false) {
    return;
  }

  main_win = new BrowserWindow({
    webPreferences: {
      nodeIntegration: true
    },
    width: dimensions.width,
    height: dimensions.height,
    //autoHideMenuBar: true,
  });

  main_win.loadFile('src/components/connect/test.html');
}

function connected_to_server(ip, port) 
{
  client = new net.Socket();
  client.connect(port, ip);

  client.on('error',function(e) {
    console.log('cant connect to server');
    return false;
  });

  client.on('ready',function() {
    client.write('00000000');
    return true;
  });

  client.on('data', function() {
  });

  return false;
}