<template>
  <div
    :id="containerId"
    :style="{'width': '100%', 'min-width': _width ? _width : '400px', 'height': _height ? _height : '400px'}"
    class="chartContainer"
    oncontextmenu="return false" />
</template>
<script>
import Echarts from 'echarts'
import themeEcharts from '../assets/css/themeEcharts'
import UUID from 'uuid'
export default {
  props: {
    title: {
      type: Object,
      default: function() {
        return {}
      }
    },
    legend: {
      type: Object,
      default: function() {
        return {}
      }
    },
    dataset: {
      type: Object,
      default: function() {
        return {}
      }
    },
    grid: {
      type: Array,
      default: function() {
        return []
      }
    },
    axisPointer: {
      type: Object,
      default: function() {
        return {}
      }
    },
    xAxis: {
      type: Array,
      default: function() {
        return []
      }
    },
    yAxis: {
      type: Array,
      default: function() {
        return []
      }
    },
    polar: {
      type: Object,
      default: function() {
        return {}
      }
    },
    radiusAxis: {
      type: Object,
      default: function() {
        return {}
      }
    },
    angleAxis: {
      type: Object,
      default: function() {
        return {}
      }
    },
    radar: {
      type: Object,
      default: function() {
        return {}
      }
    },
    dataZoom: {
      type: Array,
      default: function() {
        return []
      }
    },
    visualMap: {
      type: Object,
      default: function() {
        return {}
      }
    },
    tooltip: {
      type: Object,
      default: function() {
        return {}
      }
    },
    toolbox: {
      type: Object,
      default: function() {
        return {}
      }
    },
    brush: {
      type: Object,
      default: function() {
        return {}
      }
    },
    geo: {
      type: Object,
      default: function() {
        return {}
      }
    },
    parallel: {
      type: Object,
      default: function() {
        return {}
      }
    },
    parallelAxis: {
      type: Object,
      default: function() {
        return {}
      }
    },
    singleAxis: {
      type: Object,
      default: function() {
        return {}
      }
    },
    timeline: {
      type: Object,
      default: function() {
        return {}
      }
    },
    series: {
      type: Array,
      default: function() {
        return []
      }
    },
    color: {
      type: Array,
      default: function() {
        return []
      }
    },
    backgroundColor: {
      type: String,
      default: ''
    },
    group: {
      type: String,
      default: ''
    },
    data: {
      type: [Array, Object],
      default: function() {
        return []
      }
    },
    graphic: {
      type: Array,
      default: function() {
        return []
      }
    },
    _width: {
      type: String,
      default: ''
    },
    _height: {
      type: String,
      default: ''
    },
    resizeFlag: {
      type: String,
      default: ''
    }
  },
  data() {
    return {
      echart: {},
      containerId: UUID()
    }
  },
  watch: {
    title: {
      handler(title) {
        this.$nextTick(function() {
          this.echart.setOption({
            title
          })
        })
      },
      deep: true
    },
    grid: {
      handler(grid) {
        this.$nextTick(function() {
          this.echart.setOption({
            grid
          })
        })
      },
      deep: true
    },
    axisPointer: {
      handler(grid) {
        this.$nextTick(function() {
          this.echart.setOption({
            grid
          })
        })
      },
      deep: true
    },
    xAxis: {
      handler(xAxis) {
        this.$nextTick(function() {
          this.echart.setOption({
            xAxis
          })
        })
      },
      deep: true
    },
    dataset: {
      handler(dataset) {
        this.$nextTick(function() {
          this.echart.setOption({
            dataset
          })
        })
      },
      deep: true
    },
    yAxis: {
      handler(yAxis) {
        this.$nextTick(function() {
          this.echart.setOption({
            yAxis
          })
        })
      },
      deep: true
    },
    polar: {
      handler(polar) {
        this.$nextTick(function() {
          this.echart.setOption({
            polar
          })
        })
      },
      deep: true
    },
    radiusAxis: {
      handler(radiusAxis) {
        this.$nextTick(function() {
          this.echart.setOption({
            radiusAxis
          })
        })
      },
      deep: true
    },
    angleAxis: {
      handler(angleAxis) {
        this.$nextTick(function() {
          this.echart.setOption({
            angleAxis
          })
        })
      },
      deep: true
    },
    radar: {
      handler(radar) {
        this.$nextTick(function() {
          this.echart.setOption({
            radar
          })
        })
      },
      deep: true
    },
    dataZoom: {
      handler(dataZoom) {
        this.$nextTick(function() {
          this.echart.setOption({
            dataZoom
          })
        })
      },
      deep: true
    },
    visualMap: {
      handler(visualMap) {
        this.$nextTick(function() {
          this.echart.setOption({
            visualMap
          })
        })
      },
      deep: true
    },
    tooltip: {
      handler(tooltip) {
        console.log(tooltip)
        this.$nextTick(function() {
          this.echart.setOption({
            tooltip
          })
        })
      },
      deep: true
    },
    toolbox: {
      handler(toolbox) {
        console.log('toolbox', toolbox)
        this.$nextTick(function() {
          this.echart.setOption({
            toolbox
          })
        })
      },
      deep: true
    },
    brush: {
      handler(brush) {
        this.$nextTick(function() {
          this.echart.setOption({
            brush
          })
        })
      },
      deep: true
    },
    geo: {
      handler(geo) {
        this.$nextTick(function() {
          this.echart.setOption({
            geo
          })
        })
      },
      deep: true
    },
    parallel: {
      handler(parallel) {
        this.$nextTick(function() {
          this.echart.setOption({
            parallel
          })
        })
      },
      deep: true
    },
    parallelAxis: {
      handler(parallelAxis) {
        this.$nextTick(function() {
          this.echart.setOption({
            parallelAxis
          })
        })
      },
      deep: true
    },
    singleAxis: {
      handler(singleAxis) {
        this.$nextTick(function() {
          this.echart.setOption({
            singleAxis
          })
        })
      },
      deep: true
    },
    timeline: {
      handler(timeline) {
        this.$nextTick(function() {
          this.echart.setOption({
            timeline
          })
        })
      },
      deep: true
    },
    series: {
      handler(series) {
        this.$nextTick(function() {
          this.echart.setOption({
            legend: this.legend,
            series
          })
        })
      },
      deep: true
    },
    color: {
      handler(color) {
        this.$nextTick(function() {
          this.echart.setOption({
            color
          })
        })
      }
    },
    backgroundColor: {
      handler(backgroundColor) {
        this.$nextTick(function() {
          this.echart.setOption({
            backgroundColor
          })
        })
      }
    },
    group: {
      handler(group) {
        this.handlerConnect(group)
      }
    },
    graphic: {
      handler(graphic) {
        this.$nextTick(function() {
          this.echart.setOption({
            graphic
          })
        })
      },
      deep: true
    },
    _height: {
      handler(_height) {
        console.log('handler里面的height', _height)
        this.$nextTick(function() {
          this.echart.resize()
        })
      }
    },
    _width: {
      handler(_width) {
        this.$nextTick(function() {
          this.echart.resize()
        })
      }
    },
    data: {
      handler(data) {
        if (!data) return
        var series = []
        data.map((obj, idx) => {
          series.push({
            data: obj
          })
        })
        this.$nextTick(function() {
          this.echart.setOption({
            series
          })
        })
      }
    },
    resizeFlag: {
      handler(val) {
        console.log('val: ', val)
        if (val) {
          this.$nextTick(function() {
            this.echart.resize()
          })
        }
      }
    }
  },
  mounted() {
    let vm = this
    this.$nextTick(function() {
      this.echart = Echarts.init(
        document.getElementById(this.containerId),
        themeEcharts
      )

      if (this.group) this.handlerConnect(this.group)
      this.echart.setOption(this.getDefaultOption())
      this.echart.on('click', function(params) {
        console.log(params)
        vm.$emit('chart-click-data', {
          data: params,
          id: vm.$el.id,
          echart: vm.echart
        })
      })
      //添加legend 回调事件
      this.echart.on('legendselectchanged', params => {
        console.log(params)
        vm.$emit('chart-legendselectchanged', {
          data: params,
          id: vm.$el.id,
          echart: vm.echart
        })
      })
      window.addEventListener('resize', () => {
        this.echart.resize()
      })
    })
  },
  methods: {
    handlerConnect(group) {
      if (group) {
        Echarts.connect(group)
      }
      this.echart.group = group
    },
    renderBrushed(params) {
      console.log('renderBrushed', params)
    },
    getDefaultOption() {
      /*根据需求额外添加功能，判断是否是热力图或者是带有可以拖动时间的功能*/
      var otherEcharts = {}
      if (JSON.stringify(this.visualMap) !== '{}') {
        otherEcharts['visualMap'] = this.visualMap
      }
      if (JSON.stringify(this.axisPointer) !== '{}') {
        otherEcharts['axisPointer'] = this.axisPointer
      }
      if (JSON.stringify(this.dataset) !== '{}') {
        otherEcharts['dataset'] = this.dataset
      }
      if (JSON.stringify(this.xAxis) !== '{}') {
        otherEcharts['xAxis'] = this.xAxis
        otherEcharts['yAxis'] = this.yAxis
      }
      /*判断是否是热力图或者是带有可以拖动时间的功能*/
      var option = {
        title: this.title,
        legend: this.legend,
        tooltip: this.tooltip,
        toolbox: this.toolbox,
        /*{
                orient: 'horizontal',
                right: '0px',
                feature: {
                  restore: {
                    show: true
                  },
                  dataView: {
                    show: true
                  },
                  dataZoom: {
                    show: true
                  },
                  magicType: {
                    type: ['line', 'bar', 'stack', 'tiled']
                  },
                  saveAsImage: {
                    show: true
                  }
                }
              }*/
        grid: this.grid,
        useUTC: false,
        dataZoom: this.dataZoom,
        series: this.series,
        graphic: this.graphic
      }

      option = Object.assign(option, otherEcharts)
      return option
    },
    sizeChange() {
      this.$nextTick(function() {
        this.echart.resize()
      })
    },
    clearEchart(obj) {
      var vm = this
      vm.echart = Echarts.init(document.getElementById(obj.containerId))
      if (vm.group) vm.handlerConnect(vm.group)
      var series = obj.getDefaultOption().series
      var seriesLength = series.length
      for (var i = 0; i < seriesLength; i++) {
        series.shift()
      }
      vm.echart.setOption(obj.getDefaultOption())
      vm.echart.on('click', function(params) {
        vm.$emit('chart-click-data', {
          data: params,
          id: vm.$el.id,
          echart: vm.echart
        })
      })
    }
  }
}
</script>
