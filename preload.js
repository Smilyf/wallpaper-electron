const { contextBridge, ipcRenderer } = require('electron')

contextBridge.exposeInMainWorld('article', {
    announce: (content) => ipcRenderer.send('announce_article', content),
    on: () =>ipcRenderer.on("announce_article_reply", alert(message))
   

})
