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
              2#定尺剪报表
            </p>
            <el-table
              v-loading="loading"
              :data="tableData"
              :cell-style="{border:'1px solid #777',borderTop:'0px solid #777'}"
              :header-cell-style="{border:'1px solid #777'}"
              border
              style="width: 100%;border-bottom:1px solid #777">
              <el-table-column
                align="center"
                label="序号"
                fixed="left"
                type="index"
                width="60"/>
              <el-table-column
                align="center"
                label="母板号"
                width="150"
                fixed="left"
                prop="PLATENO"/>
              <el-table-column
                align="center"
                label="进入定尺剪时间"
                width="150"
                prop="EN_TIME"/>
              <el-table-column
                align="center"
                label="离开定尺剪时间"
                width="150"
                prop="EX_TIME"/>
              <el-table-column
                align="center"
                label="设定宽度（夹送辊开口度）"
                width="150"
                prop="SET_WID"/>
              <el-table-column
                align="center"
                label="设定厚度（侧隙调整）"
                width="150"
                prop="SET_THK"/>
              <el-table-column
                align="center"
                label="定尺剪设定刀数"
                prop="CUTNUM_SET"/>
              <el-table-column
                align="center"
                label="定尺剪设定剪切长度1"
                prop="SET_CUTLEN1"/>
              <el-table-column
                align="center"
                label="定尺剪设定剪切长度2"
                prop="SET_CUTLEN2"/>
              <el-table-column
                align="center"
                label="定尺剪设定剪切长度3"
                prop="SET_CUTLEN3"/>
              <el-table-column
                align="center"
                label="定尺剪设定剪切长度4"
                prop="SET_CUTLEN4"/>
              <el-table-column
                align="center"
                label="定尺剪设定剪切长度5"
                prop="SET_CUTLEN5"/>
              <el-table-column
                align="center"
                label="定尺剪设定剪切长度6"
                prop="SET_CUTLEN6"/>
              <el-table-column
                align="center"
                label="定尺剪设定剪切长度7"
                prop="SET_CUTLEN7"/>
              <el-table-column
                align="center"
                label="定尺剪设定剪切长度8"
                prop="SET_CUTLEN8"/>
              <el-table-column
                align="center"
                label="定尺剪设定剪切长度9"
                prop="SET_CUTLEN9"/>
              <el-table-column
                align="center"
                label="定尺剪设定剪切长度10"
                prop="SET_CUTLEN10"/>
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
            <!--            <ManagementTable
              :table-data="tableData"
              :table-columns="tableColumns"
              :loading="loading"
            />-->
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
import {
  getHmiData,
  stopGetData,
  sendMsg,
  sendTag,
  getHmiDataByEvent
} from '@/lib/GetData'
export default {
  name: 'DcjManagement2',
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
          key: 'PLATENO',
          label: '母板号'
        },
        {
          key: 'PLATE_TYPE',
          label: '钢板类型'
        },
        {
          key: 'STEELGRADE',
          label: '钢种'
        },
        {
          key: 'STDSPEC',
          label: '标准号'
        },
        {
          key: 'LEN_MEAS',
          label: '实测长度'
        },
        {
          key: 'THK_MEAS',
          label: '实测厚度'
        },
        {
          key: 'WID_MEAS',
          label: '实测宽度'
        },
        {
          key: 'CREATETIME',
          label: '上线时间'
        },
        {
          key: 'EN_TIME',
          label: '进入时间'
        },
        {
          key: 'EX_TIME',
          label: '离开时间'
        },
        {
          key: 'SET_WID',
          label: '电脑录入宽度（夹送辊开口度）'
        },
        {
          key: 'SET_THK',
          label: '电脑录入厚度（侧隙调整）'
        },
        {
          key: 'SET_CUTNUM',
          label: '设定刀数'
        },
        {
          key: 'SET_CUTTYPE1',
          label: '设定剪切类型1'
        },
        {
          key: 'SET_CUTLEN1',
          label: '设定剪切长度1'
        },
        {
          key: 'SET_CUTTYPE2',
          label: '设定剪切类型2'
        },
        {
          key: 'SET_CUTLEN2',
          label: '设定剪切长度2'
        },
        {
          key: 'SET_CUTTYPE3',
          label: '设定剪切类型3'
        },
        {
          key: 'SET_CUTLEN3',
          label: '设定剪切长度3'
        },
        {
          key: 'SET_CUTTYPE4',
          label: '设定剪切类型4'
        },
        {
          key: 'SET_CUTTYPE5',
          label: '设定剪切类型5'
        },
        {
          key: 'SET_CUTLEN5',
          label: '设定剪切长度5'
        },
        {
          key: 'SET_CUTTYPE6',
          label: '设定剪切类型6'
        },
        {
          key: 'SET_CUTLEN6',
          label: '设定剪切长度6'
        },
        {
          key: 'SET_CUTTYPE7',
          label: '设定剪切类型7'
        },
        {
          key: 'SET_CUTLEN7',
          label: '设定剪切长度7'
        },
        {
          key: 'SET_CUTTYPE8',
          label: '设定剪切类型8'
        },
        {
          key: 'SET_CUTLEN8',
          label: '设定剪切长度8'
        },
        {
          key: 'SET_CUTTYPE9',
          label: '设定剪切类型9'
        },
        {
          key: 'SET_CUTLEN9',
          label: '设定剪切长度9'
        },
        {
          key: 'SET_CUTTYPE10',
          label: '设定剪切类型10'
        },
        {
          key: 'SET_CUTLEN10',
          label: '设定剪切长度10'
        },
        {
          key: 'MEAS_LEN1',
          label: '实测剪切长度1'
        },
        {
          key: 'MEAS_LEN2',
          label: '实测剪切长度2'
        },
        {
          key: 'MEAS_LEN3',
          label: '实测剪切长度3'
        },
        {
          key: 'MEAS_LEN4',
          label: '实测剪切长度5'
        },
        {
          key: 'MEAS_LEN6',
          label: '实测剪切长度6'
        },
        {
          key: 'MEAS_LEN7',
          label: '实测剪切长度7'
        },
        {
          key: 'MEAS_LEN8',
          label: '实测剪切长度8'
        },
        {
          key: 'MEAS_LEN9',
          label: '实测剪切长度9'
        },
        {
          key: 'MEAS_LEN10',
          label: '实测剪切长度10'
        },
        {
          key: 'CUT_AUTO',
          label: '模式'
        },
        {
          key: 'CREW',
          label: '班次'
        },
        {
          key: 'SHIFT',
          label: '班别'
        },
        {
          key: 'FLAG',
          label: '标志'
        }
        /*
        * （0-B模式，1-C模式）
1-白班，2-中板，3-夜班
1-甲班，2-乙班，3-丙班，4丁班
（1设定，2实绩）
        * */
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
            table: '13',
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
