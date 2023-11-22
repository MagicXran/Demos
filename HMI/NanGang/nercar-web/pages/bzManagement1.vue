<template>
  <div>
    <el-row style="margin-bottom: 20px">
      <el-row>
        <el-col :span="21">
          <el-form
            :inline="true"
            :model="searchData">
            <el-form-item label="钢板号">
              <el-input
                v-model="searchData.plateno"
                placeholder="请输入钢板号"
                style="width: 160px"/>
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
          </el-form>
        </el-col>
        <el-col :span="3">
          <div class="btn-box">
            <el-button
              type="primary"
              size="medium"
              @click="getTableData()"
            >查询
            </el-button>
          </div>
        </el-col>
      </el-row>
      <el-row>
        <el-col :span="24">
          <div class="container-p">
            <p class="title-p">
              班组报表
            </p>
            <el-table
              v-loading="loading"
              :data="tableData"
              border
              style="width: 100%">
              <el-table-column
                align="center"
                label="序号"
                fixed="left"
                type="index"
                width="60"/>
              <el-table-column
                align="center"
                label="上班时间"
                width="150"
                fixed="left"
                prop="ONWORK_TIME"/>
              <el-table-column
                align="center"
                label="下班时间"
                width="150"
                prop="OFFWORK_TIME"/>

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
              <!-- <el-table-column
                align="center"
                label="表检时间"
                width="150"
                prop="SIS_TIME"/> -->
              <el-table-column
                align="center"
                label="矫直块数"
                width="150"
                prop="HL_NUM"/>
              <el-table-column
                align="center"
                label="矫直重量"
                prop="HL_WGT">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.ONCB1_NUM).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="上1号冷床块数"
                prop="ONCB1_NUM"/>
              <el-table-column
                align="center"
                label="上1号冷床重量"
                prop="ONCB1_WGT">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.ONCB1_WGT).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="下1号冷床块数"
                prop="OFFCB1_NUM"/>
              <el-table-column
                align="center"
                label="下1号冷床重量"
                prop="OFFCB1_WGT">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.OFFCB1_WGT).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="上2号冷床块数"
                prop="ONCB2_NUM"/>
              <el-table-column
                align="center"
                label="上2号冷床重量"
                prop="ONCB2_WGT">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.ONCB2_WGT).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="下2号冷床块数"
                prop="OFFCB2_NUM"/>
              <el-table-column
                align="center"
                label="下2号冷床重量"
                prop="OFFCB2_WGT">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.OFFCB2_WGT).toFixed(3) }}</div>
                </template>
              </el-table-column>

              <el-table-column
                align="center"
                label="上3号冷床块数"
                prop="ONCB3_NUM"/>
              <el-table-column
                align="center"
                label="上3号冷床重量"
                prop="ONCB3_WGT">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.ONCB3_WGT).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="下3号冷床块数"
                prop="OFFCB3_NUM"/>
              <el-table-column
                align="center"
                label="下3号冷床重量"
                prop="OFFCB3_WGT">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.OFFCB3_WGT).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="1/2号线"
                prop="LINE">
                <template slot-scope="scope">
                  <div>{{ scope.row.LINE }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="双边剪/圆盘剪块数"
                prop="DSS_NUM"/>
              <el-table-column
                align="center"
                label="双边剪/圆盘剪重量"
                prop="DSS_WGT">
                <template slot-scope="scope">
                  <div>{{ scope.row.DSS_WGT == 0 ? scope.row.DSS_WGT : Number(scope.row.DSS_WGT).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="定尺剪块数"
                prop="DS_NUM"/>
              <el-table-column
                align="center"
                label="定尺剪重量"
                prop="DS_WGT">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.DS_WGT).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="总重"
                prop="WGT">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.WGT).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="总数"
                prop="NUM">
                <template slot-scope="scope">
                  <div>{{ scope.row.NUM }}</div>
                </template>
              </el-table-column>
            </el-table>
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
  </div>
</template>

<script>
import ManagementTable from '@/pages/components/ManagementTable'
import simplePagination from '@/components/simplePagination'
import { getHmiData, stopGetData, sendMsg, sendTag } from '@/lib/GetData'
export default {
  name: 'BzManagement',
  components: { ManagementTable, simplePagination },
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
        pageSize: 13,
        total: 0
      },
      tableData: [],
      tableColumns: [
        {
          key: 'ONWORK_TIME',
          label: '上班时间'
        },
        {
          key: 'OFFWORK_TIME',
          label: '下班时间'
        },
        {
          key: 'SHIFT',
          label: '班'
        },
        {
          key: 'CREW',
          label: '组'
        },
        {
          key: 'HL_NUM',
          label: '矫直块数'
        },
        {
          key: 'HL_WGT',
          label: '矫直重量'
        },
        {
          key: 'ONCB1_NUM',
          label: '上1号冷床块数'
        },
        {
          key: 'ONCB1_WGT',
          label: '上1号冷床重量'
        },
        {
          key: 'OFFCB1_NUM',
          label: '下1号冷床块数'
        },
        {
          key: 'OFFCB1_WGT',
          label: '下1号冷床重量'
        },
        {
          key: 'ONCB2_NUM',
          label: '上2号冷床块数'
        },
        {
          key: 'ONCB2_WGT',
          label: '上2号冷床重量'
        },
        {
          key: 'OFFCB2_WGT',
          label: '下2号冷床重量'
        },
        {
          key: 'ONCB3_NUM',
          label: '上3号冷床块数'
        },
        {
          key: 'ONCB3_WGT',
          label: '上3号冷床重量'
        },
        {
          key: 'OFFCB3_NUM',
          label: '下3号冷床块数'
        },
        {
          key: 'OFFCB3_WGT',
          label: '下3号冷床重量'
        },
        {
          key: 'LINE',
          label: '1/2号线'
        },
        {
          key: 'FD_NUM',
          label: '探伤块数'
        },
        {
          key: 'FD_WGT',
          label: '探伤重量'
        },
        {
          key: 'DDS_NUM',
          label: '切分剪块数'
        },
        {
          key: 'DDS_WGT',
          label: '切分剪重量'
        },
        {
          key: 'DSS_NUM',
          label: '双边剪/圆盘剪块数'
        },
        {
          key: 'DSS_WGT',
          label: '双边剪/圆盘剪重量'
        },
        {
          key: 'DS_NUM',
          label: '定尺剪块数'
        },
        {
          key: 'DS_WGT',
          label: '定尺剪重量'
        },
        {
          key: 'SIS_NUM',
          label: '表检块数'
        },
        {
          key: 'SIS_WGT',
          label: '表检重量'
        },
        {
          key: 'MARK_NUM',
          label: '标印块数'
        },
        {
          key: 'MARK_WGT',
          label: '标印重量'
        },
        {
          key: 'WGT',
          label: '总重'
        },
        {
          key: 'NUM',
          label: '总数'
        },
        {
          key: 'FAULT_WGT',
          label: '计划弯刀缺陷重量'
        },
        {
          key: 'FAULT_WGT_MEAS',
          label: '实际弯刀缺陷重量'
        },
        {
          key: 'FAULT_NUM',
          label: '计划弯刀缺陷块数'
        },
        {
          key: 'FAULT_NUM_MEAS',
          label: '实际弯刀缺陷块数'
        }
      ]
    }
  },
  mounted() {
    this.getTableData()
  },
  methods: {
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
      let data = [
        [
          {
            table: '21',
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
          this.pagination.total = res.results[0][0].TotalCount
          this.loading = false
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
