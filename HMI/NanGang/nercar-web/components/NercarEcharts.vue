<template>
  <div
    :id="containerId"
    :style = "{'width': '100%', 'height': _height ? _height : '100%'}"
    class=""/>
</template>

<script>
import Echarts from 'echarts'
import themeEcharts from '@/assets/css/themeEcharts'
import UUID from 'uuid'
export default {
  name: 'NercarEcharts',
  props: {
    themeDark: {
      type: Boolean,
      default: function() {
        return true
      }
    },
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
      type: Object,
      default: function() {
        return {}
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
        return {
          show: false
        }
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
    useUTC: {
      type: Boolean,
      default: function() {
        return true
      }
    },
    _height: {
      type: String,
      default: ''
    },
    touchOffResize: {
      type: Boolean,
      default: false
    }
  },
  data() {
    return {
      containerId: UUID(),
      echart: {}
    }
  },
  watch: {
    title: {
      handler(title) {
        console.log('title is change ==========', title)
        this.$nextTick(function() {
          this.echart.setOption({ title })
        })
      },
      // immediate: true,
      deep: true
    },
    grid: {
      handler(grid) {
        console.log('grid=======', grid)
        this.$nextTick(function() {
          this.echart.setOption({ grid })
        })
      },
      deep: true
    },
    xAxis: {
      handler(xAxis) {
        console.log('xAxis=======', xAxis)
        this.$nextTick(function() {
          this.echart.setOption({ xAxis })
        })
      },
      deep: true
    },
    yAxis: {
      handler(yAxis) {
        console.log('yAxis=======', yAxis)
        this.$nextTick(function() {
          this.echart.setOption({ yAxis })
        })
      },
      deep: true
    },
    polar: {
      handler(polar) {
        console.log('polar=======', polar)
        this.$nextTick(function() {
          this.echart.setOption({ polar })
        })
      },
      deep: true
    },
    radiusAxis: {
      handler(radiusAxis) {
        console.log('radiusAxis=======', radiusAxis)
        this.$nextTick(function() {
          this.echart.setOption({ radiusAxis })
        })
      },
      deep: true
    },
    angleAxis: {
      handler(angleAxis) {
        console.log('angleAxis=======', angleAxis)
        this.$nextTick(function() {
          this.echart.setOption({ angleAxis })
        })
      },
      deep: true
    },
    radar: {
      handler(radar) {
        console.log('radar=======', radar)
        this.echart.setOption({ radar })
      },
      deep: true
    },
    dataZoom: {
      handler(dataZoom) {
        this.$nextTick(function() {
          console.log('radar=======', dataZoom)
          this.echart.setOption({ dataZoom })
        })
      },
      deep: true
    },
    visualMap: {
      handler(visualMap) {
        console.log('visualMap=======', visualMap)
        this.$nextTick(function() {
          this.echart.setOption({ visualMap })
        })
      },
      deep: true
      // immediate: true
    },
    tooltip: {
      handler(tooltip) {
        this.$nextTick(function() {
          console.log('tooltip=======', tooltip)
          this.echart.setOption({ tooltip })
        })
      },
      deep: true
    },
    toolbox: {
      handler(toolbox) {
        console.log('toolbox=======', toolbox)
        this.$nextTick(function() {
          this.echart.setOption({ toolbox })
        })
      },
      deep: true
    },
    brush: {
      handler(brush) {
        this.$nextTick(function() {
          console.log('brush=======', brush)
          this.echart.setOption({ brush })
        })
      },
      deep: true
    },
    geo: {
      handler(geo) {
        this.$nextTick(function() {
          console.log('geo=======', geo)
          this.echart.setOption({ geo })
        })
      },
      deep: true
    },
    parallel: {
      handler(parallel) {
        this.$nextTick(function() {
          console.log('parallel=======', parallel)
          this.echart.setOption({ parallel })
        })
      },
      deep: true
    },
    parallelAxis: {
      handler(parallelAxis) {
        this.$nextTick(function() {
          console.log('parallelAxis=======', parallelAxis)
          this.echart.setOption({ parallelAxis })
        })
      },
      deep: true
    },
    singleAxis: {
      handler(singleAxis) {
        this.$nextTick(function() {
          console.log('singleAxis=======', singleAxis)
          this.echart.setOption({ singleAxis })
        })
      },
      deep: true
    },
    timeline: {
      handler(timeline) {
        this.$nextTick(function() {
          console.log('timeline=======', timeline)
          this.echart.setOption({ timeline })
        })
      },
      deep: true
    },
    series: {
      handler(series) {
        this.$nextTick(function() {
          // console.log('series=======', series)
          this.echart.setOption({ legend: this.legend, series })
        })
      },
      deep: true
    },
    color: {
      handler(color) {
        console.debug('color===================', color)
        this.echart.setOption({ color })
      }
    },
    backgroundColor: {
      handler(backgroundColor) {
        // console.log('series=======', series)
        this.echart.setOption({ backgroundColor })
      }
    },
    group: {
      handler(group) {
        // console.log('series=======', series)
        this.handlerConnect(group)
      }
    },
    graphic: {
      handler(graphic) {
        // console.log('series=======', series)
        this.echart.setOption({ graphic })
      },
      deep: true
    },
    _height: {
      handler(_height) {
        console.log('_tasily chart height is change ... ')
        this.$nextTick(function() {
          this.echart.resize()
        })
      }
    },
    _width: {
      handler(_width) {
        console.log('_tasily chart width is change ... ')
        this.$nextTick(function() {
          this.echart.resize()
        })
      }
    },
    touchOffResize: {
      handler(touchOffResize) {
        //监听touchOffResize是否变化主动刷新this.echart.resize()
        console.debug('echart touchOffResize is change ... ')
        this.$nextTick(function() {
          this.echart.resize()
        })
      }
    },
    data: {
      /*这边可能有点问题*/
      handler(data) {
        if (!data) return
        var series = []
        data.map((obj, idx) => {
          series.push({ data: obj })
        })
        this.echart.setOption({ series })
      }
    }
  },
  mounted() {
    // console.log('echarts is mounted ..., ', this.containerId)
    let vm = this
    if (this.themeDark) {
      this.echart = Echarts.init(
        document.getElementById(this.containerId),
        themeEcharts
      )
    } else {
      this.echart = Echarts.init(document.getElementById(this.containerId))
    }

    // this.echart = Echarts.init(document.getElementById(this.containerId))

    if (this.group) this.handlerConnect(this.group)

    this.echart.setOption(this.getDefaultOption())

    this.echart.on('click', function(params) {
      vm.$emit('chart-click-data', {
        data: params,
        id: vm.$el.id,
        echart: vm.echart
      })
    })

    window.addEventListener('resize', () => {
      console.log('window.addEventListener  resize...')
      this.echart.resize()
    })
    this.$nextTick(function() {
      this.echart.resize()
    })
  },
  methods: {
    updated() {
      console.log('echart updated ...')
    },
    handlerConnect(group) {
      if (group) {
        Echarts.connect(group)
      }
      this.echart.group = group
    },
    getDefaultOption() {
      let option = {
        legend: this.legend,
        tooltip: this.tooltip,
        toolbox: this.toolbox,
        grid: this.grid,
        xAxis: this.xAxis,
        yAxis: this.yAxis,
        useUTC: this.useUTC,
        dataZoom: this.dataZoom,
        series: this.series,
        graphic: this.graphic
      }
      return option
    },
    sizeChange() {
      console.log('sizechange is invoke ..')
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

<style scoped>
</style>
