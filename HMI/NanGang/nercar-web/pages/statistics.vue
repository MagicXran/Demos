<template>
  <div class="statistics">
    <el-row>
      <el-col :span="24">
        <div class="container-p">
          <p class="title-p">
            月统计-块数、重量
            <el-button
              size="mini"
              type="primary"
              @click="dialogTableVisible = true"
            >打开看板</el-button>
          </p>
          <p
            class="title-p"
            style="padding-left: 110px"> <span class="title-tip">
              <span class="">总重量: {{ oneResAll.wgh.toFixed(0) }}</span>
              <span class="">总块数: {{ oneResAll.num }}</span>
          </span></p>
          <div
            v-for="(item,key) in oneResData"
            :key="key"
            class="">
            <div
              class=""
              style="font-size: 16px">
              <span>{{ item.PRINT_DATE }} 平均长宽厚</span>
              <span class="number">{{ item.LEN_AVG.toFixed(0) }} * {{ item.WID_AVG.toFixed(0) }} * {{ item.THK_AVG.toFixed(0) }}</span>
            </div>
          </div>

          <nercar-echarts
            :_height="'400px'"
            :theme-dark="false"
            :grid="echartsList[0].grid"
            :legend="echartsList[0].legend"
            :x-axis="echartsList[0].xAxis"
            :y-axis="echartsList[0].yAxis"
            :series="echartsList[0].series"
            :tooltip="echartsList[0].tooltip"
          />
        </div>

      </el-col>
    </el-row>
    <el-row>
      <div
        class="container-p"
        style="height: 380px">
        <el-col :span="12">
          <p class="title-p">
            班组统计-块数
          </p>
          <nercar-echarts
            :_height="'300px'"
            :theme-dark="false"
            :grid="echartsList[1].grid"
            :legend="echartsList[1].legend"
            :x-axis="echartsList[1].xAxis"
            :y-axis="echartsList[1].yAxis"
            :series="echartsList[1].series"
            :tooltip="echartsList[1].tooltip"
          />
        </el-col>
        <el-col
          :span="12"
          style="overflow: hidden">
          <p class="title-p">
            班组统计-重量
          </p>
          <nercar-echarts
            :_height="'300px'"
            :theme-dark="false"
            :grid="echartsList[2].grid"
            :legend="echartsList[2].legend"
            :x-axis="echartsList[2].xAxis"
            :y-axis="echartsList[2].yAxis"
            :series="echartsList[2].series"
            :tooltip="echartsList[2].tooltip"
          />
        </el-col>
      </div>
    </el-row>

    <!--:fullscreen="true"-->
    <el-dialog
      :top="'5px'"
      :before-close="handleClose"
      :visible.sync="dialogTableVisible"
      :modal-append-to-body="true"
      width="98%"
      custom-class="board"
      title="">
      <div class="board-box">
        <boardHeader
          :title="title"
        />
        <div class="container">
          <div class="score">
            <div
              v-for="(item,key) in oneResData"
              :key="key"
              class="score-box">
              <div class="score-left">
                <p>{{ item.PRINT_DATE }} 平均长宽厚</p>
                <p class="number">{{ item.LEN_AVG.toFixed(0) }} * {{ item.WID_AVG.toFixed(0) }} * {{ item.THK_AVG.toFixed(1) }}</p>
              </div>
            </div>
          </div>
          <div class="main">
            <el-row>
              <el-col :span="24">
                <el-form
                  :inline="true"
                >
                  <el-form-item label="">
                    <el-date-picker
                      v-model="month1"
                      size="mini"
                      type="month"
                      disabled
                      placeholder="开始月"/>
                  </el-form-item>
                  <el-form-item label="至">
                    <el-date-picker
                      v-model="month2"
                      type="month"
                      size="mini"
                      placeholder="结束月"/>
                  </el-form-item>
                  <el-form-item>
                    <el-button
                      size="mini"
                      type="primary"
                      @click="findOne"
                    >查询
                    </el-button>
                  </el-form-item>
                </el-form>
              </el-col>
            </el-row>
            <el-row>
              <el-col :span="24">
                <div class="item-box">
                  <p class="title-big">半年数据统计
                    <span class="title-tip">
                      <span class="">总重量: {{ oneResAll.wgh.toFixed(0) }}</span>
                      <span class="">总块数: {{ oneResAll.num }}</span>
                    </span>
                  </p>
                  <div class="content-box">
                    <nercar-echarts
                      :_height="'270px'"
                      :grid="echartsList[0].grid"
                      :legend="echartsList[0].legend"
                      :x-axis="echartsList[0].xAxis"
                      :y-axis="echartsList[0].yAxis"
                      :series="echartsList[0].series"
                      :tooltip="echartsList[0].tooltip"
                    />
                  </div>
                </div>
              </el-col>
            </el-row>
            <el-row style="margin-top: 10px">
              <el-col :span="24">
                <el-form
                  :inline="true"
                >
                  <el-form-item label="">
                    <el-date-picker
                      v-model="month3"
                      size="mini"
                      type="month"
                      placeholder="选择月"/>
                  </el-form-item>
                  <el-form-item>
                    <el-button
                      size="mini"
                      type="primary"
                      @click="findTwo"
                    >查询
                    </el-button>
                  </el-form-item>
                </el-form>
              </el-col>
            </el-row>
            <el-row :gutter="20">
              <el-col :span="12">
                <div class="item-box">
                  <p class="title-big">班组统计-块数</p>
                  <div class="content-box">
                    <nercar-echarts
                      :_height="'230px'"
                      :grid="echartsList[1].grid"
                      :legend="echartsList[1].legend"
                      :x-axis="echartsList[1].xAxis"
                      :y-axis="echartsList[1].yAxis"
                      :series="echartsList[1].series"
                      :tooltip="echartsList[1].tooltip"
                    />
                  </div>
                </div>
              </el-col>
              <el-col :span="12">
                <div class="item-box">
                  <p class="title-big">班组统计-重量</p>
                  <div class="content-box">
                    <nercar-echarts
                      :_height="'230px'"
                      :grid="echartsList[2].grid"
                      :legend="echartsList[2].legend"
                      :x-axis="echartsList[2].xAxis"
                      :y-axis="echartsList[2].yAxis"
                      :series="echartsList[2].series"
                      :tooltip="echartsList[2].tooltip"
                    />
                  </div>
                </div>
              </el-col>
            </el-row>
          </div>
        </div>
      </div>

    </el-dialog>
  </div>
