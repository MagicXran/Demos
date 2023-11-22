<template>
  <div class="jls">
    <div
      v-tag:tag="variable"
      data-page="jls"/>
    <div class="banner bgc-white">
      <!--      <div class="title">
        <p>矫直冷床双边剪</p>
      </div>-->
      <div class="bgimg">
        <div class="bgimg-box"/>
        <div class="track-box">
          <!-- 钢板 -->
          <trackItem
            :track-data="trackData"
            :top="44"
            :left="0"
            :type="1"
            @opdialog="opdialog"
            @getTableDataByTwo="getTableDataByTwo"
          />
          <!-- 光电开关图标 -->
          <div class="cmd-box">
            <ul>
              <li
                v-for="(item, index) in cmdList.slice(0,3)"
                v-if="item.value == 1"
                :style="'top:32px;'+'left:'+(item.x - 4)+'px'"
                :key="index">
                <img
                  src="../assets/green.png"
                  alt="">
              </li>
              <li
                v-for="(item, index) in cmdList.slice(3, cmdList.length)"
                v-if="item.value == 1"
                :style="'top:398px;'+'left:'+(item.x - 4)+'px'"
                :key="index+3">
                <img
                  src="../assets/green.png"
                  alt="">
              </li>
            </ul>
          </div>
          <div class="other3">
            <span>{{ gwj.gwj1 }}</span>
            <span>{{ gwj.gwj2 }}</span>
          </div>

          <!-- 退回辊道 -->
          <div class="uporback">
            <div class="upback-box">
              <div
                v-for="(item,key) in upbackList"
                :key="key"
                class="upback-item">
                <el-button
                  type="primary"
                  size="mini"
                  @click="upbackFn(item, item.onename)">{{ item.onename }}
                </el-button>
                <el-button
                  type="primary"
                  size="mini"
                  @click="upbackFn(item, item.twoname)">{{ item.twoname }}
                </el-button>
                <el-input
                  v-if="key == 0 && item.hangFlag == true || key == 2 && item.hangFlag == true || key == 4 && item.hangFlag == true"
                  v-model="item.lineData"
                  placeholder=""
                  disabled
                  @focus="openHang(item)">
                  <template slot="append">行</template>
                </el-input>
                <el-input
                  v-if="key == 0 && item.hangFlag == false|| key == 2&& item.hangFlag == false || key == 4 && item.hangFlag == false"
                  v-model="item.lineDataStatic"
                  placeholder=""
                  @blur="setHang(item ,key)">
                  <template slot="append">修</template>
                </el-input>
              </div>
            </div>
          </div>
          <warn-info
            :warn-type="1"
            :width="570"
            :pos-location="{
              top: 85,
              left: 1048,
            }"
          />
          <modif-info
            :poschangeshow="poschangeshow"
            :direction="'all'"
            :posboxsty="posboxsty"
            :pos-form="posForm"
            @submitPos="submitPos()"
            @closePos="closePos()"/>
        </div>
      </div>
    </div>

    <div class="content">
      <el-row>
        <el-col
          :span="7">
          <div class="right-box">
            <setInfo
              :type-flag="1"
              :type1-form="form"
              :type1-title="'双边剪设定'"
              @refreshHmi="getHmiData()"
              @closeRefresh="closeRefreshParent"
              @getTableDataByTwoSon="getTableDataByTwo"
            />
          </div>
        </el-col>
        <el-col :span="17">
          <steelInfo
            ref="steelinfo"
            @getTableDataByChild="tableLoading = false"
          />
        </el-col>
      </el-row>
    </div>


    <el-dialog
      :visible.sync="dialogVisibleUpLC"
      :before-close="beforeCloseLC"
      title="强制上冷床"
      width="20%">
      <el-form
        ref="form"
        :model="formUpLC"
        :rules="rules"
        label-width="80px">
        <el-form-item
          prop="plantNo1"
          label="板坯号1">
          <el-input
            v-model="formUpLC.plantNo1"
            class="clear-number-input"
            minlength="10"
            maxlength="14"
            clearable/>
        </el-form-item>
        <el-form-item
          label="板坯号2"
          prop="plantNo2">
          <el-input
            v-model="formUpLC.plantNo2"
            class="clear-number-input"
            clearable/>
        </el-form-item>
      </el-form>
      <span
        slot="footer"
        class="dialog-footer">
        <el-button @click="dialogVisibleUpLC = false">取 消</el-button>
        <el-button
          type="primary"
          @click="saveUpLC()">确 定</el-button>
      </span>
    </el-dialog>
  </div>
