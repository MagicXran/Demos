import cryptoJs from 'crypto-js'
import MD5 from 'md5'
import keys from '@/lib/Keys'
import { objEqual } from '@/lib/tools'
export function error(title, content, showClose) {
  // console.log(content, window.$nuxt.$t(content))
  window.$nuxt.$notify.error({
    title: window.$nuxt.$t(title) || title,
    message: window.$nuxt.$t(content),
    showClose: false
  })
}

export function getConfig(key) {
  return window ? window.$nuxt.$t(key) || key : ''
}

export function success(title, content, showClose) {
  window.$nuxt.$notify.success({
    title: window.$nuxt.$t(title) || title,
    message: window.$nuxt.$t(content) || content,
    showClose: !showClose
  })
}
/**
 * 将用户数据存放在以用户_id_开头的item下面
 * @param { string } key key值
 * @param { any } data value值
 */
export function persist(key, data) {
  data = typeof data === 'object' ? JSON.stringify(data) : data
  const userId = JSON.parse(localStorage.getItem('user') || '{"userId": 0}')
    .userId
  localStorage.setItem('_' + userId + '_' + key, data)
}

/**
 * 获取用户item下的数据
 * @param { string } key 需要获取的key值
 */
export function getValue(key) {
  const userId = JSON.parse(localStorage.getItem('user') || '{"userId": 0}')
    .userId
  return localStorage.getItem('_' + userId + '_' + key)
}

/**
 * 获取登录后的用户信息
 */
export function getStorageUser() {
  return !process.server ? JSON.parse(localStorage.getItem('user')) : null
}

/**
 * 获取同步密钥
 */
export function getSymmkey() {
  return !process.server ? localStorage.getItem(keys.SYMMKEY) : null
}

/**
 * 保存同步密钥
 */
export function setSymmkey(symmkey) {
  localStorage.setItem(keys.SYMMKEY, symmkey)
}

/**
 * RSA 加密
 * @param { any } data 待加密的对象
 */
export function rsaEncrypt(data) {
  const { JSEncrypt } = require('jsencrypt')
  const publicKey = window.$nuxt.$store.state.publicKey
  if (typeof data === 'object') data = JSON.stringify(data)
  const encrypt = new JSEncrypt()
  encrypt.setPublicKey(publicKey)
  return encrypt.encrypt(data)
}

/**
 * aes加密，
 * return { content: '', index: ''}
 */
export function aesEncrypt(data) {
  const symmkey = getSymmkey()
  const user = getStorageUser()

  if (!user || !symmkey) {
    error('home.systemInfo', 'home.loginTimeExpired')
    window.$nuxt.$router.push({
      path: '/login',
      query: { url: window.$nuxt.$router.currentRoute.path }
    })
    return
  }
  const userId = user.userId
  const device = process.env.device
  if (typeof data === 'object') data = JSON.stringify(data)
  data = encodeURIComponent(data)
  const key = cryptoJs.enc.Utf8.parse(symmkey)
  const iv = cryptoJs.enc.Utf8.parse('0102030405060708')
  const srcs = cryptoJs.enc.Utf8.parse(data)
  const encrypted = cryptoJs.AES.encrypt(srcs, key, {
    iv: iv,
    mode: cryptoJs.mode.CBC,
    padding: cryptoJs.pad.Pkcs7
  })
  return {
    content: encrypted.toString(),
    index: userId + '_' + device
  }
}

/**
 * aes 解密
 */
export function aesDecrypt(data) {
  const symmkey = getSymmkey()
  console.log('symmkey is ,', symmkey)
  const key = cryptoJs.enc.Utf8.parse(symmkey)
  const iv = cryptoJs.enc.Utf8.parse('0102030405060708')
  try {
    const decrypted = cryptoJs.AES.decrypt(data, key, {
      iv: iv,
      mode: cryptoJs.mode.CBC,
      padding: cryptoJs.pad.Pkcs7
    })
    if (decrypted) {
      return decrypted.toString(cryptoJs.enc.Utf8)
    }
  } catch (e) {
    loginByToken(localStorage.getItem('token'))
  }
}

export async function loginByToken(token) {
  // console.log('login by token is invoke, ', window.$nuxt.$t('home.systemInfo'))
  if (!token) {
    error('home.systemInfo', 'home.loginTimeExpired')
    window.$nuxt.$router.push('/login')
  }
  if (typeof token === 'string') token = JSON.parse(token)
  let result = await post(LOGIN_URL, token, 'no')
  window.$nuxt.$store.commit('setUser', result)
  return result
}

/**
 * 用户登录
 * @param { string } name 用户名
 * @param { string } password 密码
 */
export async function login(name, password) {
  console.log('login ============')
  const store = window.$nuxt.$store
  const wordArray = cryptoJs.lib.WordArray.random(8)
  const symmkey = cryptoJs.enc.Hex.stringify(wordArray)
  const token = {
    client: process.env.device,
    data: rsaEncrypt({ name, password, symmkey })
  }
  const result = await loginByToken(token)
  if (result.status === 'success') {
    result.photo = '/file/' + result.name + '/photo/user.file'
    result.password = MD5(password)
    store.commit('setUser', result)
    localStorage.setItem('user', JSON.stringify(result))
    localStorage.setItem('token', JSON.stringify(token))
    setSymmkey(symmkey)
  }
  console.log(result)
  return result
}

