<template>
  <div>
    <el-row>
      <el-col
        :span="24"
        style="display: flex;flex-direction: row-reverse;">
        <el-button
          :disabled="buttonFlag"
          type="primary"
          icon="el-icon-plus"
          size="small"
          @click="addTe()">添加</el-button>
        <el-button
          type="primary"
          size="small"
          style="margin-right: 20px"
          icon="el-icon-refresh"
          @click="refreshTableData()"
        >刷新</el-button>
      </el-col>
    </el-row>
    <el-row style="margin-top: 20px">
      <el-table
        :data="tableData"
        border
        style="width: 100%">
        <el-table-column
          align="center"
          label="序号"
          type="index"
          width="80"/>
        <el-table-column
          v-for="(item, index) in tableColumns"
          :key="index"
          :prop="item.key"
          :label="item.label">
          <template slot-scope="scope">
            <span v-if="item.key == 'DSS_THK_FIX'">
              {{ scope.row[item.key] == 1 ? '偏差' : '固定' }}
            </span>
            <span v-else-if="item.key == 'DSS_WID_FIX'">
              {{ scope.row[item.key] == 1 ? '偏差' : '固定' }}
            </span>
            <span v-else-if="item.key == 'THK_CODE'">
              {{ scope.row[item.key] }}
            </span>
            <!-- LEN_MODE -->
            <span v-else-if="item.key == 'THK_GAP_MODE' || item.key == 'THK_COINCID_MODE' || item.key == 'WID_MODE'||item.key == 'LEN_MODE'||item.key == 'THK_MODE'">
              {{ scope.row[item.key] == 1 ? '固定值' : scope.row[item.key] == 2 ? '加减' : '乘除' }}
            </span>
            <span v-else-if="item.key == 'THK_GAP'">
              {{ Number(scope.row[item.key]).toFixed(2) }}
            </span>
            <span v-else>
              {{ scope.row[item.key] }}
            </span>
          </template>
        </el-table-column>
        <el-table-column
          width="160"
          prop=""
          label="操作">
          <template slot-scope="scope">
            <el-button
              :disabled="buttonFlag"
              type="primary"
              style="margin-left: 10px"
              size="mini"
              @click="updateItem(scope.row)"
            >修 改</el-button>
            <el-button
              :disabled="buttonFlag"
              size="mini"
              @click="deleteItem(scope.row)"
            >删 除</el-button>
          </template>
        </el-table-column>
      </el-table>
    </el-row>

    <el-dialog
      :visible.sync="dialogFormVisibleUpdate"
      :title="'修改-  '+activeName"
      width="50%">
      <el-form :model="formUpdateList">
        <el-form-item
          v-for="(item, index) in tableColumns"
          :key="index"
          :label="item.label"
          label-width="180px">
          <template slot-scope="scope">
            <template v-if="item.key == 'GROUP_STEEL' && activeTableIndex == 1">
              <el-select
                v-model="formUpdateList[item.key]"
                placeholder="请选择">
                <el-option
                  v-for="(it, idx) in steelGroupList"
                  :key="idx"
                  :label="it['GRADE']"
                  :value="it['GRADE']"/>
              </el-select>
            </template>
            <template v-else-if="item.key == 'DSS_THK_FIX'">
              <el-select
                v-model="formUpdateList[item.key]"
                placeholder="请选择">
                <el-option
                  :value="1"
                  label="偏差"/>
                <el-option
                  :value="2"
                  label="固定"/>
              </el-select>
            </template>
            <template v-else-if="item.key == 'DSS_WID_FIX'">
              <el-select
                v-model="formUpdateList[item.key]"
                placeholder="请选择">
                <el-option
                  :value="1"
                  label="偏差"/>
                <el-option
                  :value="2"
                  label="固定"/>
              </el-select>
            </template>
            <template v-else-if="item.key == 'HTL'|| item.key == 'HTL_FLAG'">
              <el-select
                v-model="formUpdateList[item.key]"
                placeholder="请选择">
                <el-option
                  :value="'Q'"
                  label="Q"/>
                <el-option
                  :value="'-'"
                  label="-"/>
              </el-select>
            </template>
            <template v-else-if="item.key == 'THK_GAP_MODE' || item.key == 'THK_COINCID_MODE' || item.key == 'WID_MODE'||item.key == 'LEN_MODE'||item.key == 'THK_MODE'">
              <el-select
                v-model="formUpdateList[item.key]"
                placeholder="请选择">
                <el-option
                  :value="1"
                  label="固定值"/>
                <el-option
                  :value="2"
                  label="加减"/>
                <el-option
                  :value="3"
                  label="乘除"/>
              </el-select>
            </template>
            <template
              v-else
            >
              <el-input
                v-model="formUpdateList[item.key]"
                autocomplete="off"/>
            </template>
          </template>
        </el-form-item>
      </el-form>
      <div
        slot="footer"
        class="dialog-footer">
        <el-button @click="dialogFormVisibleUpdate = false">取 消</el-button>
        <el-button
          type="primary"
          @click="updateSubmit()">确 定</el-button>
      </div>
    </el-dialog>
  </div>
