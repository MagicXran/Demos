<template>
  <div>
    <el-row>
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
      </el-row>
      <el-row>
        <el-col :span="24">
          <div class="container-p">
            <p class="title-p">
              计划表 ( 板坯 )
            </p>
            <el-table
              v-loading="loading"
              :data="tableData"
              :empty-text="'暂无数据'"
              :header-cell-style="{border: '1px solid #777',backgroundColor: '#B9C8C5'}"
              :cell-style="getCellStyle"
              style="width: 100%;"
              row-key="PLATE_NO"
              border
              default-expand-all
              class="eltablecss"
              height="345"
              @row-click="clickRow">
              <el-table-column
                type="index"
                align="center"
                width="40"/>
              <el-table-column
                prop="PLATE_NO"
                label="钢板号"
                width="190"
                align="center"/>
              <el-table-column
                prop=""
                label="产品分类"
                align="center">
                <template slot-scope="scope">
                  <span v-if="scope.row.PLATE_TYPE == 1">板坯</span>
                  <span v-if="scope.row.PLATE_TYPE == 2">母板</span>
                  <span v-if="scope.row.PLATE_TYPE == 3">子板</span>
                  <span v-if="scope.row.PLATE_TYPE == 4">子母板</span>
                </template>
              </el-table-column>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="PLATE_THK"
                label="厚度"
                width="55"
                align="center"/>
              <el-table-column
                prop="PLATE_WID"
                width="65"
                label="宽度"
                align="center"/>
              <el-table-column
                prop="PLATE_LEN"
                label="计划长度"
                width="85"
                align="center"/>
              <el-table-column
                width="65"
                prop="PLATELEN_MEAS"
                label="实测长度"
                align="center"/>
              <el-table-column
                prop="PLATE_WGT"
                label="重量"
                width="65"
                align="center">
                <template slot-scope="scope">
                  <div>
                    {{ (scope.row.PLATE_WGT || 0).toFixed(3) }}
                  </div>
                </template>
              </el-table-column>
              <el-table-column
                prop="DELIVERY_DATE"
                label="交货期"
                width="85"
                align="center"/>
              <el-table-column
                prop="URGENT_ORDER"
                width="50"
                label="是否紧急订单"
                align="center"/>
              <el-table-column
                prop="ORDER_MATERIAL"
                label="订单材"
                width="40"
                align="center"/>
              <el-table-column
                prop="LEN_MAX"
                label="长度上限"
                width="65"
                align="center"/>
              <el-table-column
                prop="LEN_MIN"
                label="长度下限"
                width="65"
                align="center"/>
              <el-table-column
                prop="WID_MAX"
                label="宽度上限"
                width="65"
                align="center"/>
              <el-table-column
                prop="WID_MIN"
                label="宽度下限"
                width="65"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="STDSPEC"
                width="120"
                label="标准号"
                align="center"/>
              <el-table-column
                prop="HTL_PROCESS"
                label="热处理工序"
                width="120"
                align="center"/>
              <el-table-column
                prop="DS_TYPE"
                label="定尺"
                align="center"/>
              <el-table-column
                prop="FD_CODE"
                label="探伤"
                align="center"/>
              <el-table-column
                prop="HTM_TYPE"
                label="热处理"
                align="center"/>
              <el-table-column
                prop="CBARMTEMP"
                width="120"
                label="冷床目标温度"
                align="center"/>
              <el-table-column
                prop="ORDER_NO"
                label="订单号"
                width="160"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="IDENTIFICATION"
                label="标识标准"
                width="120"
                align="center"/>
              <el-table-column
                prop="EXCESSIVE_PRO"
                label="超量排产"
                align="center"/>
              <el-table-column
                prop="THK_MAX"
                label="厚度上限"
                align="center">
                <template slot-scope="scope">
                  <div>
                    {{ (scope.row.THK_MAX || 0).toFixed(3) }}
                  </div>
              <template/></template></el-table-column>
              <el-table-column
                prop="THK_MIN"
                label="厚度下限"
                align="center">
                <template slot-scope="scope">
                  <div>
                    {{ (scope.row.THK_MIN || 0).toFixed(3) }}
                  </div>
                </template>
              </el-table-column>
              <el-table-column
                prop="UNEVENNESS_1"
                label="钢板不平度1"
                align="center"/>
              <el-table-column
                prop="LEN_MEAS_1"
                label="测量长度1"
                align="center"/>
              <el-table-column
                prop="UNEVENNESS_2"
                label="钢板不平度2"
                align="center"/>
              <el-table-column
                prop="LEN_MEAS_2"
                label="测量长度2"
                align="center"/>
              <el-table-column
                prop="UNEVENNESS_3"
                label="不平度(mm/M)"
                align="center"/>
              <el-table-column
                prop="SAME_DIFFER"
                label="同板差"
                align="center">
                <template slot-scope="scope">
                  <div>
                    {{ (scope.row.SAME_DIFFER || 0).toFixed(3) }}
                  </div>
                </template>
              </el-table-column>
              <el-table-column
                prop="CAMBER"
                label="镰刀弯(长度%)"
                align="center">
                <template slot-scope="scope">
                  <div>
                    {{ (scope.row.CAMBER || 0).toFixed(3) }}
                  </div>
                </template>
              </el-table-column>
              <el-table-column
                prop="key0"
                label="切斜(宽度%)"
                align="center"/>
              <el-table-column
                prop="SKEW"
                label="试样备注"
                align="center"/>
              <el-table-column
                prop="REMARKS_SIZE"
                label="尺寸备注"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="REMARKS_PACK"
                label="打包备注"
                align="center"/>
              <el-table-column
                prop="REQUEST_SUR"
                label="表面客户要求"
                align="center"/>
              <el-table-column
                prop="WAREHOUSE"
                label="流向库别"
                align="center"/>
              <el-table-column
                prop="SAMP_CJ"
                label="冲击"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="SAMP_TYPE"
                label="取样频次"
                align="center"/>
              <el-table-column
                prop="SAMP_WGT"
                label="取样吨位"
                align="center"/>
              <el-table-column
                prop="SAMP_LEN"
                label="取样长度"
                align="center"/>
              <el-table-column
                prop="EXCESSIVE_PRO"
                label="超量排产"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="STANDARD"
                label="标准"
                align="center"/>
              <el-table-column
                prop="STEELGRADE"
                label="牌号"
                align="center"/>
              <el-table-column
                prop="CUSTOMER "
                label="客户名称"
                align="center"/>
              <el-table-column
                prop="SPRAY_FLAG"
                label="喷涂交货"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="SPRAY_CONTENT"
                label="加喷内容"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="SPRAY_SIDE"
                label="侧喷加喷"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="SPRAY_PRINT"
                label="冲印加喷"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="IDENT_NUM"
                label="标识次数"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="REMARKS_ORDER"
                label="订单备注"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="REMARKS_PRODUCE"
                label="生产备注"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="PLATE_STATE"
                label="钢板状态"
                align="center"/>
              <el-table-column
                prop="HTL_SAMP_LEN"
                label="热处理中间样取样长度"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="SPECIAL_REQUIRE"
                label="订单特殊要求"
                align="center"/>
              <el-table-column
                prop="ACC"
                label="控制冷却"
                align="center"/>
              <el-table-column
                prop="SRE_TEMP"
                label="成品开始堆冷温度"
                align="center"/>
              <el-table-column
                prop="SRE_TIME"
                label="成品堆冷时间（h）"
                align="center"/>
              <el-table-column
                prop="CUT_OFFLINE"
                label="离线切割"
                align="center"/>
              <el-table-column
                prop="CUT_TEMP_MAX"
                label="剪切/切割温度上限"
                align="center"/>
              <el-table-column
                prop="CUT_TEMP_MIN"
                label="剪切/切割温度下限"
                align="center"/>
              <el-table-column
                prop="CL_FLAG"
                label="使用冷矫"
                align="center"/>
            </el-table>
            <simple-pagination
              :page-size="pagination.pageSize"
              :total="pagination.total"
              :align="pagination.align"
              :current-page="pagination.currentPage"
              style="margin-top:20px"
              layout="total, prev, pager, next,jumper"
              @handleSizeChangeFn="handleSizeChange"
              @handleCurrentChangeFn="handleCurrentChange"
            />
          </div>

        </el-col>
      </el-row>
      <el-row>
        <div class="container-p1">
          <p class="title-p">
            计划表 ( 子板 )
          </p>
          <el-table
            v-loading="childLoading"
            :data="tableChildData"
            :empty-text="'暂无数据'"
            :header-cell-style="{border: '1px solid #777',backgroundColor: '#B9C8C5'}"
            :cell-style="getCellStyle"
            style="width: 100%;"
            row-key="PLATE_NO"
            height="380"
            border
            class="eltablecss"
            default-expand-all>
            <el-table-column
              type="index"
              align="center"
              width="40"/>
            <el-table-column
              prop="PLATE_NO"
              label="钢板号"
              width="190"
              align="center"/>
            <el-table-column
              prop=""
              label="产品分类"
              align="center">
              <template slot-scope="scope">
                <span v-if="scope.row.PLATE_TYPE == 1">板坯</span>
                <span v-if="scope.row.PLATE_TYPE == 2">母板</span>
                <span v-if="scope.row.PLATE_TYPE == 3">子板</span>
                <span v-if="scope.row.PLATE_TYPE == 4">子母板</span>
              </template>
            </el-table-column>
            <el-table-column
              :show-overflow-tooltip="true"
              prop="PLATE_THK"
              label="厚度"
              width="55"
              align="center"/>
            <el-table-column
              prop="PLATE_WID"
              width="65"
              label="宽度"
              align="center"/>
            <el-table-column
              prop="PLATE_LEN"
              label="计划长度"
              width="85"
              align="center"/>
            <el-table-column
              width="65"
              prop="PLATELEN_MEAS"
              label="实测长度"
              align="center"/>
            <el-table-column
              prop="PLATE_WGT"
              label="重量"
              width="65"
              align="center">
              <template slot-scope="scope">
                <div>
                  {{ (scope.row.PLATE_WGT || 0).toFixed(3) }}
                </div>
              </template>
            </el-table-column>
            <el-table-column
              prop="DELIVERY_DATE"
              label="交货期"
              width="85"
              align="center"/>
            <el-table-column
              prop="URGENT_ORDER"
              width="50"
              label="是否紧急订单"
              align="center"/>
            <el-table-column
              prop="ORDER_MATERIAL"
              label="订单材"
              width="40"
              align="center"/>
            <el-table-column
              prop="LEN_MAX"
              label="长度上限"
              width="65"
              align="center"/>
            <el-table-column
              prop="LEN_MIN"
              label="长度下限"
              width="65"
              align="center"/>
            <el-table-column
              prop="WID_MAX"
              label="宽度上限"
              width="65"
              align="center"/>
            <el-table-column
              prop="WID_MIN"
              label="宽度下限"
              width="65"
              align="center"/>
            <el-table-column
              :show-overflow-tooltip="true"
              prop="STDSPEC"
              width="120"
              label="标准号"
              align="center"/>
            <el-table-column
              prop="HTL_PROCESS"
              label="热处理工序"
              width="120"
              align="center"/>
            <el-table-column
              prop="DS_TYPE"
              label="定尺"
              align="center"/>
            <el-table-column
              prop="FD_CODE"
              label="探伤"
              align="center"/>
            <el-table-column
              prop="HTM_TYPE"
              label="热处理"
              align="center"/>
            <el-table-column
              prop="CBARMTEMP"
              width="120"
              label="冷床目标温度"
              align="center"/>
            <el-table-column
              prop="ORDER_NO"
              label="订单号"
              width="160"
              align="center"/>
            <el-table-column
              :show-overflow-tooltip="true"
              prop="IDENTIFICATION"
              label="标识标准"
              width="120"
              align="center"/>
            <el-table-column
              prop="EXCESSIVE_PRO"
              label="超量排产"
              align="center"/>
            <el-table-column
              prop="THK_MAX"
              label="厚度上限"
              align="center">
              <template slot-scope="scope">
                <div>
                  {{ (scope.row.THK_MAX || 0).toFixed(3) }}
                </div>
            <template/></template></el-table-column>
            <el-table-column
              prop="THK_MIN"
              label="厚度下限"
              align="center">
              <template slot-scope="scope">
                <div>
                  {{ (scope.row.THK_MIN || 0).toFixed(3) }}
                </div>
              </template>
            </el-table-column>
            <el-table-column
              prop="UNEVENNESS_1"
              label="钢板不平度1"
              align="center"/>
            <el-table-column
              prop="LEN_MEAS_1"
              label="测量长度1"
              align="center"/>
            <el-table-column
              prop="UNEVENNESS_2"
              label="钢板不平度2"
              align="center"/>
            <el-table-column
              prop="LEN_MEAS_2"
              label="测量长度2"
              align="center"/>
            <el-table-column
              prop="UNEVENNESS_3"
              label="不平度(mm/M)"
              align="center"/>
            <el-table-column
              prop="SAME_DIFFER"
              label="同板差"
              align="center">
              <template slot-scope="scope">
                <div>
                  {{ (scope.row.SAME_DIFFER || 0).toFixed(3) }}
                </div>
              </template>
            </el-table-column>
            <el-table-column
              prop="CAMBER"
              label="镰刀弯(长度%)"
              align="center">
              <template slot-scope="scope">
                <div>
                  {{ (scope.row.CAMBER || 0).toFixed(3) }}
                </div>
              </template>
            </el-table-column>
            <el-table-column
              prop="key0"
              label="切斜(宽度%)"
              align="center"/>
            <el-table-column
              prop="SKEW"
              label="试样备注"
              align="center"/>
            <el-table-column
              prop="REMARKS_SIZE"
              label="尺寸备注"
              align="center"/>
            <el-table-column
              :show-overflow-tooltip="true"
              prop="REMARKS_PACK"
              label="打包备注"
              align="center"/>
            <el-table-column
              prop="REQUEST_SUR"
              label="表面客户要求"
              align="center"/>
            <el-table-column
              prop="WAREHOUSE"
              label="流向库别"
              align="center"/>
            <el-table-column
              prop="SAMP_CJ"
              label="冲击"
              align="center"/>
            <el-table-column
              :show-overflow-tooltip="true"
              prop="SAMP_TYPE"
              label="取样频次"
              align="center"/>
            <el-table-column
              prop="SAMP_WGT"
              label="取样吨位"
              align="center"/>
            <el-table-column
              prop="SAMP_LEN"
              label="取样长度"
              align="center"/>
            <el-table-column
              prop="EXCESSIVE_PRO"
              label="超量排产"
              align="center"/>
            <el-table-column
              :show-overflow-tooltip="true"
              prop="STANDARD"
              label="标准"
              align="center"/>
            <el-table-column
              prop="STEELGRADE"
              label="牌号"
              align="center"/>
            <el-table-column
              prop="CUSTOMER "
              label="客户名称"
              align="center"/>
            <el-table-column
              prop="SPRAY_FLAG"
              label="喷涂交货"
              align="center"/>
            <el-table-column
              :show-overflow-tooltip="true"
              prop="SPRAY_CONTENT"
              label="加喷内容"
              align="center"/>
            <el-table-column
              :show-overflow-tooltip="true"
              prop="SPRAY_SIDE"
              label="侧喷加喷"
              align="center"/>
            <el-table-column
              :show-overflow-tooltip="true"
              prop="SPRAY_PRINT"
              label="冲印加喷"
              align="center"/>
            <el-table-column
              :show-overflow-tooltip="true"
              prop="IDENT_NUM"
              label="标识次数"
              align="center"/>
            <el-table-column
              :show-overflow-tooltip="true"
              prop="REMARKS_ORDER"
              label="订单备注"
              align="center"/>
            <el-table-column
              :show-overflow-tooltip="true"
              prop="REMARKS_PRODUCE"
              label="生产备注"
              align="center"/>
            <el-table-column
              :show-overflow-tooltip="true"
              prop="PLATE_STATE"
              label="钢板状态"
              align="center"/>
            <el-table-column
              prop="HTL_SAMP_LEN"
              label="热处理中间样取样长度"
              align="center"/>
            <el-table-column
              :show-overflow-tooltip="true"
              prop="SPECIAL_REQUIRE"
              label="订单特殊要求"
              align="center"/>
            <el-table-column
              prop="ACC"
              label="控制冷却"
              align="center"/>
            <el-table-column
              prop="SRE_TEMP"
              label="成品开始堆冷温度"
              align="center"/>
            <el-table-column
              prop="SRE_TIME"
              label="成品堆冷时间（h）"
              align="center"/>
            <el-table-column
              prop="CUT_OFFLINE"
              label="离线切割"
              align="center"/>
            <el-table-column
              prop="CUT_TEMP_MAX"
              label="剪切/切割温度上限"
              align="center"/>
            <el-table-column
              prop="CUT_TEMP_MIN"
              label="剪切/切割温度下限"
              align="center"/>
            <el-table-column
              prop="CL_FLAG"
              label="使用冷矫"
              align="center"/>
          </el-table>
          <!-- <simple-pagination
            :page-size="pagination.pageSize"
            :total="pagination.total"
            :align="pagination.align"
            :current-page="pagination.currentPage"
            style="margin-top:20px"
            layout="total, prev, pager, next,jumper"
            @handleSizeChangeFn="handleSizeChange"
            @handleCurrentChangeFn="handleCurrentChange"
          /> -->
        </div>
      </el-row>
    </el-row>
  </div>