/**
 * post 方式获取服务器端信息,不加密
 * @param { string } url 请求的url地址
 * @param { object } data value值
 * @param { isNotify } string 'no'不自动提示请求结果，默认在屏幕右上角显示服务器请求结果
 */
export async function post(url, data, isNotify) {
  // console.log('Utils.js')
  const tmp = await window.$nuxt.$postService(
    url,
    data || {},
    isNotify || 'yes'
  )
  return tmp
}

/**
 * post 方式 加密获取服务器端信息
 * @param { string } url 请求的url地址
 * @param { object } data value值
 * @param { isNotify } string 'no'不自动提示请求结果，默认在屏幕右上角显示服务器请求结果
 */
export async function $post(url, data, isNotify) {
  if (process.server) return
  console.log('$post url======', url)
  const symmkey = getSymmkey()
  const user = getStorageUser()

  if (!user || !symmkey) {
    window.$nuxt.$router.push({
      path: '/login',
      query: { url: window.$nuxt.$router.currentRoute.path }
    })
    return
  }

  data = aesEncrypt(data || {})
  const tmp = await window.$nuxt.$postService(url, data, isNotify || 'yes')
  console.debug('tmp, ', tmp, url)
  if (tmp.status === 'sysError' && tmp.code != '500') {
    window.$nuxt.$router.push({
      path: '/login',
      query: { url: window.$nuxt.$router.currentRoute.path }
    })
    return
  }
  if (!tmp) return
  return aesDecrypt(tmp.data)
}

/**
 * get 方式 获取服务器端信息,不加密
 * @param { string } url 请求的url地址
 * @param { object } data value值
 * @param { isNotify } string 'no'不自动提示请求结果，默认在屏幕右上角显示服务器请求结果
 */
export async function get(url, data, isNotify) {
  return await window.$nuxt.$getService(url, data || {}, isNotify || 'yes')
}

/**
 * get 方式 加密获取服务器端信息
 * @param { string } url 请求的url地址
 * @param { object } data value值
 * @param { isNotify } string 'no'不自动提示请求结果，默认在屏幕右上角显示服务器请求结果
 */
export async function $get(url, data, isNotify) {
  data = aesEncrypt(data || {})
  const tmp = await window.$nuxt.$postService(url, data, isNotify || 'yes')
  return aesDecrypt(tmp)
}

/**
 * [fixMenus 删选出父类叶子节点，然后去递归子节点，组织数据成{children:[{}]} 格式]
 * @param  {[type]} menus            [description]
 * @param  {[type]} fromParentIsNull ['yes' 时，只有当parent 为null时才能作为第一级目录]
 * @return {[type]}                  [description]
 */
export function fixMenus(menus, fromParentIsNull) {
  let parents = []
  menus.map((obj, idx) => {
    obj.children = []
  })
  if (fromParentIsNull && fromParentIsNull === 'yes') {
    parents = menus.filter(menu => !menu.parent && !menu.pId)
  } else {
    parents = menus.filter(menu => {
      if (!menu.parent && !menu.pId) return true
      var i = 0
      var length = menus.length
      for (; i < length; i++) {
        var tmp = menus[i]
        if (menu.parent && tmp.id === menu.parent.id) {
          return false
        }
        if (menu.pId && tmp.id === menu.pId) {
          return false
        }
        // if ((menu.parent && tmp.id === menu.parent.id) || (menu.pId && tmp.id === menu.pId)) return false
        // else if () return true
      }
      return true
    })
  }
  parents.map((obj, idx) => {
    arrageMenus(menus, obj)
  })
  return parents
}

/**
 * [arrageMenus 递归menus, 生成格式为{[children: []]}]
 * @param  {[type]} menus  [description]
 * @param  {[type]} parent [description]
 * @return {[type]}        [description]
 */
export function arrageMenus(menus, parent) {
  let objPid = parent.id
  menus.map((obj, index) => {
    var pId = ''
    if (obj.parent) {
      pId = obj.parent.id
    } else {
      pId = obj.pId ? obj.pId : 0
    }
    if (objPid === pId) {
      delete obj.children
      if (!parent.children) parent.children = []
      parent.children.push(arrageMenus(menus, obj))
    }
  })
  return parent
}

/**
 * @description 根据name/params/query判断两个路由对象是否相等
 * @param {*} route1 路由对象
 * @param {*} route2 路由对象
 */
export const routeEqual = (route1, route2) => {
  const params1 = route1.params || {}
  const params2 = route2.params || {}
  const query1 = route1.query || {}
  const query2 = route2.query || {}
  var routeEqualBool = false
  if (route1.name === route2.name) {
    if (objEqual(params1, params2)) {
      if (objEqual(query1, query2)) {
        routeEqualBool = true
      }
    }
  }
  return routeEqualBool
}
