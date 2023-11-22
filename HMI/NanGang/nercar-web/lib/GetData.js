import { post } from '@/lib/Util'
import { HMI } from '@/lib/api'

var id = 0

export function stopGetData() {
  console.log('stop get data invoke ...')
  clearInterval(id)
}

/**
 * getHmiData - description
 *
 * @param  {string} page       所属页面唯一标识符
 * @param  {Function} resultFunc 成功时的回调
 * @param  {Function} errorFunc  错误时的回调
 * @param  {number} f          查询频率，默认是500ms
 * @return {type}            description
 */
export async function getHmiData(page, resultFunc, errorFunc, f) {
  clearInterval(id)
  let tags = getVariablesByPage(page)
  let requestData = {
    action: 'get_tags',
    operator: 'abc',
    terminal: 'FM_01',
    body: tags.tags ? tags.tags : tags
  }

  var resultData = {}

  let nub = 0

  id = setInterval(async () => {
    const result = await post(HMI, requestData)
    // const { result, err } = await post('/webservice/getHmiData.hmi', tags)
    // console.log('getHmiData', result)
    // 异常处理
    if (result.code != 200) errorFunc(result.extraMsg)
    else {
      nub = nub + 1
      // /* if (nub === 1000) {
      //   location.reload()
      // } */
      // 更新查询到的数据到tags
      fixResult(requestData, result, page)
      // 把array转成object
      getResultValue(requestData, resultData)
      // requestData 中删除请求不需要的value 删除了这个就恢复了
      /*requestData['body'].map(item => {
        delete item.value
      })*/
      resultFunc(resultData)
      // resultFunc(tags)
    }
    /*setTimeout(async () => {

    }, 500)*/
  }, f || 1000)
}

/**
 * getHmiDataByEvent - 通过事件获取中间件变量
 *
 * @param  {type} data {tagName1: value1, tagName2:value2}
 * @return {type}      description
 */
export async function getHmiDataByEvent(data) {
  if (!data || data.length < 1) return
  // 获取当前页面的tags变量和msgs变量
  let requestData = {
    action: 'get_tags',
    operator: 'abc',
    terminal: 'FM_01',
    body: data
  }
  const result = await post(HMI, requestData)
  console.log('get hmiData by event', result)
  return result
}

/**
 * getVariablesByPage - 获取当前页面的查询命令 {tags:[], msgs:[]}
 *
 * @param  {type} page description
 * @return {type}      description
 */
function getVariablesByPage(page) {
  return JSON.parse(localStorage.getItem('hmi/' + page) || '{}')
}

/**
 * getTagsByPage - 获取当前页面的标签查询命令
 *
 * @param  {type} page description
 * @return {type}      description
 */
function getTagsByPage(page) {
  return JSON.parse(localStorage.getItem('hmi/' + page) || '{}').tags || []
}

/**
 * getMsgsByPage - 获取当前页面的消息查询命令
 *
 * @param  {type} page description
 * @return {type}      description
 */
function getMsgsByPage(page) {
  return JSON.parse(localStorage.getItem('hmi/' + page) || '{}').msgs || []
}

/**
 * getMsgByPage - 获取当前页面的某条消息
 *
 * @param  {string} page 当前页面
 * @param  {string} msgId 消息Id
 * @return {type}      description
 */
function getMsgByPage(page, msgId) {
  const msgs = getMsgsByPage(page)
  if (!msgs || msgs.length < 1) return null
  return msgs.filter(msg => {
    return msg.id == msgId
  })
}

/**
 * fixResult - 变量结果
 *
 * @param  {object} tags   请求的变量集合{tags: [], msgs: []}
 * @param  {object} result  返回的数据集合{tagList: [], msgList: []}
 * @param  {string} page   所属页面唯一标识符
 * @return {null}        description
 */
function fixResult(tags, result, page) {
  // let tagsTmp = result.tagList
  // let msgsTmp = result.msgList
  // updateList(tags, tagsTmp, 'tags')
  // updateList(tags, msgsTmp, 'msgs')
  let tagsTmp = result.results || result.tagList
  let msgsTmp = result.msgList
  updateList(tags, tagsTmp, 'tags')
  if (msgsTmp) updateList(tags, msgsTmp, 'msgs')
}

/**
 * updateList - 更新变量名
 *
 * @param  {object} olds {tags:[], msgs:[]}
 * @param  {array} news [{name: '', ts: 0, value: 1000, dataList}]
 * @param  {string} type "tags" || "msgs"
 * @return {null}      description
 */
