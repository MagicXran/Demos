<template>
  <el-row>
    <div
      v-tag:tag="variable"
      data-page="dcjHistory"/>
    <el-row style="margin-bottom: 20px">
      <el-col>
        <div class="banner bgc-white">
          <div class="bgimg">
            <div class="bgimg-box"/>
            <div class="track-box">
              <trackItem
                :track-data="trackData"
                :top="68"
                :left="7"
                :type="1"
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
            </div>
          </div>
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
                style="display: block; width: 100%"
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
                style="display: block; width: 100%"
                alt="">
            </div>
          </div>
        </div>
      </el-col>
      <el-col
        :span="16"
        class="">
        <warn-info
          :warn-type="2"
        />
        <div
          class="bgc-white"
          style="margin-top: 20px">
          <div class="table-box">
            <p class="title-p">
              剪切长度
            </p>
            <div>
              <hmi-table
                :table-height="330"
                :table-data="tableDataOne"
                :is-pagination-show="false"
                :table-foot="false"
                :table-head="false"
              >
                <template slot="TableBody">
                  <el-table-column
                    prop="TIME_START"
                    sortable
                    label="时间"
                    align="center"/>
                  <el-table-column
                    prop="STEEL_ID"
                    label="钢板号"
                    sortable
                    align="center"/>
                  <el-table-column
                    prop="LEN_TARGET"
                    label="目标长度"
                    sortable
                    align="center"/>
                  <el-table-column
                    prop="LEN_STOPED"
                    label="停止长度"
                    sortable
                    align="center"/>
                  <el-table-column
                    prop="LEN_CUT"
                    label="剪切长度"
                    sortable
                    align="center"/>
                </template>
            </hmi-table></div>
          </div>
        </div>
      </el-col>
    </el-row>
  </el-row>
</template>

<script>
import HmiTable from '@/components/HmiTable'
import warnInfo from '@/pages/components/warnInfo'
import { getHmiData, stopGetData } from '@/lib/GetData'
import setInfo from '@/pages/components/setInfo'
import steelInfo from '@/pages/components/steelInfo'
import modifInfo from '@/pages/components/modifInfo'
import trackItem from '@/pages/components/trackItem'
export default {
  name: 'DcjWorking',
  components: {
    HmiTable,
    warnInfo,
    setInfo,
    steelInfo,
    modifInfo,
    trackItem
  },
  data() {
    return {
      variable: [
        'LMS_Work_Url_Stop',
        'LMS_Work_Url_Cut',
        'LMS_Work_Table',
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
      imgMap: {
        stopImgUrl: '',
        cutImgUrl: ''
      },
      trackData: [],
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
      tableDataOne: []
    }
  },
  mounted() {
    this.getHmiData()
  },
  destroyed() {
    stopGetData()
  },
  methods: {
    getHmiData() {
      getHmiData(
        'dcjHistory',
        data => {
          this.imgMap.cutImgUrl = data['LMS_Work_Url_Cut']
          this.imgMap.stopImgUrl = data['LMS_Work_Url_Stop']
          this.tableDataOne = data['LMS_Work_Table']
          data['rechmi7'].forEach(item => {
            item.tailX = item.tail_x
            item.Vpos = item.v_pos
            item.headX = item.head_x
          })
          data['rechmi7'].map((item, index) => {
            item.v_pos = item.v_pos - 67270
            item.tail_x = item.tail_x - 282589
          })
          this.trackSteel(data)
          this.getTableDataByProcess(data)
          this.initCmd(data)
          this.initCamera(data)
        },
        error => {
          console.log(error)
        },
        1000
      )
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
    }
  }
}
</script>

<style scoped lang="less">
.bgc-white {
  background-color: #fff;
  box-shadow: 0px 0px 4px rgb(0 0 0 / 4%), 0px 0px 16px -2px rgb(0 0 0 / 10%);
  border-radius: 6px;
  padding: 20px !important;
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
