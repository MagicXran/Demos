<template>
  <div class="dcj2">
    <div
      v-tag:tag="variable"
      data-page="dcj2"/>
    <div class="banner bgc-white">
      <div class="bgimg">
        <div class="bgimg-box"/>
        <div class="track-box">
          <trackItem
            :track-data="trackData"
            :top="68"
            :left="7"
            :type="1"
            @opdialog="opdialog"
            @getTableDataByTwo="getTableDataByTwo"
          />
          <div class="cmd-box">
            <ul>
              <li
                v-for="(item, index) in cmdList"
                v-if="item.value == 1"
                :style="'top:56px;'+'left:'+(item.x + 11)+'px'"
                :key="index.x">
                <img
                  src="../assets/green.png"
                  alt="">
              </li>

              <li
                v-for="(item, index) in cameraList"
                v-if="item.value == 0"
                :style="'top:38px;'+'left:'+(item.x-101)+'px'"
                :key="index.x">
                <img
                  style="height: 14px"
                  src="../assets/vector.png"
                  alt="">
              </li>
            </ul>
          </div>
          <modif-info
            :poschangeshow="poschangeshow"
            :direction="'vertical'"
            :posboxsty="posboxsty"
            :pos-form="posForm"
            @submitPos="submitPos()"
            @closePos="closePos()"/>
        </div>
      </div>
    </div>

    <div class="content">
      <el-row
        :gutter="20"
        style="margin-bottom: 20px">
        <el-col
          :span="10"
        >
          <div
            class="set-info">
            <el-row class="bgcfff">
              <div>
                <el-col
                  v-if="form1.changeFlag"
                  :span="24"
                  class="bgcfff">
                  <div
                    style="padding: 24px;"
                    class="bgc-white">
                    <div
                      class="header"
                      style="display: flex;
  justify-content: space-between;
  align-items: baseline;">
                      <p class="ps">设定信息</p>
                      <div
                        class="cz"
                        style="overflow: hidden;display: flex;align-items: baseline;
    justify-content: flex-end;">
                        <div>
                          <span
                            style="font-size: 14px;
                                vertical-align: bottom;
                                color: #606266;
                                letter-spacing: 1px;
                                font-weight: 600;">L2投用</span>
                          <el-switch
                            v-model="form1.L2DSSET_UseFlag"
                            active-color="green"
                            inactive-color="red"
                            @change="closeRefresh(form1)"/>
                        </div>
                      </div>
                    </div>
                    <div class="form-boder">
                      <el-row :gutter="5">
                        <el-col :span="10">
                          <el-form
                            ref="form"
                            :model="form1"
                            label-width="75px">
                            <el-form-item label="钢板号">
                              <el-input
                                v-model="form1.L2DSSET_PlateNo"
                                size="mini"
                                @focus="closeRefresh(form1)">
                                <el-button
                                  slot="append"
                                  icon="el-icon-search"
                                  @click="getTableDataByTwo(form1.L2DSSET_PlateNo,3)"/>
                              </el-input>
                            </el-form-item>
                            <!--                      <el-form-item label="钢种">
                              <el-input
                                v-model="form1.L1DSSET_Steelgrade"
                                size="mini"
                                @focus="closeRefresh(form1)"/>
                            </el-form-item>-->
                            <el-form-item label="母板长度">
                              <el-input
                                v-model="form1.L2DSSET_Plate_Len"
                                size="mini"
                                @focus="closeRefresh(form1)">
                                <template slot="append">mm</template>
                              </el-input>
                            </el-form-item>
                            <el-form-item label="母板宽度">
                              <el-input
                                v-model="form1.L2DSSET_Plate_Wid"
                                size="mini"
                                @focus="closeRefresh(form1)">
                                <template slot="append">mm</template>
                              </el-input>
                            </el-form-item>
                            <el-form-item label="母板厚度">
                              <el-input
                                v-model="form1.L2DSSET_Plate_Thk"
                                size="mini"
                                @focus="closeRefresh(form1)">
                                <template slot="append">mm</template>
                              </el-input>
                            </el-form-item>
                          </el-form>
                        </el-col>
                        <el-col
                          :span="14"
                          class="pad0">
                          <el-table
                            :data="tableSet"
                            style="height: 195px;
    overflow-y: scroll;"
                            border
                          >
                            <el-table-column
                              :index="1"
                              type="index"
                              width="50"
                              label="序号"
                              align="left"/>
                            <el-table-column
                              label="剪切类型"
                              align="left">
                              <template slot-scope="scope">
                                <el-select
                                  v-model="scope.row.selectModel"
                                  size="mini"
                                  placeholder="请选择"
                                  @focus="closeRefresh(form1)">
                                  <el-option
                                    v-for="item in scope.row.selectData"
                                    :key="item.value"
                                    :label="item.label"
                                    :value="item.value"/>
                                </el-select>
                              </template>
                            </el-table-column>
                            <el-table-column
                              prop=""
                              label="剪切长度"
                              align="left">
                              <template slot-scope="scope">
                                <el-input
                                  v-model="scope.row.len"
                                  size="mini"
                                  @focus="closeRefresh(form1)">
                                  <template slot="append">mm</template>
                                </el-input>
                              </template>
                            </el-table-column>
                          </el-table>
                        </el-col>
                      </el-row>

                    </div>
                    <div class="form-button">
                      <!--                <el-button
                        type="primary"
                        size="mini"
                        @click="getTableDataByTwo({
                          plateno: form1.L2DSSET_PlateNo,
                          region: 0
                      },0,1)">查询</el-button>-->
                      <el-button
                        type="primary"
                        size="mini"
                        @click="saveSet()">修改</el-button>
                      <el-button
                        style=""
                        type="primary"
                        size="mini"
                        @click="againSet()">重新设定</el-button>
                    </div>
                  </div>
                </el-col>
                <el-col
                  v-if="!form1.changeFlag"
                  :span="24"
                  class="bgcfff">
                  <div
                    style="padding: 24px;"
                    class="bgc-white">
                    <div
                      class="header"
                      style="display: flex;
  justify-content: space-between;
  align-items: baseline;">
                      <p class="ps">设定信息<span
                        style="margin-left: 265px; color: #FFA958;font-size: 13px">修改中... <i
                          style="font-size: 20px;cursor: pointer"
                          class="el-icon-circle-close"
                          @click="openRefresh(form1)"
                      /></span></p>
                      <div
                        class="cz"
                        style="overflow: hidden;display: flex;align-items: baseline;
    justify-content: flex-end;">
                        <div>
                          <span
                            style="font-size: 14px;
                                vertical-align: bottom;
                                color: #606266;
                                letter-spacing: 1px;
                                font-weight: 600;">L2投用</span>
                          <el-switch
                            v-model="form1Change.L2DSSET_UseFlag"
                            active-color="green"
                            inactive-color="red"/>
                        </div>
                      </div>
                    </div>
                    <div class="form-boder">
                      <el-row :gutter="5">
                        <el-col :span="10">
                          <el-form
                            ref="form"
                            :model="form1Change"
                            label-width="75px">
                            <el-form-item label="钢板号">
                              <el-input
                                v-model="form1Change.L2DSSET_PlateNo"
                                size="mini"
                              >
                                <el-button
                                  slot="append"
                                  icon="el-icon-search"
                                  @click="getTableDataByTwo(form1Change.L2DSSET_PlateNo,3)"/>
                              </el-input>
                            </el-form-item>
                            <!--                      <el-form-item label="钢种">
                              <el-input
                                v-model="form1Change.L1DSSET_Steelgrade"
                                size="mini"
                              />
                            </el-form-item>-->
                            <el-form-item label="母板长度">
                              <el-input
                                v-model="form1Change.L2DSSET_Plate_Len"
                                size="mini"
                              >
                                <template slot="append">mm</template>
                              </el-input>
                            </el-form-item>
                            <el-form-item label="母板宽度">
                              <el-input
                                v-model="form1Change.L2DSSET_Plate_Wid"
                                size="mini"
                              >
                                <template slot="append">mm</template>
                              </el-input>
                            </el-form-item>
                            <el-form-item label="母板厚度">
                              <el-input
                                v-model="form1Change.L2DSSET_Plate_Thk"
                                size="mini"
                              >
                                <template slot="append">mm</template>
                              </el-input>
                            </el-form-item>
                          </el-form>
                        </el-col>
                        <el-col
                          :span="14"
                          class="pad0">
                          <el-table
                            :data="tableSetSubmit"
                            border
                          >
                            <el-table-column
                              :index="1"
                              type="index"
                              width="50"
                              label="序号"
                              align="left"/>
                            <el-table-column
                              label="剪切类型"
                              align="left">
                              <template slot-scope="scope">
                                <el-select
                                  v-model="scope.row.selectModel"
                                  size="mini"
                                  placeholder="请选择"
                                >
                                  <el-option
                                    v-for="item in scope.row.selectData"
                                    :key="item.value"
                                    :label="item.label"
                                    :value="item.value"/>
                                </el-select>
                              </template>
                            </el-table-column>
                            <el-table-column
                              prop=""
                              label="剪切长度"
                              align="left">
                              <template slot-scope="scope">
                                <el-input
                                  v-model="scope.row.len"
                                  size="mini"
                                >
                                  <template slot="append">mm</template>
                                </el-input>
                              </template>
                            </el-table-column>
                          </el-table>
                        </el-col>
                      </el-row>

                    </div>
                    <div class="form-button">
                      <el-button
                        type="primary"
                        size="mini"
                        @click="saveSet()">修改</el-button>
                      <el-button
                        style=""
                        type="primary"
                        size="mini"
                        @click="againSet()">重新设定</el-button>
                    </div>
                  </div>
                </el-col>
              </div>
              <!--              <el-col
                :span="10"
                class="bgcfff">
                <div
                  class="bgc-white"
                  style="padding: 24px">
                  <div
                    class="header"
                    style="display: flex;
  justify-content: space-between;
  align-items: baseline;">
                    <p class="ps">实际信息</p>
                  </div>
                  <el-table
                    :data="tableAct"
                    style="height: 195px;
    overflow-y: scroll;"
                    border
                  >
                    <el-table-column
                      :index="1"
                      type="index"
                      width="50"
                      label="序号"
                      align="left"/>
                    <el-table-column
                      prop=""
                      label="剪切类型"
                      align="left">
                      <template slot-scope="scope">
                        <span v-if="scope.row.type == 1">切头</span>
                        <span v-if="scope.row.type == 2">子板</span>
                        <span v-if="scope.row.type == 3">取样</span>
                        <span v-if="scope.row.type == 4">剩余</span>
                      </template>
                    </el-table-column>
                    <el-table-column
                      prop="len"
                      label="剪切长度"
                      align="left"/>
                    <el-table-column
                      prop=""
                      label="执行状态"
                      align="left">
                      <template slot-scope="scope">
                        <el-button
                          v-if="scope.row.com == 1"
                          type="success"
                          plain
                          size="mini">已剪切</el-button>
                        <el-button
                          v-if="scope.row.com == 0"
                          type="warning"
                          plain
                          size="mini">未剪切</el-button>
                      </template>
                    </el-table-column>
                  </el-table>
                </div>
              </el-col>-->
            </el-row>
          </div>
        </el-col>
        <el-col
          :span="14">
          LMS_Cut_Num:
          {{ tempdata }}
          <!--          <warn-info
            :warn-type="2"
          />-->
        </el-col>
      </el-row>
      <el-row>
        <el-col :span="24">
          <steelInfo
            ref="steelinfo"
            @getTableDataByChild="tableLoading = false"
          />
        </el-col>
      </el-row>
    </div>
  </div>
