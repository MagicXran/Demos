<template>
  <div class="dbj1">
    <div
      v-tag:tag="variable"
      data-page="1dbj"/>
    <div class="banner bgc-white">
      <div class="bgimg">
        <div class="bgimg-box"/>
        <div class="track-box">
          <trackItem
            :track-data="trackData"
            :top="69"
            :left="4"
            :type="1"
            @opdialog="opdialog"
            @getTableDataByTwo="getTableDataByTwo"
          />
          <div class="cmd-box">
            <ul>
              <li
                v-for="(item, index) in cmdList"
                v-if="item.value == 1"
                :data-c="item.key"
                :style="'top:57px;'+'left:'+(item.x - 2)+'px'"
                :key="index">
                <img
                  src="../assets/green.png"
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
      <el-row :gutter="20">
        <el-col :span="5">
          <div
            class="bgc-white"
            style="padding: 24px">
            <div
              class="header">
              <p class="ps">表检设定</p>
              <p
                v-if="!form1.changeFlag"
                style="color: #FFA958;font-size: 13px">修改中... <i
                  style="font-size: 20px;cursor: pointer"
                  class="el-icon-circle-close"
                  @click="openRefresh(form1)"
              /></p>
              <div
                v-if="form1.changeFlag"
                class="cz"
              >
                <div>
                  <span
                    style="font-size: 14px;
                                vertical-align: bottom;
                                color: #606266;
                                letter-spacing: 1px;
                                font-weight: 600;">L2投用</span>
                  <el-switch
                    v-model="form1.L1SISSET_UseFlag"
                    active-color="green"
                    inactive-color="red"
                    @change="closeRefresh(form1)"/>
                </div>
              </div>
              <div
                v-if="!form1.changeFlag"
                class="cz"
              >
                <div>
                  <span
                    style="font-size: 14px;
                                vertical-align: bottom;
                                color: #606266;
                                letter-spacing: 1px;
                                font-weight: 600;">L2投用</span>
                  <el-switch
                    v-model="form1Change.L1SISSET_UseFlag"
                    active-color="green"
                    inactive-color="red"/>
                </div>
              </div>
            </div>
            <div
              v-if="form1.changeFlag"
              class="form-boder">
              <el-form
                ref="form1"
                :model="form1"
                label-width="80px">
                <el-form-item label="钢板号">
                  <el-input
                    v-model="form1.L1SISSET_PlateNo"
                    size="mini"
                    @focus="closeRefresh(form1)">
                    <el-button
                      slot="append"
                      icon="el-icon-search"
                      @click="getTableDataByTwo(form1.L1SISSET_PlateNo,3)"/>
                  </el-input>
                </el-form-item>
                <el-form-item label="钢种">
                  <el-input
                    v-model="form1.L1SISSET_Stdspec"
                    size="mini"
                    @focus="closeRefresh(form1)"/>
                </el-form-item>
                <el-form-item label="母板长度">
                  <el-input
                    v-model="form1.L1SISSET_Plate_Len"
                    size="mini"
                    @focus="closeRefresh(form1)">
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
                <el-form-item label="母板宽度">
                  <el-input
                    v-model="form1.L1SISSET_Plate_Wid"
                    size="mini"
                    @focus="closeRefresh(form1)">
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
                <el-form-item label="母板厚度">
                  <el-input
                    v-model="form1.L1SISSET_Plate_Thk"
                    size="mini"
                    @focus="closeRefresh(form1)">
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
              </el-form>
            </div>
            <div
              v-if="!form1.changeFlag"
              class="form-boder">
              <el-form
                ref="form1"
                :model="form1Change"
                label-width="80px">
                <el-form-item label="钢板号">
                  <el-input
                    v-model="form1Change.L1SISSET_PlateNo"
                    size="mini"
                  >
                    <el-button
                      slot="append"
                      icon="el-icon-search"
                      @click="getTableDataByTwo(form1Change.L1SISSET_PlateNo,3)"/>
                  </el-input>
                </el-form-item>
                <el-form-item label="钢种">
                  <el-input
                    v-model="form1Change.L1SISSET_Stdspec"
                    size="mini"
                  />
                </el-form-item>
                <el-form-item label="母板长度">
                  <el-input
                    v-model="form1Change.L1SISSET_Plate_Len"
                    size="mini"
                  >
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
                <el-form-item label="母板宽度">
                  <el-input
                    v-model="form1Change.L1SISSET_Plate_Wid"
                    size="mini"
                  >
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
                <el-form-item label="母板厚度">
                  <el-input
                    v-model="form1Change.L1SISSET_Plate_Thk"
                    size="mini"
                  >
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
              </el-form>
            </div>


            <div class="form-button">
              <el-button
                type="primary"
                size="mini"
                @click="againSet(1)">重新设定
              </el-button>
              <el-button
                type="primary"
                size="mini"
                @click="saveSet(1)">修改
              </el-button>
            </div>
          </div>
        </el-col>
        <el-col :span="5">
          <div
            class="bgc-white"
            style="padding: 24px">
            <div
              class="header">
              <p class="ps">标印设定</p>
              <p
                v-if="!form2.changeFlag"
                style="color: #FFA958;font-size: 13px">修改中... <i
                  style="font-size: 20px;cursor: pointer"
                  class="el-icon-circle-close"
                  @click="openRefresh(form2)"
              /></p>
              <div
                v-if="form2.changeFlag"
                class="cz"
              >
                <div>
                  <span
                    style="font-size: 14px;
                                vertical-align: bottom;
                                color: #606266;
                                letter-spacing: 1px;
                                font-weight: 600;">L2投用</span>
                  <el-switch
                    v-model="form2.L1MRKIFSET_UseFlag"
                    active-color="green"
                    inactive-color="red"
                    @change="closeRefresh(form2)"/>
                </div>
              </div>
              <div
                v-if="!form2.changeFlag"
                class="cz"
              >
                <div>
                  <span
                    style="font-size: 14px;
                                vertical-align: bottom;
                                color: #606266;
                                letter-spacing: 1px;
                                font-weight: 600;">L2投用</span>
                  <el-switch
                    v-model="form2Change.L1MRKIFSET_UseFlag"
                    active-color="green"
                    inactive-color="red"/>
                </div>
              </div>
            </div>
            <div
              v-if="form2.changeFlag"
              class="form-boder">
              <el-form
                ref="form2"
                :model="form2"
                label-width="80px">
                <el-form-item label="钢板号">
                  <el-input
                    v-model="form2.L1MRKIFSET_PlateNo"
                    size="mini"
                    @focus="closeRefresh(form2)">
                    <el-button
                      slot="append"
                      icon="el-icon-search"
                      @click="getTableDataByTwo(form2.L1MRKIFSET_PlateNo,3)"/>
                  </el-input>
                </el-form-item>
                <el-form-item label="钢种">
                  <el-input
                    v-model="form2.L1MRKIFSET_Steelgrade"
                    size="mini"
                    @focus="closeRefresh(form2)"/>
                </el-form-item>
                <el-form-item label="母板长度">
                  <el-input
                    v-model="form2.L1MRKIFSET_Plate_Len"
                    size="mini"
                    @focus="closeRefresh(form2)">
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
                <el-form-item label="母板宽度">
                  <el-input
                    v-model="form2.L1MRKIFSET_Plate_Wid"
                    size="mini"
                    @focus="closeRefresh(form2)">
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
                <el-form-item label="母板厚度">
                  <el-input
                    v-model="form2.L1MRKIFSET_Plate_Thk"
                    size="mini"
                    @focus="closeRefresh(form2)">
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
              </el-form>
            </div>
            <div
              v-if="!form2.changeFlag"
              class="form-boder">
              <el-form
                ref="form2"
                :model="form2Change"
                label-width="80px">
                <el-form-item label="钢板号">
                  <el-input
                    v-model="form2Change.L1MRKIFSET_PlateNo"
                    size="mini"
                  >
                    <el-button
                      slot="append"
                      icon="el-icon-search"
                      @click="getTableDataByTwo(form2Change.L1MRKIFSET_PlateNo,3)"/>
                  </el-input>
                </el-form-item>
                <el-form-item label="钢种">
                  <el-input
                    v-model="form2Change.L1MRKIFSET_Steelgrade"
                    size="mini"
                  />
                </el-form-item>
                <el-form-item label="母板长度">
                  <el-input
                    v-model="form2Change.L1MRKIFSET_Plate_Len"
                    size="mini"
                  >
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
                <el-form-item label="母板宽度">
                  <el-input
                    v-model="form2Change.L1MRKIFSET_Plate_Wid"
                    size="mini"
                  >
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
                <el-form-item label="母板厚度">
                  <el-input
                    v-model="form2Change.L1MRKIFSET_Plate_Thk"
                    size="mini"
                  >
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
              </el-form>
            </div>

            <div class="form-button">
              <el-button
                type="primary"
                size="mini"
                @click="againSet(2)">重新设定
              </el-button>
              <el-button
                type="primary"
                size="mini"
                @click="saveSet(2)">修改
              </el-button>
            </div>
          </div>
        </el-col><!--
        <el-col :span="4">
          <div
            class="bgc-white"
            style="padding: 24px">
            <div class="header">
              <p class="ps">垛板设定</p>
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
                    v-model="form3.L1PILERSET_UseFlag"
                    active-color="#13356F"
                    inactive-color="#5e0f0f"
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
                    v-model="form3Change.L1PILERSET_UseFlag"
                    active-color="#13356F"
                    inactive-color="#5e0f0f"/>
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
                    v-model="form3.L1PILERSET_PlateNo"
                    size="mini"
                    @focus="closeRefresh(form3)">
                    <el-button
                      slot="append"
                      icon="el-icon-search"
                      @click="getTableDataByTwo(form3.L1PILERSET_PlateNo,3)"/>
                  </el-input>
                </el-form-item>
                <el-form-item label="钢种">
                  <el-input
                    v-model="form3.L1PILERSET_Stdspec"
                    size="mini"
                    @focus="closeRefresh(form3)"/>
                </el-form-item>
                <el-form-item label="母板长度">
                  <el-input
                    v-model="form3.L1PILERSET_Plate_Len"
                    size="mini"
                    @focus="closeRefresh(form3)">
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
                <el-form-item label="母板宽度">
                  <el-input
                    v-model="form3.L1PILERSET_Plate_Wid"
                    size="mini"
                    @focus="closeRefresh(form3)">
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
                <el-form-item label="母板厚度">
                  <el-input
                    v-model="form3.L1PILERSET_Plate_Thk"
                    size="mini"
                    @focus="closeRefresh(form3)">
                    <template slot="append">mm</template>
                  </el-input>
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
                    v-model="form3Change.L1PILERSET_PlateNo"
                    size="mini"
                  >
                    <el-button
                      slot="append"
                      icon="el-icon-search"
                      @click="getTableDataByTwo(form3Change.L1PILERSET_PlateNo,3)"
                    />
                  </el-input>
                </el-form-item>
                <el-form-item label="钢种">
                  <el-input
                    v-model="form3Change.L1PILERSET_Stdspec"
                    size="mini"
                  />
                </el-form-item>
                <el-form-item label="母板长度">
                  <el-input
                    v-model="form3Change.L1PILERSET_Plate_Len"
                    size="mini">
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
                <el-form-item label="母板宽度">
                  <el-input
                    v-model="form3Change.L1PILERSET_Plate_Wid"
                    size="mini">
                    <template slot="append">mm</template>
                  </el-input>
                </el-form-item>
                <el-form-item label="母板厚度">
                  <el-input
                    v-model="form3Change.L1PILERSET_Plate_Thk"
                    size="mini">
                    <template slot="append">mm</template>
                  </el-input>
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
        </el-col>-->

        <el-col :span="14">
          <warn-info
            :warn-type="2"
          />
        </el-col>
      </el-row>
      <el-row style="margin-top: 20px">
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
import steelInfo from '@/pages/components/steelInfo'
import modifInfo from '@/pages/components/modifInfo'
import trackItem from '@/pages/components/trackItem'

