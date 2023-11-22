<template>
  <div>
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
              1#子板报表
            </p>
            <!-- <ManagementTable
              :table-data="tableData"
              :table-columns="tableColumns"
              :loading="loading"
            /> -->
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
                label="子板号"
                width="150"
                fixed="left"
                prop="PLATENO"/>
              <el-table-column
                align="center"
                label="下线时间"
                width="150"
                prop="OFFTIME"/>
              <el-table-column
                align="center"
                label="剪切长度"
                width="150"
                prop="PLATE_DSLEN"/>
              <el-table-column
                align="center"
                label="计划长度"
                width="150"
                prop="PLATE_LEN"/>
              <!-- <el-table-column
                align="center"
                label="表检时间"
                width="150"
                prop="SIS_TIME"/> -->
              <el-table-column
                align="center"
                label="表检设定钢板号"
                width="150"
                prop="SIS_PLATRNO"/>
              <el-table-column
                align="center"
                label="表检设定钢种"
                prop="SIS_STEELGRADE"/>
              <el-table-column
                align="center"
                label="表检设定长度"
                prop="SIS_PLATELEN">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.SIS_PLATELEN).toFixed(1) }}</div>
                </template>
              </el-table-column>
              <el-table-column
                align="center"
                label="表检设定宽度"
                prop="SIS_PLATEWID"/>
              <el-table-column
                align="center"
                label="表检设定厚度"
                prop="SIS_PLATETHK">
                <template slot-scope="scope">
                  <div>{{ Number(scope.row.SIS_PLATETHK).toFixed(1) }}</div>
                </template>
              </el-table-column>
              <!-- <el-table-column
                align="center"
                label="标印时间"
                prop="ENMARK_TIME">
                <template slot-scope="scope">
                  <div>{{ scope.row.ENMARK_TIME }}</div>
                </template>
              </el-table-column> -->
              <!-- <el-table-column
                align="center"
                label="剁扳机设定钢板号"
                width="150"
                prop="PILER_PLATENO">
                <template slot-scope="scope">
                  <div>{{ scope.row.PILER_PLATENO }}</div>
                </template>
              </el-table-column> -->
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
  name: 'LcManagement',
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
          label: '子板号'
        },
        {
          key: 'OFFTIME',
          label: '下线时间'
        },
        {
          key: 'SIS_TIME',
          label: '表检时间'
        },
        {
          key: 'SIS_PLATRNO',
          label: '表检设定钢板号'
        },
        {
          key: 'SIS_STEELGRADE',
          label: '表检设定钢种'
        },
        {
          key: 'SIS_PLATELEN',
          label: '表检设定长度'
        },
        {
          key: 'SIS_PLATEWID',
          label: '表检设定宽度'
        },
        {
          key: 'SIS_PLATETHK',
          label: '表检设定厚度'
        },
        {
          key: 'ENMARK_TIME',
          label: '标印时间'
        },
        {
          key: 'PILER_PLATENO',
          label: '剁扳机设定钢板号'
        },
        {
          key: 'CREW',
          label: '班次'
        },
        {
          key: 'SHIFT',
          label: '班别'
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
      if (this.searchData.start_time == null) {
        this.searchData.start_time = ''
      }
      if (this.searchData.end_time == null) {
        this.searchData.end_time = ''
      }
      let data = [
        [
          {
            table: '4',
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
<style>
.el-table th {
  display: table-cell !important;
}
</style>
