// index.js
// import Api from '@/plugins/api'
// export const plugins = [Api]
// export var pageButtonPower = '测试11'
export const strict = false //严格模式
export const state = () => ({
  wsUrl: '',
  pageButtonPower: '',
  //一级菜单导航
  publicKey: '',
  companyName: '',
  bigLogoPath: '',
  smallLogoPath: '',
  loginLogoPath: '',
  apiGate: '',
  user: {},
  equipments: [],
  departments: [],
  currentEquipment: {},
  currentDepartment: {},
  // menus: 用户的目录
  config: '',
  dataMessage: {},
  localeInfo: [
    {
      type: 'zh',
      name: '中文'
    },
    {
      type: 'en',
      name: 'English'
    }
  ],
  locales: ['zh', 'en'],
  locale: 'zh',
  workTime: '' // 工作时间
})
export const getters = {
  // ...
  getJurisdiction: state => routeName => {
    var resources = state.user.resources
    if (!state.user.resources) {
      var user = JSON.parse(localStorage.getItem('user'))
      resources = user.resources
    }
    return resources.indexOf(routeName) > -1
  },
  pageButtonPower: state => state.pageButtonPower
}

export const mutations = {
  SET_WORKTIME(state, workTime) {
    state.workTime = workTime
  },
  SET_LANG(state, locale) {
    if (state.locales.indexOf(locale) !== -1) {
      state.locale = locale
    }
  },
  allMenus(state, allMenus) {
    state.allMenus = allMenus
  },
  setUser(state, user) {
    console.debug('用户信息:', user)
    if (!user) return
    state.user = user
  },
  /**

   * @description: 设置导航栏当前选择的页面
   */
  setTagNavModel(state, tagNavModel) {
    console.debug('setTagNavModel:', tagNavModel)
    var item = tagNavModel.name
    state.tagNavModel = item
  },
  /**

   * @description: 设置导航栏列表
   */
  setTagNavList(state, tagNavList) {
    console.debug('导航目录stort：', tagNavList)
    if (typeof tagNavList === 'object') {
      if (isNaN(tagNavList.length)) {
        console.debug('对象')
        var isAddPath = true
        if (tagNavList && state.tagNavList) {
          state.tagNavList.map(function(item, index) {
            if (item.name === tagNavList.name) {
              isAddPath = false
            }
          })
        }
        if (isAddPath) {
          var pathItem = {
            name: tagNavList.name,
            path: tagNavList.path,
            metaName: tagNavList.metaName
          }
          state.tagNavList.push(pathItem)
        }
      } else {
        console.debug('数组')
        state.tagNavList = []
        tagNavList.map(function(item, index) {
          // var pathItem = { name: item.name, path: item.path }
          state.tagNavList.push(item)
        })
      }
    }
  },
  setInitInfo(state, result) {
    state.publicKey = result.publicKey
    state.apiGate = result.apiGate
    if (!result.version) {
      return
    }
    var versionInfo =
      typeof result.version.content === 'string'
        ? JSON.parse(result.version.content)
        : result.version.content
    var array = versionInfo[0].split(',')
    // console.log(versionInfo)
    state.companyName = versionInfo[0]
    state.bigLogoPath = (versionInfo[3] ? versionInfo[3] : '').split(':')[1] // 找张默认图片
    state.smallLogoPath = (versionInfo[2] ? versionInfo[2] : '').split(':')[1]
    state.baseUrl =
      versionInfo.length < 5 ? 'http://localhost:8099' : versionInfo[4]
    state.loginLogoPath = (versionInfo[5] ? versionInfo[5] : '').split(':')[1] // 登录页logo
  },
  setSymmkey(state, symmkey) {
    state.symmkey = symmkey
  }
}

// export const actions = {
//   async nuxtServerInit({ commit }, { app }) {
//     console.debug('nuxt server init')
//     const result = await app.$axios.$post('/user/getPublicKey.form', {
//       version: 0
//     })
//     // console.log(JSON.stringify(result))
//     commit('setInitInfo', result)
//   }
// }
