<template>
  <div class="alarm">
    <div
      v-tag:tag="variable"
      data-page="alarm"/>
    <el-row
      :gutter="20"
      class="bgc-white">
      <el-col
        :span="4"
        style="margin: 25px 0px">
        <div>
          <span
            :class="statsList['dba'] == 1? 'green':'red'"
            class="yuan"/>
          <span style="vertical-align: middle;letter-spacing: 1px;">本地数据库</span>
        </div>
      </el-col>
      <el-col
        :span="4"
        style="margin: 25px 0px">
        <div>
          <span
            :class="statsList['mes'] == 1? 'green':'red'"
            class="yuan red"/>
          <span style="vertical-align: middle;letter-spacing: 1px;">三级数据库</span>
        </div>
      </el-col>
      <el-col
        :span="4"
        style="margin: 25px 0px">
        <div>
          <span
            :class="statsList['sisdba1'] == 1? 'green':'red'"
            class="yuan"/>
          <span style="vertical-align: middle;letter-spacing: 1px;">一线表检数据库</span>
        </div>
      </el-col>
      <el-col
        :span="4"
        style="margin: 25px 0px">
        <div>
          <span
            :class="statsList['sisdba2'] == 1? 'green':'red'"
            class="yuan"/>
          <span style="vertical-align: middle;letter-spacing: 1px;">二线表检数据库</span>
        </div>
      </el-col>
      <el-col
        :span="4"
        style="margin: 25px 0px">
        <div>
          <span
            :class="statsList['HLTRACK'] == 1? 'green':'red'"
            class="yuan"/>
          <span style="vertical-align: middle;letter-spacing: 1px;">轧线TDC</span>
        </div>
      </el-col>
      <el-col
        :span="4"
        style="margin: 25px 0px">
        <div>
          <span
            :class="statsList['CBTRACK'] == 1? 'green':'red'"
            class="yuan"/>
          <span style="vertical-align: middle;letter-spacing: 1px;">矫直冷床TDC</span>
        </div>
      </el-col>
      <el-col
        :span="4"
        style="margin: 25px 0px">
        <div>
          <span
            :class="statsList['L1DSSTRACK'] == 1? 'green':'red'"
            class="yuan"/>
          <span style="vertical-align: middle;letter-spacing: 1px;">1#双边、定尺剪TDC</span>
        </div>
      </el-col>
      <el-col
        :span="4"
        style="margin: 25px 0px">
        <div>
          <span
            :class="statsList['L1PILERTRACK'] == 1? 'green':'red'"
            class="yuan"/>
          <span style="vertical-align: middle;letter-spacing: 1px;">1#剁扳TDC</span>
        </div>
      </el-col>
      <el-col
        :span="4"
        style="margin: 25px 0px">
        <div>
          <span
            :class="statsList['L2DDSTRACK'] == 1? 'green':'red'"
            class="yuan"/>
          <span style="vertical-align: middle;letter-spacing: 1px;">2#切分、圆盘剪TDC</span>
        </div>
      </el-col>
      <el-col
        :span="4"
        style="margin: 25px 0px">
        <div>
          <span
            :class="statsList['L2DSTRACK'] == 1? 'green':'red'"
            class="yuan"/>
          <span style="vertical-align: middle;letter-spacing: 1px;">2#定尺剪TDC</span>
        </div>
      </el-col>
      <el-col
        :span="4"
        style="margin: 25px 0px">
        <div>
          <span
            :class="statsList['OFFDDSTRACK'] == 1? 'green':'red'"
            class="yuan"/>
          <span style="vertical-align: middle;letter-spacing: 1px;">离线分段剪TDC</span>
        </div>
      </el-col>
      <el-col
        :span="4"
        style="margin: 25px 0px">
        <!--        <div>
          <span
            :class="statsList['L1LMSSCAN'] == 1? 'green':'red'"
            class="yuan"/>
          <span style="vertical-align: middle;letter-spacing: 1px;">取样机器人TDC</span>
        </div>-->
      </el-col>
    </el-row>
    <el-row
      :gutter="20"
      style="margin-top: 20px"
      class="bgc-white">
      <el-col :span="24">
        <el-table
          :data="tableData"
          border
          style="width: 100%"
        >
          <el-table-column
            align="center"
            label="序号"
            type="index"
            width="60"/>
          <el-table-column
            prop="NAME"
            label="通讯方"
            align="center"/>
          <el-table-column
            prop="IP"
            label="IP"
            align="center"/>
          <el-table-column
            prop="accessname"
            label="通道名"
            align="center"/>
          <el-table-column
            prop="describe"
            label="通讯"
            align="center"/>
        </el-table>
      </el-col>
    </el-row>
  </div>
</template>

<script>
import { getHmiData, stopGetData, sendMsg, sendTag } from '@/lib/GetData'
export default {
  name: 'Alarm',
  data() {
    return {
      variable: ['ComStatus', 'ERRComStatus'],
      tableData: [],
      statsList: []
    }
  },
  mounted() {
    this.getHmiData()
  },
  destroyed() {
    stopGetData()
  },
  methods: {
    getHmiData() {
      getHmiData(
        'alarm',
        data => {
          this.tableData = data['ERRComStatus']
          console.log(this.tableData)
          this.statsList = data['ComStatus'][0]
        },
        error => {
          console.log(error)
        },
        1000
      )
    }
  }
}
</script>

<style scoped lang="less">
.bgc-white {
  background-color: #fff;
  box-shadow: 0px 0px 4px rgb(0 0 0 / 4%), 0px 0px 16px -2px rgb(0 0 0 / 10%);
  border-radius: 6px;
  padding: 20px !important;
}
.yuan {
  display: inline-block;
  width: 25px;
  height: 25px;
  border-radius: 50%;
  vertical-align: middle;
  letter-spacing: 1px;
}
.red {
  background-color: #f56c6c;
}
.green {
  background-color: #67c23a;
}
</style>
