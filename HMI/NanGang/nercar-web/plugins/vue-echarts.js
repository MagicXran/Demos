// import Vue from 'vue'
// import ECharts from 'vue-echarts/components/ECharts.vue'

// // 手动引入 ECharts 各模块来减小打包体积
// import 'echarts/lib/chart/bar'
// import 'echarts/lib/component/tooltip'

// // 如果需要配合 ECharts 扩展使用，只需要直接引入扩展包即可
// // 以 ECharts-GL 为例：
// // 需要安装依赖：npm install --save echarts-gl，并添加如下引用
// import 'echarts-gl'

// // 注册组件后即可使用
// Vue.component('v-chart', ECharts)
import Vue from 'vue'
import echarts from 'echarts' // 引入echarts
import 'echarts-gl'
Vue.prototype.$echarts = echarts // 引入组件（将echarts注册为全局）
