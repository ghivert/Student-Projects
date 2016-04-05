'use strict'

const electron = require('electron')
const client   = require('./lib/client/client.js')
const ipcMain  = electron.ipcMain

electron.dialog.showErrorBox = function (title, content) {}

const app           = electron.app            // Module to control application life.
const BrowserWindow = electron.BrowserWindow  // Module to create native browser window.

global.mainWindow = null                         // Global Reference for GC
global.ready = { 'ready': false }

const quit_debug = true
var win

// Creating GUI.
function createWindow() {
  global.mainWindow = new BrowserWindow({
    width: 900,
    height: 800,
    titleBarStyle: "hidden"
  })
  global.mainWindow.loadURL('file://' + __dirname + '/index.html')
  win = new BrowserWindow({
    width: 900,
    height: 800
  })
  win.loadURL('file://' + __dirname + '/login.html')

  global.mainWindow.on('closed', function() {
    global.mainWindow = null
  })
}

app.on('ready', function() {
  // Connecting to the server.
  createWindow()
  try {
    ipcMain.on('name', function() {
      win.close()
      client.connect()
    })
  } catch (err) {
    console.log(err)
    app.quit()
  }

  process.on('SIGINT', function() {
    try {
      client.unconnect()
    } catch (err) {
      console.log(err)
    }
    app.quit()
  })
})

app.on('window-all-closed', function() {
  if (process.platform !== 'darwin') {
    try {
      client.unconnect()
    } catch (err) {
      console.log(err)
    }
    app.quit()
  }
  if (quit_debug) {
    try {
      client.unconnect()
    } catch (err) {
      console.log(err)
    }
    app.quit()
  }
})
