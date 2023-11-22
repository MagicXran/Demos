<template>
  <div class="steel-info">
    <el-table
      v-loading="tableLoading"
      :data="steelTableSon"
      :tree-props="{children: 'children', hasChildren: 'hasChildren'}"
      :row-class-name="tableRowClassName"
      :empty-text="'暂无数据'"
      :header-cell-style="{border: '1px solid #777',backgroundColor: '#B9C8C5'}"
      :cell-style="getCellStyle"
      class="eltablecss"
      style="width: 100%;"
      row-key="PLATE_NO"
      height="345px"
      border
      default-expand-all
      @selection-change="handleSelectionChange">
      <el-table-column
        :selectable="selectable"
        type="selection"
        fixed="left"
        align="center"
        width="40"/>
      <el-table-column
        fixed="left"
        prop="PLATE_NO"
        label="钢板号"
        width="190"
        align="center"/>
      <el-table-column
        fixed="right"
        label="操作"
        width="140">
        <template slot-scope="scope">
          <el-button
            type="text"
            size="mini"
            @click="revoke(scope.row)">吊销</el-button>
          <el-button
            v-if="scope.row.PLATE_TYPE == 2 || scope.row.PLATE_TYPE == 4"
            type="text"
            size="mini"
            @click="subsection(scope.row)">分段</el-button>
          <el-button
            v-if="scope.row.PLATE_TYPE == 2 || scope.row.PLATE_TYPE == 4 || scope.row.PLATE_TYPE == 1"
            type="text"
            size="mini"
            @click="openSx(scope.row.PLATE_NO)">上线</el-button>
            <!-- <el-button
            v-if="scope.row.PLATE_TYPE == 2 || scope.row.PLATE_TYPE == 4 || scope.row.PLATE_TYPE == 1"
            type="text"
            size="mini"
            @click="openWarehouse(scope.row.PLATE_NO)">中间库</el-button> -->
        </template>
      </el-table-column>
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
        width="65"
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
    <!-- 上线-->
    <el-dialog
      :visible.sync="dialogVisibleOnline"
      :before-close="beforeCloseOnline"
      :width="'400px'"
      class="Dialog"
      inline>
      <div
        slot="title"
        style="font-weight:600;color:#777">
        上 线
      </div>
      <el-form
        ref="form"
        :model="formOnline">
        <el-form-item>
          <div
            slot="label"
            style="width:60px">板坯号</div>
          <el-input
            v-model="formOnline.plantNo"
            style="width:200px"
            readonly/>
        </el-form-item>
        <el-form-item>
          <div
            slot="label"
            style="width:60px">上线区域</div>
          <el-select
            v-model="formOnline.region"
            style="width:200px"
            placeholder="请选择上线区域"
            @change="onlineChange(formOnline.region)">
            <el-option
              label="矫直后辊道"
              value="1"/>
            <el-option
              label="1号精整线"
              value="5"/>
            <el-option
              label="2号精整线"
              value="7"/>
          </el-select>
        </el-form-item>
        <el-form-item>
          <div
            slot="label"
            style="width:60px">具体位置</div>
          <el-select
            v-model="formOnline.postion"
            style="width:200px"
            placeholder="请选择上线位置">
            <el-option
              v-for="item in formOnline.postionList"
              :key="item.value"
              :label="item.label"
              :value="item.value"/>
          </el-select>
        </el-form-item>
      </el-form>
      <span
        slot="footer"
        class="dialog-footer">
        <el-button @click="dialogVisibleOnline = false">取 消</el-button>
        <el-button
          type="primary"
          @click="saveUp()">确 定</el-button>
      </span>
    </el-dialog>
  </div>
</template>

<script>
import { getHmiData, stopGetData, sendMsg, sendTag } from '@/lib/GetData'

