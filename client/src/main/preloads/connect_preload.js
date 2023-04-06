const { contextBridge, ipcRenderer } = require('electron')

contextBridge.exposeInMainWorld('electronAPI', {
    connect_to_server: (info) => ipcRenderer.send('app: connect_to_server', info)
})