</template>

<script>
import {
  getHmiData,
  stopGetData,
  sendMsg,
  sendTag,
  getHmiDataByEvent
} from '@/lib/GetData'
export default {
  name: 'TabPane',
  props: {
    activeTableIndex: {
      type: Number,
      default: 0
    },
    buttonFlag: {
      type: Boolean,
      default: true
    },
    activeName: {
      type: String,
      default: ''
    },
    index: {
      type: String,
      default: 'first'
    },
    tableData: {
      type: Array,
      default: () => {
        return []
      }
    },
    tableColumns: {
      type: Array,
      default: () => {
        return []
      }
    }
  },
  data() {
    return {
      dialogFormVisibleUpdate: false,
      formUpdateList: [], //显示数据
      steelGroupList: []
    }
  },
  mounted() {},
  methods: {
    addTe() {
      this.$emit('addTeByson')
    },
    refreshTableData() {
      this.$emit('refreshTableData')
    },
    deleteItem(item) {
      this.$confirm('是否确定删除?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          let data = [
            [
              {
                table: this.activeTableIndex,
                ROWID: item.ROWID
              }
            ]
          ]
          sendMsg(data, 1824, 'HMI').then(res => {
            if (res.code == 200) {
              this.$message({
                type: 'success',
                message: '删除成功'
              })
              this.refreshTableData()
            }
          })
        })
        .catch(() => {
          this.$message({
            type: 'info',
            message: '已取消删除'
          })
        })
    },
    updateItem(item) {
      this.formUpdateList = item
      this.getSteelGroup()
      // this.formUpdateList = []
      this.dialogFormVisibleUpdate = true
    },
    updateSubmit() {
      this.formUpdateList.table = this.activeTableIndex
      let data = [[this.formUpdateList]]
      console.log(data)
      sendMsg(data, 1823, 'HMI').then(res => {
        if (res.code == 200) {
          this.$message({
            type: 'success',
            message: '更新成功'
          })
        }
        this.dialogFormVisibleUpdate = false
        this.refreshTableData()
      })
    },
    getSteelGroup() {
      let data = [{ tagName: 'L1DSSTECHGRADE', timestamp: 0 }]
      getHmiDataByEvent(data).then(res => {
        if (res.code == 200) {
          this.steelGroupList = res.results[0].value
        }
      })
    }
  }
}
</script>

<style scoped>
/deep/ .el-button--mini,
/deep/ .el-button--mini.is-round {
  padding: 4px 10px;
}
.el-form {
  display: flex;
  flex-wrap: wrap;
  justify-content: space-between;
}
.el-button--primary {
  background-color: #13356f;
  border-color: #13356f;
}

/deep/ .el-radio__input.is-disabled.is-checked .el-radio__inner {
  border-color: #409eff;
  background: #409eff;
}

/deep/ .el-table .cell {
  white-space: nowrap;
}
</style>