</template>

<script>
import nercarEcharts from '@/components/NercarEcharts'
import boardHeader from './components/boardHeader'
import {
  getHmiData,
  getHmiDataByEvent,
  sendMsg,
  sendTag,
  stopGetData
} from '@/lib/GetData'
export default {
  name: 'Statistics',
  components: {
    nercarEcharts,
    boardHeader
  },
  data() {
    return {
      title: '南钢板卷精整跟踪项目数据统计',
      month1: '',
      month2: new Date(),
      month3: new Date(),
      dialogTableVisible: true,
      allData: [],
      dataByTime: {},
      avgList: [],
      num_sum: 0,
      wgt_sum: 0,
      dataByBanzu: {
        甲: {
          PDINUM: 0,
          PDIWGT: 0
        },
        乙: {
          PDINUM: 0,
          PDIWGT: 0
        },
        丙: {
          PDINUM: 0,
          PDIWGT: 0
        },
        丁: {
          PDINUM: 0,
          PDIWGT: 0
        }
      },
      echartsList: [
        {
          name: '半年总块数与总重量',
          grid: {
            left: '1%',
            right: '1%',
            bottom: '3',
            top: '16%',
            containLabel: true
          },
          tooltip: {
            trigger: 'axis'
          },
          legend: {
            right: '50%',
            top: '4%',
            data: ['总块数', '总重量']
          },
          xAxis: [
            {
              type: 'category',
              data: ['1', '2', '3', '4', '5', '6'],
              axisPointer: {
                type: 'shadow'
              },
              axisLine: {
                show: false // 不显示坐标轴线
              },
              splitLine: {
                lineStyle: {
                  color: 'rgba(77, 96, 129, 1)'
                }
              }
            }
          ],
          yAxis: [
            {
              min: 0,
              type: 'value',
              scale: true,
              name: '重量/块数',
              axisLine: {
                show: false // 不显示坐标轴线
              },
              axisLabel: {
                formatter: '{value} '
              },
              splitLine: {
                lineStyle: {
                  color: 'rgba(77, 96, 129, 1)'
                }
              }
            },
            {
              min: 0,
              name: '总重量',
              scale: true,
              show: false,
              type: 'value',
              axisLine: {
                show: false // 不显示坐标轴线
              },
              splitLine: {
                lineStyle: {
                  color: 'rgba(77, 96, 129, 1)'
                }
              },
              axisLabel: {
                formatter: '{value} '
              }
            }
          ],
          series: [
            {
              name: '总块数',
              type: 'bar',
              barGap: '80%' /*多个并排柱子设置柱子之间的间距*/,
              itemStyle: {
                color: '#3391FF',
                normal: {
                  label: {
                    show: true, //开启显示
                    position: 'top', //在上方显示
                    distance: 5,
                    rotate: 20,
                    offset: [0, 0],
                    textStyle: {
                      //数值样式
                      color: '#fff',
                      fontSize: 12
                    }
                  }
                }
              },
              barWidth: 30,
              data: []
            },
            {
              name: '总重量',
              type: 'bar',
              yAxisIndex: 0,
              itemStyle: {
                color: 'rgba(255, 152, 0, 1)',
                normal: {
                  label: {
                    show: true, //开启显示
                    position: 'top', //在上方显示
                    distance: 5,
                    rotate: 20,
                    offset: [0, 0],
                    textStyle: {
                      //数值样式
                      color: '#fff',
                      fontSize: 12
                    }
                  }
                }
              },
              barWidth: 30,
              data: []
            }
          ]
        },
        {
          name: '班组统计-块数',
          grid: {
            left: '1%',
            right: '5%',
            bottom: '3',
            top: '16%',
            containLabel: true
          },
          tooltip: {
            trigger: 'axis'
          },
          legend: {
            right: '12%',
            top: '0%',
            data: ['总块数', '总重量']
          },
          xAxis: [
            {
              type: 'category',
              data: ['甲', '乙', '丙', '丁'],
              axisPointer: {
                type: 'shadow'
              },
              axisLine: {
                show: false // 不显示坐标轴线
              },
              splitLine: {
                lineStyle: {
                  color: 'rgba(77, 96, 129, 1)'
                }
              }
            }
          ],
          yAxis: [
            {
              type: 'value',
              scale: true,
              min: 0,
              name: '总块数',
              axisLine: {
                show: false // 不显示坐标轴线
              },
              axisLabel: {
                formatter: '{value} '
              },
              splitLine: {
                lineStyle: {
                  color: 'rgba(77, 96, 129, 1)'
                }
              }
            }
          ],
          series: [
            {
              name: '总块数',
              type: 'bar',
              barGap: '80%' /*多个并排柱子设置柱子之间的间距*/,
              itemStyle: {
                color: '#3391FF',
                normal: {
                  label: {
                    show: true, //开启显示
                    position: 'top', //在上方显示
                    distance: 5,
                    rotate: 20,
                    offset: [0, 0],
                    textStyle: {
                      //数值样式
                      color: '#fff',
                      fontSize: 12
                    }
                  }
                }
              },
              barWidth: 30,
              data: []
            }
          ]
        },
        {
          name: '班组统计-重量',
          grid: {
            left: '1%',
            right: '5%',
            bottom: '3',
            top: '16%',
            containLabel: true
          },
          tooltip: {
            trigger: 'axis'
          },
          legend: {
            right: '12%',
            top: '0%',
            data: ['总块数', '总重量']
          },
          xAxis: [
            {
              type: 'category',
              data: ['甲', '乙', '丙', '丁'],
              axisPointer: {
                type: 'shadow'
              },
              axisLine: {
                show: false // 不显示坐标轴线
              },
              splitLine: {
                lineStyle: {
                  color: 'rgba(77, 96, 129, 1)'
                }
              }
            }
          ],
          yAxis: [
            {
              min: 0,
              type: 'value',
              scale: true,
              name: '总重量',
              axisLine: {
                show: false // 不显示坐标轴线
              },
              axisLabel: {
                formatter: '{value} '
              },
              splitLine: {
                lineStyle: {
                  color: 'rgba(77, 96, 129, 1)'
                }
              }
            }
          ],
          series: [
            {
              name: '总重量',
              type: 'bar',
              barGap: '80%' /*多个并排柱子设置柱子之间的间距*/,
              itemStyle: {
                normal: {
                  color: 'rgb(245,165,47)',
                  label: {
                    show: true, //开启显示
                    position: 'top', //在上方显示
                    distance: 5,
                    rotate: 20,
                    offset: [0, 0],
                    textStyle: {
                      //数值样式
                      color: '#fff',
                      fontSize: 12
                    }
                  }
                }
              },
              barWidth: 30,
              data: []
            }
          ]
        }
      ],
      oneResData: [],
      oneResAll: {
        num: 0,
        wgh: 0
      }
    }
  },
  watch: {
    month2: {
      handler(data) {
        const currentDate = new Date(data)
        const lastMonth = new Date(
          currentDate.getFullYear(),
          currentDate.getMonth() - 5,
          currentDate.getDate()
        )
        this.month1 = lastMonth
      },
      immediate: true,
      deep: true
    }
  },
  mounted() {
    this.findOne()
    this.findTwo()
  },
  methods: {
    handleClose() {
      this.dialogTableVisible = false
    },
    findOne() {
      this.oneResAll.wgh = 0
      this.oneResAll.num = 0
      let data = [
        [
          {
            table: '5',
            end_time: this.month2.getTime() + ''
          }
        ]
      ]
      sendMsg(data, 1825, 'HMI').then(res => {
        if (!res.results[0][0].msg) {
          this.oneResData = res.results[0]
          let PDINUM_list = []
          let PDIWGT_list = []
          let PRINT_DATE_list = []
          for (let i = 0; i < res.results[0].length; i++) {
            this.oneResAll.num += res.results[0][i].PDINUM
            this.oneResAll.wgh += res.results[0][i].PDIWGT
            PDINUM_list.push(res.results[0][i].PDINUM)
            PDIWGT_list.push(res.results[0][i].PDIWGT.toFixed(0))
            PRINT_DATE_list.push(res.results[0][i].PRINT_DATE)
          }
          this.echartsList[0].xAxis[0].data = PRINT_DATE_list
          this.echartsList[0].series[0].data = PDINUM_list
          this.echartsList[0].series[1].data = PDIWGT_list
        } else {
          alert(res.results[0][0].msg)
        }
      })
    },
    findTwo() {
      let data = [
        [
          {
            table: '6',
            newtime: this.month3.getTime() + ''
          }
        ]
      ]
      sendMsg(data, 1825, 'HMI').then(res => {
        if (!res.results[0][0].msg) {
          this.echartsList[1].series[0].data = []
          this.echartsList[2].series[0].data = []
          for (let i = 0; i < res.results[0].length; i++) {
            this.echartsList[1].series[0].data.push(res.results[0][i].PDINUM)
            this.echartsList[2].series[0].data.push(
              res.results[0][i].PDIWGT.toFixed(0)
            )
          }
        } else {
          alert(res.results[0][0].msg)
        }
      })
    }
  }
}
</script>

