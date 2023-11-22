<template>
  <div class="lcb">
    <div
      v-tag:tag="variable"
      data-page="1dcj"/>
    <div class="banner bgc-white">
      <div class="bgimg">
        <div class="bgimg-box"/>
        <div class="track-box">
          <div class="cmd-box">
            <ul>
              <li
                v-for="(item, index) in cmdList"
                v-if="item.value == 1"
                :style="'top:58px;'+'left:'+(item.x - 1 )+'px'"
                :key="index">
                <img
                  src="../assets/green.png"
                  alt="">
              </li>
            </ul>
          </div>
          <trackItem
            :track-data="trackData"
            :top="70"
            :left="0"
            :type="1"
            @opdialog="opdialog"
            @getTableDataByTwo="getTableDataByTwo"
          />
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
          :span="15"
        >
          <setInfo
            :type-flag="2"
            :type2-form="form"
            :type2-table-set = "tableFrom1"
            :type2-table-act = "tableFrom2"
            @refreshHmi="getHmiData()"
            @getTableDataByTwoSon="getTableDataByTwo"
            @bigSaveSet="bigSaveSet"
            @realLength="realLength"
          />
        </el-col>
        <el-col
          :span="9">
          <div
            class="bgc-white"
            style="padding: 24px;display: flex; ustify-content: space-between;">
            <div style="width: 55%;">
              <div class="header">
                <p class="ps">取样机器人设定</p>
                <p
                  v-if="!form3.changeFlag"
                  style="color: #FFA958;font-size: 13px">修改中... <i
                    style="font-size: 20px;cursor: pointer"
                    class="el-icon-circle-close"
                    @click="openRefresh(form3)"
                /></p>
                <div
                  v-if="form3.changeFlag"
                  class="cz">
                  <div>
                    <span
                      style="font-size: 14px;
                                vertical-align: bottom;
                                color: #606266;
                                letter-spacing: 1px;
                                font-weight: 600;">L2投用</span>
                    <el-switch
                      v-model="form3.L1SAMPSET_UseFlag"
                      active-color="green"
                      inactive-color="red"
                      @change="closeRefresh(form3)"/>
                  </div>
                </div>
                <div
                  v-if="!form3.changeFlag"
                  class="cz">
                  <div>
                    <span
                      style="font-size: 14px;
                                vertical-align: bottom;
                                color: #606266;
                                letter-spacing: 1px;
                                font-weight: 600;">L2投用</span>
                    <el-switch
                      v-model="form3Change.L1SAMPSET_UseFlag"
                      active-color="green"
                      inactive-color="red"/>
                  </div>
                </div>
              </div>
              <div
                v-if="form3.changeFlag"
                class="form-boder">
                <el-form
                  ref="form"
                  :model="form3"
                  label-width="80px">
                  <el-form-item label="钢板号">
                    <el-input
                      v-model="form3.L1SAMPSET_PlateNo"
                      size="mini"
                      @focus="closeRefresh(form3)">
                      <el-button
                        slot="append"
                        icon="el-icon-search"
                        @click="getTableDataByTwo(form3.L1SAMPSET_PlateNo,3)"/>
                    </el-input>
                  </el-form-item>
                  <el-form-item label="样条长">
                    <el-input
                      v-model="form3.L1SAMPSET_Plate_Len"
                      size="mini"
                      @focus="closeRefresh(form3)">
                      <template slot="append">mm</template>
                    </el-input>
                  </el-form-item>
                  <el-form-item label="样条宽">
                    <el-input
                      v-model="form3.L1SAMPSET_Plate_Wid"
                      size="mini"
                      @focus="closeRefresh(form3)">
                      <template slot="append">mm</template>
                    </el-input>
                  </el-form-item>
                  <el-form-item label="样条厚">
                    <el-input
                      v-model="form3.L1SAMPSET_Plate_Thk"
                      size="mini"
                      @focus="closeRefresh(form3)">
                      <template slot="append">mm</template>
                    </el-input>
                  </el-form-item>
                  <el-form-item label="下发方式">
                    <template>
                      <el-radio
                        v-model="form3.L1SAMPSET_Samp_Type"
                        style="margin-right: 5px"
                        label="0"
                        @input="closeRefresh(form3)">并样</el-radio>
                      <el-radio
                        v-model="form3.L1SAMPSET_Samp_Type"
                        style="margin-right: 5px"
                        label="1"
                        @input="closeRefresh(form3)">正样</el-radio>
                      <el-radio
                        v-model="form3.L1SAMPSET_Samp_Type"
                        style="margin-right: 5px"
                        label="2"
                        @input="closeRefresh(form3)">备样</el-radio>
                    </template>
                  </el-form-item>
                </el-form>
              </div>
              <div
                v-if="!form3.changeFlag"
                class="form-boder">
                <el-form
                  ref="form"
                  :model="form3Change"
                  label-width="80px">
                  <el-form-item label="钢板号">
                    <el-input
                      v-model="form3Change.L1SAMPSET_PlateNo"
                      size="mini"
                    >
                      <el-button
                        slot="append"
                        icon="el-icon-search"
                        @click="getTableDataByTwo(form3Change.L1SAMPSET_PlateNo,3)"
                      />
                    </el-input>
                  </el-form-item>
                  <el-form-item label="样条长">
                    <el-input
                      v-model="form3Change.L1SAMPSET_Plate_Len"
                      size="mini">
                      <template slot="append">mm</template>
                    </el-input>
                  </el-form-item>
                  <el-form-item label="样条宽">
                    <el-input
                      v-model="form3Change.L1SAMPSET_Plate_Wid"
                      size="mini">
                      <template slot="append">mm</template>
                    </el-input>
                  </el-form-item>
                  <el-form-item label="样条厚">
                    <el-input
                      v-model="form3Change.L1SAMPSET_Plate_Thk"
                      size="mini">
                      <template slot="append">mm</template>
                    </el-input>
                  </el-form-item>
                  <el-form-item label="下发方式">
                    <template>
                      <el-radio
                        v-model="form3Change.L1SAMPSET_Samp_Type"
                        style="margin-right: 0"
                        label="0">并样下发</el-radio>
                      <el-radio
                        v-model="form3Change.L1SAMPSET_Samp_Type"
                        style="margin-right: 0"
                        label="1">正样下发</el-radio>
                      <el-radio
                        v-model="form3Change.L1SAMPSET_Samp_Type"
                        style="margin-right: 0"
                        label="2">是否备样</el-radio>
                    </template>
                  </el-form-item>
                </el-form>
              </div>
              <div class="form-button">
                <el-button
                  type="primary"
                  size="mini"
                  @click="againSet(3)">重新设定
                </el-button>
                <el-button
                  type="primary"
                  size="mini"
                  @click="saveSet(3)">修改
                </el-button>
              </div>
            </div>
            <div style="width: 40%;padding:40px 1px 1px 1px;margin-left: 30px">
              <div
                class="form-boder">
                <el-form
                  v-if="form3.sampsLenFlag"
                  ref="form"
                  :model="form3"
                  label-width="80px">
                  <el-form-item label="输入正样">
                    <el-switch
                      v-model="form3.L1SAMPSET_Manual"
                      active-color="#13356F"
                      inactive-color="#5e0f0f"
                      @change="allowSetSampsLen()"
                    />
                  </el-form-item>
                  <div
                    style="overflow-y: scroll; height: 155px;padding: 0px 1px 1px 1px">
                    <el-form-item
                      v-for="(item, index) in form3.L1SAMPSET_Samps_Len"
                      :key="index"
                      :label="String(index + 1)"
                      style="height: auto">
                      <el-input
                        v-model="item.samp_len"
                        size="mini"
                        @focus="changeIsTrue"
                      >
                        <template slot="append">mm</template>
                      </el-input>
                    </el-form-item>
                  </div>
                </el-form>
                <el-form
                  v-if="!form3.sampsLenFlag"
                  ref="form"
                  :model="form3Change"
                  label-width="80px">
                  <el-form-item label="输入正样">
                    <el-switch
                      v-model="form3Change.L1SAMPSET_Manual"
                      active-color="#13356F"
                      inactive-color="#5e0f0f"

                    />
                    <p
                      v-if="isTrue"
                      style="color: #FFA958;font-size: 13px;display: inline; margin-left: 10px;">修改中... <i
                        style="font-size: 20px;cursor: pointer"
                        class="el-icon-circle-close"
                        @click="form3.sampsLenFlag = true"
                    /></p>
                  </el-form-item>
                  <div
                    style="overflow-y: scroll; height: 155px;padding: 0px 1px 1px 1px">
                    <el-form-item
                      v-for="(item, index) in form3Change.L1SAMPSET_Samps_Len"
                      :key="index"
                      :label="String(index + 1)"
                      style="height: auto">
                      <el-input
                        v-model="item.samp_len"
                        size="mini"
                      >
                        <template slot="append">mm</template>
                      </el-input>
                    </el-form-item>
                  </div>
                </el-form>
                <div class="sampleBtn">
                  <el-button
                    type="primary"
                    size="mini"
                    @click="saveSet(4)">修改
                  </el-button>
                  <el-button
                    type="primary"
                    size="mini"
                    @click="changeEmpty">一键清空
                  </el-button>
                </div>

              </div>
            </div>
          </div>
        </el-col>
      </el-row>
      <el-row style="margin-bottom: 20px">
        <el-col :span="24">
          <steelInfo
            ref="steelinfo"
            @getTableDataByChild="tableLoading = false"
          />
        </el-col>
      </el-row>
      <el-row>
        <el-col :span="24">
          <warn-info
            :warn-type="2"
          />
        </el-col>
      </el-row>

    </div>
    <el-dialog
      :visible.sync="dialogVisibleBigSet"
      :before-close="beforeCloseBigSet"
      title="设定信息-修改"
      width="40%">
      <el-form
        ref="form"
        :model="formBigSet"
        style="display: flex;flex-wrap: wrap;"
        label-width="80px">
        <el-form-item
          prop=""
          label="板坯号">
          <el-input v-model="formBigSet.L1DSSET_PlateNo" >
            <template slot="append">mm</template>
          </el-input>
        </el-form-item>
        <el-form-item
          prop=""
          label="母板长度">
          <el-input v-model="formBigSet.L1DSSET_Plate_Len" >
            <template slot="append">mm</template>
          </el-input>
        </el-form-item>
        <el-form-item
          prop=""
          label="母板宽度">
          <el-input v-model="formBigSet.L1DSSET_Plate_Wid" >
            <template slot="append">mm</template>
          </el-input>
        </el-form-item>
        <el-form-item
          prop=""
          label="母板厚度">
          <el-input v-model="formBigSet.L1DSSET_Plate_Thk" >
            <template slot="append">mm</template>
          </el-input>
        </el-form-item>
      </el-form>
      <el-table
        :data="formBigSetList"
        border
      >
        <el-table-column
          :index="1"
          type="index"
          width="60"
          label="序号"
          align="left"/>
        <el-table-column
          label="剪切类型"
          width="250"
          align="left">
          <template slot-scope="scope">
            <el-select
              v-model="scope.row.selectModel"
              size="small"
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
              size="small"
            >
              <template slot="append">mm</template>
            </el-input>
          </template>
        </el-table-column>
      </el-table>
      <span
        slot="footer"
        class="dialog-footer">
        <el-button @click="dialogVisibleBigSet = false">取 消</el-button>
        <el-button
          type="primary"
          @click="saveClose()">ok(关闭弹窗)</el-button>
        <el-button
          type="primary"
          @click="saveOpen()">应用(保留弹窗)</el-button>
      </span>
    </el-dialog>
    <el-dialog
      :visible.sync="dialogVisibleReal"
      :before-close="handleCloseReal"
      :modal="false"
      top="300px"
      title=""
      width="23%">
      <el-checkbox
        v-model="shanChecked"
        style="font-weight: bold;letter-spacing: 1px;"
        @change="changeCheck()">开启闪烁功能</el-checkbox>
      <h1
        :class="shanshuoFlag==true?'blink':''"
        style="font-size: 80px;text-align: center;letter-spacing: 2px;color: #000;height: 100px">{{ Number(real_mat_len).toFixed(1) }}</h1>
      <span
        slot="footer"
        class="dialog-footer">
        <el-button
          type="primary"
          @click="handleCloseShan()">关闭闪烁</el-button>
        <el-button @click="handleCloseReal()">关 闭</el-button>
      </span>
    </el-dialog>
  </div>
