<template>
  <div class="technologyManage">
    <template>
      <div class="login-box">
        <el-button
          size="small"
          type="warning"
          @click="login()">登 录</el-button>
        <el-button
          v-if="!buttonFlag"
          size="small"
          type="info"
          @click="logout()">注 销</el-button>
        <el-button
          v-if="!buttonFlag"
          type="success"
          size="mini"
          style="padding: 7px"
          icon="el-icon-check"
          circle/>
      </div>
      <el-tabs
        v-model="activeName"
        class="bgc-white"
        @tab-click="handleClick">

        <el-tab-pane
          v-for="(item, index) in tableDataList"
          :key="index"
          :label="item.title"
          :name="item.title"
        >
          <TablePane
            :active-table-index="activeTableIndex"
            :active-name="activeName"
            :table-data="item.tableData"
            :table-columns="item.tableColumns"
            :button-flag="buttonFlag"
            @addTeByson="addTe(item.title)"
            @refreshTableData="getTableData"
          />
        </el-tab-pane>
      </el-tabs>
    </template>

    <el-dialog
      :visible.sync="dialogFormVisibleAdd"
      :title="dialogTitle +'--'+ dialogType"
      width="50%">
      <el-form :model="formAdd">
        <el-form-item
          v-for="(item, index) in tableDataList[activeIndex].tableColumns"
          :key="index"
          :label="item.label"
          label-width="180px">
          <template slot-scope="scope">
            <template v-if="item.key == 'GROUP_STEEL' && activeTableIndex == 1">
              <el-select
                v-model="formAdd[item.key]"
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
                v-model="formAdd[item.key]"
                placeholder="请选择">
                <el-option
                  label="偏差"
                  value="1"/>
                <el-option
                  label="固定"
                  value="2"/>
              </el-select>
            </template>
            <template v-else-if="item.key == 'DSS_WID_FIX'">
              <el-select
                v-model="formAdd[item.key]"
                placeholder="请选择">
                <el-option
                  label="偏差"
                  value="1"/>
                <el-option
                  label="固定"
                  value="2"/>
              </el-select>
            </template>
            <template v-else-if="item.key == 'HTL' || item.key == 'HTL_FLAG'">
              <el-select
                v-model="formAdd[item.key]"
                placeholder="请选择">
                <el-option
                  label="Q"
                  value="Q"/>
                <el-option
                  label="-"
                  value="-"/>
              </el-select>
            </template>
            <template v-else-if="item.key == 'THK_GAP_MODE' || item.key == 'THK_COINCID_MODE' || item.key == 'WID_MODE'||item.key == 'LEN_MODE'||item.key == 'THK_MODE'">
              <el-select
                v-model="formAdd[item.key]"
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
            <template v-else>
              <el-input
                v-model="formAdd[item.key]"
                autocomplete="off"/>
            </template>
          </template>
        </el-form-item>
      </el-form>
      <div
        slot="footer"
        class="dialog-footer">
        <el-button @click="dialogFormVisibleAdd = false">取 消</el-button>
        <el-button
          type="primary"
          @click="addSubmit()">确 定</el-button>
      </div>
    </el-dialog>
    <!--    登录校验-->
    <el-dialog
      :visible.sync="dialogFormVisibleLogin"
      width="30%"
      title="登录校验">
      <el-form
        ref="formLogin"
        :model="formLogin"
        :rules="loginRules">
        <el-form-item
          :label-width="formLoginLabelWidth"
          prop="name"
          label="姓名">
          <el-input
            v-model="formLogin.name"
          />
        </el-form-item>
        <el-form-item
          :label-width="formLoginLabelWidth"
          prop="password"
          label="密码">
          <el-input
            v-model="formLogin.password"
            type="password"
          />
        </el-form-item>
      </el-form>
      <div
        slot="footer"
        class="dialog-footer">
        <el-button @click="resetForm()">取 消</el-button>
        <el-button
          v-loading.fullscreen.lock="fullscreenLoading"
          type="primary"
          @click="submitLogin()">确 定</el-button>
      </div>
    </el-dialog>
  </div>
</template>