function updateList(olds, news, type) {
  // if (!news || news.length < 1) return
  // news.map(o => {
  //   let exist = olds[type].some((t, index) => {
  //     if ((t.id || t.name) == (o.id || o.name)) {
  //       // 更新变量
  //       olds[type].splice(index, 1, o)
  //       // 跳出循环
  //       return true
  //     }
  //   })
  //   if (!exist) olds[type].push(o)
  // })
  if (!news || news.length < 1) return
  news.map(o => {
    let exist = olds['body'].some((t, index) => {
      if ((t.id || t.tagName) == (o.id || o.tagName)) {
        // 更新变量
        olds['body'].splice(index, 1, o)
        // 跳出循环
        return true
      }
    })
    // delete o.value //删除请求不需要的value值
    if (!exist) olds['body'].push(o)
  })
}

/**
 * getResultValue - 把array转成object
 *
 * @param  {type} tagsInfo description
 * @param  {type} tagsData description
 * @return {type}          description
 */
export function getResultValue(tagsInfo, tagsData) {
  // if (tagsInfo.tags) convertArrayToObject(tagsInfo.tags, tagsData)
  // if (tagsInfo.msgs) convertArrayToObject(tagsInfo.msgs, tagsData)
  if (tagsInfo.body) convertArrayToObject(tagsInfo.body, tagsData)
  if (tagsInfo.msgs) convertArrayToObject(tagsInfo.msgs, tagsData)
}

function convertArrayToObject(array, object) {
  // array.some(o => {
  //   console.log('detail info')
  //   if (o.dataList) object[o.name || o.id] = o.dataList
  //   else object[o.name || o.id] = o.value
  // })
  array.some(o => {
    // console.log('detail info')
    if (o.dataList) object[o.tagName || o.id] = o.dataList
    else object[o.tagName || o.id] = o.value
  })
}

/**
 * sendMessage - 发送消息到服务器
 *
 * @param  {type} page 当前页面唯一标识
 * @param  {type} data [{id: '', data: [{}]}]
 * @return {type}      description
 */
export async function sendMessage(page, data) {
  // 获取当前页面的tags变量和msgs变量
  if (!data || data.length < 1) return
  var reqData = []
  data.forEach(d1 => {
    // 查找到消息体
    let msgs = getMsgByPage(page, d1.id)
    if (msgs && msgs.length > 0) {
      var msg = msgs[0]
      msg.data = d1.data //更新 msg的请求数据
      reqData.push(msg)
    }
  })
  const result = await post('/webservice/sendMessage.hmi', { msgList: reqData })
  console.log('send message result', result)
}

/**
 * sendMessage - 发送消息到服务器
 *
 * @param  {type} page 当前页面唯一标识
 * @param  {type} data {tagName1: value1, tagName2:value2}
 * @return {type}      description
 */
export async function sendTag(data) {
  if (!data || data.length < 1) return
  // 获取当前页面的tags变量和msgs变量
  let requestData = {
    action: 'set_tags',
    operator: 'abc',
    terminal: 'FM_01',
    body: data
  }
  const result = await post(HMI, requestData)
  console.log('send tag result', result)
  return result
}

/**
 *
 * @param {*} data: 请求的参数
 * @param {*} msgId: 消息id
 * @param {*} sendTo: 后台标示
 * @param {*} hostUrl: pcdp地址
 * @param {*} timeout: 超时时间
 * @param {*} waitReply: 是否等待返回
 * @returns
 */
//返回数据待封装
export async function sendMsg(
  data,
  msgId,
  sendTo,
  hostUrl,
  timeout,
  waitReply
) {
  // 获取当前页面的tags变量和msgs变量
  if (!data || data.length < 1) return
  let requestData = {
    action: 'send_msg',
    operator: 'abc',
    terminal: 'FM_01',
    body: {
      msgId: msgId,
      sendTo: sendTo,
      waitReply: waitReply ? waitReply : true,
      timeout: timeout ? timeout : 5,
      params: data
    }
  }

  // hostUrl = hostUrl ? PCDPURL[hostUrl] : PCDPURL.defaultURL
  // var url = '/pcdp/' + hostUrl + '/hmiData.form'
  const result = await post(HMI, requestData)
  // console.log('send message result', result)
  if (result.code != 200) {
    // window.$nuxt.$store.commit('SET_ERROR_INFO', result)
    // 异常处理
    window.$nuxt.$notify.error({
      title: '系统信息',
      message:
        process.env.NODE_ENV === 'production'
          ? '通讯出错了，请稍后再试'
          : result.errInfo,
      showClose: true
    })
  }
  return result
}