export default {
  name: 'Lcb2',
  components: { HmiTable, warnInfo, steelInfo, modifInfo, trackItem },
  data() {
    return {
      variable: [
        'rechmi4',
        'L1DSTRACK.EXDSCMD1',
        'L1DSTRACK.EXDSCMD2',
        'L1DSTRACK.EXDSCMD3',
        'L1DSTRACK.EXDSCMD4',
        'L1DSTRACK.EXDSCMD5',
        'L1PILERTRACK.PILERSIGNAL13',
        'L1PILERTRACK.PILERSIGNAL14',
        'L1PILERTRACK.PILERSIGNAL15',
        'L1PILERTRACK.PILERSIGNAL16',
        //设定信息
        'L1SISSET_PlateNo',
        'L1SISSET_Stdspec',
        'L1SISSET_Plate_Len',
        'L1SISSET_Plate_Wid',
        'L1SISSET_Plate_Thk',
        'L1SISSET_UseFlag',
        'L1SISSET_FLAG',
        'L1MRKIFSET_PlateNo',
        'L1MRKIFSET_Steelgrade',
        'L1MRKIFSET_Plate_Len',
        'L1MRKIFSET_Plate_Wid',
        'L1MRKIFSET_Plate_Thk',
        'L1MRKIFSET_UseFlag',
        'L1MRKIFSET_FLAG',
        'L1PILERSET_PlateNo',
        'L1PILERSET_Stdspec',
        'L1PILERSET_Plate_Len',
        'L1PILERSET_Plate_Wid',
        'L1PILERSET_Plate_Thk',
        'L1PILERSET_UseFlag',
        'L1PILERSET_FLAG'
      ],
      isReadOnly: 3,
      posForm: {
        oldId: '',
        plant: '',
        radio: '1',
        unit: 1,
        num: '',
        region: ''
      },
      currentId: [],
      tableLoading: false,
      posboxsty: {
        top: '',
        left: ''
      },
      poschangeshow: false,
      timer: null,
      cmdList: [
        {
          key: 'L1DSTRACK.EXDSCMD1',
          value: '',
          x: 290.0608519
        },
        {
          key: 'L1DSTRACK.EXDSCMD2',
          value: '',
          x: 534.158215
        },
        {
          key: 'L1DSTRACK.EXDSCMD3',
          value: '',
          x: 764.9492901
        },
        {
          key: 'L1DSTRACK.EXDSCMD4',
          value: '',
          x: 894.8681542
        },
        {
          key: 'L1DSTRACK.EXDSCMD5',
          value: '',
          x: 1046.795132
        },
        {
          key: 'L1PILERTRACK.PILERSIGNAL13',
          value: '',
          x: 1260.748479
        },
        {
          key: 'L1PILERTRACK.PILERSIGNAL14',
          value: '',
          x: 1332.04503
        },
        {
          key: 'L1PILERTRACK.PILERSIGNAL15',
          value: '',
          x: 1515.841785
        },
        {
          key: 'L1PILERTRACK.PILERSIGNAL16',
          value: '',
          x: 1596.896552
        }
      ],
      steelTablePar: [{}, {}, {}],
      trackData: [],
      form1Change: {},
      form2Change: {},
      form3Change: {},
      form1: {
        name: '表检',
        changeFlag: true,
        L1SISSET_PlateNo: '',
        L1SISSET_Stdspec: '',
        L1SISSET_Plate_Len: '',
        L1SISSET_Plate_Wid: '',
        L1SISSET_Plate_Thk: '',
        L1SISSET_UseFlag: '',
        L1SISSET_FLAG: ''
      },
      form2: {
        name: '标印',
        changeFlag: true,
        L1MRKIFSET_PlateNo: '',
        L1MRKIFSET_Steelgrade: '',
        L1MRKIFSET_Plate_Len: '',
        L1MRKIFSET_Plate_Wid: '',
        L1MRKIFSET_Plate_Thk: '',
        L1MRKIFSET_UseFlag: '',
        L1MRKIFSET_FLAG: ''
      },
      form3: {
        name: '垛板',
        changeFlag: true,
        L1PILERSET_PlateNo: '',
        L1PILERSET_Stdspec: '',
        L1PILERSET_Plate_Len: '',
        L1PILERSET_Plate_Wid: '',
        L1PILERSET_Plate_Thk: '',
        L1PILERSET_UseFlag: '',
        L1PILERSET_FLAG: ''
      }
    }
  },
  computed: {},
  mounted() {
    this.getHmiData()
  },
  destroyed() {
    stopGetData()
  },
  methods: {
    saveSet(num) {
      this.$confirm('是否确定修改?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          let data
          //判断typeFlag 决定submitForm
          if (num == 1) {
            data = {
              L1SISSET_PlateNo: this.form1Change.L1SISSET_PlateNo,
              L1SISSET_Stdspec: this.form1Change.L1SISSET_Stdspec,
              L1SISSET_Plate_Len: this.form1Change.L1SISSET_Plate_Len,
              L1SISSET_Plate_Wid: this.form1Change.L1SISSET_Plate_Wid,
              L1SISSET_Plate_Thk: this.form1Change.L1SISSET_Plate_Thk,
              L1SISSET_UseFlag:
                this.form1Change.L1SISSET_UseFlag == true ? '1' : '0',
              L1SISSET_FLAG: 1
            }
          } else if (num == 2) {
            data = {
              L1MRKIFSET_PlateNo: this.form2Change.L1MRKIFSET_PlateNo,
              L1MRKIFSET_Steelgrade: this.form2Change.L1MRKIFSET_Steelgrade,
              L1MRKIFSET_Plate_Len: this.form2Change.L1MRKIFSET_Plate_Len,
              L1MRKIFSET_Plate_Wid: this.form2Change.L1MRKIFSET_Plate_Wid,
              L1MRKIFSET_Plate_Thk: this.form2Change.L1MRKIFSET_Plate_Thk,
              L1MRKIFSET_UseFlag:
                this.form2Change.L1MRKIFSET_UseFlag == true ? '1' : '0',
              L1MRKIFSET_FLAG: 1
            }
          } else if (num == 3) {
            data = {
              L1PILERSET_PlateNo: this.form3Change.L1PILERSET_PlateNo,
              L1PILERSET_Stdspec: this.form3Change.L1PILERSET_Stdspec,
              L1PILERSET_Plate_Len: this.form3Change.L1PILERSET_Plate_Len,
              L1PILERSET_Plate_Wid: this.form3Change.L1PILERSET_Plate_Wid,
              L1PILERSET_Plate_Thk: this.form3Change.L1PILERSET_Plate_Thk,
              L1PILERSET_UseFlag:
                this.form3Change.L1PILERSET_UseFlag == true ? '1' : '0',
              L1PILERSET_FLAG: 1
            }
          }
          sendTag(data).then(res => {
            if (res.code == 200) {
              this.$message({
                message: '修改成功',
                type: 'success'
              })
              switch (num) {
                case 1:
                  this.form1.changeFlag = true
                case 2:
                  this.form2.changeFlag = true
                case 3:
                  this.form3.changeFlag = true
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
    againSet(num) {
      let data
      if (num == 1) {
        data = [
          [
            {
              plateno: this.form1.L1SISSET_PlateNo,
              process: '3'
            }
          ]
        ]
      } else if (num == 2) {
        data = [
          [
            {
              plateno: this.form2.L1MRKIFSET_PlateNo,
              process: '4'
            }
          ]
        ]
      } else if (num == 3) {
        data = [
          [
            {
              plateno: this.form3.L1PILERSET_PlateNo,
              process: '5'
            }
          ]
        ]
      }
      sendMsg(data, 1808, 'HMI').then(res => {
        if (res.results[0][0].msg) {
          this.$message({
            message: res.results[0][0].msg,
            type: 'success'
          })
        }
      })
    },
    initForm(name) {
      let obj = {
        表检: () => {
          this.form1Change = { ...this.form1 } //不参加原数组修改
        },
        标印: () => {
          this.form2Change = { ...this.form2 }
        },
        垛板: () => {
          this.form3Change = { ...this.form3 }
        }
      }
      obj[name]()
    },
    openRefresh(form) {
      //恢复正常
      form.changeFlag = true
    },
    closeRefresh(form) {
      //修改中
      //修改中让其他form恢复正常
      form.changeFlag = false
      switch (form.name) {
        case '表检':
          this.form2.changeFlag = true
          this.form3.changeFlag = true
          break
        case '标印':
          this.form1.changeFlag = true
          this.form3.changeFlag = true
          break
        case '垛板':
          this.form2.changeFlag = true
          this.form1.changeFlag = true
          break
      }
      this.initForm(form.name)
      console.log('change事件', this.form1)
      console.log(form.name + '关闭实时刷新')
    },
    //封装成对象方法使用
    trackSteel(data) {
      // 页面和实际比例 以整个图为例 宽度: 实际3.51m  页面68px  总长  长度: 实际315273-394753m  页面长度 1613px
      // 辊道 实际3.51m  页面68px
      let [actWid, pageWid, actLen, pageLen, actgd, pagegd] = [
        3.51 * 1000,
        68,
        79.48 * 1000,
        1610,
        3.51 * 1000,
        68
      ]
      this.trackData = []
      for (let i = 0; i < data['rechmi4'].length; i++) {
        let item = data['rechmi4'][i]
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
    getHmiData() {
      getHmiData(
        '1dbj',
        data => {
          data['rechmi4'].forEach(item => {
            item.tailX = item.tail_x
            item.Vpos = item.v_pos
            item.headX = item.head_x
          })
          data['rechmi4'].map((item, index) => {
            item.v_pos = item.v_pos - 40000
            item.tail_x = item.tail_x - 315273
          })
          this.trackSteel(data)
          this.initCmd(data)
          this.getTableDataByProcess(data)
          this.initFormData(data)
        },
        error => {
          console.log(error)
        },
        1000
      )
    },
    initFormData(data) {
      this.form1.L1SISSET_FLAG = data['L1SISSET_FLAG']
      this.form1.L1SISSET_UseFlag = data['L1SISSET_UseFlag'] == 1 ? true : false
      this.form1.L1SISSET_PlateNo = data['L1SISSET_PlateNo']
      this.form1.L1SISSET_Stdspec = data['L1SISSET_Stdspec']
      this.form1.L1SISSET_Plate_Len = data['L1SISSET_Plate_Len']
      this.form1.L1SISSET_Plate_Wid = data['L1SISSET_Plate_Wid']
      this.form1.L1SISSET_Plate_Thk = data['L1SISSET_Plate_Thk']

      this.form2.L1MRKIFSET_FLAG = data['L1MRKIFSET_FLAG']
      this.form2.L1MRKIFSET_UseFlag =
        data['L1MRKIFSET_UseFlag'] == 1 ? true : false
      this.form2.L1MRKIFSET_PlateNo = data['L1MRKIFSET_PlateNo']
      this.form2.L1MRKIFSET_Steelgrade = data['L1MRKIFSET_Steelgrade']
      this.form2.L1MRKIFSET_Plate_Len = data['L1MRKIFSET_Plate_Len']
      this.form2.L1MRKIFSET_Plate_Wid = data['L1MRKIFSET_Plate_Wid']
      this.form2.L1MRKIFSET_Plate_Thk = data['L1MRKIFSET_Plate_Thk']

      /*this.form3.L1PILERSET_FLAG = data['L1PILERSET_FLAG']
      this.form3.L1PILERSET_UseFlag =
        data['L1PILERSET_UseFlag'] == 1 ? true : false
      this.form3.L1PILERSET_PlateNo = data['L1PILERSET_PlateNo']
      this.form3.L1PILERSET_Stdspec = data['L1PILERSET_Stdspec']
      this.form3.L1PILERSET_Plate_Len = data['L1PILERSET_Plate_Len']
      this.form3.L1PILERSET_Plate_Wid = data['L1PILERSET_Plate_Wid']
      this.form3.L1PILERSET_Plate_Thk = data['L1PILERSET_Plate_Thk']*/
    },
    initCmd(data) {
      this.cmdList.forEach(item => {
        item.value = data[item.key]
        // item.value = 1
      })
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
    getTableDataByProcess(data) {
      let fordata = data['rechmi4']
      for (let i = 0; i < fordata.length; i++) {
        if (fordata[i].process == 1) {
          if (this.currentId.indexOf(fordata[i].plateno) < 0) {
            this.currentId.push(fordata[i].plateno)
            console.log('触发process == 1')
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
        this.form1.changeFlag = true //关闭修改中
        this.form2.changeFlag = true //关闭修改中
        this.form3.changeFlag = true //关闭修改中
        this.$refs.steelinfo.getTableDataChild(plateno, type, itemInfo.region)
        this.tableLoading = true
      }, 400)
    },
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
.el-tooltip__popper {
  white-space: pre-line !important;
  font-size: 14px;
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

.el-form {
  display: flex;
  width: 100%;
  flex-wrap: wrap;

  .cz {
    overflow: hidden;
    display: flex;
    align-items: baseline;
    justify-content: flex-end;
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
    margin-bottom: 8px;
  }
}

.form-button {
  margin-top: 20px;
  display: flex;
  justify-content: space-between;
}

.dbj1 {
  /*
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
  }*/

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
      height: 139px;
      position: relative;
      //overflow: hidden;
      .bgimg-box {
        height: 100%;
        //background: url('../assets/1dbj.png') no-repeat 100% 100%;
        background: url('../assets/bg/dbj1.png') no-repeat 100% 100%;
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
        top: 69px;
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
}
/deep/ .el-table {
  .el-table__fixed-header-wrapper {
    .el-checkbox__inner {
      display: none !important;
    }
  }
}
</style>
