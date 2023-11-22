import { MessageBox } from 'element-ui'
import * as store from '@/store'
import { wsIp } from '../config'
const WSIP = wsIp,
  HeartBeat = 5000,
  Maxima = 5
let CurrentTime = 0
export default class Websocket {
  constructor(url, messageCallback) {
    this.url = !url ? store.state().wsUrl : url
    // this.messageCallback = messageCallback
    this.global_callback = null
  }
  init() {
    let vm = this
    console.log('websocket INIT.....')
    if (typeof WebSocket === 'undefined') {
      MessageBox.alert('您的浏览器不支持WebSocket！', '提示', {
        confirmButtonText: '确定',
        callback: action => {}
      })
    } else {
      this.$ws.onopen = function() {
        console.log('websoket连接成功.....')
      }
      this.$ws.onmessage = function(e) {
        console.log(this.url + '数据:' + JSON.parse(e.data))
        vm.global_callback(JSON.parse(e.data))
      }
      this.$ws.onerror = function() {
        if (this) {
          this.close()
          console.log('websocket ERROR 已关闭.....')
        }
      }
      this.$ws.onclose = function() {
        if (this) {
          this.close()
          console.log('websocket onclose 已关闭.....')
        }
      }
    }
  }
  open() {
    //初始化websocket
    console.log('websocket初始化中.....')
    this.$ws = new WebSocket(this.wsUrl())
    this.init()
  }
  wsUrl() {
    return 'ws://' + WSIP + '/webSocket/' + this.url
  }
  sendSock(agentData, callback) {
    this.open() //初始化
    this.global_callback = callback
    if (this.$ws.readyState === 1) {
      //若是ws开启状态
      //发送消息
    } else if (this.$ws.readyState === 3) {
      CurrentTime++
      if (CurrentTime >= Maxima) {
        console.log('重新连接失败.....')
        this.close()
      } else {
        setTimeout(function() {
          this.sendSock(agentData, callback)
        }, HeartBeat)
      }
    }
  }
  close() {
    console.log('关闭：' + this.url)
    this.$ws.close()
  }
}
