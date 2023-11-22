<template>
  <el-row>
    <el-row style="margin-bottom: 20px">
      <el-col :span="18">
        <el-form
          :inline="true"
          :model="searchData">
          <el-form-item label="钢板号">
            <el-input
              v-model="searchData.plateno"
              style="width: 180px"
              placeholder="请输入钢板号">
              <i
                slot="suffix"
                class="el-input__icon"/>
            </el-input>
          </el-form-item>
          <el-form-item label="起始时间">
            <el-date-picker
              v-model="searchData.start_time"
              value-format="timestamp"
              type="datetime"
              placeholder="起始时间"/>
          </el-form-item>
          <el-form-item label="结束时间">
            <el-date-picker
              v-model="searchData.end_time"
              value-format="timestamp"
              type="datetime"
              placeholder="结束时间"/>
          </el-form-item>
        </el-form>
      </el-col>
      <el-col :span="6">
        <div class="btn-box">
          <el-button
            type="primary"
            size="medium"
            @click="getTableData"
          >查询
          </el-button>
        </div>
      </el-col>
    </el-row>
    <el-row :gutter="20">
      <el-col
        :span="8"
        class="">
        <div class="img-box">
          <div class="bgc-white img-item">
            <p class="title-p">
              停止时照片
            </p>
            <div>
              <img
                :src="imgMap.stopImgUrl"
                style="display: block;width: 100%;"
                alt="">
            </div>
          </div>
          <div class="bgc-white img-item">
            <p class="title-p">
              剪切时照片
            </p>
            <div>
              <img
                :src="imgMap.cutImgUrl"
                style="display: block;width: 100%;"
                alt="">
            </div>
          </div>
        </div>
      </el-col>
      <el-col
        :span="16"
        class="bgc-white">
        <div class="table-box">
          <p class="title-p">
            剪切长度
          </p>
          <div>
            <el-table
              v-loading="loading"
              :data="tableData"
              border
              style="width: 100%"
              @row-click="rowClick">
              <el-table-column
                align="center"
                label="序号"
                type="index"
                width="60"/>
              <el-table-column
                prop="TIME_START"
                label="时间"
                align="center"/>
              <el-table-column
                prop="STEEL_ID"
                label="钢板号"
                align="center"/>
              <el-table-column
                prop="LEN_TARGET"
                label="目标长度"
                align="center"/>
              <el-table-column
                prop="LEN_STOPED"
                label="停止时长度"
                align="center"/>
              <el-table-column
                prop="LEN_CUT"
                label="剪切时长度"
                align="center"/>
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
        </div>
      </el-col>
    </el-row>
  </el-row>
</template>

<script>
import HmiTable from '@/components/HmiTable'
import simplePagination from '@/components/simplePagination'
import { getHmiData, sendMsg, sendTag, stopGetData } from '@/lib/GetData'

export default {
  name: 'DcjHistory',
  components: { HmiTable, simplePagination },
  data() {
    return {
      loading: false,
      imgMap: {
        stopImgUrl: '',
        cutImgUrl: ''
      },
      tableData: [],
      searchData: {
        start_time: '',
        end_time: '',
        plateno: ''
      },
      pagination: {
        align: 'right',
        currentPage: 1,
        pageSizes: [10, 20, 30, 40],
        pageSize: 10,
        total: 0
      }
    }
  },
  mounted() {
    this.getTableData()
  },
  destroyed() {},
  methods: {
    getTableData() {
      let data = [
        [
          {
            start_time: this.searchData.start_time + '',
            end_time: this.searchData.end_time + '',
            plateno: this.searchData.plateno,
            pageNo: this.pagination.currentPage,
            pageSize: this.pagination.pageSize
          }
        ]
      ]
      sendMsg(data, 1831, 'HMI').then(res => {
        if (res.code == 200) {
          this.loading = false
          this.pagination.total = res.results[0][0].TotalCount
          this.tableData = res.results[0]
          this.getImgList(res.results[0][0])
        }
      })
    },
    getImgList(imgList) {
      this.imgMap.stopImgUrl =
        imgList.SERVERIP_STOPED + imgList.IMAGENAME_STOPED
      this.imgMap.cutImgUrl = imgList.SERVERIP_CUT + imgList.IMAGENAME_CUT
    },
    rowClick(row, column, event) {
      this.getImgList(row)
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
/deep/ .el-input-p .el-input__inner {
  height: 32px;
  line-height: 32px;
}

/deep/ .el-input-p .el-input__icon {
  line-height: 32px;
}

.btn-box {
  float: right;
  padding-right: 40px;
}

.bgc-white {
  background-color: #fff;
  box-shadow: 0px 0px 4px rgb(0 0 0 / 4%), 0px 0px 16px -2px rgb(0 0 0 / 10%);
  border-radius: 6px;
  padding: 20px !important;
}

.img-box {
  .img-item {
    height: 400px;
    width: 100%;
    margin-bottom: 20px;
  }
}

.table-box {
}

.title-p {
  font-size: 16px;
  color: #606266;
  font-weight: bold;
  font-family: 'Microsoft YaHei UI';
  margin-bottom: 15px;
}
</style>
