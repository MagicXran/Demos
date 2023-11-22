<template>
  <div class="main">
    <div
      v-tag:tag="item"
      v-for="(item,index) in variable"
      :key="index"
      data-page="main"/>
    <div class="banner bgc-white">
      <!--      <div class="title">
        <p>精整区</p>
      </div>-->
      <div class="bgimg">
        <div class="bgimg-box"/>
        <div class="track-box">
          <div class="one-box">
            <el-tooltip
              v-for="(item,key) in trackData"
              :key="key"
              class="item"
              effect="light"
              placement="top-start">
              <div slot="content"> 钢板号 <span style="font-weight: bold">{{ item.plateno }}</span>
                母板厚度 <span style="font-weight: bold">{{ Number(item.platethk).toFixed(3) }}</span>
                母板宽度 <span style="font-weight: bold">{{ Number(item.platewid).toFixed(3) }}</span>
                母板长度 <span style="font-weight: bold">{{ Number(item.platelen).toFixed(3) }}</span>
                母板重量 <span style="font-weight: bold">{{ Number(item.platewet).toFixed(3) }}</span>
                冷床流向 <span style="font-weight: bold">{{ item.cbdec != null ? Number(item.cbdec).toFixed(3) :'' }}</span>
              </div>
              <div
                :style="{width: item.width+'px',height:item.height+'px',left:item.tailpos+2+'px',top:item.vPos+46+'px'}"
                class="one"
                @click="sendMsgFn(item.plateno)">
                <span>
                  {{ item.platenoSimple }}
                </span>
              </div>
            </el-tooltip>
          </div>
          <div class="other">
            <div
              v-show="CMDFlag.one"
              class="cmd"><img
                src="../assets/green.png"
                alt=""></div>
            <div
              v-show="CMDFlag.two"
              class="cmd"><img
                src="../assets/green.png"
                alt=""></div>
            <div
              v-show="CMDFlag.three"
              class="cmd"><img
                src="../assets/green.png"
                alt=""></div>
            <div
              v-show="CMDFlag.four"
              class="cmd"><img
                src="../assets/green.png"
                alt=""></div>
            <div
              v-show="CMDFlag.five"
              class="cmd"><img
                src="../assets/green.png"
                alt=""></div>
            <div
              v-show="CMDFlag.six"
              class="cmd"><img
                src="../assets/green.png"
                alt=""></div>
            <div
              v-show="CMDFlag.seven"
              class="cmd"><img
                src="../assets/green.png"
                alt=""></div>
          </div>
          <div class="other2">
            <div
              v-for="(item, index) in CMDFlagOne"
              v-show="item"
              :key="index"
              class="cmd"><img
                src="../assets/green.png"
                alt=""></div>
          </div>
          <div class="other3">
            <span>{{ gwj.gwj1 }}</span>
            <span>{{ gwj.gwj2 }}</span>
          </div>
        </div>
      </div>
    </div>
    <div class="content">
      <el-row>
        <el-col :span="24">
          <div class="left-box">
            <div class="left-top bgc-white">
              <hmi-table
                :table-data="tableDataLeftTop"
                :is-pagination-show="false"
                :table-height="120"
                :table-foot="false"
                :table-head="false"
              >
                <template slot="TableBody">
                  <el-table-column
                    prop="PLATE_NO"
                    label="板坯号"
                    width="180"
                    align="center"/>
                  <el-table-column
                    prop=""
                    label="产品分类"
                    align="center">
                    <template slot-scope="scope">
                      <!--                      <span>{{ scope.row.PLATE_TYPE }}</span>-->
                      <span v-if="scope.row.PLATE_TYPE == 1">板坯</span>
                      <span v-if="scope.row.PLATE_TYPE == 2">母板</span>
                      <span v-if="scope.row.PLATE_TYPE == 3">子板</span>
                    </template>
                  </el-table-column>
                  <el-table-column
                    prop="PLATE_THK"
                    label="厚度"
                    align="center"/>
                  <el-table-column
                    prop="PLATE_WID"
                    label="宽度"
                    align="center"/>
                  <el-table-column
                    prop="PLATE_LEN"
                    label="长度"
                    align="center"/>
                  <el-table-column
                    prop="PLATE_WGT"
                    label="重量"
                    align="center"/>
                  <el-table-column
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
                    prop="IDENTIFICATION"
                    label="标识标准"
                    width="120"
                    align="center"/>
                  <el-table-column
                    prop="DELIVERY_DATE"
                    label="交货期"
                    width="120"
                    align="center"/>
                  <el-table-column
                    prop="URGENT_ORDER"
                    label="是否紧急订单"
                    align="center"/>
                  <el-table-column
                    prop="ORDER_MATERIAL"
                    label="订单材"
                    align="center"/>
                  <el-table-column
                    prop="EXCESSIVE_PRO"
                    label="超量排产"
                    align="center"/>
                  <el-table-column
                    prop="THK_MAX"
                    label="厚度上限"
                    align="center"/>
                  <el-table-column
                    prop="THK_MIN"
                    label="厚度下限"
                    align="center"/>
                  <el-table-column
                    prop="LEN_MAX"
                    label="长度上限"
                    align="center"/>
                  <el-table-column
                    prop="LEN_MIN"
                    label="长度下限"
                    align="center"/>
                  <el-table-column
                    prop="WID_MAX"
                    label="宽度上限"
                    align="center"/>
                  <el-table-column
                    prop="WID_MIN"
                    label="宽度下限"
                    align="center"/>
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
                    align="center"/>
                  <el-table-column
                    prop="CAMBER"
                    label="镰刀弯(长度%)"
                    align="center"/>
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
                    prop="SPRAY_CONTENT"
                    label="加喷内容"
                    align="center"/>
                  <el-table-column
                    prop="SPRAY_SIDE"
                    label="侧喷加喷"
                    align="center"/>
                  <el-table-column
                    prop="SPRAY_PRINT"
                    label="冲印加喷"
                    align="center"/>
                  <el-table-column
                    prop="IDENT_NUM"
                    label="标识次数"
                    align="center"/>
                  <el-table-column
                    prop="REMARKS_ORDER"
                    label="订单备注"
                    align="center"/>
                  <el-table-column
                    prop="REMARKS_PRODUCE"
                    label="生产备注"
                    align="center"/>
                  <el-table-column
                    prop="PLATE_STATE"
                    label="钢板状态"
                    align="center"/>
                  <el-table-column
                    prop="HTL_SAMP_LEN"
                    label="热处理中间样取样长度"
                    align="center"/>
                  <el-table-column
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
                </template>
              </hmi-table>
            </div>
            <!--            <div class="left-bottom bgc-white">
              <hmi-table
                :table-data="tableDataLeftBottom"
                :is-pagination-show="true"
                :table-head="false"
                index-type="index">
                <template slot="TableBody">
                  <el-table-column
                    prop="key0"
                    label="子板号"
                    align="center"/>
                  <el-table-column
                    prop="key0"
                    label="钢种"
                    align="center"/>
                  <el-table-column
                    prop="key0"
                    label="标准号"
                    align="center"/>
                  <el-table-column
                    prop="key0"
                    label="厚度"
                    align="center"/>
                  <el-table-column
                    prop="key0"
                    label="宽度"
                    align="center"/>
                  <el-table-column
                    prop="key0"
                    label="长度"
                    align="center"/>
                  <el-table-column
                    prop="key0"
                    label="重量"
                    align="center"/>
                  <el-table-column
                    prop="key0"
                    label="切边"
                    align="center"/>
                  <el-table-column
                    prop="key0"
                    label="探伤"
                    align="center"/>
                  <el-table-column
                    prop="key0"
                    label="热处理"
                    align="center"/>
                  <el-table-column
                    prop="key0"
                    label="冷床目标温度"
                    align="center"/>
                </template>
              </hmi-table>
            </div>-->
          </div>
        </el-col>
        <!--        <el-col :span="5">
          <div class="right-box bgc-white">
            <div class="title">
              <p>质量统计</p>
            </div>
            <hmi-table
              :table-data="tableDataRight"
              :is-pagination-show="false"
              :table-head="false">
              <template slot="TableBody">
                <el-table-column
                  prop="key0"
                  label="1#块数"
                  align="center"/>
                <el-table-column
                  prop="key0"
                  label="100"
                  align="center"/>
              </template>
            </hmi-table>
          </div>
        </el-col>-->
      </el-row>
    </div>
  </div>