</template>

<script>
import HmiTable from '@/components/HmiTable'
import { getHmiData, sendMsg, sendTag, stopGetData } from '@/lib/GetData'
import warnInfo from '@/pages/components/warnInfo'
import setInfo from '@/pages/components/setInfo'
import steelInfo from '@/pages/components/steelInfo'
import modifInfo from '@/pages/components/modifInfo'
import trackItem from '@/pages/components/trackItem'
export default {
  name: 'Lcb2',
  components: { warnInfo, HmiTable, setInfo, steelInfo, modifInfo, trackItem },
  data() {
    return {
      tempdata: 0,
      form1: {
        changeFlag: true,
        L2DSSET_UseFlag: '',
        L2DSSET_PlateNo: '',
        L2DSSET_Steelgrade: '',
        L2DSSET_Plate_Len: '',
        L2DSSET_Plate_Wid: '',
        L2DSSET_Plate_Thk: ''
      },
      form1Change: {},
      tableFrom1: [],
      tableFrom2: [],
      tableSet: [], //获取的设定信息表格
      tableAct: [], //获取的实际信息表格
      tableSetSubmit: [], //修改提交的设定信息表格
      variable: [
        'LMS_Cut_Num',
        'rechmi7',
        'L2DSTRACK.ENDSCMD1',
        'L2DSTRACK.ENDSCMD2',
        'L2DSTRACK.ENDSCMD3',
        'L2DSTRACK.ENDSCMD4',
        'L2DSTRACK.ENDSCMD5',
        'L2DSTRACK.EXDSCMD1',
        'L2DSTRACK.EXDSCMD2',
        'L2DSTRACK.EXDSCMD3',
        'L2DSTRACK.EXDSCMD4',
        'L2DSTRACK.PILERCMD1',
        'L2DSSET_HMI',
        'L2DSCOM_HMI',
        'L2DSSET_UseFlag',
        'L2DSSET_PlateNo',
        'L2DSSET_Steelgrade',
        'L2DSSET_Plate_Len',
        'L2DSSET_Plate_Wid',
        'L2DSSET_Plate_Thk',
        'LMSSCAN_CAMERA.CameraOn_1',
        'LMSSCAN_CAMERA.CameraOn_2',
        'LMSSCAN_CAMERA.CameraOn_3',
        'LMSSCAN_CAMERA.CameraOn_4',
        'LMSSCAN_CAMERA.CameraOn_5',
        'LMSSCAN_CAMERA.CameraOn_6',
        'LMSSCAN_CAMERA.CameraOn_7',
        'LMSSCAN_CAMERA.CameraOn_8',
        'LMSSCAN_CAMERA.CameraOn_9',
        'LMSSCAN_CAMERA.CameraOn_10',
        'LMSSCAN_CAMERA.CameraOn_11',
        'LMSSCAN_CAMERA.CameraOn_12',
        'LMSSCAN_CAMERA.CameraOn_13',
        'LMSSCAN_CAMERA.CameraOn_14',
        'LMSSCAN_CAMERA.CameraOn_15',
        'LMSSCAN_CAMERA.CameraOn_16',
        'LMSSCAN_CAMERA.CameraOn_17',
        'LMSSCAN_CAMERA.CameraOn_18',
        'LMSSCAN_CAMERA.CameraOn_19'
      ],
      cmdList: [
        {
          key: 'L2DSTRACK.ENDSCMD1',
          value: '',
          x: -3
        },
        {
          key: 'L2DSTRACK.ENDSCMD2',
          value: '',
          x: 197.1083799
        },
        {
          key: 'L2DSTRACK.ENDSCMD3',
          value: '',
          x: 381.0910615
        },
        {
          key: 'L2DSTRACK.ENDSCMD4',
          value: '',
          x: 547.2480447
        },
        {
          key: 'L2DSTRACK.ENDSCMD5',
          value: '',
          x: 680.2536313
        },
        {
          key: 'L2DSTRACK.EXDSCMD1',
          value: '',
          x: 906.1005587
        },
        {
          key: 'L2DSTRACK.EXDSCMD2',
          value: '',
          x: 1088.98324
        },
        {
          key: 'L2DSTRACK.EXDSCMD3',
          value: '',
          x: 1221.988827
        },
        {
          key: 'L2DSTRACK.EXDSCMD4',
          value: '',
          x: 1305.117318
        },
        {
          key: 'L2DSTRACK.PILERCMD1',
          value: '',
          x: 1487
        }
      ],
      cameraList: [
        {
          key: 'LMSSCAN_CAMERA.CameraOn_1',
          value: '',
          x: 1000
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_2',
          value: '',
          x: 1018
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_3',
          value: '',
          x: 1036
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_4',
          value: '',
          x: 1054
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_5',
          value: '',
          x: 1072
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_6',
          value: '',
          x: 1089
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_7',
          value: '',
          x: 1107
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_8',
          value: '',
          x: 1125
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_9',
          value: '',
          x: 1143
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_10',
          value: '',
          x: 1161
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_11',
          value: '',
          x: 1179
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_12',
          value: '',
          x: 1197
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_13',
          value: '',
          x: 1215
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_14',
          value: '',
          x: 1233
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_15',
          value: '',
          x: 1251
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_16',
          value: '',
          x: 1269
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_17',
          value: '',
          x: 1286
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_18',
          value: '',
          x: 1304
        },
        {
          key: 'LMSSCAN_CAMERA.CameraOn_19',
          value: '',
          x: 1322
        }
      ],
      dialogVisibleUp: false,
      formUp: {
        postion: '',
        plantNo: '',
        region: ''
      },
      tableLoading: false,
      currentId: [],
      //2 钢板号打开  1 其他打开 3 都打开
      isReadOnly: 3,
      timer: null,
      poschangeshow: false,
      posboxsty: {
        top: '',
        left: ''
      },
      posForm: {
        oldId: '',
        plant: '',
        radio: '3', //默认值修改为3
        unit: 1,
        num: '',
        region: ''
      },
      steelTablePar: [{}, {}, {}],
      trackData: []
    }
  },
  mounted() {
    this.getHmiData()
  },
  destroyed() {
    stopGetData()
  },
  methods: {
    initForm() {
      this.form1Change = { ...this.form1 } //不参加原数组修改
      this.tableSetSubmit = [...this.tableSet]
    },
    openRefresh(form) {
      form.changeFlag = true
    },
    closeRefresh(form) {
      form.changeFlag = false
      this.initForm()
      console.log('关闭实时刷新')
    },
    saveSet() {
      this.$confirm('是否确定修改?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          console.log(111)
          //判断typeFlag 决定submitForm
          let data = {
            L2DSSET_UseFlag:
              this.form1Change.L2DSSET_UseFlag == true ? '1' : '0',
            L2DSSET_PlateNo: this.form1Change.L2DSSET_PlateNo,
            L2DSSET_Plate_Len: this.form1Change.L2DSSET_Plate_Len,
            L2DSSET_Plate_Wid: this.form1Change.L2DSSET_Plate_Wid,
            L2DSSET_Plate_Thk: this.form1Change.L2DSSET_Plate_Thk,
            L2DSSET_Steelgrade: this.form1Change.L2DSSET_Steelgrade,
            L2DSSET_ModFlag: 1, // 双边剪设定，点击修改按钮后，将该变量置1
            L2DSSET_HMI: []
          }
          for (let i = 0; i < this.tableSetSubmit.length; i++) {
            data['L2DSSET_HMI'].push({
              len: this.tableSetSubmit[i].len,
              type: this.tableSetSubmit[i].selectModel
            })
          }
          sendTag(data).then(res => {
            this.$message({
              message: '修改成功',
              type: 'success'
            })
            this.form1.changeFlag = true
          })
        })
        .catch(() => {
          console.log(222)
          this.$message({
            type: 'info',
            message: '已取消修改'
          })
        })
    },
    againSet() {
      this.form1Change = { ...this.form1 } //不参加原数组修改
      let data = [
        [
          {
            plateno: this.form1Change.L2DSSET_PlateNo,
            process: '8'
          }
        ]
      ]
      sendMsg(data, 1808, 'HMI').then(res => {
        if (res.results[0][0].msg) {
          this.$message({
            message: res.results[0][0].msg,
            type: 'success'
          })
        }
      })
    },
    getSetData(data) {
      this.form1.L2DSSET_UseFlag = data['L2DSSET_UseFlag'] == 1 ? true : false
      this.form1.L2DSSET_ModFlag = data['L2DSSET_ModFlag']
      this.form1.L2DSSET_PlateNo = data['L2DSSET_PlateNo']
      this.form1.L2DSSET_Steelgrade = data['L2DSSET_Steelgrade']
      this.form1.L2DSSET_Plate_Len = data['L2DSSET_Plate_Len']
      this.form1.L2DSSET_Plate_Wid = data['L2DSSET_Plate_Wid']
      this.form1.L2DSSET_Plate_Thk = data['L2DSSET_Plate_Thk']
      this.tableSet = []
      for (let i = 0; i < data['L2DSSET_HMI'].length; i++) {
        this.tableSet.push({
          selectModel: data['L2DSSET_HMI'][i].type,
          len: data['L2DSSET_HMI'][i].len,
          selectData: [
            {
              label: '切头',
              value: 1
            },
            {
              label: '子板',
              value: 2
            },
            {
              label: '取样',
              value: 3
            },
            {
              label: '剩余',
              value: 4
            }
          ]
        })
      }
      // this.tableAct = data['L2DSCOM_HMI']
    },
    //封装成对象方法使用
    trackSteel(data) {
      // 页面和实际比例 以整个图为例 宽度: 实际3.51m  页面50px  总长  长度: 实际282589-372755m  冷床页面长度 1610px
      // 辊道 宽度 3.51 页面 50px
      let [actWid, pageWid, actLen, pageLen, actgd, pagegd] = [
        3.5 * 1000,
        50,
        // 90.166 * 1000,
        372755 - 282589,
        1613,
        3.51 * 1000,
        50
      ]
      this.trackData = []
      for (let i = 0; i < data['rechmi7'].length; i++) {
        let item = data['rechmi7'][i]
        this.trackData.push({
          width: this.countSteelLeng(actLen, pageLen, item.platelenmeas),
          height: this.countSteelWid(actWid, pageWid, item.platewid),
          tailpos: this.countSteeltail(
            actLen,
            pageLen,
            item.tail_x
            // item.head_x - item
          ),
          vPos:
            this.countSteelPosY(actWid, pageWid, item.v_pos) +
            (pagegd - this.countSteelWid(actgd, pagegd, item.platewid)) / 2, //计算辊道中心位置
          plateno: item.plateno,
          platethk: item.platethk,
          platewid: item.platewid,
          platelen: item.platelenmeas,
          platewet: item.platewet,
          cbdec: item.cbdec,
          region: item.region,
          platenoSimple:
            item.platelenmeas > 12000
              ? item.plateno
              : '..' + item.plateno.slice(5, item.plateno.length),
          plate_type:
            item.plate_type == 1
              ? '板坯'
              : item.plate_type == 2
                ? '母板'
                : item.plate_type == 3
                  ? '子板'
                  : item.plate_type == 4
                    ? '子母板'
                    : '钢板',
          tailX: item.tailX,
          Vpos: item.Vpos,
          headX: item.headX,
          color: item.colour
        })
      }
      // console.log(this.trackData)
    },
    //actWid, pageWid, actLen, pageLen
    countSteelLeng(actLen, pageLen, mat_len) {
      return (pageLen * mat_len) / actLen
    },
    countSteelWid(actWid, pageWid, mat_wid) {
      return (pageWid * mat_wid) / actWid
    },
    countSteeltail(actLen, pageLen, tail_x) {
      return (pageLen * tail_x) / actLen
    },
    countSteelPosY(actWid, pageWid, head_Y) {
      return (pageWid * head_Y) / actWid
    },
    getHmiData() {
      getHmiData(
        'dcj2',
        data => {
          data['rechmi7'].forEach(item => {
            item.tailX = item.tail_x
            item.Vpos = item.v_pos
            item.headX = item.head_x
          })
          data['rechmi7'].map((item, index) => {
            item.v_pos = item.v_pos - 67270
            item.tail_x = item.tail_x - 282589
          })
          this.tempdata = data['LMS_Cut_Num']
          this.trackSteel(data)
          this.getTableDataByProcess(data)
          this.initCmd(data)
          this.initCamera(data)
          this.getSetData(data)
        },
        error => {
          console.log(error)
        },
        1000
      )
    },
    initCmd(data) {
      this.cmdList.forEach(item => {
        item.value = data[item.key]
      })
    },
    initCamera(data) {
      this.cameraList.forEach(item => {
        item.value = data[item.key]
      })
    },
    handleChangeNum() {
      this.isReadOnly = 1
    },

    submitPos() {
      this.poschangeshow = false
      this.posForm.num = ''
    },
    closePos() {
      this.posForm.num = ''
      this.poschangeshow = false
    },
    opdialog(event, item) {
      let targetPos = {
        top: event.currentTarget.offsetTop,
        left: event.currentTarget.offsetLeft,
        width: event.currentTarget.offsetWidth
      }
      console.log(targetPos)
      clearTimeout(this.timer) //清除未执行的定时器
      if (item.region == 2 || item.region == 3 || item.region == 4) {
        this.posForm.unit = 3.6
        this.countposdia234(event)
      } else if (item.region == 1 || item.region == 5 || item.region == 7) {
        this.countposdia15(event)
        this.posForm.unit = 10
      }
      this.posForm.plant = item.plateno
      this.posForm.region = item.region
      this.posForm.oldId = item.plateno
      this.poschangeshow = true
    },
    countposdia234(event) {
      //冷床
      let targetPos = {
        top: event.currentTarget.offsetTop,
        left: event.currentTarget.offsetLeft,
        width: event.currentTarget.offsetWidth
      }
      this.posboxsty.top = targetPos.top
      this.posboxsty.left = targetPos.left + targetPos.width + 10
    },
    countposdia15(event) {
      //辊道
      let targetPos = {
        top: event.currentTarget.offsetTop,
        left: event.currentTarget.offsetLeft,
        width: event.currentTarget.offsetWidth,
        height: event.currentTarget.offsetHeight
      }
      this.posboxsty.top = targetPos.top + targetPos.height + 10
      this.posboxsty.left =
        targetPos.left > 1275 ? 1275 : targetPos.left < 0 ? 0 : targetPos.left
    },
    getTableDataByProcess(data) {
      let fordata = data['rechmi7']
      for (let i = 0; i < fordata.length; i++) {
        if (fordata[i].process == 2) {
          if (this.currentId.indexOf(fordata[i].plateno) < 0) {
            this.currentId.push(fordata[i].plateno)
            console.log('触发process == 2')
            this.getTableDataByTwo(fordata[i].plateno, 0)
          }
        }
      }
    },
    //查询钢板信息
    getTableDataByTwo(plateno, type, itemInfo) {
      if (!itemInfo) {
        itemInfo = {
          region: 0
        }
      }
      //process == 0 点击钢板查询 其他从记录集获取
      clearTimeout(this.timer)
      this.timer = setTimeout(() => {
        this.form1.changeFlag = true
        this.$refs.steelinfo.getTableDataChild(plateno, type, itemInfo.region)
        this.tableLoading = true
      }, 400)
    },
    checkboxFn(item) {},
    revoke(item) {
      let data = [
        [
          {
            plateno: item.PLATE_NO,
            region: item.region
          }
        ]
      ]
      sendMsg(data, 1801, 'HMI').then(res => {
        this.dialogVisibleUp = false
        this.$message({
          message: '吊销成功',
          type: 'success'
        })
      })
    },
    subsection(item) {
      let resultArr = {
        parentId: '',
        childrenIds: []
      }
      for (let i = 0; i < item.children.length; i++) {
        resultArr.childrenIds.push({
          id: item.children[i].PLATE_NO,
          flag: item.children[i].checkboxM
        })
        resultArr.parentId = item.children[i].parentId
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
        this.$message({
          message: '分段成功',
          type: 'success'
        })
      })
    },
    openSx(id, region) {
      this.formUp.plantNo = id
      this.formUp.region = region
      this.dialogVisibleUp = true
    },
    saveUp() {
      let data = [
        [
          {
            plateno: this.formUp.plantNo,
            region: this.formUp.region,
            postion: this.formUp.postion
          }
        ]
      ]
      sendMsg(data, 1805, 'HMI').then(res => {
        this.dialogVisibleUp = false
        this.$message({
          message: '上线成功',
          type: 'success'
        })
      })
    },
    beforeClose() {
      this.dialogVisibleUp = false
    },
    handleSelectionChange() {},
    arraySpanMethod({ row, column, rowIndex, columnIndex }) {
      if (rowIndex == 0) {
        if (columnIndex == 1) {
          return [1, 3]
        } else if (columnIndex == 2 || columnIndex == 3) {
          return [0, 0]
        }
      }
    }
  }
}
</script>