</template>

<script>
// import ManagementTable from '@/pages/components/ManagementTable'
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
  components: { simplePagination },
  data() {
    return {
      loading: false,
      searchData: {
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
        pageSize: 50,
        total: 0
      },
      tableData: [],
      tableChildData: [],
      childLoading: false
    }
  },
  mounted() {
    this.getTableData()
  },
  methods: {
    // 主表数据
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
            table: '22',
            start_time: this.searchData.start_time + '',
            end_time: this.searchData.end_time + '',
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
          let tabelData = []
          tabelData = res.results[0]
          this.tableData = tabelData
        }
      })
    },
    // 点击主表获取子表数据
    clickRow(row) {
      this.childLoading = true
      console.log(row)
      let data = [
        [
          {
            table: '24',
            plateno: row.PLATE_NO,
            pageNo: 1,
            pageSize: 5
          }
        ]
      ]
      sendMsg(data, 1825, 'HMI').then(res => {
        if (res.code == 200) {
          this.childLoading = false
          if (res.results.length == 0) {
            this.$message({
              message: '查无数据',
              type: 'warning'
            })
            return
          }
          let tabelData = []
          tabelData = res.results[0]
          this.tableChildData = tabelData
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
    },
    // 修改table样式
    getCellStyle({ row, column, rowIndex, columnIndex }) {
      if (row.PLATE_TYPE == 1) {
        return 'background: #F0B8F0;border: solid 1px #777;border-top:0px'
      } else if (row.PLATE_TYPE == 2 || row.PLATE_TYPE == 4) {
        return 'background: #B1E8ED;border: solid 1px #777;border-top:0px'
      } else if (row.PLATE_TYPE == 3) {
        return 'background: #CDF8CE;border: solid 1px #777;'
      }
    }
  }
}
</script>

<style scoped lang="less">
.container-p {
  background-color: #fff;
  box-shadow: 0px 0px 4px rgb(0 0 0 / 4%), 0px 0px 16px -2px rgb(0 0 0 / 10%);
  border-radius: 6px;
  padding: 24px 24px 10px 24px;
}
.container-p1 {
  background-color: #fff;
  box-shadow: 0px 0px 4px rgb(0 0 0 / 4%), 0px 0px 16px -2px rgb(0 0 0 / 10%);
  border-radius: 6px;
  padding: 24px 24px 10px 24px;
  margin-top: 10px;
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
.eltablecss .el-table thead .tr .th {
  background: #b9c8c5 !important;
}
</style>
<style>
.el-table th {
  display: table-cell !important;
}
</style>
