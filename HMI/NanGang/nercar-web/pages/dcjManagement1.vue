<template>
  <div>
    <el-row style="margin-bottom: 20px">
      <el-row>
        <el-col :span="24">
          <el-form
            :inline="true"
            :model="searchData"
            class="topForm">
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
            <div class="flex_ful">
              <p class="title-p">
                1#定尺剪报表
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
            <!-- <ManagementTable
              :table-data="tableData"
              :table-columns="tableColumns"
              :loading="loading"
            />
            <simple-pagination
              :page-size="pagination.pageSize"
              :total="pagination.total"
              :align="pagination.align"
              :current-page="pagination.currentPage"
              layout="total, prev, pager, next,jumper"
              @handleSizeChangeFn="handleSizeChange"
              @handleCurrentChangeFn="handleCurrentChange"
            /> -->
            <el-row
              v-show="isTrue==0"
              style="margin-bottom: 20px">
              <el-table
                v-loading="loading"
                :data="tableData"
                :cell-style="{borderRight:'1px solid #777',borderBottom:'1px solid #777',borderLeft:'1px solid #777'}"
                :header-cell-style="{border:'1px solid #777'}"
                border
                style="width: 100%;border-right:1px solid #777;border-bottom:1px solid #777">
                <el-table-column
                  align="center"
                  label="序号"
                  type="index"
                  fixed="left"
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
                  prop="ENDS_TIME"/>
                <!-- <el-table-column
                  align="center"
                  label="离开定尺剪时间"
                  width="150"
                  prop="EXDS_TIME"/> -->
                <!-- <el-table-column
                  align="center"
                  label="母板长度"
                  prop="L1_DSS_PLATELEN"/> -->
                <el-table-column
                  align="center"
                  label="实际长度"
                  prop="LEN_MEAS"/>
                <el-table-column
                  align="center"
                  label="母板宽度"
                  prop="L1_DSS_PLATEWID"/>
                <el-table-column
                  align="center"
                  label="母板厚度"
                  prop="L1_DSS_PLATETHK">
                  <template slot-scope="scope">
                    <div>{{ scope.row.L1_DSS_PLATETHK }}</div>
                  </template>
                </el-table-column>
                <el-table-column
                  align="center"
                  label="曲阜强度"
                  prop="L1_DSS_STRENGTH"/>
                <el-table-column
                  align="center"
                  label="定尺剪刀数"
                  prop="DS_SSNUM"/>
                <el-table-column
                  align="center"
                  label="实际剪切长度"
                  prop="L2_DSS_STRENGTH">
                  <el-table-column
                    align="center"
                    label="切头"
                    prop="L1_DSS_SETLEN1">
                    <template slot-scope="scope">
                      <div>{{ scope.row.L1_DSS_SETLEN1 }}</div>
                    </template>
                  </el-table-column>
                  <el-table-column
                    align="center"
                    label="1"
                    prop="L1_DSS_SETLEN2">
                    <template slot-scope="scope">
                      <div>{{ scope.row.L1_DSS_SETLEN2 }}</div>
                    </template>
                  </el-table-column>
                  <el-table-column
                    align="center"
                    label="2"
                    prop="L1_DSS_SETLEN3">
                    <template slot-scope="scope">
                      <div>{{ scope.row.L1_DSS_SETLEN3 }}</div>
                    </template>
                  </el-table-column>
                  <el-table-column
                    align="center"
                    label="3"
                    prop="L1_DSS_SETLEN4">
                    <template slot-scope="scope">
                      <div>{{ scope.row.L1_DSS_SETLEN4 }}</div>
                    </template>
                  </el-table-column>
                  <el-table-column
                    align="center"
                    label="4"
                    prop="L1_DSS_SETLEN5"/>
                  <el-table-column
                    align="center"
                    label="5"
                    prop="L1_DSS_SETLEN6"/>
                  <el-table-column
                    align="center"
                    label="6"
                    prop="L1_DSS_SETLEN7"/>
                  <el-table-column
                    align="center"
                    label="7"
                    prop="L1_DSS_SETLEN8"/>
                  <el-table-column
                    align="center"
                    label="8"
                    prop="L1_DSS_SETLEN9"/>
                  <el-table-column
                    align="center"
                    label="9"
                    prop="L1_DSS_SETLEN10"/>
                  <el-table-column
                    align="center"
                    label="10"
                    prop="L1_DSS_SETLEN11"/>
                </el-table-column>
              </el-table>
            </el-row>
            <el-row
              v-show="isTrue==1"
              style="margin-bottom: 20px" >
              <el-table
                v-loading="loading"
                :data="tableData"
                :cell-style="{borderRight:'1px solid #777',borderBottom:'1px solid #777',borderLeft:'1px solid #777'}"
                :header-cell-style="{border:'1px solid #777'}"
                border
                style="width: 100%;border-right:1px solid #777;border-bottom:1px solid #777">
                <el-table-column
                  align="center"
                  label="序号"
                  fixed="left"
                  type="index"
                  width="60"/>
                <el-table-column
                  align="center"
                  label="母板号"
                  fixed="left"
                  width="150"
                  prop="PLATENO"/>
                <el-table-column
                  align="center"
                  label="进入双边剪时间"
                  width="150"
                  prop="ENDS_TIME"/>
                <!-- <el-table-column
                  align="center"
                  label="离开双边剪时间"
                  width="150"
                  prop="EXDS_TIME"/> -->
                <!-- <el-table-column
                  align="center"
                  label="设定母板长度"
                  prop="L2_DSS_PLATELEN"/> -->
                <el-table-column
                  align="center"
                  label="实际长度"
                  prop="LEN_MEAS"/>
                <el-table-column
                  align="center"
                  label="设定母板宽度"
                  prop="L2_DSS_PLATEWID"/>
                <el-table-column
                  align="center"
                  label="设定母板厚度"
                  prop="L2_DSS_PLATETHK">
                  <template slot-scope="scope">
                    <div>{{ Number(scope.row.L2_DSS_PLATETHK).toFixed(3) }}</div>
                  </template>
                </el-table-column>
                <el-table-column
                  align="center"
                  label="设定曲阜强度"
                  prop="L2_DSS_STRENGTH"/>
                <el-table-column
                  align="center"
                  label="设定剪切长度"
                  prop="L2_DSS_STRENGTH">
                  <!-- <template slot-scope="scope">
                    <div>{{ scope.row.L2_DSS_SETLEN5 }}</div>
                  </template> -->
                  <el-table-column
                    align="center"
                    label="切头"
                    prop="L2_DSS_SETLEN1"/>
                  <el-table-column
                    align="center"
                    label="1"
                    prop="L2_DSS_SETLEN2"/>
                  <el-table-column
                    align="center"
                    label="2"
                    prop="L2_DSS_SETLEN3"/>
                  <el-table-column
                    align="center"
                    label="3"
                    prop="L2_DSS_SETLEN4"/>
                  <el-table-column
                    align="center"
                    label="4"
                    prop="L2_DSS_SETLEN5">
                    <template slot-scope="scope">
                      <div>{{ scope.row.L2_DSS_SETLEN5 }}</div>
                    </template>
                  </el-table-column>
                  <el-table-column
                    align="center"
                    label="5"
                    prop="L2_DSS_SETLEN6"/>
                  <el-table-column
                    align="center"
                    label="6"
                    prop="L2_DSS_SETLEN7"/>
                  <el-table-column
                    align="center"
                    label="7"
                    prop="L2_DSS_SETLEN8"/>
                  <el-table-column
                    align="center"
                    label="8"
                    prop="L2_DSS_SETLEN9"/>
                  <el-table-column
                    align="center"
                    label="9"
                    prop="L2_DSS_SETLEN10"/>
                  <el-table-column
                    align="center"
                    label="10"
                    prop="L2_DSS_SETLEN11"/>
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
  name: 'LcManagement',
  components: { ManagementTable, simplePagination },
  data() {
    return {
      loading: false,
      isTrue: 0,
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
        pageSize: 12,
        total: 0
      },
      tableData: [],
      tableColumns: [
        {
          key: 'PLATENO',
          label: '母板号'
        },
        {
          key: 'THK_MEAS',
          label: '实测厚度'
        },
        {
          key: 'LEN_MEAS',
          label: '实测长度'
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
          key: 'ENDS_TIME',
          label: '进入定尺剪时间'
        },
        {
          key: 'EXDS_TIME',
          label: '离开定尺剪时间'
        },
        {
          key: 'DS_SSNUM',
          label: '定尺剪刀数'
        },
        {
          key: 'L2_DSS_PLATELEN',
          label: '定尺剪设定母板长度'
        },
        {
          key: 'L2_DSS_PLATEWID',
          label: '定尺剪设定母板宽度'
        },
        {
          key: 'L2_DSS_PLATETHK',
          label: '定尺剪设定母板厚度'
        },
        {
          key: 'L2_DSS_SETLEN1',
          label: '定尺剪设定剪切长度1'
        },
        {
          key: 'L2_DSS_SETLEN2',
          label: '定尺剪设定剪切长度2'
        },
        {
          key: 'L2_DSS_SETLEN3',
          label: '定尺剪设定剪切长度3'
        },
        {
          key: 'L2_DSS_SETLEN4',
          label: '定尺剪设定剪切长度4'
        },
        {
          key: 'L2_DSS_SETLEN5',
          label: '定尺剪设定剪切长度5'
        },
        {
          key: 'L2_DSS_SETLEN6',
          label: '定尺剪设定剪切长度6'
        },
        {
          key: 'L2_DSS_SETLEN7',
          label: '定尺剪设定剪切长度7'
        },
        {
          key: 'L2_DSS_SETLEN8',
          label: '定尺剪设定剪切长度8'
        },
        {
          key: 'L2_DSS_SETLEN9',
          label: '定尺剪设定剪切长度9'
        },
        {
          key: 'L2_DSS_SETLEN10',
          label: '定尺剪设定剪切长度10'
        },
        {
          key: 'L2_DSS_SETLEN11',
          label: '定尺剪设定剪切长度11'
        },
        {
          key: 'L1_DSS_PLATELEN',
          label: '一级投用定尺剪设定母板长度'
        },
        {
          key: 'L1_DSS_PLATEWID',
          label: '一级投用定尺剪设定母板宽度'
        },
        {
          key: 'L1_DSS_PLATETHK',
          label: '一级投用定尺剪设定母板厚度'
        },
        {
          key: 'L1_DSS_STRENGTH',
          label: '一级投用定尺剪设定曲阜强度'
        },
        {
          key: 'L1_DSS_SETLEN1',
          label: '一级投用定尺剪设定剪切长度1'
        },
        {
          key: 'L1_DSS_SETLEN2',
          label: '一级投用定尺剪设定剪切长度2'
        },
        {
          key: 'L1_DSS_SETLEN3',
          label: '一级投用定尺剪设定剪切长度3'
        },
        {
          key: 'L1_DSS_SETLEN4',
          label: '一级投用定尺剪设定剪切长度4'
        },
        {
          key: 'L1_DSS_SETLEN5',
          label: '一级投用定尺剪设定剪切长度5'
        },
        {
          key: 'L1_DSS_SETLEN6',
          label: '一级投用定尺剪设定剪切长度6'
        },
        {
          key: 'L1_DSS_SETLEN7',
          label: '一级投用定尺剪设定剪切长度7'
        },
        {
          key: 'L1_DSS_SETLEN8',
          label: '一级投用定尺剪设定剪切长度8'
        },
        {
          key: 'L1_DSS_SETLEN9',
          label: '一级投用定尺剪设定剪切长度9'
        },
        {
          key: 'L1_DSS_SETLEN10',
          label: '一级投用定尺剪设定剪切长度10'
        },
        {
          key: 'L1_DSS_SETLEN11',
          label: '一级投用定尺剪设定剪切长度11'
        },
        {
          key: 'DS_AUT_C',
          label: 'C模式'
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
            table: '3',
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
          res.results[0].forEach(item => {
            if (item.CREW == 1) {
              item.CREW = '甲班'
            } else if (item.CREW == 2) {
              item.CREW = '乙班'
            } else if (item.CREW == 3) {
              item.CREW = '丙班'
            } else if (item.CREW == 4) {
              item.CREW = '丁班'
            }
            if (item.SHIFT == 1) {
              item.SHIFT = '早班'
            } else if (item.SHIFT == 2) {
              item.SHIFT = '中班'
            } else if (item.SHIFT == 3) {
              item.SHIFT = '晚班'
            }
          })
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
.topForm {
  text-align: left;
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
/deep/ .el-table {
  .el-table__fixed-header-wrapper {
    .el-checkbox__inner {
      display: none !important;
    }
  }
}
</style>
<style>
.el-table th {
  display: table-cell !important;
}
</style>