<script>
import TablePane from '@/pages/components/TabPane'
// import userinfo from '@/lib/userinfo.json'
import {
  getHmiData,
  stopGetData,
  sendMsg,
  sendTag,
  getHmiDataByEvent
} from '@/lib/GetData'
export default {
  name: 'TechnologyManage',
  components: { TablePane },
  data() {
    return {
      fullscreenLoading: false,
      dialogFormVisibleLogin: false,
      formLogin: {
        name: '',
        password: ''
      },
      loginRules: {
        name: [{ required: true, message: '请输入姓名', trigger: 'blur' }],
        password: [{ required: true, message: '请输入密码', trigger: 'blur' }]
      },
      formLoginLabelWidth: '60px',
      buttonFlag: true, // true: 禁用 false 启用
      dialogType: '添加',
      dialogTitle: '',
      dialogFormVisibleAdd: false,
      formAdd: {},
      activeName: '钢种分组',
      allObjData: {
        钢种分组: {
          index: 0,
          tableIndex: 0
        },
        '1#线双边剪': {
          index: 1,
          tableIndex: 1
        },
        管线钢取样: {
          index: 2,
          tableIndex: 3
        },
        '1#线定尺剪': {
          index: 3,
          tableIndex: 2
        },
        '2#圆盘剪': {
          index: 4,
          tableIndex: 12
        },
        '2#定尺剪': {
          index: 5,
          tableIndex: 13
        },
        冷床模型分档: {
          index: 6,
          tableIndex: 21
        },
        冷床模型参数: {
          index: 7,
          tableIndex: 22
        }
      },
      steelGroupList: [],
      tableDataList: [
        {
          title: '钢种分组',
          tableData: [{}, {}, {}, {}],
          tableColumns: [
            {
              key: 'STEEL_GROUP',
              label: '钢种'
            },
            {
              key: 'GROUP_STEEL',
              label: '分组'
            }
          ]
        },
        {
          title: '1#线双边剪',
          tableData: [{}, {}, {}, {}],
          tableColumns: [
            {
              key: 'GROUP_STEEL',
              label: '钢种分组'
            },
            {
              key: 'HTL',
              label: '热处理标志'
            },
            {
              key: 'DSS_THK_MIN',
              label: '厚度下限'
            },
            {
              key: 'DSS_THK_MAX',
              label: '厚度上限'
            },
            {
              key: 'DSS_THK_FIX',
              label: '厚度规则选择'
            },
            {
              key: 'DSS_THK_SET',
              label: '厚度设定'
            },
            {
              key: 'DSS_WID_MIN',
              label: '宽度下限'
            },
            {
              key: 'DSS_WID_MAX',
              label: '宽度上限'
            },
            {
              key: 'DSS_WID_FIX',
              label: '宽度规则选择'
            },
            {
              key: 'DSS_WID_SET',
              label: '宽度偏差偏差'
            }
          ]
        },
        {
          title: '管线钢取样',
          tableData: [{}, {}, {}, {}],
          tableColumns: [
            {
              key: 'STEELGRADE',
              label: '钢种'
            },
            {
              key: 'HEAD_LEN1',
              label: '头部取样'
            },
            {
              key: 'HEAD_LEN2',
              label: '头部取样2'
            },
            {
              key: 'MID_LEN1',
              label: '中部取样'
            },
            {
              key: 'MID_LEN2',
              label: '中部取样2'
            },
            {
              key: 'TAIL_LEN1',
              label: '尾部取样'
            },
            {
              key: 'TAIL_LEN2',
              label: '尾部取样2'
            },
            {
              key: 'TAIL_LEN3',
              label: '尾部取样3'
            }
          ]
        },
        {
          title: '1#线定尺剪',
          tableData: [{}, {}, {}, {}],
          tableColumns: [
            {
              key: 'HTL',
              label: '热处理标志'
            },
            {
              key: 'DS_THK_MIN',
              label: '厚度下限'
            },
            {
              key: 'DS_THK_MAX',
              label: '厚度上限'
            },
            {
              key: 'DS_WID_MIN',
              label: '宽度下限'
            },
            {
              key: 'DS_WID_MAX',
              label: '宽度上限'
            },
            {
              key: 'DS_LEN_MIN',
              label: '长度下限'
            },
            {
              key: 'DS_LEN_MAX',
              label: '长度上限'
            },
            {
              key: 'DS_HTLEN_SETDIV',
              label: '头尾长度偏差设定'
            },
            {
              key: 'DS_LEN_SETDIV',
              label: '长度偏差设定'
            },
            {
              key: 'DS_ARC_SET1',
              label: '圆弧设定'
            },
            {
              key: 'DS_ARC_SET2',
              label: '圆弧设定2'
            },
            {
              key: 'DS_THK_SETDIV',
              label: '厚度设定偏差'
            },
            {
              key: 'DS_WID_SETDIV',
              label: '宽度偏差偏差'
            }
          ]
        },
        {
          title: '2#圆盘剪',
          tableData: [{}, {}, {}, {}],
          tableColumns: [
            {
              key: 'HTL_FLAG',
              label: '热处理板'
            },
            {
              key: 'THK_GAP_MIN',
              label: '厚度最小值mm'
            },
            {
              key: 'THK_GAP_MAX',
              label: '厚度最大值mm'
            },
            {
              key: 'THK_GAP_MODE',
              label: '厚度（间隙）规则'
            },
            {
              key: 'THK_GAP',
              label: '厚度偏差（间隙）mm'
            },
            {
              key: 'THK_COINCID_MODE',
              label: '厚度（重合度）规则'
            },
            {
              key: 'THK_COINCID',
              label: '厚度偏差（重合度）mm'
            },
            {
              key: 'WID_DEV_MIN',
              label: '宽度最小值mm'
            },
            {
              key: 'WID_DEV_MAX',
              label: '宽度最大值mm'
            },
            {
              key: 'WID_LASER_MODE',
              label: '宽度（激光划线）规则（'
            },
            {
              key: 'WID_LASER_DEV',
              label: '宽度偏差mm'
            },
            {
              key: 'WID_PINCH_MODE',
              label: '宽度（夹送辊）规则'
            },
            {
              key: 'WID_PINCH_DEV',
              label: '宽度偏差mm'
            }
          ]
        },
        {
          title: '2#定尺剪',
          tableData: [{}, {}, {}, {}],
          tableColumns: [
            {
              key: 'HTL_FLAG',
              label: '热处理标志'
            },
            {
              key: 'THK_MIN',
              label: '厚度最小值'
            },
            {
              key: 'THK_MAX',
              label: '厚度最大值'
            },
            {
              key: 'WID_MIN',
              label: '宽度最小值'
            },
            // {
            //   key: 'THK_GAP_MIN',
            //   label: '厚度最小值（间隙）mm'
            // },
            {
              key: 'WID_MAX',
              label: '宽度最大值'
            },
            {
              key: 'LEN_MIN',
              label: '长度最小值'
            },
            {
              key: 'LEN_MAX',
              label: '长度最大值'
            },
            {
              key: 'LEN_MODE',
              label: '长度规则'
            },
            {
              key: 'LEN_DEV',
              label: '长度偏差mm'
            }
          ]
        },
        {
          title: '冷床模型分档',
          tableData: [{}, {}, {}, {}],
          tableColumns: [
            {
              key: 'COOL_TYPE',
              label: '冷却类型'
            },
            {
              key: 'STEEL_GRADE',
              label: '钢种'
            },
            {
              key: 'CEQ',
              label: '碳当量'
            }
          ]
        },
        {
          title: '冷床模型参数',
          tableData: [{}, {}, {}, {}],
          tableColumns: [
            {
              key: 'COOL_TYPE',
              label: '冷却类型'
            },
            {
              key: 'THKCODE',
              label: '厚度分档'
            },
            {
              key: 'TEMPCODE',
              label: '温度分档'
            },
            {
              key: 'LEARN_COEFF',
              label: '自学习系数'
            },
            {
              key: 'AIM_TEMP',
              label: '目标温度'
            },
            {
              key: 'TEMP_DEV',
              label: '修正值'
            }
          ]
        }
      ]
    }
  },
  computed: {
    activeTableIndex: function() {
      return this.allObjData[this.activeName]['tableIndex']
    },
    activeIndex: function() {
      return this.allObjData[this.activeName]['index']
    }
  },
  mounted() {
    // console.log(userinfo)
    this.getTableData()
    this.verifyLoginInfo()
  },
  methods: {
    getTableData() {
      //0---钢种分组、1---L1双边剪、2----L1定尺剪
      //11--L2号线切分剪 12--2#圆盘剪  13--2#定尺剪；21--冷床模型分档  22--冷床模型参数
      let data = [
        [
          {
            table: this.allObjData[this.activeName]['tableIndex']
          }
        ]
      ]
      let tar = this.allObjData[this.activeName]['index']
      console.log('111', tar)
      sendMsg(data, 1821, 'HMI').then(res => {
        if (res.code == 200) {
          this.tableDataList[tar].tableData = res.results[0]
        }
      })
    },
    handleClick(tab, event) {
      this.getTableData()
    },
    addTe(title) {
      this.dialogFormVisibleAdd = true
      this.dialogType = '添加'
      this.dialogTitle = title
      this.getSteelGroup()
    },
    getSteelGroup() {
      let data = [{ tagName: 'L1DSSTECHGRADE', timestamp: 0 }]
      getHmiDataByEvent(data).then(res => {
        if (res.code == 200) {
          this.steelGroupList = res.results[0].value
        }
      })
    },
    addSubmit() {
      this.formAdd.table = this.activeTableIndex
      let data = [[this.formAdd]]
      sendMsg(data, 1822, 'HMI').then(res => {
        if (res.code == 200) {
          this.$message({
            message: '添加成功',
            type: 'success'
          })
          this.getTableData()
        }
      })
      this.dialogFormVisibleAdd = false
    },
    login() {
      this.dialogFormVisibleLogin = true
    },
    logout() {
      setTimeout(() => {
        localStorage.removeItem('loginInfo')
        this.verifyLoginInfo()
        this.$message.info('注销成功')
      }, 500)
    },
    submitLogin() {
      this.$refs['formLogin'].validate(valid => {
        if (valid) {
          this.fullscreenLoading = true
          if (
            this.formLogin.name == 'admin' &&
            this.formLogin.password == 'admin'
          ) {
            setTimeout(() => {
              this.fullscreenLoading = false
              this.$message.success('登录成功')
              this.dialogFormVisibleLogin = false
              //存入缓存
              localStorage.setItem('loginInfo', JSON.stringify(this.formLogin))
              this.verifyLoginInfo()
            }, 800)
          } else {
            setTimeout(() => {
              this.fullscreenLoading = false
              this.$message.error('帐号密码不正确')
              this.dialogFormVisibleLogin = true
            }, 800)
          }
        } else {
          console.log('error submit!!')
          return false
        }
      })
    },
    resetForm() {
      this.$refs['formLogin'].resetFields()
      this.dialogFormVisibleLogin = false
    },
    verifyLoginInfo() {
      let loginInfo = localStorage.getItem('loginInfo')
      if (!loginInfo) {
        this.buttonFlag = true
      } else {
        this.buttonFlag = false
      }
    },
    someLogin(name) {
      let userinfo_ = userinfo
      return userinfo_.some(item => item.name === name)
      console.log('someLogin')
    }
  }
}
</script>

<style scoped lang="less">
/deep/ .el-tabs__item.is-active {
  color: #409eff;
  font-weight: 700;
  font-size: 16px;
}
/deep/ .el-button--mini,
/deep/ .el-button--mini.is-round {
  padding: 4px 10px;
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
.el-form {
  display: flex;
  flex-wrap: wrap;
  justify-content: space-between;
}
.technologyManage {
  //padding: 20px;
  .bgc-white {
    background-color: #fff;
    box-shadow: 0px 0px 4px rgb(0 0 0 / 4%), 0px 0px 16px -2px rgb(0 0 0 / 10%);
    border-radius: 6px;
    padding: 20px;
  }
  .login-box {
    padding: 15px 26px 0 0;
    position: absolute;
    right: 26px;
    z-index: 999;
  }
}
</style>