export default {
  name: 'SteelInfo',
  props: {
    warehouseshow: {
      type: Boolean,
      default: false
    }
  },
  data() {
    return {
      steelTableSon: [],
      tableLoading: false,
      dialogVisibleOnline: false,
      formOnline: {
        postion: '',
        postionList: [
          {
            label: '1#冷床上料辊道',
            value: '1'
          }
        ],
        plantNo: '',
        region: ''
      },
      saveUpPostData: [
        [
          {
            plateno: '',
            region: '',
            postion: '',
            num: '',
            matid1: '',
            matid2: '',
            matid3: '',
            matid4: '',
            matid5: '',
            matid6: '',
            matid7: '',
            matid8: '',
            matid9: '',
            matid10: ''
          }
        ]
      ],
      matidList: []
    }
  },
  mounted() {},
  methods: {
    /*
    * page==0：自动刷新时，记录集中的page=0；点击钢板时才>0。
      page==1：矫直冷床双边剪子页面：双边剪设定
      page==2：1#定尺剪子页面：定尺剪设定
      page==3：1#垛板机子页面：表检、标印、垛板设定
      page==4：冷床切分剪子页面：切分剪设定
      page==5：圆盘剪子页面：圆盘剪设定
      page==6：2#定尺剪子页面：定尺剪设定
      page==7：2#垛板机子页面：表检、标印、垛板设定
    *
    * */
    getPageByRoute(page) {
      let obj = {
        jls: 1,
        '1dcj': 2,
        '1dbj': 3,
        lq: 4,
        ypj: 5,
        '2dcj': 6,
        '2dbj': 7,
        lxfdj: 1
      }
      return obj[page]
    },
    beforeCloseOnline() {
      this.dialogVisibleOnline = false
    },
    checkboxFn(item) {},
    revoke(item) {
      console.log(item)
      this.$confirm('是否确定吊销?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          let data = [
            [
              {
                plateno: item.PLATE_NO,
                region: item.region
              }
            ]
          ]
          console.log(data)
          sendMsg(data, 1801, 'HMI').then(res => {
            this.dialogVisibleOnline = false
            if (res.results[0][0].msg) {
              this.$message({
                type: 'success',
                message: res.results[0][0].msg
              })
            }
          })
        })
        .catch(() => {
          this.$message({
            type: 'info',
            message: '已取消吊销'
          })
        })
    },
    subsection(item) {
      // console.log('分段开始', item)
      this.$confirm('是否确定分段?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          let resultArr = {
            parentId: '',
            childrenIds: []
          }
          for (let i = 0; i < item.children.length; i++) {
            resultArr.childrenIds.push({
              id: item.children[i].PLATE_NO,
              flag: item.children[i].checkboxM
            })
            resultArr.parentId = item.children[i].parentid
          }
          let result = [
            {
              plateno: resultArr.parentId,
              region: item.region,
              group: '',
              children: resultArr.childrenIds.length
            }
          ]
          for (let k = 0; k < resultArr.childrenIds.length; k++) {
            result.push({
              plateno: resultArr.childrenIds[k].id,
              region: item.region,
              group: resultArr.childrenIds[k].flag == false ? 2 : 1, //选中是1 未选中是2
              children: ''
            })
          }
          sendMsg([result], 1810, 'HMI').then(res => {
            if (res.results[0][0].msg) {
              //分段结束后 需要重新查询即可
              // console.log('分段完成', item)
              this.getTableDataChild(item.plateno, 2)
              this.$message({
                type: 'success',
                message: res.results[0][0].msg
              })
            }
          })
        })
        .catch(() => {
          this.$message({
            type: 'info',
            message: '已取消分段'
          })
        })
    },
    onlineChange(region) {
      let bar = {
        1: [
          {
            value: 1,
            label: '1#冷床上料辊道'
          },
          {
            value: 2,
            label: '2#冷床上料辊道'
          }
        ],
        5: [
          {
            value: 1,
            label: '1#冷床下料辊道'
          },
          {
            value: 2,
            label: '2#冷床下料辊道'
          }
        ],
        7: [
          {
            value: 1,
            label: '3#冷床下料辊道'
          },
          {
            value: 2,
            label: '切分剪后天桥'
          },
          {
            value: 3,
            label: '定尺剪前'
          }
        ]
      }
      this.formOnline.postionList = bar[region]
    },
    // 计划表上线
    openSx(id) {
      this.formOnline.plantNo = id
      this.formOnline.region = ''
      this.formOnline.postion = ''
      this.dialogVisibleOnline = true
    },
    //计划表确定上线
    saveUp() {
      console.log('套用组件')
      this.saveUpPostData = [
        [
          {
            plateno: '',
            region: '',
            postion: '',
            num: '',
            matid1: '',
            matid2: '',
            matid3: '',
            matid4: '',
            matid5: '',
            matid6: '',
            matid7: '',
            matid8: '',
            matid9: '',
            matid10: ''
          }
        ]
      ]
      let plantNoList = []
      this.matidList.forEach(item => {
        plantNoList.push(Number(item.PLATE_NO))
      })
      plantNoList.sort((old, New) => {
        return old - New
      })
      let strList = []
      plantNoList.forEach(item => {
        strList.push(String(item))
      })
      this.saveUpPostData[0][0].plateno = this.formOnline.plantNo
      this.saveUpPostData[0][0].region = this.formOnline.region
      this.saveUpPostData[0][0].postion = this.formOnline.postion
      this.saveUpPostData[0][0].num = this.matidList.length
      if (strList[9]) {
        this.saveUpPostData[0][0].matid10 = strList[9]
      }
      if (strList[8]) {
        this.saveUpPostData[0][0].matid9 = strList[8]
      }
      if (strList[7]) {
        this.saveUpPostData[0][0].matid8 = strList[7]
      }
      if (strList[6]) {
        this.saveUpPostData[0][0].matid7 = strList[6]
      }
      if (strList[5]) {
        this.saveUpPostData[0][0].matid6 = strList[5]
      }
      if (strList[4]) {
        this.saveUpPostData[0][0].matid5 = strList[4]
      }
      if (strList[3]) {
        this.saveUpPostData[0][0].matid4 = strList[3]
      }
      if (strList[2]) {
        this.saveUpPostData[0][0].matid3 = strList[2]
      }
      if (strList[1]) {
        this.saveUpPostData[0][0].matid2 = strList[1]
      }
      if (strList[0]) {
        this.saveUpPostData[0][0].matid1 = strList[0]
      }
      // console.log(strList)
      sendMsg(this.saveUpPostData, 1805, 'HMI').then(res => {
        if (res.results[0][0].msg) {
          this.$message({
            message: res.results[0][0].msg,
            type: 'success'
          })
          this.dialogVisibleOnline = false
        }
      })
    },
    // 中间库上线
    openWarehouse(id) {
      this.formOnline.plantNo = id
      this.dialogVisibleOnline = true
    },
    // saveUp() {
    //   let data = [
    //     [
    //       {
    //         plateno: this.formOnline.plantNo,
    //         region: this.formOnline.region,
    //         postion: this.formOnline.postion
    //       }
    //     ]
    //   ]
    //   sendMsg(data, 1805, 'HMI').then(res => {
    //     if (res.results[0][0].msg) {
    //       this.$message({
    //         message: res.results[0][0].msg,
    //         type: 'success'
    //       })
    //       this.dialogVisibleOnline = false
    //     }
    //   })
    // },
    // 多选框选中的数据
    handleSelectionChange(row) {
      this.matidList = row
      // console.log(this.matidList)
    },
    tableRowClassName({ row, rowIndex }) {
      // if (row.GROUP_FLAG == 1) {
      //   return 'warning-row'
      // } else if (row.GROUP_FLAG == 2) {
      //   return 'success-row'
      // }
      // return ''
    },
    // 表格多选框处理（显示隐藏、是否可选）
    cellClass({ row, columnIndex }) {
      if (row.PLATE_TYPE != 3) {
        // 根据某个属性，添加样式，隐藏复选框
        return 'myCell'
      }
    },
    selectable(row, index) {
      if (row.PLATE_TYPE == 3) {
        return true
      } else {
        return false
      }
    },
    getTableDataChild(plateno, type, clickRegion) {
      // console.log(clickRegion)
      let data = [
        [
          {
            plateno: plateno,
            page: this.getPageByRoute(this.$route.name),
            type: type,
            region: clickRegion
          }
        ]
      ]
      sendMsg(data, 1803, 'HMI').then(res => {
        let forData = res.results[0]
        console.log('检查报错res.results[0]', res)
        if (forData.PLATE_NO === '') {
          this.steelTableSon = []
          return
        }
        let resultArr = []
        let resultArr1 = []
        let resultArr2 = []
        forData.forEach(item => {
          // 一层
          if (item.group_1 == item.group_2 && item.group_1 == 0) {
            resultArr.push(item)
          }
          // 二层
          if (item.group_2 == 0 && item.group_1 != 0) {
            resultArr1.push(item)
          }
          // 三层
          if (item.group_1 != 0 && item.group_2 != 0) {
            resultArr2.push(item)
          }
        })
        // 三层
        if (resultArr.length > 0) {
          resultArr.forEach(item => {
            item.children = []
            resultArr1.forEach(val => {
              val.children = []
              resultArr2.forEach(val1 => {
                if (
                  val1.group_1 == val.group_1 &&
                  val1.group_0 == val.group_0
                ) {
                  val.children.push(val1)
                }
              })
              if (item.group_0 == val.group_0) {
                item.children.push(val)
              }
            })
          })
        }
        if (resultArr.length == 0 && resultArr1.length > 0) {
          resultArr1.forEach(val => {
            val.children = []
            resultArr2.forEach(val1 => {
              if (val1.group_1 == val.group_1) {
                val.children.push(val1)
              }
            })
          })
          resultArr = resultArr1
        }
        if (resultArr1.length == 0 && resultArr.length == 0) {
          resultArr = forData
        }
        this.steelTableSon = resultArr
        this.tableLoading = false
      })
    },
    // 修改table样式
    getCellStyle({ row, column, rowIndex, columnIndex }) {
      if (row.PLATE_TYPE == 1) {
        return 'background: #F0B8F0;border: solid 1px #777;border-top:0px'
      } else if (row.PLATE_TYPE == 2 || row.PLATE_TYPE == 4) {
        return 'background: #B1E8ED;border: solid 1px #777;border-top:0px'
      } else if (row.PLATE_TYPE == 3) {
        return 'background: #CDF8CE;border: solid 1px #777'
      }
    }
  }
}
</script>

<style scoped lang="less">
.steel-info {
  padding: 24px;
  background-color: #fff;
}
/deep/ .el-table__header tr,//修改th表头高度
  .el-table__header th {
  padding: 0;
  height: 30px;
  line-height: 30px;
}
/deep/ .el-table {
  .el-table__fixed-header-wrapper {
    .el-checkbox__inner {
      display: none !important;
    }
  }
}
</style>
<style lang="less">
.myCell .el-checkbox__input {
  display: none !important;
}
.el-table th {
  display: table-cell !important;
}
</style>