<style scoped lang="less">
.el-form--inline .el-form-item {
  margin-bottom: 0;
}
/deep/ .el-input__inner {
  color: #ffffff;
  background-color: transparent !important;
}
/deep/.board {
  .item-box {
    background: url('../assets/board_img/box_bg.png') no-repeat;
    background-size: 100% 100%;
  }
  .title-tip {
    float: right;
    color: #ffffff;
    > span {
      font-size: 18px;
      margin-right: 8px;
    }
  }
  .title-big {
    width: 100%;
    height: 50px;
    line-height: 50px;
    font-size: 20px;
    font-weight: 700;
    padding: 0 20px;
    background: url('../assets/board_img/biaotiL.png') no-repeat;
    background-size: 100% 100%;
    color: #ffffff;
  }
  .board-box {
    background-color: #152540;
    height: 100%;
    width: 100%;
    color: rgba(180, 192, 204, 1);
  }
  .container {
    padding: 20px 30px;
  }
  .score {
    display: flex;
    width: 100%;
    flex-wrap: nowrap;
    justify-content: space-evenly;
    .score-box {
      background: url('../assets/board_img/border_bg.png') no-repeat;
      background-size: 100% 100%;
      //width: 220px;
      //height: 82px;
      width: 286px;
      height: 90px;
      display: flex;
      justify-content: space-around;
      padding: 5px 20px;
      .score-left {
        width: 100%;
        font-size: 24px;
        color: #adeaff;
        .number {
          font-size: 26px;
          margin-top: 8px;
          color: #1fc6ff;
          > i {
            font-size: 16px;
          }
        }
        .font {
          color: #19be6b;
        }
      }
      .score-right {
        width: 30%;
        line-height: 110px;
        > img {
          width: 56px;
          display: block;
          margin-top: 20px;
          margin-left: 8px;
        }
      }
    }
  }
  .main {
    margin-top: 20px;
  }
  background-color: #152540;
  .el-dialog__header {
    padding: 0;
  }
  .el-dialog__body {
    padding: 0;
  }
  .el-dialog__headerbtn {
    z-index: 99;
    top: 7px;
    right: 13px;
    > i {
      color: rgba(180, 192, 204, 1);
    }
  }
}
.container-p {
  background-color: #fff;
  box-shadow: 0px 0px 4px rgb(0 0 0 / 4%), 0px 0px 16px -2px rgb(0 0 0 / 10%);
  border-radius: 6px;
  padding: 24px;
  margin-bottom: 20px;
}
.title-p {
  font-weight: 700;
  font-size: 20px;
  color: #606266;
  font-family: 'Microsoft YaHei UI';
  margin-bottom: 15px;
}
</style>
