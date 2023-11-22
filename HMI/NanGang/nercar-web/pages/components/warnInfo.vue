<template>
  <div class="warn-info">
    <!-- <div
      v-if="warnType == 1"
      :style="'left:'+posLocation.left+'px; top:'+posLocation.top+'px; width:'+width+'px'"
      class="warn-info-box type1">
      <p>报警信息</p>
      <hmi-table
        :table-data="tableDataWarn"
        :is-pagination-show="false"
        :table-foot="false"
        :table-head="false"
      >
        <template slot="TableBody">
          <el-table-column
            prop="MATID"
            width="150"
            label="钢板号"
            align="center"/>
          <el-table-column
            prop="LEVEL"
            label="报警等级"
            width="70"
            align="center"/>
          <el-table-column
            prop="TIME"
            label="报警时间"
            align="center"/>
          <el-table-column
            prop="REGION"
            width="120"
            label="报警区域"
            align="center"/>
          <el-table-column
            prop="MSG"
            label="报警内容"
            align="center"/>
        </template>
      </hmi-table>
    </div> -->

    <!-- <div
      v-if="warnType == 2"
      style="padding: 24px;"
      class="bgc-white type2">
      <div class="header">
        <p class="ps">报警信息</p>
      </div>
      <div>
        <hmi-table
          :table-data="tableDataWarn"
          :is-pagination-show="false"
          :table-foot="false"
          :table-head="false"
        >
          <template slot="TableBody">
            <el-table-column
              prop="MATID"
              label="钢板号"
              align="center"/>
            <el-table-column
              prop="LEVEL"
              label="报警等级"
              width="70"
              align="center"/>
            <el-table-column
              prop="TIME"
              label="报警时间"
              align="center"/>
            <el-table-column
              prop="REGION"
              width="120"
              label="报警区域"
              align="center"/>
            <el-table-column
              prop="MSG"
              label="报警内容"
              align="center"/>
          </template>
        </hmi-table>
      </div>
    </div> -->
  </div>
</template>

<script>
import HmiTable from '@/components/HmiTable'
import { getHmiDataByEvent } from '@/lib/GetData'
export default {
  name: 'WarnInfo',
  components: { HmiTable },
  props: {
    width: {
      type: Number,
      default: 670
    },
    warnType: {
      //1表示定位 2 表示常规布局
      type: Number,
      default: 1
    },
    posLocation: {
      type: Object,
      default: () => {
        return {}
      }
    }
  },
  data() {
    return {
      tableDataWarn: [{}, {}, {}, {}, {}, {}, {}]
    }
  },
  mounted() {
    this.getWarnTableData()
  },
  methods: {
    getWarnInfoByRoute() {
      let pcdpKeyVal = {
        home: 'ALARM_ALL',
        jls: 'ALARM_HL_CB_DSS',
        '1dcj': 'ALARM_FL1DS',
        '1dbj': 'ALARM_FL1PILER',
        lq: 'ALARM_CB3_DDS',
        ypj: 'ALARM_FL2CS',
        '2dbj': 'ALARM_FL2DS',
        '2dcj': 'ALARM_FL2PILER',
        dcjWorking: 'ALARM_FL2DSLMS',
        lxfdj: 'ALARM_HL_CB_DSS'
      }
      return pcdpKeyVal[this.$route.name]
    },
    getWarnTableData() {
      let data = [{ tagName: this.getWarnInfoByRoute(), timestamp: 0 }]
      getHmiDataByEvent(data).then(res => {
        if (res.code == 200) {
          this.tableDataWarn = res.results[0].value
        }
      })
    }
  }
}
</script>

<style scoped lang="less">
.bgc-white {
  background-color: #fff;
  box-shadow: 0px 0px 4px rgb(0 0 0 / 4%), 0px 0px 16px -2px rgb(0 0 0 / 10%);
  border-radius: 6px;
}
.header {
  margin-bottom: 16px;
  .ps {
    font-size: 16px;
    color: #606266;
    font-weight: bold;
  }
}
.warn-info-box {
  position: absolute;
  > p {
    font-size: 15px;
    color: #606266;
    font-weight: bold;
    letter-spacing: 1px;
    border-left: 6px solid #606266;
    padding-left: 6px;
    margin-bottom: 14px;
  }
}
</style>
