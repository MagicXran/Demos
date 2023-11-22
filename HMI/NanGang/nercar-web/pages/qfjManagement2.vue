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
              二线标印实绩表
            </p>
            <el-table
              v-loading="loading"
              :data="tableData"
              :empty-text="'暂无数据'"
              :header-cell-style="{border: '1px solid #777',background:'#f5f7fa'}"
              :cell-style="{border: 'solid 1px #777',borderTop:'0px'}"
              style="width: 100%;"
              row-key="PLATE_NO"
              border
              default-expand-all
              class="eltablecss"
              height="810">
              <el-table-column
                type="index"
                align="center"
                width="40"/>
              <el-table-column
                prop="PLATENO"
                label="钢板号"
                width="150"
                align="center"/>
              <!-- <el-table-column
                prop=""
                label="产品分类"
                align="center">
                <template slot-scope="scope">
                  <span v-if="scope.row.PLATE_TYPE == 1">板坯</span>
                  <span v-if="scope.row.PLATE_TYPE == 2">母板</span>
                  <span v-if="scope.row.PLATE_TYPE == 3">子板</span>
                  <span v-if="scope.row.PLATE_TYPE == 4">子母板</span>
                </template>
              </el-table-column> -->
              <el-table-column
                :show-overflow-tooltip="true"
                prop="PRINT_TIME"
                label="标印时间"
                width="150"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="SURSPR_1"
                width="160"
                label="表喷1"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="SURSPR_2"
                width="180"
                label="表喷2"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="SURSPR_3"
                width="210"
                label="表喷3"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="SURSPR_4"
                label="表喷4"
                width="60"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="EMBSTAMP_1"
                label="冲印1"
                width="200"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="EMBSTAMP_2"
                label="冲印2"
                width="60"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="EMBSTAMP_3"
                label="冲印3"
                width="60"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="EMBSTAMP_4"
                label="冲印4"
                width="60"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="SIDESPRAY"
                label="侧喷内容"
                width="200"
                align="center"/>
              <el-table-column
                :show-overflow-tooltip="true"
                prop="LASER_QR_CODE"
                width="200"
                label="激光二维码内容"
                align="center"/>
              <!-- <el-table-column
                prop="PLATE_WGT"
                label="重量"
                width="65"
                align="center">
                <template slot-scope="scope">
                  <div>
                    {{ (scope.row.PLATE_WGT || 0).toFixed(3) }}
                  </div>
                </template>
              </el-table-column> -->
              <el-table-column
                prop="HAMMER_LOGO"
                label="双锤商标"
                align="center"/>
              <el-table-column
                prop="PAINT_LOGO"
                label="表喷认证1"
                width="60"
                align="center"/>
              <el-table-column
                prop="PAINT_LOGO2"
                label="表喷认证2"
                width="60"
                align="center"/>
              <el-table-column
                prop="PAINT_LOGO3"
                label="表喷认证3"
                width="60"
                align="center"/>
              <el-table-column
                prop="COMP"
                width="60"
                label="船徽1"
                align="center"/>
              <el-table-column
                prop="COMP2"
                width="60"
                label="船徽2"
                align="center"/>
              <el-table-column
                prop="COMP3"
                width="60"
                label="船徽3"
                align="center"/>
              <el-table-column
                prop="COMP4"
                label="船徽4"
                width="60"
                align="center"/>
              <el-table-column
                prop="PUNCH_LOGO"
                width="60"
                label="冲印认证1"
                align="center"/>
              <el-table-column
                prop="PUNCH_LOGO2"
                label="冲印认证2"
                width="60"
                align="center"/>
              <el-table-column
                prop="PUNCH_LOGO3"
                label="冲印认证3"
                width="60"
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
    </el-row>
  </div>
</template>

<script>
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
        pageSize: 18,
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
            table: '25',
            start_time: this.searchData.start_time + '',
            end_time: this.searchData.end_time + '',
            plateno: this.searchData.plateno,
            pageNo: this.pagination.currentPage,
            pageSize: this.pagination.pageSize
          }
        ]
      ]
      sendMsg(data, 1825, 'HMI').then(res => {
        if (res.code == 200) {
          if (res.results[0][0].msg) {
            this.loading = false
            this.tableData = []
            this.$message({
              type: 'warning',
              message: res.results[0][0].msg
            })
            return
          }
          this.loading = false
          this.pagination.total = res.results[0][0].TotalCount
          let tabelData = []
          tabelData = res.results[0]
          this.tableData = tabelData
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
/*.eltablecss .el-table thead .tr .th {
  background: #b9c8c5 !important;
}*/
</style>
<style>
.el-table th {
  display: table-cell !important;
}
</style>
