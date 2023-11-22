<template>
  <el-row style="margin-bottom: 20px">
    <el-row>
      <el-col :span="24">
        <el-form
          :inline="true"
          :model="searchData">
          <el-form-item label="钢板号">
            <el-input
              v-model="searchData.plateno"
              placeholder="请输入钢板号"
              style="width: 160px"/>
          </el-form-item>
          <el-form-item label="是否空过">
            <el-select
              v-model="searchData.dss_emp"
              style="width: 160px"
              clearable
              placeholder="请选择空过"
            >
              <el-option
                :value="0"
                label="空过"/>
              <el-option
                :value="1"
                label="不空过"/>
            </el-select>
          </el-form-item>
          <el-form-item label="班别">
            <el-select
              v-model="searchData.crew"
              style="width: 160px"
              clearable
              placeholder="请选择班别"
            >
              <el-option
                :value="1"
                label="甲班"/>
              <el-option
                :value="2"
                label="乙班"/>
              <el-option
                :value="3"
                label="丙班"/>
              <el-option
                :value="4"
                label="丁班"/>
            </el-select>
          </el-form-item>
          <el-form-item label="班次">
            <el-select
              v-model="searchData.shift"
              clearable
              placeholder="请选择班次"
              style="width: 160px"
            >
              <el-option
                :value="1"
                label="早班"/>
              <el-option
                :value="2"
                label="中班"/>
              <el-option
                :value="3"
                label="晚班"/>
            </el-select>
          </el-form-item>
          <el-form-item label="时间">
            <el-date-picker
              v-model="searchData.start_time"
              value-format="timestamp"
              type="datetime"
              placeholder="起始时间"/>
            <el-date-picker
              v-model="searchData.end_time"
              value-format="timestamp"
              type="datetime"
              placeholder="结束时间"/>
          </el-form-item>
          <el-form-item>
            <el-button
              type="primary"
              size="medium"
              @click="getTableData()"
            >查询
            </el-button>
          </el-form-item>
        </el-form>
      </el-col>
      <!-- <el-col :span="3">
        <div class="btn-box">
          <el-button
            type="primary"
            size="medium"
            @click="getTableData()"
          >查询
          </el-button>
        </div>
      </el-col> -->
    </el-row>
    <el-row>
      <el-col :span="24">
        <div class="container-p">
          <div class="flex_ful">
            <p class="title-p">
              1#双边剪报表
            </p>
            <el-button-group>
              <el-button
                type="warning"
                size="mini"
                @click="changebnt(0)">实际表</el-button>
              <el-button
                type="warning"
                size="mini"
                @click="changebnt(1)">设定表</el-button>
            </el-button-group>
          </div>
          <el-row
            v-show="isTrue==0"
            style="margin-bottom: 20px">
            <el-table
              v-loading="loading"
              :data="tableData"
              :cell-style="{border:'1px solid #777',borderTop:'0px solid #777'}"
              :header-cell-style="{border:'1px solid #777'}"
              border
              style="width: 100%;border-bottom:1px solid #777;border-right:1px solid #777;">
              <el-table-column
                align="center"
                label="序号"
                type="index"
                width="60"/>
              <el-table-column
                align="center"
                label="钢板号"
                prop="PLATENO"/>
              <el-table-column
                align="center"
                label="进入双边剪时间"
                prop="ENDSS_TIME"/>
              <!-- <el-table-column
                align="center"
                label="离开双边剪时间"
                width="150"
                prop="EXDSS_TIME"/> -->
              <!-- <el-table-column
                align="center"
                label="母板长度"
                prop="L1_DSS_PLATELEN"/> -->
              <!-- <el-table-column
                align="center"
                label="母板宽度"
                prop="L1_DSS_PLATEWID"/> -->
              <el-table-column
                align="center"
                label="订单宽度"
                prop="WID_MAX"/>
              <el-table-column
                align="center"
                label="剪切宽度"
                prop="L1_DSS_CUTWID"/>
              <el-table-column
                align="center"
                label="母板厚度"
                prop="L1_DSS_PLATETHK">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.L1_DSS_PLATETHK).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <!-- <el-table-column
                align="center"
                label="曲阜强度"
                prop="L1_DSS_STRENGTH"/>         -->
              <el-table-column
                align="center"
                label="激光划线1"
                prop="DSSLASER1">
                <template slot-scope="scope">
                  <div>{{ scope.row.DSSLASER1 == 0 ? scope.row.DSSLASER1 : Number(scope.row.DSSLASER1).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="主剪刀间隙1"
                prop="MAIN_GAP_1">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.MAIN_GAP_1).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="碎刀剪刀间隙1"
                prop="SCRAP_GAP_1">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.SCRAP_GAP_1).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="夹送辊宽度"
                prop="WIDTH_ADJUST">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.WIDTH_ADJUST).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="空过"
                prop="DSS_EMP"/>
            </el-table>
          </el-row>
          <el-row
            v-show="isTrue==1"
            style="margin-bottom: 20px" >
            <el-table
              v-loading="loading"
              :data="tableData"
              :cell-style="{border:'1px solid #777',borderTop:'0px solid #777'}"
              :header-cell-style="{border:'1px solid #777'}"
              border
              style="width: 100%;border-bottom:1px solid #777;border-right:1px solid #777;">
              <el-table-column
                align="center"
                label="序号"
                type="index"
                width="60"/>
              <el-table-column
                align="center"
                label="钢板号"
                prop="PLATENO"/>
              <el-table-column
                align="center"
                label="进入双边剪时间"
                width="150"
                prop="ENDSS_TIME"/>
              <!-- <el-table-column
                align="center"
                label="离开双边剪时间"
                width="150"
                prop="EXDSS_TIME"/> -->
              <!-- <el-table-column
                align="center"
                label="设定母板长度"
                prop="L2_DSS_PLATELEN"/> -->
              <!-- <el-table-column
                align="center"
                label="设定母板宽度"
                prop="L2_DSS_PLATEWID"/> -->
              <el-table-column
                align="center"
                label="订单宽度"
                prop="WID_MAX"/>
              <el-table-column
                align="center"
                label="设定剪切宽度"
                prop="L2_DSS_CUTWID"/>
              <el-table-column
                align="center"
                label="设定母板厚度"
                prop="L2_DSS_PLATETHK">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.L2_DSS_PLATETHK).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <!-- <el-table-column
                align="center"
                label="设定曲阜强度"
                prop="L2_DSS_STRENGTH"/> -->

              <!-- <el-table-column
                align="center"
                label="是否探伤"
                prop="FD_EMP"/>
              <el-table-column
                align="center"
                label="探伤时间"
                width="150"
                prop="FD_TIME"/> -->
              <el-table-column
                align="center"
                label="冷床出口温度"
                prop="CDT">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.CDT).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="班次"
                prop="SHIFT">
                <template slot-scope="scope">
                  <div>{{ scope.row.SHIFT ==1?'早班':scope.row.SHIFT==2?'中班':scope.row.SHIFT==3?'晚班': '' }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="班别"
                prop="CREW">
                <template slot-scope="scope">
                  <div>{{ scope.row.CREW==1?'甲班':scope.row.CREW==2?'乙班':scope.row.CREW==3?'丙班': scope.row.CREW==4?'丁班':'' }}</div>
                </template>
              </el-table-column>
            </el-table>
          </el-row>

          <!-- <ManagementTable
            :table-data="tableData"
            :table-columns="tableColumns"
            :loading="loading"
          /> -->
          <simple-pagination
            :page-size="pagination.pageSize"
            :total="pagination.total"
            :align="pagination.align"
            :current-page="pagination.currentPage"
            layout="total, prev, pager, next,jumper"
            @handleSizeChangeFn="handleSizeChange"
            @handleCurrentChangeFn="handleCurrentChange"
          />
        </div>

      </el-col>
    </el-row>
  </el-row>
</template>

<script>
import ManagementTable from '@/pages/components/ManagementTable'
import simplePagination from '@/components/simplePagination'
import {
  getHmiData,
  stopGetData,
  sendMsg,
  sendTag,
  getHmiDataByEvent
} from '@/lib/GetData'
export default {
  name: 'LcManagement',
  components: { ManagementTable, simplePagination },
  data() {
    return {
      isTrue: 0,
      loading: false,
      searchData: {
        dss_emp: '',
        start_time: '',
        end_time: '',
        crew: '',
        shift: '',
        plateno: ''
      },
      pagination: {
        align: 'right',
        currentPage: 1,
        pageSizes: [10, 20, 30, 40],
        pageSize: 13,
        total: 0
      },
      tableData: []
    }
  },
  mounted() {
    this.getTableData()
  },
  methods: {
    //tab切换
    changebnt(nub) {
      if (nub == 0) {
        this.isTrue = 0
      } else {
        this.isTrue = 1
      }
    },
    getTableData() {
      /*
      *  1——1号线冷床实绩
          2——1号线双边剪实绩
          3——1号线定尺剪实绩
          4——1号线子板实绩
          11——2号线切分剪实绩
          12——2号线圆盘剪实绩
          13——2号线定尺剪实绩
          14——2号线子板实绩
          21——班组统计
      *
      * */
      this.loading = true
      if (this.searchData.start_time == null) {
        this.searchData.start_time = ''
      }
      if (this.searchData.end_time == null) {
        this.searchData.end_time = ''
      }
      let data = [
        [
          {
            table: '2',
            start_time: this.searchData.start_time + '',
            end_time: this.searchData.end_time + '',
            dss_emp: this.searchData.dss_emp,
            crew: this.searchData.crew,
            shift: this.searchData.shift,
            plateno: this.searchData.plateno,
            pageNo: this.pagination.currentPage,
            pageSize: this.pagination.pageSize
          }
        ]
      ]
      sendMsg(data, 1825, 'HMI').then(res => {
        if (res.code == 200) {
          this.loading = false
          this.pagination.total = res.results[0][0].TotalCount
          this.tableData = res.results[0]
        }
      })
    },
    handleSizeChange(val) {
      this.pagination.pageSize = val
      this.getTableData()
    },
    handleCurrentChange(val) {
      this.pagination.currentPage = val
      this.getTableData()
    }
  }
}
</script>

<style scoped lang="less">
.container-p {
  background-color: #fff;
  box-shadow: 0px 0px 4px rgb(0 0 0 / 4%), 0px 0px 16px -2px rgb(0 0 0 / 10%);
  border-radius: 6px;
  padding: 24px;
  margin-bottom: 20px;
}
.flex_ful {
  display: flex;
  justify-content: flex-start;
  align-items: center;
  /deep/.el-button-group {
    position: relative;
    top: -6px;
    left: 20px;
  }
}
.title-p {
  font-weight: 700;
  font-size: 20px;
  color: #606266;
  font-family: 'Microsoft YaHei UI';
  margin-bottom: 15px;
}
.btn-box {
  float: right;
  padding-right: 40px;
}
</style>
<style>
.el-table th {
  display: table-cell !important;
}
</style>
