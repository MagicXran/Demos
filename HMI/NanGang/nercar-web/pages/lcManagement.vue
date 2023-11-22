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
          <el-form-item label="冷床位置">
            <el-select
              v-model="searchData.cb"
              style="width: 160px"
              clearable
              placeholder="请选择冷床"
            >
              <el-option
                :value="1"
                label="1#冷床"/>
              <el-option
                :value="2"
                label="2#冷床"/>
              <el-option
                :value="3"
                label="3#冷床"/>
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
          <p class="title-p">
            冷床报表
          </p>
          <!-- <ManagementTable
            :table-data="tableData"
            :table-columns="tableColumns"
            :loading="loading"
          /> -->
          <el-row style="margin-bottom: 20px">
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
                v-for="(item, index) in tableColumns"
                :key="index"
                :prop="item.key"
                :label="item.label"
                align="center"/>
              <el-table-column
                align="center"
                label="上冷床温度"
                width="150">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.ENCB_TEMP).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="下冷床温度"
                width="150">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.EXCB_TEMP).toFixed(3) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="冷床流向"
                width="100">
                <template slot-scope="scope">
                  <div>{{ scope.row.CB_DEC==1?'1#冷床':scope.row.CB_DEC==2?'2#冷床':scope.row.CB_DEC==3?'3#冷床': '' }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="精整流向"
                width="100">
                <template slot-scope="scope">
                  <div>{{ scope.row.EX_DEC==4?'1#线':scope.row.EX_DEC==6?'2#线':'' }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="班次"
                width="100">
                <template slot-scope="scope">
                  <div>{{ scope.row.SHIFT ==1?'早班':scope.row.SHIFT==2?'中班':scope.row.SHIFT==3?'晚班': '' }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="班别"
                width="100">
                <template slot-scope="scope">
                  <div>{{ scope.row.CREW==1?'甲班':scope.row.CREW==2?'乙班':scope.row.CREW==3?'丙班': scope.row.CREW==4?'丁班':'' }}</div>
                </template>
              </el-table-column>
            </el-table>
          </el-row>
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
      loading: false,
      searchData: {
        start_time: '',
        end_time: '',
        cb: '',
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
          label: '钢板号'
        },
        // {
        //   key: 'THK_MEAS',
        //   label: '实测厚度'
        // },
        // {
        //   key: 'LEN_MEAS',
        //   label: '实测长度'
        // },
        // {
        //   key: 'WID_MEAS',
        //   label: '实测宽度'
        // },
        // {
        //   key: 'CREATETIME',
        //   label: '上线时间'
        // },
        {
          key: 'ENCB_TIME',
          label: '上冷床时间'
        },
        {
          key: 'EXCB_TIME',
          label: '下冷床时间'
        },
        {
          key: 'CAL_CB_TIME',
          label: '计算降温时间'
        },
        {
          key: 'ACT_CB_TIME',
          label: '实际降温时间'
        }
        // {
        //   key: 'ENCB_TEMP',
        //   label: '上冷床温度'
        // },
        // {
        //   key: 'EXCB_TEMP',
        //   label: '下冷床温度'
        // },
        // {
        //   key: 'DDS_SHEARFLAG',
        //   label: '分段剪'
        // },
        // {
        //   key: 'CB_DEC',
        //   label: '冷床流向'
        // },
        // {
        //   key: 'EX_DEC',
        //   label: '精整流向'
        // },
        // {
        //   key: 'CREW',
        //   label: '班次'
        // },
        // {
        //   key: 'SHIFT',
        //   label: '班别'
        // }
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
      if (this.searchData.start_time == null) {
        this.searchData.start_time = ''
      }
      if (this.searchData.end_time == null) {
        this.searchData.end_time = ''
      }
      let data = [
        [
          {
            table: '1',
            start_time: this.searchData.start_time + '',
            end_time: this.searchData.end_time + '',
            cb: this.searchData.cb,
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
<style>
.el-table th {
  display: table-cell !important;
}
</style>
