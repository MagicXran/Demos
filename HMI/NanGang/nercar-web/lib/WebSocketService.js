let ws
export default {
  getInstance(onMessageHandler, onOpen, userName) {
    console.log('=================================***')
    ws = window.tsWebSocket
    if ('WebSocket' in window) {
      if (!ws) {
        console.log('create new websocket !!!!!! ')
        var webSocketServer
        if (!localStorage.getItem('user')) {
          webSocketServer = '170.0.35.134:8030/' + userName
        } else {
          webSocketServer =
            JSON.parse(localStorage.getItem('user')).webSocketServer +
            '/websocket'
        }
        console.log('localStorage=======：', webSocketServer)
        // .webSocketServer
        ws = new window.WebSocket('ws://' + webSocketServer + '/websocket')
        window.tsWebSocket = ws
      }
      if (onMessageHandler) ws.onmessage = onMessageHandler
      ws.onerror = this.onerror
      ws.onopen = onOpen || this.onopen
      ws.onbeforeunload = this.onbeforeunload
      ws.onclose = this.onclose
      return ws
    } else return null
  },
  onerror(error) {
    console.log(error)
  },

  onclose() {
    ws.close()
    console.log('close')
  },

  onbeforeunload() {
    if (window.tsWebSocket) window.tsWebSocket.close()
  },

  onopen() {
    console.log('ws is open')
    window.tsWebSocket.send('{command: "register", id: "1_web"}')
  },

  closeWebSocket() {
    if (window.tsWebSocket) {
      window.tsWebSocket.close()
      window.tsWebSocket = null
    }
  }
}
