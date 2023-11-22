import Vue from 'vue'
import uuid from 'uuid'
// import locale from 'element-ui/lib/locale/lang/en'
export default () => {
  // 注册一个全局自定义指令 `v-command`
  Vue.directive('command', {
    // 当被绑定的元素插入到 DOM 中时……
    update: function(el, binding) {
      console.log('update')
      // 聚焦元素
      console.log('command show control =========')
      var pbp = JSON.parse(localStorage.getItem('pageButtonPower') || {})
      let resources = pbp.result || []
      let compare = []
      resources.forEach((v, k) => {
        compare.push(v.resourceEname)
      })
      if (compare.indexOf(binding.value) == -1) {
        // el.style.display = 'none'
        el.remove()
      }
    }
  })

  Vue.directive('isrc', {
    // 当被绑定的元素插入到 DOM 中时……
    update: function(el, binding) {
      // 聚焦元素
      let url = $nuxt.$store.state.baseUrl + '/' + binding.value
      el.src = url
    }
  })

  // let page = 3
  function getDataPage(el) {
    console.log('prepare tag directive')
    var page = ''
    if (!el.childNodes || el.childNodes.length < 1) return el.dataset.page
    for (var i = 0; i < el.childNodes.length; i++) {
      var child = el.childNodes[i]
      if (child.childNodes && child.childNodes.length > 0) {
        var tmp = getDataPage(child)
        if (tmp && tmp.length > 1) {
          page = tmp
          break
        }
      } else {
        if (child.dataset && child.dataset.page) {
          page = child.dataset.page
          break
        }
      }
    }
    return page
  }
  /*
  @author：awen
  @email: miaomia0mia0@163.com
  @date：2022/9/17  11:13
  @name：优化获取中间件变量方法
  @describe: 通过更改绑定参数方式, 优化页面tag变量减少 实际请求并未减少的问题
             同时可以通过删除对应tar来暂缓试试刷新词tag
   */
  Vue.directive('tag', {
    // 当被绑定的元素插入到 DOM 中时……
    bind: function(el, binding) {
      // 聚焦元素
      console.log(binding.arg + ': Binding')
      // 指令所在的页面
      // var page = el.dataset.page
      var page = getDataPage(el)
      // 如果没传入页面，则视为无效的绑定
      if (!page) return
      // 是消息还是tag
      var type = binding.arg + 's'
      // 存储的当前页面的消息
      // pageItem 格式如下
      // pageItem = {tags:[{name: '', ts: 0}], msgs: [{name: '', ts: 0}]}
      var pageItem = JSON.parse(localStorage.getItem('hmi/' + page) || '{}')
      // localStorage.clear('hmi/' + page)
      // localStorage.clear()
      // tag名
      var tagNameList = binding.value.map(item => {
        if (type == 'msgs') {
          return {
            tagName: item,
            timestamp: 0,
            ticket: uuid().replace(new RegExp('-', 'g'), ''),
            id: item,
            reply: true,
            timeout: 0
          }
        } else {
          return {
            tagName: item,
            timestamp: 0
          }
        }
      })
      pageItem[type] = tagNameList
      localStorage.setItem('hmi/' + page, JSON.stringify(pageItem))
    }
  })
}
