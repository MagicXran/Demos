<template>
  <div class="main">
    <div
      v-tag:tag="variable"
      data-page="main"/>
    <div class="banner bgc-white">
      <!--      <div class="title">
        <p>精整区</p>
      </div>-->
      <div class="bgimg">
        <div class="bgimg-box"/>
        <div class="track-box">
          <trackItem
            :track-data="trackData"
            :top="46"
            :left="2"
            :track-data-big="trackDataBig"
            @opdialog="modColor"
            @getTableDataByTwo="sendMsgFn"
          />
          <!--          <div class=""></div>-->
          <div class="cmd-box">
            <ul>
              <li
                v-for="item in cmdList.slice(0,7)"
                :data-cc="item.key"
                :style="'top:36px;'+'left:'+(item.x - 2)+'px'"
                :key="item.x">
                <img
                  v-if="item.value == 1"
                  src="../assets/green.png"
                  alt="">
                <img
                  v-if="item.value == 3"
                  src="../assets/yellow.png"
                  alt="">
                <span
                  class="transparency"
                  @dblclick="amend(item)"/>
              </li>
              <li
                v-for="item in cmdList.slice(7, 33)"

                :style="'top:389px;'+'left:'+(item.x - 2)+'px'"
                :data-cc="item.key"
                :key="item.x">
                <img
                  v-if="item.value == 1"
                  src="../assets/green.png"
                  alt="">
                <img
                  v-if="item.value == 3"
                  src="../assets/yellow.png"
                  alt="">
                <span
                  class="transparency"
                  @dblclick="amend(item)"
                />
              </li>
              <li
                v-for="item in cmdList.slice(33, cmdList.length)"
                :style="'top:631px;'+'left:'+(item.x - 3.2)+'px'"
                :data-cc="item.key"
                :key="item.x">
                <img
                  v-if="item.value == 1"
                  src="../assets/green.png"
                  alt="">
                <img
                  v-if="item.value == 3"
                  src="../assets/yellow.png"
                  alt="">
                <span
                  class="transparency"
                  @dblclick="amend(item)"
                />
              </li>

              <li
                v-for="item in cmdList.slice(24, 33)"
                :style="'top:523px;'+'left:'+(item.x_big)+'px'"
                :data-cc="item.key"
                :key="item.x+Math.random()">
                <img
                  v-if="item.value == 1"
                  src="../assets/green.png"
                  alt="">
                <img
                  v-if="item.value == 3"
                  src="../assets/yellow.png"
                  alt="">
                <span
                  class="transparency"
                  @dblclick="amend(item)"
                />
              </li>
              <li
                v-for="item in cmdList.slice(cmdList.length-8, cmdList.length)"
                :style="'top:767px;'+'left:'+(item.x_big)+'px'"
                :data-cc="item.key"
                :key="item.x+Math.random()">
                <img
                  v-if="item.value == 1"
                  src="../assets/green.png"
                  alt="">
                <img
                  v-if="item.value == 3"
                  src="../assets/yellow.png"
                  alt="">
                <span
                  class="transparency"
                  @dblclick="amend(item)"
                />
              </li>
            </ul>
          </div>
          <div class="other3">
            <span>{{ gwj.gwj1 }}</span>
            <span>{{ gwj.gwj2 }}</span>
          </div>
          <!--          <div class="other4">
            <span>总重量： <i class="blue">{{ Number(MESPRINT_WGT).toFixed(1) }}</i></span>
            <span>总块数： <i class="blue">{{ MESPRINT_NUM }}</i></span>
          </div>-->
          <!--          <warn-info
            :warn-type="1"
            :width="670"
            :pos-location="{
              top: 60,
              left: 984,
            }"
          />
          &lt;!&ndash;          定尺剪钢板号单独显示&ndash;&gt;
          <div
            :style="{top:dcjhData1.length==0 ? 256 +'px':dcjhData1.length==1 ? 290+'px':dcjhData1.length==2 ? 256+'px':dcjhData1.length==3 ? 236+'px':dcjhData1.length==4 ? 209+'px':180+'px'}"
            class="dcjh-box1">
            <el-table
              :data="dcjhData1"
              :cell-style="{border:'1px solid #777',borderTop:'0px solid #777'}"
              :header-cell-style="{border:'1px solid #777'}"
              style="width: 100%;border-bottom:1px solid #777;border-right:1px solid #777;border-left:1px solid #777;"
              stripe
              border>
              <el-table-column
                prop="plateno"
                label="1#定尺剪后&#45;&#45;钢板号"
                width="180"/>
            </el-table>
          </div>
          <div
            :style="{top:dcjhData2.length==0 ? 509 +'px':dcjhData2.length==1 ? 530+'px':dcjhData2.length==2 ? 509+'px':dcjhData2.length==3 ? 488+'px':dcjhData2.length==4 ? 468+'px':448+'px'}"
            class="dcjh-box2"
          >
            <el-table
              :data="dcjhData2"
              :cell-style="{border:'1px solid #777',borderTop:'0px solid #777'}"
              :header-cell-style="{border:'1px solid #777'}"
              style="width: 100%;border-bottom:1px solid #777;border-right:1px solid #777;border-left:1px solid #777;"
              stripe
              border>
              <el-table-column
                prop="plateno"
                label="2#定尺剪后&#45;&#45;钢板号"
                width="180"/>
            </el-table>
          </div>-->
        </div>
      </div>
    </div><!--
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
                      &lt;!&ndash;                      <span>{{ scope.row.PLATE_TYPE }}</span>&ndash;&gt;
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
          </div>
        </el-col>
      </el-row>
    </div>-->
    <el-dialog
      :visible.sync="dialogVisibleCmd"
      :before-close="handleClose"
      :title="updateCmdText"
      width="20%">
      <el-form
        ref="form"
        label-width="80px">
        <el-form-item
          v-if="!updateCmdDisabled"
          label="正常/备用">
          <el-select
            v-model="updateCmdSelect"
            placeholder="请选择是否 备用"
            size="small">
            <el-option
              :value="1"
              label="正常"/>
            <el-option
              :value="2"
              label="备用"/>
          </el-select>
        </el-form-item>
        <el-form-item
          label="选择状态">
          <el-radio
            v-model="radioCmd"
            :label="1">正常</el-radio>
          <el-radio
            v-model="radioCmd"
            :label="2">故障</el-radio>
        </el-form-item>
      </el-form>
      <span
        slot="footer"
        class="dialog-footer">
        <el-button @click="dialogVisibleCmd = false">取 消</el-button>
        <el-button
          type="primary"
          @click="subCmdStatus()">确 定</el-button>
      </span>
    </el-dialog>
  </div>