</template>

<script>
import { post } from '@/lib/Util'
import HmiTable from '@/components/HmiTable'
import { GET_TAGS } from '@/lib/api'
import { getHmiData, stopGetData, sendMsg, sendTag } from '@/lib/GetData'
export default {
  layout: 'default',
  name: 'Main',
  components: { HmiTable },
  data() {
    return {
      variable: [
        'flall_mat',
        'HLTRACK.CMD2',
        'HLTRACK.CMD3',
        'HLTRACK.CMD4',
        'HLTRACK.CMD5',
        'HLTRACK.CMD6',
        'HLTRACK.CMD7',
        'HLTRACK.CMD8',
        'CBTRACK.CMD1',
        'CBTRACK.CMD2',
        'CBTRACK.CMD3',
        'L1DSSTRACK.FDCMD1',
        'L1DSSTRACK.DSSCMD1_1',
        'L1DSSTRACK.DSSCMD2_1',
        'L1DSSTRACK.DSSCMD3_1',
        'L1DSSTRACK.DSSCMD4_1',
        'L1DSSTRACK.DSSCMD5_1',
        'L1DSSTRACK.DSSCMD6',
        'L1DSSTRACK.DSSCMD7',
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
        'CBTRACK.ENCBHDT',
        'CBTRACK.EXCBHDT'
      ],
      gwj: {
        gwj1: 0,
        gwj2: 0
      },
      CMDFlag: {
        one: true,
        two: true,
        three: true,
        four: true,
        five: true,
        six: true,
        seven: true
      },
      CMDFlagOne: [
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true
      ],
      trackData: [],
      trackDataOne: [],
      trackDataTwo: [],
      trackDataThree: [],
      trackCoolDataOne: [],
      trackCoolDataTwo: [],
      trackCoolDataThree: [],
      tableDataLeftTop: [
        {
          key0: ''
        }
      ],
      tableDataLeftBottom: [
        {
          key0: '文本内容'
        },
        {
          key0: '文本内容'
        },
        {
          key0: '文本内容'
        }
      ],
      tableDataRight: [
        {
          key0: '1#重量'
        },
        {
          key0: '200'
        },
        {
          key0: '2#块数'
        },
        {
          key0: '110'
        },
        {
          key0: '2#重量'
        },
        {
          key0: '220'
        }
      ]
    }
  },
  mounted() {
    this.getHmiData()
    // this.sendTagTest()
  },
  destroyed() {
    stopGetData()
  },
  methods: {
    //封装成对象方法使用
    trackSteel(data) {
      // 页面和实际比例 以整个图为例 宽度: 实际67.270m  页面620px  冷床  长度: 实际53.3m  冷床页面长度 423px
      // 辊道 宽度 3.51 页面 30px
      let [actWid, pageWid, actLen, pageLen, actgd, pagegd] = [
        67.27 * 1000,
        620,
        53.3 * 1000,
        423,
        3.51 * 1000,
        30
      ]
      this.trackData = []
      for (let i = 0; i < data['flall_mat'].length; i++) {
        this.trackData.push({
          width: this.countSteelLeng(
            actLen,
            pageLen,
            data['flall_mat'][i].platelenmeas
          ),
          height: this.countSteelWid(
            actWid,
            pageWid,
            data['flall_mat'][i].platewid
          ),
          tailpos: this.countSteeltail(
            actLen,
            pageLen,
            data['flall_mat'][i].tail_x
            // data['flall_mat'][i].head_x - data['flall_mat'][i]
          ),
          vPos:
            this.countSteelPosY(actWid, pageWid, data['flall_mat'][i].v_pos) +
            (pagegd -
              this.countSteelWid(
                actgd,
                pagegd,
                data['flall_mat'][i].platewid
              )) /
              2, //计算辊道中心位置
          plateno: data['flall_mat'][i].plateno,
          platenoSimple:
            data['flall_mat'][i].platelenmeas > 12000
              ? data['flall_mat'][i].plateno
              : '..' +
                data['flall_mat'][i].plateno.slice(
                  5,
                  data['flall_mat'][i].plateno.length
                ),
          platethk: data['flall_mat'][i].platethk,
          platewid: data['flall_mat'][i].platewid,
          platelen: data['flall_mat'][i].platelenmeas,
          platewet: data['flall_mat'][i].platewet,
          cbdec: data['flall_mat'][i].cbdec
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
    getCMDdata(data) {
      /*0代表关闭红色 1代表打开绿色*/
      this.CMDFlag.one = data['HLTRACK.CMD2'] == 0 ? false : true
      this.CMDFlag.two = data['HLTRACK.CMD3'] == 0 ? false : true
      this.CMDFlag.three = data['HLTRACK.CMD4'] == 0 ? false : true
      // this.CMDFlag.four = data['HLTRACK.CMD5'] == 0 ? false : true
      this.CMDFlag.five = data['HLTRACK.CMD5'] == 0 ? false : true
      this.CMDFlag.six = data['HLTRACK.CMD7'] == 0 ? false : true
      this.CMDFlag.seven = data['HLTRACK.CMD6'] == 0 ? false : true
    },
    getCMDONEData(data) {
      let temp = [
        'CBTRACK.CMD1',
        'CBTRACK.CMD2',
        'CBTRACK.CMD3',
        'L1DSSTRACK.FDCMD1',
        'L1DSSTRACK.DSSCMD1_1',
        // 'L1DSSTRACK.DSSCMD2_1',
        'L1DSSTRACK.DSSCMD3_1',
        'L1DSSTRACK.DSSCMD4_1',
        'L1DSSTRACK.DSSCMD5_1',
        'L1DSSTRACK.DSSCMD6',
        'L1DSSTRACK.DSSCMD7',
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
        'L1DSTRACK.EXDSCMD5'
      ]
      for (let i = 0; i < this.CMDFlagOne.length; i++) {
        this.CMDFlagOne[i] = data[temp[i]] == 0 ? false : true
      }
    },
    getGWJData(data) {
      this.gwj.gwj1 = data['CBTRACK.ENCBHDT'].toFixed(0)
      this.gwj.gwj2 = data['CBTRACK.EXCBHDT'].toFixed(0)
    },
    getHmiData() {
      getHmiData(
        'main',
        data => {
          this.trackSteel(data)
          this.getCMDdata(data)
          this.getCMDONEData(data)
          this.getGWJData(data)
        },
        error => {
          console.log(error)
        },
        1000
      )
    },
    sendMsgFn(plateno) {
      let data = [
        [
          {
            plateno: plateno
          }
        ]
      ]
      sendMsg(data, 1804, 'PDI').then(res => {
        console.log('sendMsg', res)
        if (res.code != 200) return
        if (Object.getOwnPropertyNames(res.results[0]).length <= 1) {
          alert(res.results[0].msg)
        }
        res.results[0].map((item, index) => {
          item.PLATE_WGT = item.PLATE_WGT.toFixed(1)
          item.PLATE_WID = item.PLATE_WID.toFixed(1)
        })
        this.tableDataLeftTop = res.results[0]
      })
    },
    sendTagTest() {
      let data = {
        HMICESHI: 101,
        HMITEST: '9999'
      }
      sendTag(data).then(res => {
        console.log(res)
      })
    }
  }
}
</script>

<style lang="less">
.el-table .cell {
  white-space: nowrap;
}

.el-tooltip__popper {
  white-space: pre-line !important;
  font-size: 14px;
}
.main {
  .bgc-white {
    background-color: #ffffff;
  }

  .banner {
    //height: 592px;
    padding: 10px 18px;
    width: 100%;

    .title {
      p {
        font-weight: 700;
        font-size: 20px;
        color: #606266;
      }
    }

    .bgimg {
      width: 100%;
      height: 725px;
      position: relative;
      overflow-x: scroll;
      .bgimg-box {
        height: 100%;
        width: 3248px;
        background: url('../assets/bgimgbig.png') no-repeat;
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
        top: 48px;
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
          font-size: 12px;
          //color: #f50101;
          color: #ffffff;
          line-height: 22px;
          //transform: scale(0.9);
          font-size: 12px;
          display: block;
        }
      }

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
    margin-top: 10px;

    .left-box {
      .left-top {
        padding: 20px;
        margin-bottom: 20px;
      }

      .left-bottom {
        padding: 20px;
      }

      //margin-right: 20px;
    }

    .right-box {
      padding: 20px;
      height: 604px;

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
</style>