</template>

<script>
import HmiTable from '@/components/HmiTable'
import {
  getHmiData,
  getHmiDataByEvent,
  sendMsg,
  sendTag,
  stopGetData
} from '@/lib/GetData'
import warnInfo from '@/pages/components/warnInfo'
import setInfo from '@/pages/components/setInfo'
import steelInfo from '@/pages/components/steelInfo'
import modifInfo from '@/pages/components/modifInfo'
import trackItem from '@/pages/components/trackItem'
export default {
  name: 'Dcj1',
  components: { warnInfo, HmiTable, setInfo, steelInfo, modifInfo, trackItem },
  data() {
    return {
      variable: [
        'rechmi3',
        'L1DSSET_PlateNo',
        'L1DSSET_Plate_Len',
        'L1DSSET_Plate_Wid',
        'L1DSSET_Plate_Thk',
        'L1DSSET_Steelgrade',
        'L1DSSET_UseFlag',
        'L1DSSET_FLAG',
        'L1DSCOM_HMI',
        'L1DSSET_HMI',
        'L1DSTRACK.ENDSCMD1_1',
        'L1DSTRACK.ENDSCMD2_1',
        'L1DSTRACK.ENDSCMD3_1',
        'L1DSTRACK.ENDSCMD4_1',
        'L1DSTRACK.ENDSCMD5_1',
        'L1DSTRACK.ENDSCMD6_1',
        'L1DSTRACK.EXDSCMD1',
        'L1DSTRACK.EXDSCMD2',
        'L1DSTRACK.EXDSCMD3',
        'L1DSTRACK.EXDSCMD4',
        'L1DSTRACK.EXDSCMD5',
        //取样机器人
        'L1SAMPSET_PlateNo',
        'L1SAMPSET_Steelgrade',
        'L1SAMPSET_Plate_Len',
        'L1SAMPSET_Plate_Wid',
        'L1SAMPSET_Plate_Thk',
        'L1SAMPSET_UseFlag',
        'L1SAMPSET_ModFlag',
        'L1SAMPSET_Samp_Type',
        'L1SAMPSET_Manual',
        'L1SAMPSET_Samps_Len',
        'L1LMSSCAN.mat_len_meas',
        'L1LMSSCAN_Flicker'
      ],
      cmdList: [
        {
          key: 'L1DSTRACK.ENDSCMD1_1',
          value: '',
          x: 0
        },
        {
          key: 'L1DSTRACK.ENDSCMD2_1',
          value: '',
          x: 152.2261484
        },
        {
          key: 'L1DSTRACK.ENDSCMD3_1',
          value: '',
          x: 293.0883392
        },
        {
          key: 'L1DSTRACK.ENDSCMD4_1',
          value: '',
          x: 435.8303887
        },
        {
          key: 'L1DSTRACK.ENDSCMD5_1',
          value: '',
          x: 577.1448763
        },
        {
          key: 'L1DSTRACK.ENDSCMD6_1',
          value: '',
          x: 703.0812721
        },
        {
          key: 'L1DSTRACK.EXDSCMD1',
          value: '',
          x: 1084.805654
        },
        {
          key: 'L1DSTRACK.EXDSCMD2',
          value: '',
          x: 1252.897527
        },
        {
          key: 'L1DSTRACK.EXDSCMD3',
          value: '',
          x: 1415.717314
        },
        {
          key: 'L1DSTRACK.EXDSCMD4',
          value: '',
          x: 1506.24735
        },
        {
          key: 'L1DSTRACK.EXDSCMD5',
          value: '',
          x: 1610.113074
        }
      ],
      dialogVisibleUp: false,
      dialogVisibleReal: false,
      timerRealLen: null,
      real_mat_len: 0,
      shanshuoFlag: true,
      shanChecked: false,
      currentId: [],
      formUp: {
        postion: '',
        plantNo: '',
        region: ''
      },
      tableLoading: false,
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
      tableFrom1: [],
      tableFrom2: [],
      steelTablePar: [{}, {}, {}],
      trackData: [],
      form: {
        L1DSSET_UseFlag: '',
        L1DSSET_FLAG: '',
        L1DSSET_PlateNo: '',
        L1DSSET_Steelgrade: '',
        L1DSSET_Plate_Len: '',
        L1DSSET_Plate_Wid: '',
        L1DSSET_Plate_Thk: '',
        L1DSSET_DSS_Wid: '',
        L1DSSET_DSS_Empty: ''
      },
      //取样机器人
      form3: {
        sampsLenFlag: true,
        changeFlag: true,
        L1SAMPSET_PlateNo: '',
        L1SAMPSET_Steelgrade: '',
        L1SAMPSET_Plate_Len: '',
        L1SAMPSET_Plate_Wid: '',
        L1SAMPSET_Plate_Thk: '',
        L1SAMPSET_UseFlag: '',
        L1SAMPSET_ModFlag: '',
        L1SAMPSET_Samp_Type: '',
        L1SAMPSET_Manual: '',
        L1SAMPSET_Samps_Len: ''
      },
      form3Change: {},
      //修改字样
      isTrue: true,
      dialogVisibleBigSet: false,
      formBigSet: {},
      formBigSetList: {}
    }
  },
  mounted() {
    this.getHmiData()
  },
  destroyed() {
    stopGetData()
    // clearInterval(this.timerRealLen)
    // this.timerRealLen = null
  },
  methods: {
    //封装成对象方法使用
    trackSteel(data) {
      // 页面和实际比例 以整个图为例 宽度: 实际3.51m  页面50px  总长  长度: 实际 252823-366880 = 114057m  冷床页面长度 1612px
      // 辊道 宽度 3.51 页面 50px
      let [actWid, pageWid, actLen, pageLen, actgd, pagegd] = [
        3.5 * 1000,
        50,
        114.057 * 1000,
        1610,
        3.51 * 1000,
        50
      ]
      this.trackData = []
      for (let i = 0; i < data['rechmi3'].length; i++) {
        let item = data['rechmi3'][i]
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
    getSetData(data) {
      this.form.L1DSSET_UseFlag = data['L1DSSET_UseFlag'] == '1' ? true : false
      this.form.L1DSSET_FLAG = data['L1DSSET_FLAG']
      this.form.L1DSSET_PlateNo = data['L1DSSET_PlateNo']
      this.form.L1DSSET_Steelgrade = data['L1DSSET_Steelgrade']
      this.form.L1DSSET_Plate_Len = data['L1DSSET_Plate_Len']
      this.form.L1DSSET_Plate_Wid = data['L1DSSET_Plate_Wid']
      this.form.L1DSSET_Plate_Thk = data['L1DSSET_Plate_Thk']
      this.form.L1DSSET_DSS_Wid = data['L1DSSET_DSS_Wid']
      this.form.L1DSSET_DSS_Empty = data['L1DSSET_DSS_Empty']
      this.tableFrom1 = []
      for (let i = 0; i < data['L1DSSET_HMI'].length; i++) {
        this.tableFrom1.push({
          selectModel: data['L1DSSET_HMI'][i].type,
          len: data['L1DSSET_HMI'][i].len,
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
      this.tableFrom2 = data['L1DSCOM_HMI']

      this.form3.L1SAMPSET_ModFlag = data['L1SAMPSET_ModFlag']
      this.form3.L1SAMPSET_UseFlag =
        data['L1SAMPSET_UseFlag'] == 1 ? true : false
      this.form3.L1SAMPSET_PlateNo = data['L1SAMPSET_PlateNo']
      this.form3.L1SAMPSET_Steelgrade = data['L1SAMPSET_Steelgrade']
      this.form3.L1SAMPSET_Plate_Len = data['L1SAMPSET_Plate_Len']
      this.form3.L1SAMPSET_Plate_Wid = data['L1SAMPSET_Plate_Wid']
      this.form3.L1SAMPSET_Plate_Thk = data['L1SAMPSET_Plate_Thk']
      //-并样下发0  正样下发1 头部不要2
      this.form3.L1SAMPSET_Samp_Type = data['L1SAMPSET_Samp_Type'] + ''
      this.form3.L1SAMPSET_Manual = data['L1SAMPSET_Manual'] == 1 ? true : false //人工录入正样长度按钮
      this.form3.L1SAMPSET_Samps_Len = data['L1SAMPSET_Samps_Len'] //人工录入正样长度
    },
    getHmiData() {
      getHmiData(
        '1dcj',
        data => {
          data['rechmi3'].forEach(item => {
            item.tailX = item.tail_x
            item.Vpos = item.v_pos
            item.headX = item.head_x
          })
          data['rechmi3'].map((item, index) => {
            item.v_pos = item.v_pos - 40000
            item.tail_x = item.tail_x - 252823
          })
          this.trackSteel(data)
          this.getTableDataByProcess(data)
          this.initCmd(data)
          this.getSetData(data)
          this.getShanshuo(data)
          this.getRealMatLen(data)
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
      // console.log('cmd', this.cmdList)
    },
    //修改字样显示
    changeIsTrue() {
      this.isTrue = true
      this.form3.sampsLenFlag = false
      this.initForm()
    },
    //一件清空
    changeEmpty() {
      this.isTrue = true
      this.form3.sampsLenFlag = false
      this.initForm()
      this.form3Change.L1SAMPSET_Samps_Len.forEach(item => {
        item.samp_len = 0
      })
    },
    saveSet(num) {
      this.$confirm('是否确定修改?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          let data
          if (num === 3) {
            data = {
              L1SAMPSET_PlateNo: this.form3Change.L1SAMPSET_PlateNo,
              L1SAMPSET_Steelgrade: this.form3Change.L1SAMPSET_Steelgrade,
              L1SAMPSET_Plate_Len: this.form3Change.L1SAMPSET_Plate_Len,
              L1SAMPSET_Plate_Wid: this.form3Change.L1SAMPSET_Plate_Wid,
              L1SAMPSET_Plate_Thk: this.form3Change.L1SAMPSET_Plate_Thk,
              L1SAMPSET_Samp_Type: this.form3Change.L1SAMPSET_Samp_Type,
              L1SAMPSET_UseFlag:
                this.form3Change.L1SAMPSET_UseFlag == true ? '1' : '0',
              L1SAMPSET_ModFlag: 1
            }
          } else if (num === 4) {
            data = {
              L1SAMPSET_Samps_Len: this.form3Change.L1SAMPSET_Samps_Len,
              L1SAMPSET_Manual:
                this.form3Change.L1SAMPSET_Manual == true ? '1' : '0',
              L1SAMPSET_Manual_ModFlah: 1
            }
            console.log(data)
          }

          sendTag(data).then(res => {
            if (res.code == 200) {
              this.$message({
                message: '修改成功',
                type: 'success'
              })
              if (num === 3) {
                this.form3.changeFlag = true
              } else if (num === 4) {
                this.isTrue = false
                this.form3.sampsLenFlag = true
              }
            }
          })
        })
        .catch(() => {
          this.$message({
            message: '已取消修改',
            type: 'info'
          })
        })
    },
    againSet() {
      let data = [
        [
          {
            plateno: this.form3.L1SAMPSET_PlateNo,
            process: '5'
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
    initForm() {
      this.form3Change = { ...this.form3 }
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
      let fordata = data['rechmi3']
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
    getTableDataByTwo(plateno, type, itemInfo) {
      if (!itemInfo) {
        itemInfo = {
          region: 0
        }
      }
      //process == 0 只有在记录集自动触发时为变量 此时2 其他都传入0
      clearTimeout(this.timer)
      this.timer = setTimeout(() => {
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
    },
    allowSetSampsLen() {
      this.form3.sampsLenFlag = false
      this.initForm()
      this.isTrue = true
    },
    openRefresh(form) {
      form.changeFlag = true
    },
    closeRefresh(form) {
      this.initForm()
      form.changeFlag = false
    },
    beforeCloseBigSet() {
      this.dialogVisibleBigSet = false
    },
    realLength() {
      this.dialogVisibleReal = true
      this.getShanshuoFlag()
      /*this.timerRealLen = setInterval(() => {
        this.getShanshuo()
        this.getRealMatLen()
      }, 1000)*/
    },
    getShanshuo(data_) {
      //L1LMSSCAN_Flicker //是否闪烁变量
      /*let data = [{ tagName: 'L1LMSSCAN_Flicker', timestamp: 0 }]
      getHmiDataByEvent(data).then(res => {
        if (res.code == 200) {
          if (res.results[0].value == 1) {
            this.shanshuoFlag = true
          } else {
            this.shanshuoFlag = false
          }
        }
      })*/
      if (data_['L1LMSSCAN_Flicker'] == 1) {
        this.shanshuoFlag = true
      } else {
        this.shanshuoFlag = false
      }
    },
    getRealMatLen(data_) {
      /*let data = [{ tagName: 'L1LMSSCAN.mat_len_meas', timestamp: 0 }]
      getHmiDataByEvent(data).then(res => {
        if (res.code == 200) {
          this.real_mat_len = res.results[0].value
        }
      })*/
      this.real_mat_len = data_['L1LMSSCAN.mat_len_meas']
    },
    getShanshuoFlag() {
      let data = [{ tagName: 'L1LMSSCAN_Flicker_flag', timestamp: 0 }]
      getHmiDataByEvent(data).then(res => {
        if (res.code == 200) {
          this.shanChecked = res.results[0].value == 1 ? true : false
        }
      })
    },
    changeCheck() {
      // L1LMSSCAN_Flicker_flag 闪烁功能开关
      if (this.shanChecked) {
        let data = {
          L1LMSSCAN_Flicker_flag: 1
        }
        sendTag(data).then(res => {
          this.$message({
            message: '打开闪烁功能',
            type: 'success'
          })
        })
      } else {
        let data = {
          L1LMSSCAN_Flicker_flag: 0
        }
        sendTag(data).then(res => {
          this.$message({
            message: '关闭闪烁功能',
            type: 'success'
          })
        })
      }
    },
    handleCloseReal() {
      // clearInterval(this.timerRealLen)
      // this.timerRealLen = null
      this.dialogVisibleReal = false
    },
    handleCloseShan() {
      let data = {
        L1LMSSCAN_Flicker: 0
      }
      sendTag(data).then(res => {
        this.getShanshuo()
        this.$message({
          message: '关闭闪烁成功',
          type: 'success'
        })
      })
    },
    bigSaveSet(type2Form, type2TableSet) {
      this.formBigSet = type2Form
      this.formBigSetList = type2TableSet
      this.dialogVisibleBigSet = true
    },
    saveClose() {
      this.submitSetBig()
      setTimeout(() => {
        this.dialogVisibleBigSet = false
      }, 1500)
    },
    saveOpen() {
      this.submitSetBig()
    },
    submitSetBig() {
      this.$confirm('是否确定修改?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          //判断typeFlag 决定submitForm
          let data = {
            L1DSSET_UseFlag:
              this.formBigSet.L1DSSET_UseFlag == true ? '1' : '0',
            L1DSSET_PlateNo: this.formBigSet.L1DSSET_PlateNo,
            L1DSSET_Plate_Len: this.formBigSet.L1DSSET_Plate_Len,
            L1DSSET_Plate_Wid: this.formBigSet.L1DSSET_Plate_Wid,
            L1DSSET_Plate_Thk: this.formBigSet.L1DSSET_Plate_Thk,
            L1DSSET_Steelgrade: this.formBigSet.L1DSSET_Steelgrade,
            L1DSSET_FLAG: 1,
            L1DSSET_HMI: []
          }
          for (let i = 0; i < this.formBigSetList.length; i++) {
            data['L1DSSET_HMI'].push({
              len: Number(this.formBigSetList[i].len),
              type: this.formBigSetList[i].selectModel
            })
          }
          console.log(data)
          sendTag(data).then(res => {
            this.$message({
              message: '修改成功',
              type: 'success'
            })
            console.log(res)
          })
        })
        .catch(() => {
          this.$message({
            type: 'info',
            message: '已取消修改'
          })
        })
    }
  }
}
</script>


<style scoped lang="less">
// dialog 去除遮罩层 弹窗底下可点击
/deep/.el-dialog__wrapper {
  //opacity: 0.1 !important;
}
.sampleBtn {
  margin-top: 20px;
}
/deep/.el-table__row td,
/deep/.el-table__header th {
  padding: 3px 0 !important;
}
/deep/ .el-table .cell {
  white-space: nowrap;
}
.pad0 {
  .el-table td,
  .el-table th {
    padding: 3px 0 !important;
  }
}
/deep/ .el-input-group__append,
/deep/ .el-input-group__prepend {
  padding: 0 6px;
}
/deep/ .el-form-item__content .el-input-group {
  vertical-align: baseline;
}
.el-button--primary {
  background-color: #13356f;
  border-color: #13356f;
}
/deep/ .el-radio__input.is-disabled.is-checked .el-radio__inner {
  border-color: #409eff;
  background: #409eff;
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
.header {
  margin-bottom: 16px;
  display: flex;
  justify-content: space-between;
  flex-wrap: wrap;
  align-items: baseline;
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

.lcb {
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
      //width: 100%;
      width: 1622px;
      height: 167px;
      position: relative;
      //overflow: hidden;
      .bgimg-box {
        height: 100%;
        //background: url('../assets/1dcj.png') no-repeat 100% 100%;
        background: url('../assets/bg/dcj1.png') no-repeat 100% 100%;
      }
      .one {
        position: absolute;
        top: 70px;
        left: 0px;
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
          line-height: 35px;
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
}
/deep/ .el-table {
  .el-table__fixed-header-wrapper {
    .el-checkbox__inner {
      display: none !important;
    }
  }
}
.blink {
  animation: blink 0.3s linear infinite alternate;
}

@keyframes blink {
  0% {
    color: #000000;
    //text-shadow: 0 0 1px #20a348;
  }
  100% {
    color: red;
    font-size: 85px;
    //text-shadow: 0 0 1px red;
  }
}
</style>
