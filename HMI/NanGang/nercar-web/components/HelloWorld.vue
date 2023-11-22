<template>
  <div>
    <div>{{ title }}</div>
    <div>{{ changeTitle }}</div>
    <!--
:style="{'background-position':'0 '+position+'px'}"
-->

    <div
      :style="{'background-position':'0 '+position+'px'}"
      class="container"
      @mousemove="mousemove"/>
  </div>
</template>

<script>
import * as d3 from 'd3'
export default {
  name: 'HelloWorld',
  props: {
    title: {
      type: String,
      default: ''
    }
  },
  data() {
    return {
      changeTitle: this.title,
      position: 5940
    }
  },
  watch: {
    changeTitle(newVal) {
      this.title = newVal
    }
  },
  mounted() {
    // this.changeTitle = '子组件修改的title'
  },
  methods: {
    mousemove(bar) {
      /*
      * 思路  根据鼠标滑动多少 修改background-position位置
      * 1 根据960/2 = 480 和鼠标滑动具体算比例
      * 区间:
      * [0, 540, 1080, 1620, 2160, 2700, 3240, 3780, 4320, 4860, 5400, 5940, 6480, 7020, 7560, 8100, 8640, 9180, 9720, 10260, 10800]
      * */
      let [num, pos] = [0, 0]
      // let num = 0
      let arr = [
        0,
        540,
        1080,
        1620,
        2160,
        2700,
        3240,
        3780,
        4320,
        4860,
        5400,
        5940,
        6480,
        7020,
        7560,
        8100,
        8640,
        9180,
        9720,
        10260,
        10800
      ]
      num = (Math.abs(bar.offsetX - 480) * 5670) / 480 //根据比例算图片上下移动像素值
      if (bar.offsetX < 480) {
        //向左偏移
        pos = 5670 - num
      } else {
        //向右偏移
        pos = 5670 + num
      }
      //通过区间计算position
      this.position = arr[this.countArea(pos, arr)]
      console.log('position', this.position)
    },
    countArea(num, arr) {
      for (let i = 0; i < arr.length; i++) {
        if (num > i * 540 && num < (i + 1) * 540) {
          return i
        }
      }
    }
  }
}
</script>

<style scoped lang="less">
.container {
  height: 540px;
  width: 960px;
  margin: 50px auto;
  border: 1px solid pink;
  background-image: url(../assets/animation/frame.png);
  background-position: 0 5940px; // 第11个是中间
}
</style>