</template>

<script>
import { getHmiData, stopGetData, sendMsg, sendTag } from '@/lib/GetData'
import { deleteArrByName } from '@/lib/tools'
import warnInfo from '@/pages/components/warnInfo'
import steelInfo from '@/pages/components/steelInfo'
import setInfo from '@/pages/components/setInfo'
import modifInfo from '@/pages/components/modifInfo'
import trackItem from '@/pages/components/trackItem'

export default {
  name: 'Jls',
  components: { warnInfo, steelInfo, setInfo, modifInfo, trackItem },
  data() {
    return {
      gwj: {
        gwj1: 0,
        gwj2: 0
      },
      variable: [
        'rechmi2',
        'sele_fix',
        'DSS_Use_Flag',
        'L1DSSSET_PlateNo',
        'L1DSSSET_Plate_Len',
        'L1DSSSET_Plate_Wid',
        'L1DSSSET_Plate_Thk',
        'L1DSSSET_DSS_Wid',
        'DSS_Strength',
        'L1DSSSET_DSS_Empty',
        'CB1ROW',
        'CB2ROW',
        'CB3ROW',
        'L1DSSSET_DSS_Wid_MOD',
        'L1DSSSET_DSS_THK_MOD',
        'sele_fix_wid',
        'sele_fix_len',
        'HLTRACK.CMD6',
        'HLTRACK.CMD7',
        'HLTRACK.CMD5',
        'HLTRACK.CMD8',
        'CBTRACK.CMD1',
        'CBTRACK.CMD2',
        'CBTRACK.CMD3',
        'L1DSSTRACK.FDCMD1',
        'L1DSTRACK.EXDSCMD2',
        'L1DSSTRACK.DSSCMD1_1',
        'L1DSSTRACK.DSSCMD2_1',
        'L1DSSTRACK.DSSCMD3_1',
        'L1DSSTRACK.DSSCMD4_1',
        'L1DSSTRACK.DSSCMD5_1',
        'L1DSSTRACK.DSSCMD6',
        'L1DSSTRACK.DSSCMD7',
        'CBTRACK.ENCBHDT',
        'CBTRACK.EXCBHDT'
      ],
      cmdList: [
        {
          key: 'HLTRACK.CMD5',
          value: '',
          x: 433.1833061
        },
        {
          key: 'HLTRACK.CMD7',
          value: '',
          x: 499.4680851
        },
        {
          key: 'HLTRACK.CMD6',
          value: '',
          x: 932.2422259
        },
        {
          key: 'CBTRACK.CMD1',
          value: '',
          x: 443.4288052
        },
        {
          key: 'CBTRACK.CMD2',
          value: '',
          x: 500.7119476
        },
        {
          key: 'CBTRACK.CMD3',
          value: '',
          x: 936.1047463
        },
        {
          key: 'L1DSSTRACK.FDCMD1',
          value: '',
          x: 1021.481178
        },
        /*{
          key: 'L1DSTRACK.EXDSCMD2',
          value: '',
          x: 1040.261866
        },*/
        {
          key: 'L1DSSTRACK.DSSCMD1_1',
          value: '',
          x: 1171.252046
        },
        {
          key: 'L1DSSTRACK.DSSCMD2_1',
          value: '',
          x: 1256.824877
        },
        {
          key: 'L1DSSTRACK.DSSCMD3_1',
          value: '',
          x: 1334.509002
        },
        {
          key: 'L1DSSTRACK.DSSCMD4_1',
          value: '',
          x: 1423.91162
        },
        {
          key: 'L1DSSTRACK.DSSCMD5_1',
          value: '',
          x: 1456.047463
        },
        {
          key: 'L1DSSTRACK.DSSCMD6',
          value: '',
          x: 1495.12275
        },
        {
          key: 'L1DSSTRACK.DSSCMD7',
          value: '',
          x: 1533.11784
        }
      ],
      //2 钢板号打开  1 其他打开 3 都打开
      isReadOnly: 3,
      tableLoading: false,
      currentId: [],
      rules: {
        plantNo1: [
          {
            min: 10,
            max: 14,
            message: '长度在 10 到 14 个字符',
            trigger: 'blur'
          }
        ],
        plantNo2: [
          {
            min: 10,
            max: 14,
            message: '长度在 10 到 14 个字符',
            trigger: 'blur'
          }
        ]
      },
      formUpLC: {
        cbno: '',
        plantNo1: '',
        plantNo2: ''
      },
      formUp: {
        postion: '',
        plantNo: '',
        region: ''
      },
      dialogVisibleUpLC: false,
      timer: null,
      poschangeshow: false,
      posForm: {
        oldId: '',
        plant: '',
        radio: '1',
        unit: 1,
        num: '',
        region: ''
      },
      upbackList: [
        {
          onename: '退回辊道',
          twoname: '上冷床',
          lineData: '',
          lineDataStatic: '',
          cb_no: 1,
          hangFlag: true
        },
        {
          onename: '退回冷床',
          twoname: '下冷床',
          lineData: '',
          lineDataStatic: '',
          cb_no: 1,
          hangFlag: true
        },
        {
          onename: '退回辊道',
          twoname: '上冷床',
          lineData: '',
          lineDataStatic: '',
          cb_no: 2,
          hangFlag: true
        },
        {
          onename: '退回冷床',
          twoname: '下冷床',
          lineData: '',
          lineDataStatic: '',
          cb_no: 2,
          hangFlag: true
        },
        {
          onename: '退回辊道',
          twoname: '上冷床',
          lineData: '',
          lineDataStatic: '',
          cb_no: 3,
          hangFlag: true
        },
        {
          onename: '退回冷床',
          twoname: '下冷床',
          lineData: '',
          lineDataStatic: '',
          cb_no: 3,
          hangFlag: true
        }
      ],
      form: {
        DSS_Use_Flag: '',
        L1DSSSET_PlateNo: '',
        L1DSSSET_Plate_Len: '',
        L1DSSSET_Plate_Wid: '',
        L1DSSSET_Plate_Thk: '',
        L1DSSSET_DSS_Wid: '',
        L1DSSSET_DSS_Empty: '',
        DSS_Strength: '',
        sele_fix: '',
        L1DSSSET_DSS_Wid_MOD: '',
        L1DSSSET_DSS_THK_MOD: '',
        sele_fix_wid: '',
        sele_fix_len: ''
      },
      trackData: [],
      steelTablePar: [],
      posboxsty: {
        top: '',
        left: ''
      },
      checkboxData: [],
      currentDblSteelInfo: {},
      hangNum: 0
    }
  },
  mounted() {
    this.getHmiData()
  },
  destroyed() {
    stopGetData()
  },
  methods: {
    closeRefreshParent(tagName) {},
    initHang(data) {
      this.upbackList[0].lineData = data['CB1ROW']
      this.upbackList[2].lineData = data['CB2ROW']
      this.upbackList[4].lineData = data['CB3ROW']
    },
    openHang(item) {
      item.hangFlag = false
    },
    setHang(item, index) {
      this.hangNum++
      if (this.hangNum <= 1) return
      console.log('dynamic')
      this.$confirm('是否确定修改冷床钢板行数, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          let tt = {
            0: {
              CB1ROW: this.upbackList[0].lineDataStatic
            },
            2: {
              CB2ROW: this.upbackList[2].lineDataStatic
            },
            4: {
              CB3ROW: this.upbackList[4].lineDataStatic
            }
          }
          let data = tt[index]
          sendTag(data).then(res => {
            this.$message({
              type: 'success',
              // message: res.results[0][0].msg
              message: '修改成功'
            })
            item.hangFlag = true
            this.hangNum = 0
            this.getHmiData() // 打开
          })
        })
        .catch(() => {
          this.$message({
            type: 'info',
            message: '已取消修改'
          })
          item.hangFlag = true
          this.hangNum = 0
          this.getHmiData() // 打开
        })
    },
    upbackFn(item, name) {
      if (name == '上冷床') {
        this.dialogVisibleUpLC = true
        //单独处理
        this.formUpLC.cbno = item.cb_no
        let data = [
          [
            {
              cbno: item.cb_no,
              plateno1: '',
              plateno2: '',
              platenum: '',
              frequency: '1' //frequency：接口使用次数（点击“上冷床”按钮时为1，点击弹窗内"确定"按钮为2）
            }
          ]
        ]
        //
        this.formUpLC.plantNo1 = ''
        this.formUpLC.plantNo2 = ''
        //查询钢板号信息
        sendMsg(data, 1811, 'HMI').then(res => {
          if (res.results[0][0].platenum == 1) {
            this.formUpLC.plantNo1 = res.results[0][0].plateno1
          } else if (res.results[0][0].platenum == 2) {
            this.formUpLC.plantNo1 = res.results[0][0].plateno1
            this.formUpLC.plantNo2 = res.results[0][0].plateno2
          }
          console.log('强制上冷床', res.results[0])
        })
      } else {
        let bt = ''
        switch (name) {
          case '退回辊道':
            bt = 1
            break
          case '上冷床':
            bt = 2
            break
          case '退回冷床':
            bt = 3
            break
          case '下冷床':
            bt = 4
        }
        let data = [
          [
            {
              cb_no: item.cb_no,
              button: bt
            }
          ]
        ]
        this.$confirm('是否' + name + ', 是否继续?', '提示', {
          confirmButtonText: '确定',
          cancelButtonText: '取消',
          type: 'warning'
        })
          .then(() => {
            sendMsg(data, 1809, 'HMI').then(res => {
              this.dialogVisibleUp = false
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
              message: '已取消' + name + ''
            })
          })
      }
    },
    saveUpLC() {
      let uPattern = /^[Z0-9_-]+$/ //数字0-9
      if (this.formUpLC.plantNo1 == '' && this.formUpLC.plantNo2 == '') {
        alert('请输入钢板号')
        return
      }
      if (
        !uPattern.test(this.formUpLC.plantNo1) &&
        !uPattern.test(this.formUpLC.plantNo2)
      ) {
        alert('请输入正确钢板号，钢板号只含有数字，-，_')
        return
      }
      let num = 0
      if (this.formUpLC.plantNo1 == '' || this.formUpLC.plantNo2 == '') {
        num = 1
      } else if (this.formUpLC.plantNo1 != '' && this.formUpLC.plantNo2 != '') {
        num = 2
      }
      console.log(this.formUpLC)
      let data = [
        [
          {
            cbno: this.formUpLC.cbno,
            plateno1: this.formUpLC.plantNo1,
            plateno2: this.formUpLC.plantNo2,
            platenum: num,
            frequency: '2' //frequency：接口使用次数（点击“上冷床”按钮时为1，点击弹窗内"确定"按钮为2）
          }
        ]
      ]
      sendMsg(data, 1811, 'HMI').then(res => {
        console.log(res)
        if (res.results[0][0].msg) {
          // alert(res.results[0][0].msg)
          this.$message({
            type: 'success',
            message: res.results[0][0].msg
          })
        }
        this.dialogVisibleUpLC = false
      })
    },
    beforeCloseLC() {
      this.dialogVisibleUpLC = false
    },
    handleChangeNum() {
      this.isReadOnly = 1
    },
    //双击钢板修改信息相关方法
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
    closePos() {
      this.posForm.num = ''
      this.poschangeshow = false
    },
    submitPos() {
      this.poschangeshow = false
      this.posForm.num = ''
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
    //封装成对象方法使用
    trackSteel(data) {
      // 14==>47
      // 页面和实际比例 以整个图为例 宽度: 实际40m  页面367px  双边剪  长度: 实际198.248m  页面长度 1622px
      // 辊道 宽度 3.51 页面 30px
      let [actWid, pageWid, actLen, pageLen, actgd, pagegd] = [
        40 * 1000,
        367,
        198.248 * 1000,
        1622,
        3.51 * 1000,
        30
      ]
      this.trackData = []
      for (let i = 0; i < data['rechmi2'].length; i++) {
        let item = data['rechmi2'][i]
        /*region==2:1号冷床
        region==3:2号冷床
        region==4:3号冷床*/
        //修改width和定位left(tailpos)值即可
        if (item.region == 2 || item.region == 3 || item.region == 4) {
          this.trackData.push({
            width: this.countSteelLeng(actLen, pageLen, item.platelenmeas_cb),
            tailpos: this.countSteeltail(actLen, pageLen, item.tail_x_cb),
            height: this.countSteelWid(actWid, pageWid, item.platewid),
            vPos:
              this.countSteelPosY(actWid, pageWid, item.v_pos) +
              (pagegd - this.countSteelWid(actgd, pagegd, item.platewid)) / 2, //计算辊道中心位置
            plateno: item.plateno,
            platenoSimple:
              item.platelenmeas > 12000
                ? item.plateno
                : '..' + item.plateno.slice(5, item.plateno.length),
            platethk: item.platethk,
            platewid: item.platewid,
            platelen: item.platelenmeas,
            platewet: item.platewet,
            cbdec: item.cbdec,
            region: item.region,
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
        } else {
          this.trackData.push({
            width: this.countSteelLeng(actLen, pageLen, item.platelenmeas),
            tailpos: this.countSteeltail(actLen, pageLen, item.tail_x),
            height: this.countSteelWid(actWid, pageWid, item.platewid),
            vPos:
              this.countSteelPosY(actWid, pageWid, item.v_pos) +
              (pagegd - this.countSteelWid(actgd, pagegd, item.platewid)) / 2, //计算辊道中心位置
            plateno: item.plateno,
            platenoSimple:
              item.platelenmeas > 12000
                ? item.plateno
                : '..' + item.plateno.slice(5, item.plateno.length),
            platethk: item.platethk,
            platewid: item.platewid,
            platelen: item.platelenmeas,
            platewet: item.platewet,
            cbdec: item.cbdec,
            region: item.region,
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
      }
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
      console.log('打开HMI')
      getHmiData(
        'jls',
        data => {
          data['rechmi2'].forEach(item => {
            item.tailX = item.tail_x
            item.Vpos = item.v_pos
            item.headX = item.head_x
          })
          data['rechmi2'].map((item, index) => {
            item.tail_x = item.tail_x - 40400
            item.tail_x_cb = item.tail_x_cb - 40400
          })

          this.trackSteel(data)
          this.getTableDataByProcess(data)
          this.initHang(data)
          this.initCmd(data)
          this.getGWJData(data)
          this.initFormData(data)
          // stopGetData()
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
    initFormData(data) {
      //sele_fix ==1 偏差值，0固定
      this.form.DSS_Use_Flag = data['DSS_Use_Flag'] == 1 ? true : false
      this.form.L1DSSSET_PlateNo = data['L1DSSSET_PlateNo']
      this.form.L1DSSSET_Plate_Len = data['L1DSSSET_Plate_Len'].toFixed(2)
      this.form.L1DSSSET_Plate_Wid = data['L1DSSSET_Plate_Wid'].toFixed(2)
      this.form.L1DSSSET_Plate_Thk = data['L1DSSSET_Plate_Thk'].toFixed(2)
      this.form.L1DSSSET_DSS_Wid = data['L1DSSSET_DSS_Wid'].toFixed(2)
      this.form.L1DSSSET_DSS_Wid_MOD = data['L1DSSSET_DSS_Wid_MOD'].toFixed(2)
      this.form.L1DSSSET_DSS_THK_MOD = data['L1DSSSET_DSS_THK_MOD'].toFixed(2)
      this.form.L1DSSSET_DSS_Empty =
        data['L1DSSSET_DSS_Empty'] == 1 ? true : false
      this.form.DSS_Strength = data['DSS_Strength']
      this.form.sele_fix = data['sele_fix'] == 0 ? true : false
    },
    closeRefresh() {
      //获取焦点关闭时候刷新 让用户可以刷新
      console.log('focus')
      stopGetData()
    },
    arraySpanMethod({ row, column, rowIndex, columnIndex }) {
      if (rowIndex == 0) {
        if (columnIndex == 1) {
          return [1, 3]
        } else if (columnIndex == 2 || columnIndex == 3) {
          return [0, 0]
        }
      }
    },
    getTableDataByProcess(data) {
      let fordata = data['rechmi2']
      for (let i = 0; i < fordata.length; i++) {
        if (fordata[i].process == 1) {
          // console.log('已存在数组', this.currentId)
          if (this.currentId.indexOf(fordata[i].plateno) < 0) {
            this.currentId.push(fordata[i].plateno)
            console.log(
              '触发process == 1 此时钢板号==' +
                fordata[i].plateno +
                '------process == ' +
                fordata[i].process
            )
            this.getTableDataByTwo(fordata[i].plateno, 0)
          }
        }
      }
    },
    getTableDataByTwo(plateno, type, itemInfo) {
      if (!itemInfo) {
        itemInfo = {
          region: 0
        }
      }
      //process == 0 点击钢板查询 其他从记录集获取
      clearTimeout(this.timer)
      this.timer = setTimeout(() => {
        this.$refs.steelinfo.getTableDataChild(plateno, type, itemInfo.region)
        this.tableLoading = true
      }, 400)
    },
    getGWJData(data) {
      this.gwj.gwj1 = data['CBTRACK.ENCBHDT'].toFixed(0)
      this.gwj.gwj2 = data['CBTRACK.EXCBHDT'].toFixed(0)
    }
  }
}
</script>


<style scoped lang="less">
/deep/ .el-tooltip__popper {
  white-space: pre-line !important;
  font-size: 14px;
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

.clear-number-input ::v-deep input[type='number']::-webkit-outer-spin-button,
.clear-number-input ::v-deep input[type='number']::-webkit-inner-spin-button {
  -webkit-appearance: none !important;
}

.el-tooltip__popper {
  white-space: pre-line !important;
  font-size: 14px;
}

.pos-change {
  position: absolute;
  top: 100px;
  left: 300px;
  width: 360px;
  z-index: 999;

  .el-card {
    border: 2px solid #dcdfe6;
  }

  .el-form-item {
    margin-bottom: 2px;
  }

  .el-radio {
    margin-right: 20px;
  }

  /deep/ .el-card__header {
    padding: 10px 20px;
  }

  /deep/ .el-input__inner {
    //width: 150px;
    height: 28px;
  }

  /deep/ .el-card__body {
    padding: 0px;
  }

  .body1 {
    padding: 10px 20px;
    //border-bottom: 1px solid #ebeef5;
  }

  .body2 {
    padding: 0 20px;
  }
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

.jls {
  .form-boder {
    .el-form {
      display: flex;
      width: 100%;
      flex-wrap: wrap;

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
      height: 659px;
      position: relative;
      //overflow: hidden;

      .bgimg-box {
        height: 100%;
        //background: url('../assets/jzlcsbj.png') no-repeat;
        background: url('../assets/bg/jls.png') no-repeat;
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
            top: 15px;
            left: 153px;
            color: #cd0808;
          }

          &:nth-child(2) {
            top: 450px;
            left: 945px;
            color: #cd0808;
          }
        }
      }

      .uporback {
        .upback-box {
          .upback-item {
            &:nth-child(1) {
              //left: 427px;  8px  32px
              //top: 47px;
              left: 435px;
              top: 79px;
            }

            &:nth-child(2) {
              left: 435px;
              top: 319px;
            }

            &:nth-child(3) {
              left: 935px;
              top: 79px;
            }

            &:nth-child(4) {
              left: 935px;
              top: 319px;
            }

            &:nth-child(5) {
              left: 435px;
              top: 446px;
            }

            &:nth-child(6) {
              left: 435px;
              top: 582px;
            }

            width: 60px;
            position: absolute;

            .el-button {
              margin-left: 0px;
              padding: 4px 3px;
              margin-bottom: 2px;
              width: 58px;
            }

            .el-input {
              /deep/ .el-input__inner {
                height: 26px;
                line-height: 26px;
                font-size: 12px;
                padding: 0px;
                padding-left: 6px;
              }

              /deep/ .el-input-group__append {
                padding: 0 5px;
              }
            }
          }
        }
      }

      /*.one {
        position: absolute;
        top: 12px;
        left: 0px;
        width: 100px;
        height: 22px;
        cursor: pointer;
        //background-color: #a09393;
        background-color: #5e0f0f;
        font-size: 12px;
        text-align: center;

        > span {
          !*transform: scale(0.9);
          font-size: 12px;
          display: block;
          margin-top: -3px;
          color: #f50101;*!
          font-size: 12px;
          //color: #f50101;
          color: #ffffff;
          //line-height: 22px;
          //transform: scale(0.9);
          font-size: 12px;
          display: block;
        }
      }*/

      /* .two {
        position: absolute;
        height: 22px;
        width: 40px;
        background-color: #910606;
        top: 265px;
        left: 83px;
      }

      .three {
        position: absolute;
        height: 22px;
        width: 40px;
        background-color: #910606;
        top: 476px;
        left: 83px;
      }

      .cool-one {
        position: absolute;
        width: 30px;
        height: 25px;
        left: 0px;
        top: 53px;
        background-color: #910606;
      }*/
    }
  }

  .content {
    margin-top: 20px;

    .right-box {
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
        //margin-bottom: 10px;
        padding: 0px 10px;
        display: flex;
        justify-content: space-between;
        align-items: baseline;

        p {
          font-size: 16px;
          color: #606266;
          font-weight: 700;
          margin-bottom: 5px;
        }
      }
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