</template>

<script>
import { post } from '@/lib/Util'
import HmiTable from '@/components/HmiTable'
import warnInfo from '@/pages/components/warnInfo'
import { GET_TAGS } from '@/lib/api'
import { getHmiData, stopGetData, sendMsg, sendTag } from '@/lib/GetData'
import trackItem from '@/pages/components/trackItem'

export default {
  layout: 'default',
  name: 'Main',
  components: { HmiTable, warnInfo, trackItem },
  data() {
    return {
      variable: [
        'MESPRINT_NUM',
        'MESPRINT_WGT',
        'flall_mat',
        'CMD_USE',
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
        'L1DSSTRACK.DSSCMD3_2', //3_1 信号有问题
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
        'L1PILERTRACK.PILERSIGNAL13',
        'L1PILERTRACK.PILERSIGNAL14',
        'L1PILERTRACK.PILERSIGNAL15',
        'L1PILERTRACK.PILERSIGNAL16',
        'L2DDSTRACK.DDSCMD1',
        'L2DDSTRACK.DDSCMD2',
        'L2DDSTRACK.DDSCMD3',
        'L2DDSTRACK.DDSCMD4',
        'L2DDSTRACK.DDSCMD5',
        'L2DDSTRACK.DDSCMD6',
        'L2DDSTRACK.DDSCMD7',
        'L2DDSTRACK.DDSCMD8',
        'L2CSTRACK.CSCMD1',
        'L2CSTRACK.CSCMD2',
        'L2CSTRACK.CSCMD3',
        'L2CSTRACK.CSCMD4',
        'L2CSTRACK.CSCMD5',
        'L2CSTRACK.CSCMD6',
        'L2CSTRACK.CSCMD7',
        'L2CSTRACK.CSCMD8',
        'L2CSTRACK.CSCMD9',
        'L2CSTRACK.CSCMD10',
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
        'L2DSTRACK.PILERCMD2',
        'L2DSTRACK.PILERCMD3',
        'L2DSTRACK.PILERCMD4',
        'CBTRACK.ENCBHDT',
        'CBTRACK.EXCBHDT'
      ],
      gwj: {
        gwj1: 0,
        gwj2: 0
      },
      //keyList :修改记录集中的 光电开关位置及备用开光位置
      cmdList: [
        //7个
        {
          key: 'HLTRACK.CMD2',
          value: '',
          x: 3.142019271,
          keyList: [1],
          line: 'one'
        },
        {
          key: 'HLTRACK.CMD3',
          value: '',
          x: 20.6954336,
          keyList: [2],
          line: 'one'
        },
        {
          key: 'HLTRACK.CMD4',
          value: '',
          x: 89.56849602,
          keyList: [3],
          line: 'one'
        },
        {
          //第四个一直为0  写死不影响顺序排列
          key: 'HLTRACK.CMD5',
          value: '',
          x: 135,
          keyList: [4],
          line: 'one'
        },
        {
          key: 'HLTRACK.CMD5',
          value: '',
          x: 391.7469627,
          keyList: [5],
          line: 'one'
        },
        {
          key: 'HLTRACK.CMD7',
          value: '',
          x: 425.6807708,
          keyList: [6],
          line: 'one'
        },
        {
          key: 'HLTRACK.CMD6',
          value: '',
          x: 647.235023,
          keyList: [7],
          line: 'one'
        },

        //26个
        {
          key: 'CBTRACK.CMD1',
          value: '',
          x: 396.9920402,
          keyList: [1],
          line: 'two'
        },
        {
          key: 'CBTRACK.CMD2',
          value: '',
          x: 426.3175534,
          keyList: [2],
          line: 'two'
        },
        {
          key: 'CBTRACK.CMD3',
          value: '',
          x: 649.2124005,
          keyList: [3],
          line: 'two'
        },
        {
          key: 'L1DSSTRACK.FDCMD1',
          value: '',
          x: 692.9199832,
          keyList: [4],
          line: 'two'
        },
        {
          key: 'L1DSSTRACK.DSSCMD1_1',
          value: '',
          x: 769.5936322,
          keyList: [5, 6],
          line: 'two'
        },
        {
          key: 'L1DSSTRACK.DSSCMD2_1',
          value: '',
          x: 813.4017595,
          keyList: [7, 8],
          line: 'two'
        },
        {
          key: 'L1DSSTRACK.DSSCMD3_2',
          value: '',
          x: 853.1713448,
          keyList: [9, 10],
          line: 'two'
        },
        {
          key: 'L1DSSTRACK.DSSCMD4_1',
          value: '',
          x: 898.9400922,
          keyList: [11, 12],
          line: 'two'
        },
        {
          key: 'L1DSSTRACK.DSSCMD5_1',
          value: '',
          x: 915.3917051,
          keyList: [13],
          line: 'two'
        },
        {
          key: 'L1DSSTRACK.DSSCMD6',
          value: '',
          x: 935.3958944,
          keyList: [14],
          line: 'two'
        },
        {
          key: 'L1DSSTRACK.DSSCMD7',
          value: '',
          x: 954.8470884,
          keyList: [15],
          line: 'two'
        },
        {
          key: 'L1DSTRACK.ENDSCMD1_1',
          value: '',
          x: 1059.166318,
          keyList: [16, 17],
          line: 'two'
        },
        {
          key: 'L1DSTRACK.ENDSCMD2_1',
          value: '',
          x: 1104.285714,
          keyList: [18, 19],
          line: 'two'
        },
        {
          key: 'L1DSTRACK.ENDSCMD3_1',
          value: '',
          x: 1146.036866,
          keyList: [20, 21],
          line: 'two'
        },
        {
          key: 'L1DSTRACK.ENDSCMD4_1',
          value: '',
          x: 1188.345203,
          keyList: [22, 23],
          line: 'two'
        },
        {
          key: 'L1DSTRACK.ENDSCMD5_1',
          value: '',
          x: 1230.230415,
          keyList: [24, 25],
          line: 'two'
        },
        {
          key: 'L1DSTRACK.ENDSCMD6_1',
          value: '',
          x: 1267.557604,
          keyList: [26, 27],
          line: 'two'
        },
        {
          key: 'L1DSTRACK.EXDSCMD1',
          value: '',
          x: 1380.699623,
          x_big: 649.5,
          keyList: [28],
          line: 'two'
        },
        {
          key: 'L1DSTRACK.EXDSCMD2',
          value: '',
          x: 1431.11437,
          x_big: 833,
          keyList: [29],
          line: 'two'
        },
        {
          key: 'L1DSTRACK.EXDSCMD3',
          value: '',
          x: 1478.780897,
          x_big: 1007,
          keyList: [30],
          line: 'two'
        },
        {
          key: 'L1DSTRACK.EXDSCMD4',
          value: '',
          x: 1505.613741,
          x_big: 1107.41,
          keyList: [31],
          line: 'two'
        },
        {
          key: 'L1DSTRACK.EXDSCMD5',
          value: '',
          x: 1536.99204,
          x_big: 1220.79,
          keyList: [32],
          line: 'two'
        },
        {
          key: 'L1PILERTRACK.PILERSIGNAL13',
          value: '',
          x: 1580.561374,
          x_big: 1389.36,
          keyList: [33],
          line: 'two'
        },
        {
          key: 'L1PILERTRACK.PILERSIGNAL14',
          value: '',
          x: 1596.443234,
          x_big: 1441.24,
          keyList: [34],
          line: 'two'
        },
        {
          key: 'L1PILERTRACK.PILERSIGNAL15',
          value: '',
          x: 1633.866778,
          x_big: 1579.67,
          keyList: [35],
          line: 'two'
        },
        {
          key: 'L1PILERTRACK.PILERSIGNAL16',
          value: '',
          x: 1650.607457,
          x_big: 1641.607457,
          keyList: [36],
          line: 'two'
        },
        /*---2号线 31个---*/
        {
          key: 'L2DDSTRACK.DDSCMD1',
          value: '',
          x: 260.0339338,
          keyList: [1],
          line: 'three'
        },
        {
          key: 'L2DDSTRACK.DDSCMD2',
          value: '',
          x: 391.7050691,
          keyList: [2],
          line: 'three'
        },
        {
          key: 'L2DDSTRACK.DDSCMD3',
          value: '',
          x: 413.2245496,
          keyList: [3],
          line: 'three'
        },
        {
          key: 'L2DDSTRACK.DDSCMD4',
          value: '',
          x: 471.875576,
          keyList: [4],
          line: 'three'
        },
        {
          key: 'L2DDSTRACK.DDSCMD5',
          value: '',
          x: 501.2010892,
          keyList: [5],
          line: 'three'
        },
        {
          key: 'L2DDSTRACK.DDSCMD6',
          value: '',
          x: 547.2840385,
          keyList: [6],
          line: 'three'
        },
        {
          key: 'L2DDSTRACK.DDSCMD7',
          value: '',
          x: 597.5563469,
          keyList: [7],
          line: 'three'
        },
        {
          key: 'L2DDSTRACK.DDSCMD8',
          value: '',
          x: 647.8286552,
          keyList: [8],
          line: 'three'
        },
        {
          key: 'L2CSTRACK.CSCMD1',
          value: '',
          x: 693.9116045,
          keyList: [9],
          line: 'three'
        },
        {
          key: 'L2CSTRACK.CSCMD2',
          value: '',
          x: 739.9945538,
          keyList: [10],
          line: 'three'
        },
        {
          key: 'L2CSTRACK.CSCMD3',
          value: '',
          x: 786.0775031,
          keyList: [11],
          line: 'three'
        },
        {
          key: 'L2CSTRACK.CSCMD4',
          value: '',
          x: 827.9710934,
          keyList: [12],
          line: 'three'
        },
        {
          key: 'L2CSTRACK.CSCMD5',
          value: '',
          x: 869.8646837,
          keyList: [13],
          line: 'three'
        },
        {
          key: 'L2CSTRACK.CSCMD6',
          value: '',
          x: 937.7323,
          keyList: [14],
          line: 'three'
        },
        {
          key: 'L2CSTRACK.CSCMD7',
          value: '',
          x: 984.6531211,
          keyList: [15],
          line: 'three'
        },
        {
          key: 'L2CSTRACK.CSCMD8',
          value: '',
          x: 1031.155006,
          keyList: [16],
          line: 'three'
        },
        {
          key: 'L2CSTRACK.CSCMD9',
          value: '',
          x: 1068.859238,
          keyList: [17],
          line: 'three'
        },
        {
          key: 'L2CSTRACK.CSCMD10',
          value: '',
          x: 1127.510264,
          keyList: [18],
          line: 'three'
        },
        {
          key: 'L2DSTRACK.ENDSCMD1',
          value: '',
          x: 1169.003854,
          keyList: [19],
          line: 'three'
        },
        {
          key: 'L2DSTRACK.ENDSCMD2',
          value: '',
          x: 1219.076163,
          keyList: [20],
          line: 'three'
        },
        {
          key: 'L2DSTRACK.ENDSCMD3',
          value: '',
          x: 1265.759112,
          keyList: [21],
          line: 'three'
        },
        {
          key: 'L2DSTRACK.ENDSCMD4',
          value: '',
          x: 1307.652702,
          keyList: [22],
          line: 'three'
        },
        {
          key: 'L2DSTRACK.ENDSCMD5',
          value: '',
          x: 1340.167574,
          keyList: [23],
          line: 'three'
        },
        {
          key: 'L2DSTRACK.EXDSCMD1',
          value: '',
          x: 1397.723921,
          x_big: 717,
          keyList: [24],
          line: 'three'
        },
        {
          key: 'L2DSTRACK.EXDSCMD2',
          value: '',
          x: 1443.806871,

          x_big: 885.81,
          keyList: [25],
          line: 'three'
        },
        {
          key: 'L2DSTRACK.EXDSCMD3',
          value: '',
          x: 1477.321743,

          x_big: 1007,
          keyList: [26],
          line: 'three'
        },
        {
          key: 'L2DSTRACK.EXDSCMD4',
          value: '',
          x: 1498.268538,

          x_big: 1082,
          keyList: [27],
          line: 'three'
        },
        {
          key: 'L2DSTRACK.PILERCMD1',
          value: '',
          x: 1544.351487,

          x_big: 1251,
          keyList: [28],
          line: 'three'
        },
        {
          key: 'L2DSTRACK.PILERCMD2',
          value: '',
          x: 1577.866359,

          x_big: 1376,
          keyList: [29],
          line: 'three'
        },
        {
          key: 'L2DSTRACK.PILERCMD3',
          value: '',
          x: 1611.381232,

          x_big: 1497,
          keyList: [30],
          line: 'three'
        },
        {
          key: 'L2DSTRACK.PILERCMD4',
          value: '',
          x: 1649.085463,

          x_big: 1635,
          keyList: [31],
          line: 'three'
        }
      ],
      cmd_use: [],
      dialogVisibleCmd: false,
      updateCmdText: '',
      updateCmdSelect: 1,
      updateCmdList: [],
      radioCmd: 2,
      updateCmdDisabled: true,
      currentCmdInfo: {},
      trackData: [],
      trackDataBig: [],
      tableDataLeftTop: [
        {
          key0: ''
        }
      ],
      dcjhData1: [], //1324.4px
      dcjhData2: [], //1324.4px
      MESPRINT_WGT: 0,
      MESPRINT_NUM: 0
    }
  },
  beforeCreate() {},
  mounted() {
    this.getHmiData()
    // this.sendTagTest()
  },
  destroyed() {
    stopGetData()
  },
  methods: {
    getHmiData() {
      getHmiData(
        'main',
        data => {
          data['flall_mat'].forEach(item => {
            item.tailX = item.tail_x
            item.Vpos = item.v_pos
            item.headX = item.head_x
          })
          this.trackSteel(data)
          this.getGWJData(data)
          this.initCmd(data)
          this.cmd_use = data['CMD_USE']
          this.MESPRINT_WGT = data['MESPRINT_WGT']
          this.MESPRINT_NUM = data['MESPRINT_NUM']
          // stopGetData()
        },
        error => {
          console.log(error)
        },
        1000
      )
    },
    //封装成对象方法使用
    trackSteel(data) {
      // 页面和实际比例 以整个图为例 宽度: 实际67.270m  页面604px  七点==>1号线终点  长度: 实际394.753m  页面长度 1654px
      // 辊道 宽度 3.51 页面 30px
      let [actWid, pageWid, actLen, pageLen, actgd, pagegd] = [
        67.27 * 1000,
        598.8,
        394.753 * 1000,
        1654,
        3.51 * 1000,
        30
      ]
      this.trackData = []
      this.dcjhData1 = []
      this.dcjhData2 = []
      for (let i = 0; i < data['flall_mat'].length; i++) {
        let item = data['flall_mat'][i]
        if (item.region == 2 || item.region == 3 || item.region == 4) {
          this.trackData.push({
            width: this.countSteelLeng(actLen, pageLen, item.platelenmeas_cb),
            tailpos: this.countSteeltail(actLen, pageLen, item.tail_x_cb),
            tailposbig: this.countSteeltail(79888, 1218, item.tail_x_cb),
            height: this.countSteelWid(actWid, pageWid, item.platewid),
            vPos:
              this.countSteelPosY(actWid, pageWid, item.v_pos) +
              (pagegd - this.countSteelWid(actgd, pagegd, item.platewid)) / 2, //计算辊道中心位置
            plateno: item.plateno,
            platenoSimple:
              item.platelenmeas > 16000
                ? item.plateno
                : '..' + item.plateno.slice(-5),
            platethk: item.platethk,
            platewid: item.platewid,
            platelen: item.platelenmeas,
            platewet: item.platewet,
            cbdec: item.cbdec,
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
            color: item.colour,
            region: item.region
          })
        } else {
          this.trackData.push({
            width: this.countSteelLeng(actLen, pageLen, item.platelenmeas),
            tailpos: this.countSteeltail(actLen, pageLen, item.tail_x),
            tailposbig: this.countSteeltail(79480, 1218, item.tail_x - 315259),
            height: this.countSteelWid(actWid, pageWid, item.platewid),
            vPos:
              this.countSteelPosY(actWid, pageWid, item.v_pos) +
              (pagegd - this.countSteelWid(actgd, pagegd, item.platewid)) / 2, //计算辊道中心位置
            plateno: item.plateno,
            platenoSimple:
              item.platelenmeas > 16000
                ? item.plateno
                : '..' + item.plateno.slice(-5),
            platethk: item.platethk,
            platewid: item.platewid,
            platelen: item.platelenmeas,
            platewet: item.platewet,
            cbdec: item.cbdec,
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
            color: item.colour,
            region: item.region
          })
        }
        /*region==5：1号精整线 region==7：2号精整线*/
        if (
          item.region == 5 &&
          this.countSteeltail(actLen, pageLen, item.tail_x) > 1324 &&
          this.countSteeltail(actLen, pageLen, item.tail_x) < 1489
        ) {
          this.dcjhData1.push({
            plateno: item.plateno
          })
        }
        if (
          item.region == 7 &&
          this.countSteeltail(actLen, pageLen, item.tail_x) > 1385 &&
          this.countSteeltail(actLen, pageLen, item.tail_x) < 1605
        ) {
          this.dcjhData2.push({
            plateno: item.plateno
          })
        }
      }
      //筛选出放大区域数据 left 1322  re 5, 7
      this.trackDataBig = this.trackData.filter(
        item =>
          (item.region == 5 && item.tailpos >= 1320) ||
          (item.region == 7 && item.tailpos >= 1382)
      )
    },
    initCmd(data) {
      this.cmdList.forEach(item => {
        item.value = data[item.key]
        // item.value = 3
      })
      let cmd3ListHl = data['CMD_USE']
        .filter(v => v.HLCMD_USE != -1)
        .map(i => i.HLCMD_USE)
      let cmd3ListFL1 = data['CMD_USE']
        .filter(
          v =>
            v.FL1CMD_USE != -1 &&
            v.CMD_SEQ != 6 &&
            v.CMD_SEQ != 8 &&
            v.CMD_SEQ != 10 &&
            v.CMD_SEQ != 12 &&
            v.CMD_SEQ != 17 &&
            v.CMD_SEQ != 19 &&
            v.CMD_SEQ != 21 &&
            v.CMD_SEQ != 23 &&
            v.CMD_SEQ != 25 &&
            v.CMD_SEQ != 27
        )
        .map(i => i.FL1CMD_USE)
      let cmd3ListFL2 = data['CMD_USE']
        .filter(v => v.FL2CMD_USE != -1)
        .map(i => i.FL2CMD_USE)
      let cmd3all = [...cmd3ListHl, ...cmd3ListFL1, ...cmd3ListFL2]
      // console.log(this.cmdList)
      // console.log(cmd3ListHl)
      // console.log(cmd3ListFL1)
      // console.log(cmd3ListFL2)
      for (let i = 0; i < cmd3all.length; i++) {
        if (cmd3all[i] == 0) {
          this.cmdList[i].value = 3
        }
      }
      // console.log(this.cmdList)
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
    getGWJData(data) {
      this.gwj.gwj1 = data['CBTRACK.ENCBHDT'].toFixed(0)
      this.gwj.gwj2 = data['CBTRACK.EXCBHDT'].toFixed(0)
    },
    modColor(opdialog, item) {
      clearTimeout(this.timer)
      this.$confirm('是否确定删除/添加钢板缺陷颜色, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          let data = [
            [
              {
                plateno: item.plateno,
                region: item.region
              }
            ]
          ]
          sendMsg(data, 1812, 'HMI').then(res => {
            if (res.code != 200) return
            this.$message({
              message: '修改成功',
              type: 'success'
            })
          })
        })
        .catch(() => {
          this.$message({
            type: 'info',
            message: '已取消修改'
          })
        })
    },
    sendMsgFn(plateno) {
      clearTimeout(this.timer)
      this.timer = setTimeout(() => {
        console.log('1804')
        let data = [
          [
            {
              plateno: plateno
            }
          ]
        ]
        sendMsg(data, 1804, 'HMI').then(res => {
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
      }, 400)
    },
    amend(item) {
      this.currentCmdInfo = item
      this.updateCmdText = item.key
      this.radioCmd = item.value == 3 ? 2 : 1
      this.updateCmdDisabled = item.keyList.length == 2 ? false : true
      this.dialogVisibleCmd = true
    },
    subCmdStatus() {
      let data = {
        CMD_USE: this.cmd_use
      }
      if (this.currentCmdInfo.keyList.length == 1) {
        let e = ''
        switch (this.currentCmdInfo.line) {
          case 'one':
            e = 'HLCMD_USE'
            break
          case 'two':
            e = 'FL1CMD_USE'
            break
          case 'three':
            e = 'FL2CMD_USE'
            break
        }

        data.CMD_USE[this.currentCmdInfo.keyList[0] - 1][e] =
          this.radioCmd == 2 ? 0 : 1
        console.log(data.CMD_USE)
      }

      if (this.currentCmdInfo.keyList.length == 2) {
        let e = ''
        switch (this.currentCmdInfo.line) {
          case 'one':
            e = 'HLCMD_USE'
            break
          case 'two':
            e = 'FL1CMD_USE'
            break
          case 'three':
            e = 'FL2CMD_USE'
            break
        }
        if (this.updateCmdSelect == 1) {
          data.CMD_USE[this.currentCmdInfo.keyList[0] - 1][e] =
            this.radioCmd == 2 ? 0 : 1
        } else if (this.updateCmdSelect == 2) {
          data.CMD_USE[this.currentCmdInfo.keyList[1] - 1][e] =
            this.radioCmd == 2 ? 0 : 1
        }
        console.log(data.CMD_USE)
      }
      sendTag(data).then(res => {
        this.$message({
          message: '修改成功',
          type: 'success'
        })
        this.dialogVisibleCmd = false
      })
    },
    handleClose() {
      this.dialogVisibleCmd = false
    }
  }
}
</script>

<style lang="less">
.transparency {
  position: absolute;
  top: 0;
  width: 12px;
  height: 12px;
  border-radius: 50%;
  background-color: transparent;
  //border: 1px solid darkred;
  cursor: pointer;
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

.el-table .cell {
  white-space: nowrap;
}

.el-tooltip__popper {
  white-space: pre-line !important;
  font-size: 14px;
}

.main {
  .bgc-white {
    background-color: #fff;
    box-shadow: 0px 0px 4px rgb(0 0 0 / 4%), 0px 0px 16px -2px rgb(0 0 0 / 10%);
    border-radius: 6px;
  }

  .banner {
    //height: 592px;
    //padding: 10px 18px;
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
      height: 1032px;
      position: relative;
      //overflow-x: scroll;
      .bgimg-box {
        height: 100%;
        //width: 3248px;
        //background: url('../assets/bgimgbig.png') no-repeat;
        background: url('../assets/bg/home.png') no-repeat;
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
            top: 22px;
            left: 261px;
            color: #cd0808;
          }

          &:nth-child(2) {
            top: 452px;
            left: 666px;
            color: #cd0808;
          }
        }
      }
      .other4 {
        position: absolute;
        right: 160px;
        top: 100px;
        font-size: 24px;
        > span {
          .blue {
            font-size: 26px;
            color: #2e80ec;
          }
          &:nth-child(1) {
            margin-right: 20px;
          }
        }
      }

      .one {
        position: absolute;
        //top: 48px;
        top: 49px;
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
          //line-height: 22px;
          //transform: scale(0.9);
          font-size: 12px;
          display: block;
        }
      }

      .dcjh-box1 {
        position: absolute;
        right: 110px;
        top: 180px;

        .el-table td,
        .el-table th {
          padding: 2px 0;
        }
      }

      .dcjh-box2 {
        position: absolute;
        right: 110px;
        top: 380px;

        .el-table td,
        .el-table th {
          padding: 2px 0;
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
