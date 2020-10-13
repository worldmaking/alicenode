const WebSocket = require('ws')

const wss = new WebSocket.Server({ port:9090 })

wss.on('connection', ws => {
  ws.on('message', message => {
    console.log(`Received message => ${message}`)
  })
  ws.send('ho!')
})