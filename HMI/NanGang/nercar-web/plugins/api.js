// import { Loading } from 'element-ui'
// api.js
export default ({ app }, inject) => {
  // url : string, 服务器端url
  // data: Object, 请求的数据
  // isNotify: bool, 是否在右上角显示提示信息，默认'yes', 不显示传'no'
  inject('postService', async function(url, data, isNotify) {
    // console.log('api.js')
    // 客户端请求，需要使用前缀/api/代理
    // console.log('window from remoteserver, ', app, inject)
    if (!process.server) {
      // url = '/api/' + url
      url = url
    }
    // console.log('process env device', process.env.device)
    // // lement-ui 加载窗初始化
    // let loadingInstance = Loading.service({
    //   lock: true,
    //   text: '', //'Loading',
    //   spinner: 'el-icon-loading--a', // 设置无效图标
    //   background: 'rgba(0, 0, 0, 0)' // 设置透明笼罩层背景
    // })
    try {
      const result = await app.$axios.$post(url, data)
      if (!process.server && (!isNotify || isNotify !== 'no')) {
        // this.$notify.success({
        //   title: app.i18n.t('home.systemInfo'),
        //   message: '操作成功',
        //   showClose: false
        // })
        // this.$message({
        //   showClose: true,
        //   message: '操作成功',
        //   type: 'success'
        // })
        console.debug('接口请求成功')
      }
      // loadingInstance.close() // 关闭笼罩层
      return result
    } catch (e) {
      if (process.server) return
      this.$notify.error({
        title: '系统信息',
        message:
          process.env.NODE_ENV === 'production'
            ? '通讯出错了，请稍后再试'
            : e.message,
        showClose: true
      })
      // loadingInstance.close() // 关闭笼罩层
      return {
        status: 'sysError',
        code: e.response && e.response.status ? e.response.status : '401'
      }
      console.log('response status is  ', e.response.status, 'url is ', url)
    }
  })

  inject('getService', async function(url, data, isNotify) {
    // console.log(process.env.NODE_ENV)
    // console.log(process.env.BASE_URL)
    // console.log(process.env.PORT)
    console.log(data)
    // 客户端请求，需要使用前缀/api/代理
    if (!process.server) {
      // url = '/api/' + url
      url = url
    }
    try {
      const result = await app.$axios.$get(url)
      if (!process.server && (!isNotify || isNotify !== 'no')) {
        // this.$notify.success({
        //   title: '系统信息',
        //   message: '操作成功',
        //   showClose: false
        // })
        // this.$message({
        //   showClose: true,
        //   message: '操作成功',
        //   type: 'success'
        // })
      }
      return result
    } catch (e) {
      if (process.server) return
      this.$notify.error({
        title: '系统信息',
        message:
          process.env.NODE_ENV === 'production'
            ? '通讯出错了，请稍后再试'
            : e.message,
        showClose: false
      })
      console.log('response status is  ', e.response.status, 'url is ', url)
    }
  })
}