<style scoped lang="less">
/deep/ .el-table__row td,
/deep/ .el-table__header th {
  padding: 3px 0 !important;
}
.cmd-box {
  > ul {
    > li {
      width: 10px;
      height: 10px;
      position: absolute;
      > img {
        display: block;
        width: 100%;
        height: 100%;
      }
    }
  }
}
.dcj2 {
  .bgc-white {
    background-color: #fff;
    box-shadow: 0px 0px 4px rgb(0 0 0 / 4%), 0px 0px 16px -2px rgb(0 0 0 / 10%);
    border-radius: 6px;
  }

  .banner {
    padding: 24px;
    width: 100%;

    .title {
      p {
        font-weight: 700;
        font-size: 20px;
        color: #606266;
      }
      margin-bottom: 10px;
    }

    .bgimg {
      width: 100%;
      height: 159px;
      position: relative;
      //overflow: hidden;
      .bgimg-box {
        width: 1632px;
        height: 100%;
        //background: url('../assets/2dcj.png') no-repeat 100% 100%;
        background: url('../assets/bg/dcj2.png') no-repeat 100% 100%;
      }

      .other {
        .cmd {
          width: 10px;
          height: 10px;
          position: absolute;

          &:nth-child(1) {
            top: 36px;
            left: 4px;
          }

          &:nth-child(2) {
            top: 36px;
            left: 36px;
          }

          &:nth-child(3) {
            top: 36px;
            left: 168px;
          }

          &:nth-child(4) {
            top: 36px;
            left: 258px;
          }

          &:nth-child(5) {
            top: 36px;
            left: 744px;
          }

          &:nth-child(6) {
            top: 36px;
            left: 802px;
          }

          &:nth-child(7) {
            top: 36px;
            left: 1226px;
          }

          img {
            display: block;
            width: 100%;
            height: 100%;
          }
        }
      }

      .other2 {
        .cmd {
          width: 10px;
          height: 10px;
          position: absolute;
          top: 402px;

          &:nth-child(1) {
            left: 750px;
          }

          &:nth-child(2) {
            left: 806px;
          }

          &:nth-child(3) {
            left: 1230px;
          }

          &:nth-child(4) {
            left: 1316px;
          }

          &:nth-child(5) {
            left: 1538px;
          }

          &:nth-child(6) {
            left: 1618px;
          }

          &:nth-child(7) {
            left: 1706px;
          }

          &:nth-child(8) {
            left: 1738px;
          }

          &:nth-child(9) {
            left: 1770px;
          }

          &:nth-child(10) {
            left: 1812px;
          }

          &:nth-child(11) {
            left: 2008px;
          }

          &:nth-child(12) {
            left: 2096px;
          }

          &:nth-child(13) {
            left: 2174px;
          }

          &:nth-child(14) {
            left: 2256px;
          }

          &:nth-child(15) {
            left: 2336px;
          }

          &:nth-child(16) {
            left: 2406px;
          }

          &:nth-child(17) {
            left: 2624px;
          }

          &:nth-child(18) {
            left: 2712px;
          }

          &:nth-child(19) {
            left: 2808px;
          }

          &:nth-child(20) {
            left: 2864px;
          }

          &:nth-child(21) {
            left: 2904px;
          }

          &:nth-child(22) {
            left: 3032px;
          }

          &:nth-child(23) {
            left: 3102px;
          }

          &:nth-child(24) {
            left: 3134px;
          }

          img {
            display: block;
            width: 100%;
            height: 100%;
          }
        }
      }

      .other3 {
        > span {
          position: absolute;
          font-weight: 600;

          &:nth-child(1) {
            top: 16px;
            left: 176px;
            color: #cd0808;
          }

          &:nth-child(2) {
            top: 455px;
            left: 1245px;
            color: #cd0808;
          }
        }
      }

      .one {
        position: absolute;
        top: 0px;
        left: 4px;
        width: 40px;
        height: 2px;
        cursor: pointer;
        //background-color: #a09393;
        background-color: #5e0f0f;
        font-size: 12px;
        text-align: center;

        > span {
          /*transform: scale(0.9);
          font-size: 12px;
          display: block;
          margin-top: -3px;
          color: #f50101;*/
          font-size: 18px;
          //color: #f50101;
          color: #ffffff;
          line-height: 44px;
          //transform: scale(0.9);
          display: block;
        }
      }
    }
  }

  .content {
    margin-top: 20px;

    .left-box {
      .left-top {
        padding: 20px;
        margin-bottom: 20px;
      }

      .left-bottom {
        padding: 20px;
      }

      margin-right: 20px;
    }

    .right-box {
      //height: 604px;

      .title {
        p {
          font-size: 16px;
          color: #606266;
          font-weight: 700;
          margin-bottom: 15px;
        }
      }
    }
  }

  /deep/ .el-input-group__append,
  /deep/ .el-input-group__prepend {
    padding: 0 6px;
  }
  /deep/ .el-form-item__content .el-input-group {
    vertical-align: baseline;
  }
  .set-info {
    .el-button--primary {
      background-color: #13356f;
      border-color: #13356f;
    }
    .bgcfff {
      background-color: #ffffff;
    }
    .type1 .el-form-item {
      //width: 50% !important;
    }
    .form-boder {
      .el-form {
        display: flex;
        width: 100%;
        flex-wrap: wrap;
        .dandu-item1 {
          /deep/.el-form-item__label {
            width: 120px !important;
          }
        }
        .dandu-item2 {
          /deep/.el-form-item__label {
            width: 10px;
          }
          /deep/.el-form-item__content {
            margin-left: 20px !important;
          }
        }
        .dandu-item {
          /deep/.el-form-item__label {
            width: 10px;
          }
          /deep/.el-form-item__content {
            margin-left: 0 !important;
          }
        }
        .el-form-item {
          //width: 50%;
          border: 1px solid #dcdfe6;
          padding: 1px 6px;
          width: 100%;
          height: 40px;
          line-height: 40px;
          margin-left: -1px;
          margin-bottom: -1px;
          /deep/ .el-input--mini .el-input__inner {
            height: 26px;
            line-height: 26px;
          }
        }
      }
    }
    .title {
      font-size: 16px;
      color: #606266;
      font-weight: bold;
    }
    .header {
      margin-bottom: 16px;
      .ps {
        font-size: 16px;
        color: #606266;
        font-weight: bold;
      }
    }
    .form-button {
      margin-top: 20px;
      display: flex;
      justify-content: flex-end;
    }
  }
}
/deep/ .el-table {
  .el-table__fixed-header-wrapper {
    .el-checkbox__inner {
      display: none !important;
    }
  }
}
</style>
