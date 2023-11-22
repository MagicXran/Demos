<template>
  <div class="one-box">
    <el-tooltip
      v-for="(item,key) in trackData"
      :key="key"
      class="item"
      effect="light"
      placement="top-start">
      <div slot="content">{{ item.plate_type }}号 <span style="font-weight: bold">{{ item.plateno }}</span>
        {{ item.plate_type }}厚度 <span style="font-weight: bold">{{ Number(item.platethk).toFixed(3) }}</span>
        {{ item.plate_type }}宽度 <span style="font-weight: bold">{{ Number(item.platewid).toFixed(3) }}</span>
        {{ item.plate_type }}长度 <span style="font-weight: bold">{{ Number(item.platelen).toFixed(3) }}</span>
        {{ item.plate_type }}重量 <span style="font-weight: bold">{{ Number(item.platewet).toFixed(3) }}</span>
        <span>
          头部位置 <span style="font-weight: bold">{{ Number(item.headX).toFixed(3) }}</span>
          尾部位置 <span style="font-weight: bold">{{ Number(item.tailX).toFixed(3) }}</span>
          <span v-if="item.region == 2 || item.region == 3 || item.region == 4">
            y轴位置 <span style="font-weight: bold">{{ Number(item.Vpos).toFixed(3) }}</span>
          </span>
        </span>

      </div>
      <div
        :style="{width: item.width+'px','line-height':item.height+'px',height:item.height+'px'
                 ,left:item.tailpos+ left +'px',top:item.vPos+ top +'px'
                 ,backgroundColor:item.color == 0?'#5e0f0f':item.color == 1?'#cb7c26' :item.color == 2?'#17622e': '#8a28bc'}"
        class="one"
        @dblclick="opdialog($event,item)"
        @click="getTableDataByTwo(item.plateno, 1, item)">
        <span>
          <!--          {{ item.platenoSimple }}-->
          {{ countIdShowNum(item) }}
          <!-- {{ setPlateno(item) }} -->
        </span>
      </div>
    </el-tooltip>
    <el-tooltip
      v-for="(item) in trackDataBig"
      :key="item.plateno+Math.random()"
      class="item"
      effect="light"
      placement="top-start">
      <div slot="content"> {{ item.plate_type }}号 <span style="font-weight: bold">{{ item.plateno }}</span>
        {{ item.plate_type }}厚度 <span style="font-weight: bold">{{ Number(item.platethk).toFixed(3) }}</span>
        {{ item.plate_type }}宽度 <span style="font-weight: bold">{{ Number(item.platewid).toFixed(3) }}</span>
        {{ item.plate_type }}长度 <span style="font-weight: bold">{{ Number(item.platelen).toFixed(3) }}</span>
        {{ item.plate_type }}重量 <span style="font-weight: bold">{{ Number(item.platewet).toFixed(3) }}</span>
        <span>
          头部位置 <span style="font-weight: bold">{{ Number(item.headX).toFixed(3) }}</span>
          尾部位置 <span style="font-weight: bold">{{ Number(item.tailX).toFixed(3) }}</span>
          <span v-if="item.region == 2 || item.region == 3 || item.region == 4">
            y轴位置 <span style="font-weight: bold">{{ Number(item.Vpos).toFixed(3) }}</span>
          </span>
        </span>
      </div>
      <div
        :style="{width: item.width*3.65+'px','line-height':item.height+'px',height:item.height+'px'
                 ,left:(item.tailposbig+ left+430) +'px',top:item.vPos+ top+133 +'px'
                 ,backgroundColor:item.color == 0?'#5e0f0f':item.color == 1?'#cb7c26' :item.color == 2?'#17622e': '#8a28bc'}"
        class="one"
        @dblclick="opdialog($event,item)"
        @click="getTableDataByTwo(item.plateno, 1, item)">
        <span>
          {{ item.plateno }}
          <!--          {{ countIdShowNum(item) }}-->
          <!--          {{ setPlateno(item) }}-->
        </span>
      </div>
    </el-tooltip>
  </div>
</template>

<script>
export default {
  name: 'TrackItem',
  props: {
    top: {
      type: Number,
      default: 0
    },
    left: {
      type: Number,
      default: 0
    },
    trackData: {
      type: Array,
      default: () => {
        return []
      }
    },
    trackDataBig: {
      type: Array,
      default: () => {
        return []
      }
    },
    type: {
      type: Number,
      default: 0
    }
  },
  data() {
    return {}
  },
  methods: {
    opdialog(event, item) {
      this.$emit('opdialog', event, item)
    },
    getTableDataByTwo(plateno, type, item) {
      this.$emit('getTableDataByTwo', plateno, this.type, item)
    },
    countIdShowNum(item) {
      // - 6 左右各留2px以及 ..
      let fontSize = 7
      let num = item.plateno.length - (item.width - 2) / fontSize //算出可以存放多少个字母 -2:留有2像素的余点
      if (item.plateno.length * fontSize <= item.width) {
        //如果钢板的字母数量*10  小于  钢板页面宽度  直接显示钢板号即可
        return item.plateno
      } else {
        // 如果钢板的字母数量*10  不小于 钢板页面宽度
        // 截取 它能存放的个数 (钢板号的后面)
        // console.log('234', num)
        return '.' + item.plateno.slice(num + 1, item.plateno.length)
      }
    },
    // 处理显示的钢板号
    setPlateno(pla) {
      // console.log(pla.plateno.split(''))
      let str = pla.plateno.split('')
      let nameList = []
      let name = ''
      if (Number(pla.width) < 44) {
        str.forEach((item, index) => {
          if (index > str.length - 6) {
            nameList.push(item)
          }
        })
        console.log(nameList.join(''))
        return nameList.join('')
      } else {
        return pla.plateno
      }
    }
  }
}
</script>

<style lang="less">
.el-tooltip__popper {
  white-space: pre-line !important;
  font-size: 14px;
}

.one {
  position: absolute;
  top: 12px;
  left: 0px;
  width: 100px;
  height: 22px;
  cursor: pointer;
  //background-color: #a09393;
  background-color: #5e0f0f;
  font-size: 12px;
  text-align: center;

  > span {
    /*transform: scale(0.9);
    font-size: 12px;
    display: block;
    margin-top: -3px;
    color: #f50101;*/
    font-size: 12px;
    //color: #f50101;
    color: #ffffff;
    //line-height: 22px;
    //transform: scale(0.9);
    font-size: 12px;
    display: block;
  }
}
</style>
