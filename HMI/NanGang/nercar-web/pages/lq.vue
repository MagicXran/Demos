<template>
  <div class="lq">
    <div
      v-tag:tag="variable"
      data-page="lq"/>
    <div class="banner bgc-white">
      <div class="bgimg">
        <div class="bgimg-box"/>
        <div class="track-box">
          <trackItem
            :track-data="trackData"
            :top="0"
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
                :style="'top:337px;'+'left:'+(item.x-4.5)+'px'"
                :key="index">
                <img
                  src="../assets/green.png"
                  alt="">
              </li>
            </ul>
          </div>
          <div class="uporback">
            <div class="upback-box">
              <div
                v-for="(item,key) in upbackList"
                v-if="key == 4 || key ==5"
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
                  v-if="item.hangFlag == true && key == 4"
                  v-model="item.lineData"
                  placeholder=""
                  disabled
                  @focus="openHang(item)">
                  <template slot="append">行</template>
                </el-input>
                <el-input
                  v-if="item.hangFlag == false && key == 4"
                  v-model="item.lineDataStatic"
                  placeholder=""
                  @blur="setHang(item ,key)">
                  <template slot="append">修</template>
                </el-input>
              </div>
            </div>
          </div>
          <warn-info
            :width="815"
            :warn-type="1"
            :pos-location="{
              top: 0,
              left: 824,
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
      <div class="topTable">
        <el-table
          v-loading="topTableLoading"
          :data="topTableSon"
          :tree-props="{children: 'children', hasChildren: 'hasChildren'}"
          :row-class-name="tableRowClassName"
          :empty-text="'暂无数据'"
          class="eltablecss"
          height="305px"
          style="width: 100%;"
          row-key="PLATE_NO"
          border
          default-expand-all>
          <!-- <el-table-column
            fixed="left"
            width="90"
          >
            <template slot-scope="scope">
              <el-checkbox
                v-if="scope.row.PLATE_TYPE == 3"
                v-model="scope.row.checkboxM"
                @change="checkboxFn(scope.row)"/>
            </template>
          </el-table-column> -->
          <el-table-column
            fixed="left"
            prop="PLATE_NO"
            label="钢板号"
            width="170"
            align="center"/>
          <el-table-column
            prop="CREATE_TIME"
            label="吊销日期"
            width="160"
            align="center"/>
          <el-table-column
            fixed="right"
            label="操作"
            width="120">
            <template slot-scope="scope">
              <el-button
                type="text"
                size="mini"
                @click="libraryRevoke(scope.row.PLATE_NO)">吊销
              </el-button>
              <!-- <el-button
                v-if="scope.row.PLATE_TYPE == 2 || scope.row.PLATE_TYPE == 4"
                type="text"
                size="mini"
                @click="subsection(scope.row)">分段</el-button> -->
              <el-button
                type="text"
                size="mini"
                @click="libraryOpenSx(scope.row.PLATE_NO)">上线
              </el-button>
              <!-- <el-button
              v-if="scope.row.PLATE_TYPE == 2 || scope.row.PLATE_TYPE == 4 || scope.row.PLATE_TYPE == 1"
              type="text"
              size="mini"
              @click="openWarehouse(scope.row.PLATE_NO)">中间库</el-button> -->
            </template>
          </el-table-column>
          <el-table-column
            prop=""
            label="钢板长"
            align="center">
            <template slot-scope="scope">
              <div>{{ scope.row.PLATE_LEN }}</div>
            </template>
          </el-table-column>
          <el-table-column
            prop="PLATE_WID"
            label="钢板宽"
            align="center">
            <template slot-scope="scope">
              <div>{{ scope.row.PLATE_WID }}</div>
            </template>
          </el-table-column>
          <el-table-column
            prop="PLATE_THK"
            label="钢板厚"
            align="center">
            <template slot-scope="scope">
              <div>{{ scope.row.PLATE_THK }}</div>
            </template>
          </el-table-column>
          <el-table-column
            prop="PLATE_WGT"
            label="钢板重"
            align="center">
            <template slot-scope="scope">
              <div>{{ (scope.row.PLATE_WGT || 0).toFixed(3) }}</div>
            </template>
          </el-table-column>
          <el-table-column
            prop="PLATELEN_MEAS"
            label="实际长度"
            align="center">
            <template slot-scope="scope">
              <div>{{ scope.row.PLATELEN_MEAS }}</div>
            </template>
          </el-table-column>
          <el-table-column
            :show-overflow-tooltip="true"
            prop="CHILD_NO1"
            label="子板1"
            width="60"
            align="center"/>
          <el-table-column
            :show-overflow-tooltip="true"
            prop="CHILD_NO2"
            label="子板2"
            width="60"
            align="center"/>
          <el-table-column
            :show-overflow-tooltip="true"
            prop="CHILD_NO3"
            label="子板4"
            width="60"
            align="center"/>
          <el-table-column
            :show-overflow-tooltip="true"
            prop="CHILD_NO5"
            label="子板5"
            width="60"
            align="center"/>
        </el-table>
        <simple-pagination
          :page-size="pagination.pageSize"
          :total="pagination.total"
          :align="pagination.align"
          :current-page="pagination.currentPage"
          layout="total, prev, pager, next,jumper"
          @handleSizeChangeFn="handleSizeChange"
          @handleCurrentChangeFn="handleCurrentChange"
        />
      </div>
    </div>

    <div class="content">
      <el-row :gutter="20">
        <el-col :span="5">
          <div
            class="bgc-white1"
            style="padding: 24px">
            <div
              class="header">
              <p class="ps">切分剪干预</p>
              <el-checkbox
                v-model="revokeChecked"
                @change="revokeCheckedFn()">连续吊销中间库
              </el-checkbox>
              <!-- <p
              v-if="!form1.changeFlag"
              style="color: #FFA958;font-size: 13px">修改中... <i
                style="font-size: 20px;cursor: pointer"
                class="el-icon-circle-close"
                @click="openRefresh(form1)"
            /></p> -->
              <!-- <div
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
                  v-model="form1.L2DDSET_UseFlag"
                  active-color="#13356F"
                  inactive-color="#5e0f0f"
                  @change="closeRefresh(form1)"/>
              </div>
            </div> -->
              <!-- <div
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
                  v-model="form1Change.L2DDSET_UseFlag"
                  active-color="#13356F"
                  inactive-color="#5e0f0f"/>
              </div>
            </div> -->
            </div>
            <div
              v-if="form1.changeFlag"
              class="form-boder">
              <el-form
                ref="form1"
                :model="form1"
                label-width="80px"
                class="leftForm">
                <el-form-item
                  label=""
                  style="width: 100%">
                  <div style="display: flex; align-items: center;justify-content: space-between;">
                    <!--新增选项-->
                    <el-select
                      v-model="form1.dbTable"
                      style="width: 38%;"
                      placeholder="请选择">
                      <el-option
                        :value="0"
                        label="计划表"/>
                      <el-option
                        :value="1"
                        label="中间库"/>
                    </el-select>
                    <el-input
                      v-model="form1.L2DDSET_PlateNo"
                      style="width: 60%;"
                      size="mini"
                      @focus="closeRefresh(form1)">
                      <el-button
                        slot="append"
                        icon="el-icon-search"
                        @click="getTableDataByTwo(form1.L2DDSET_PlateNo,3,0,'t')"/>
                    </el-input>
                  </div>

                </el-form-item>

                <el-form-item
                  v-if="checkShow && form1.changeFlag"
                >
                  <div style="display: flex; align-items: center;justify-content: space-between;width:100%">
                    <el-input
                      v-model="lenmeasName"
                      style="width:63%;margin-right:6px"
                      size="mini"/>
                    <el-input
                      v-model="lenmeas"
                      size="mini">
                      <template slot="append">mm</template>
                    </el-input>
                  </div>
                </el-form-item>

                <el-form-item v-if="checkShow && form1.changeFlag">
                  <el-checkbox-group
                    v-model="checkModel"
                    style="width:100%">
                    <el-checkbox
                      v-for="item in checkList"
                      :label="item"
                      :key="item"
                      style="margin:0;width:33%;"
                      @change="clickChecked(item)">{{ item }}
                    </el-checkbox>
                  </el-checkbox-group>
                </el-form-item>

              </el-form>
            </div>

            <div
              v-if="!form1.changeFlag"
              class="form-boder">
              <el-form
                ref="form1"
                :model="form1Change"
                label-width="80px"
                class="leftForm">
                <el-form-item
                  label=""
                  style="width: 100%">
                  <div style="display: flex; align-items: center;justify-content: space-between;">
                    <el-select
                      v-model="form1.dbTable"
                      style="width: 38%;"
                      placeholder="请选择">
                      <el-option
                        :value="0"
                        label="计划表"/>
                      <el-option
                        :value="1"
                        label="中间库"/>
                    </el-select>
                    <el-input
                      ref="strname"
                      v-model="form1Change.L2DDSET_PlateNo"
                      style="width: 60%;"
                      size="mini"
                    >
                      <el-button
                        slot="append"
                        icon="el-icon-search"
                        @click="getTableDataByTwo(form1Change.L2DDSET_PlateNo,3,0,'t')"/>
                    </el-input>
                  </div>
                </el-form-item>

                <el-form-item
                  v-if="checkShow && !form1.changeFlag"
                >
                  <div style="display: flex; align-items: center;justify-content: space-between;width:100%">
                    <el-input
                      v-model="lenmeasName"
                      style="width:63%;margin-right:6px"
                      size="mini"/>
                    <el-input
                      v-model="lenmeas"
                      size="mini">
                      <template slot="append">mm</template>
                    </el-input>
                  </div>
                </el-form-item>

                <el-form-item v-if="checkShow && !form1.changeFlag">
                  <el-checkbox-group
                    v-model="checkModel"
                    style="width:100%">
                    <el-checkbox
                      v-for="item in checkList"
                      :label="item"
                      :key="item"
                      style="margin:0;width:33%;"
                      @change="clickChecked(item)">{{ item }}
                    </el-checkbox>
                  </el-checkbox-group>
                </el-form-item>
              </el-form>
            </div>

            <div class="form-button">
              <el-button
                v-if="checkModel.length > 0"
                type="primary"
                size="mini"
                @click="intervene()">干预
              </el-button>
            </div>
          </div>
        </el-col>
        <el-col
          :span="19"
          class="tableCol">
          <el-table
            v-loading="tableLoading"
            :data="steelTableSon"
            :tree-props="{children: 'children', hasChildren: 'hasChildren'}"
            :row-class-name="tableRowClassName"
            :empty-text="'暂无数据'"
            :cell-class-name="cellClass"
            :cell-style="getCellStyle"
            :header-cell-style="{border: '1px solid #777',backgroundColor: '#B9C8C5'}"
            class="eltablecss"
            height="470px"
            style="width: 100%;"
            row-key="PLATE_NO"
            border
            default-expand-all
            @selection-change="handleSelectionChange">
            <!-- <el-table-column
              fixed="left"
              width="90"
            >
              <template slot-scope="scope">
                <el-checkbox
                  v-if="scope.row.PLATE_TYPE == 3"
                  v-model="scope.row.checkboxM"
                  @change="checkboxFn(scope.row)"/>
              </template>
            </el-table-column> -->
            <el-table-column
              :selectable="selectable"
              type="selection"
              fixed="left"
              align="center"
              width="90"/>
            <el-table-column
              fixed="left"
              prop="PLATE_NO"
              label="钢板号"
              width="170"
              align="center"/>
            <el-table-column
              fixed="right"
              label="操作"
              width="180">
              <template slot-scope="scope">
                <el-button
                  type="text"
                  size="mini"
                  @click="revoke(scope.row)">吊销
                </el-button>
                <el-button
                  v-if="scope.row.PLATE_TYPE == 2 || scope.row.PLATE_TYPE == 4"
                  type="text"
                  size="mini"
                  @click="subsection(scope.row)">分段
                </el-button>
                <el-button
                  v-if="scope.row.PLATE_TYPE == 2 || scope.row.PLATE_TYPE == 4 || scope.row.PLATE_TYPE == 1"
                  type="text"
                  size="mini"
                  @click="openSx(scope.row.PLATE_NO)">上线
                </el-button>
                <el-button
                  v-if="scope.row.PLATE_TYPE == 2 || scope.row.PLATE_TYPE == 4 || scope.row.PLATE_TYPE == 1"
                  type="text"
                  size="mini"
                  @click="openWarehouse(scope.row.PLATE_NO)">中间库
                </el-button>
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
              width="60"
              align="center">
              <template slot-scope="scope">
                <div>
                  {{ (scope.row.PLATE_THK || 0).toFixed(3) }}
                </div>
              </template>
            </el-table-column>
            <el-table-column
              prop="PLATE_WID"
              label="宽度"
              align="center"/>
            <el-table-column
              prop="PLATE_LEN"
              label="计划长度"
              align="center"/>
            <el-table-column
              prop="PLATELEN_MEAS"
              label="实测长度"
              align="center"/>
            <el-table-column
              prop="PLATE_WGT"
              label="重量"
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
              width="100"
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
              </template>
            </el-table-column>
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
        </el-col>
      </el-row>
    </div>
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
            style="width:60px">板坯号
          </div>
          <el-input
            v-model="formOnline.plantNo"
            style="width:200px"
            readonly/>
        </el-form-item>
        <el-form-item>
          <div
            slot="label"
            style="width:60px">上线区域
          </div>
          <el-select
            v-model="formOnline.region"
            style="width:200px"
            placeholder="请选择上线区域"
            @change="onlineChange(formOnline.region)">
            <el-option
              v-if="libraryShow"
              label="矫直后辊道"
              value="1"/>
            <el-option
              v-if="libraryShow"
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
            style="width:60px">具体位置
          </div>
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
          v-if="libraryShow"
          type="primary"
          @click="saveUp()">确 定</el-button>
        <el-button
          v-if="!libraryShow"
          type="primary"
          @click="librarySaveUp()">确 定</el-button>
      </span>
    </el-dialog>
  </div>
</template>

<script>
import HmiTable from '@/components/HmiTable'
import {
  getHmiData,
  sendMsg,
  sendTag,
  stopGetData,
  GET_TAGS,
  getHmiDataByEvent
} from '@/lib/GetData'
import warnInfo from '@/pages/components/warnInfo'
import steelInfo from '@/pages/components/steelInfo'
import setInfo from '@/pages/components/setInfo'
import modifInfo from '@/pages/components/modifInfo'
import trackItem from '@/pages/components/trackItem'
import simplePagination from '@/components/simplePagination'
import { stringify } from 'querystring'

export default {
  name: 'Lcb2',
  components: {
    HmiTable,
    warnInfo,
    setInfo,
    steelInfo,
    modifInfo,
    trackItem,
    simplePagination
  },
  data() {
    return {
      revokeChecked: 1,
      libraryShow: true,
      pagination: {
        align: 'right',
        currentPage: 1,
        pageSizes: [10, 20, 30, 40],
        pageSize: 10,
        total: 0
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
      variable: [
        'rechmi5',
        'L2DDSTRACK.DDSCMD1',
        'L2DDSTRACK.DDSCMD2',
        'L2DDSTRACK.DDSCMD3',
        'L2DDSTRACK.DDSCMD4',
        'L2DDSTRACK.DDSCMD5',
        'L2DDSTRACK.DDSCMD6',
        'L2DDSTRACK.DDSCMD7',
        'L2DDSTRACK.DDSCMD8',
        'L2DDSET_UseFlag',
        'L2DDSET_PlateNo',
        'L2DDSET_Steelgrade',
        'L2DDSET_Plate_Len',
        'L2DDSET_Plate_Wid',
        'L2DDSET_Plate_Thk',
        'CB1ROW',
        'CB2ROW',
        'CB3ROW',
        'middleDB'
      ],
      cmdList: [
        {
          key: 'L2DDSTRACK.DDSCMD1',
          value: '',
          x: 298.0951624
        },
        {
          key: 'L2DDSTRACK.DDSCMD2',
          value: '',
          x: 745.0781738
        },
        {
          key: 'L2DDSTRACK.DDSCMD3',
          value: '',
          x: 816.4172831
        },
        {
          key: 'L2DDSTRACK.DDSCMD4',
          value: '',
          x: 1016.813111
        },
        {
          key: 'L2DDSTRACK.DDSCMD5',
          value: '',
          x: 1113.011025
        },
        {
          key: 'L2DDSTRACK.DDSCMD6',
          value: '',
          x: 1269.893461
        },
        {
          key: 'L2DDSTRACK.DDSCMD7',
          value: '',
          x: 1440.947028
        },
        {
          key: 'L2DDSTRACK.DDSCMD8',
          value: '',
          x: 1611.000595
        }
      ],
      steelTableSon: [],
      trackData: [],
      currentId: [],
      tableLoading: false,
      checkboxData: [],
      form1: {
        changeFlag: true,
        dbTable: 0,
        L2DDSET_UseFlag: '',
        L2DDSET_PlateNo: '',
        L2DDSET_Steelgrade: '',
        L2DDSET_Plate_Len: '',
        L2DDSET_Plate_Wid: '',
        L2DDSET_Plate_Thk: ''
      },
      form1Change: {},
      steelTablePar: [{}, {}, {}, {}],
      timer: null,
      middleDBtimer: null,
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
      formUpLC: {
        cbno: '',
        plantNo1: '',
        plantNo2: ''
      },
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
      dialogVisibleOnline: false,
      postForm: {
        action: 'send_msg',
        operator: 'abc',
        terminal: 'FM_01',
        body: {
          msgId: '1815',
          sendTo: 'HMI',
          waitReply: true,
          timeout: '1',
          params: [
            [
              {
                plateno: ''
              }
            ]
          ]
        }
      },
      topTableLoading: false,
      topTableSon: [],
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
      matidList: [],
      checkModel: [],
      checkList: [],
      checkShow: false,
      lenmeas: '',
      lenmeasName: '实际长度',
      clickPlantno: '',
      inputTimer: null
    }
  },
  mounted() {
    this.getHmiData()
    this.getTopTableMsg()
    this.getRevokeChecked()
  },
  destroyed() {
    stopGetData()
    clearInterval(this.middleDBtimer)
  },
  methods: {
    //连续吊销中间库
    revokeCheckedFn() {
      let msg = this.revokeChecked ? '选中' : '取消'
      this.$confirm('确定' + msg + '连续吊销中间库, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          console.log(this.revokeChecked)
          let data = {
            L2DDSmiddle: this.revokeChecked == true ? '1' : '0'
          }
          sendTag(data).then(res => {
            if (res.code == 200) {
              this.$message({
                message: '修改成功',
                type: 'success'
              })
              this.getRevokeChecked()
            }
          })
        })
        .catch(() => {
          this.getRevokeChecked()
          this.$message({
            type: 'info',
            message: '已取消操作'
          })
        })
    },
    getRevokeChecked() {
      let data = [{ tagName: 'L2DDSmiddle', timestamp: 0 }]
      getHmiDataByEvent(data).then(res => {
        if (res.code == 200) {
          this.revokeChecked = res.results[0].value == 1 ? true : false
          console.log('吊销中间库', this.revokeChecked)
        }
      })
    },
    // 进入页面获取中间库消息
    getTopTableMsg() {
      let data = [
        [
          {
            pageNo: this.pagination.currentPage,
            pageSize: this.pagination.pageSize
          }
        ]
      ]
      // 是否返回成功
      sendMsg(data, 1814, 'HMI').then(res => {
        let msg = res.results[0][0].msg
        // console.log(msg)
        // console.log(res)
      })
    },
    // 获取中间库数据
    getTopTableData(data) {
      // console.log(data.middleDB)
      let topTableData = []
      topTableData = data.middleDB
      this.topTableSon = topTableData
      this.pagination.total = data.middleDB[0].TotalCount
    },
    handleSizeChange(val) {
      this.pagination.pageSize = val
      this.getTopTableMsg()
    },
    handleCurrentChange(val) {
      this.pagination.currentPage = val
      this.getTopTableMsg()
    },
    //封装成对象方法使用
    trackSteel(data) {
      // 页面和实际比例 以整个图为例 宽度: 实际153559-40575  页面390px  总长  长度: 实际53.3m  页面长度 688px
      // 辊道 实际3.51m  页面46px
      let [actWid, pageWid, actLen, pageLen, actgd, pagegd] = [
        67270 - 41550,
        375,
        154398 - 40575,
        1619,
        3.51 * 1000,
        46
      ]
      this.trackData = []
      for (let i = 0; i < data['rechmi5'].length; i++) {
        let item = data['rechmi5'][i]
        if (item.region == 2 || item.region == 3 || item.region == 4) {
          this.trackData.push({
            width: this.countSteelLeng(actLen, pageLen, item.platelenmeas_cb),
            tailpos: this.countSteeltail(actLen, pageLen, item.tail_x_cb),
            height: this.countSteelWid(actWid, pageWid, item.platewid),
            vPos:
              this.countSteelPosY(actWid, pageWid, item.v_pos) -
              this.countSteelWid(actgd, pagegd, item.platewid) / 2, //计算辊道中心位置
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
            headX: item.headX,
            tailX: item.tailX,
            Vpos: item.Vpos,
            color: item.colour
          })
        } else {
          this.trackData.push({
            width: this.countSteelLeng(actLen, pageLen, item.platelenmeas),
            height: this.countSteelWid(actWid, pageWid, item.platewid),
            tailpos: this.countSteeltail(actLen, pageLen, item.tail_x),
            vPos:
              this.countSteelPosY(actWid, pageWid, item.v_pos) -
              this.countSteelWid(actgd, pagegd, item.platewid) / 2, //计算辊道中心位置
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
            headX: item.headX,
            tailX: item.tailX,
            Vpos: item.Vpos,
            color: item.colour
          })
        }
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
    initHang(data) {
      this.upbackList[0].lineData = data['CB1ROW']
      this.upbackList[2].lineData = data['CB2ROW']
      this.upbackList[4].lineData = data['CB3ROW']
    },
    // 多个数据一个接口刷新
    getHmiData() {
      getHmiData(
        'lq',
        data => {
          data['rechmi5'].forEach(item => {
            item.tailX = item.tail_x
            item.Vpos = item.v_pos
            item.headX = item.head_x
          })
          data['rechmi5'].map((item, index) => {
            item.v_pos = item.v_pos - 41750
            item.tail_x = item.tail_x - 40575
            item.tail_x_cb = item.tail_x_cb - 40575
          })
          this.trackSteel(data)
          this.initCmd(data)
          this.initFormData(data)
          this.initHang(data)
          //获取中间库数据
          this.getTopTableData(data)
        },
        error => {
          // console.log(error)
        },
        1000
      )
    },
    initFormData(data) {
      this.form1.L2DDSET_UseFlag = data['L2DDSET_UseFlag']
      this.form1.L2DDSET_PlateNo = data['L2DDSET_PlateNo']
      this.form1.L2DDSET_Steelgrade = data['L2DDSET_Steelgrade']
      this.form1.L2DDSET_Plate_Len = data['L2DDSET_Plate_Len'].toFixed(2)
      this.form1.L2DDSET_Plate_Wid = data['L2DDSET_Plate_Wid'].toFixed(2)
      this.form1.L2DDSET_Plate_Thk = data['L2DDSET_Plate_Thk'].toFixed(2)
    },
    initCmd(data) {
      this.cmdList.forEach(item => {
        item.value = data[item.key]
        // item.value = 1
      })
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
    openRefresh(form) {
      form.changeFlag = true
    },
    closeRefresh(form) {
      this.getFocus()
      form.changeFlag = false
      this.initForm()
      // console.log('关闭实时刷新')
    },
    // input获取焦点
    getFocus() {
      this.$nextTick(function() {
        if (this.inputTimer) {
          clearTimeout(this.inputTimer)
        }
        this.inputTimer = setTimeout(() => {
          this.$refs.strname.focus()
        }, 100)
      })
    },
    initForm() {
      this.form1Change = { ...this.form1 } //不参加原数组修改
    },
    getTableDataByProcess(data) {
      let fordata = data['hl_cb_ds_mat']
      for (let i = 0; i < fordata.length; i++) {
        if (fordata[i].process == 1) {
          if (this.currentId.indexOf(fordata[i].plateno) < 0) {
            this.currentId.push(fordata[i].plateno)
            // console.log('触发process == 1')
            console.log(fordata[i])
            this.getTableDataByTwo(fordata[i].plateno, 0)
          }
        }
      }
    },
    getTableDataByTwo(plateno, type, itemInfo, hava) {
      this.clickPlantno = plateno
      this.checkModel = []
      let data = [
        [
          {
            plateno: plateno,
            page: 7
          }
        ]
      ]
      sendMsg(data, 1818, 'HMI').then(res => {
        if (res.results[0][0].msg) {
          this.checkShow = false
          // this.$message({
          //   type: 'error',
          //   message: res.results[0][0].msg
          // })
          return
        } else {
          this.checkShow = true
          this.lenmeas = res.results[0][0].lenmeas
          let list = []
          res.results[0].forEach(item => {
            list.push(item.matid)
          })
          this.checkList = list
        }
      })
      if (!itemInfo) {
        itemInfo = {
          region: 0
        }
      }
      // console.log(clickRegion)
      //判断是否是计划表还是中间库
      if (this.form1.dbTable == 1 && hava && type == 3) {
        type = 1813
      }
      //process == 0 点击钢板查询 其他从记录集获取
      clearTimeout(this.timer)
      this.timer = setTimeout(() => {
        // this.$refs.steelinfo.getTableDataChild(plateno, type)
        this.getTableDataChild(plateno, type, itemInfo.region)
        this.tableLoading = true
      }, 400)
    },
    // 切分剪干预多选框选中
    clickChecked(val) {
      // console.log(val)
      // this.checkModel.push(val)
      // console.log(this.checkModel)
    },
    // 干预按钮
    intervene() {
      this.$confirm('是否确定干预?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          let data = [
            [
              {
                plateno: this.clickPlantno,
                page: 7,
                num: 1,
                MATID_1: '0101'
              }
            ]
          ]
          sendMsg(data, 1819, 'HMI').then(res => {
            if (res.results[0][0].msg) {
              this.$message({
                type: 'success',
                message: res.results[0][0].msg
              })
            }
          })
          let valList = []
          let MATIDList = []
          this.checkModel.forEach(item => {
            valList.push(Number(item))
          })
          valList.sort((old, New) => {
            return old - New
          })
          // console.log(valList)
          valList.forEach(item => {
            if (String(item).split('').length < 4) {
              MATIDList.push('0' + item)
            }
          })
          // console.log(MATIDList)
          data[0][0].num = MATIDList.length
          MATIDList.forEach((item, index) => {
            // data[0][0].MATID_1 = '0101'
            if (index == 0) {
              data[0][0].MATID_1 = item
            }
            if (index == 1) {
              data[0][0].MATID_2 = item
            }
            if (index == 2) {
              data[0][0].MATID_3 = item
            }
            if (index == 3) {
              data[0][0].MATID_4 = item
            }
            if (index == 4) {
              data[0][0].MATID_5 = item
            }
            if (index == 5) {
              data[0][0].MATID_6 = item
            }
            if (index == 6) {
              data[0][0].MATID_7 = item
            }
            if (index == 7) {
              data[0][0].MATID_8 = item
            }
            if (index == 8) {
              data[0][0].MATID_9 = item
            }
            if (index == 9) {
              data[0][0].MATID_10 = item
            }
          })
          console.log(data[0][0])
        })
        .catch(() => {
          this.$message({
            type: 'info',
            message: '已取消干预'
          })
        })
    },
    // 获取计划表数据
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
        if (!res.results[0][0].PLATE_NO && type != 1813) {
          this.steelTableSon = []
          this.$message({
            type: 'warning',
            message: res.results[0][0].msg
          })
          this.tableLoading = false
          return
        }
        if (type == 1813) {
          this.steelTableSon = []
          this.tableLoading = false
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
    againSet() {
      let data = [
        [
          {
            plateno: this.form1.L2DDSET_PlateNo,
            process: '6'
          }
        ]
      ]
      sendMsg(data, 1808, 'HMI').then(res => {
        if (res.results[0][0].msg) {
          this.$message({
            type: 'success',
            message: res.results[0][0].msg
          })
        }
      })
    },
    saveSet() {
      this.$confirm('是否确定修改?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          let data = {
            DSS_Use_Flag: this.form1Change.DSS_Use_Flag == true ? '1' : '0',
            L2DDSET_PlateNo: this.form1Change.L2DDSET_PlateNo,
            L2DDSET_Steelgrade: this.form1Change.L2DDSET_Steelgrade,
            L2DDSET_Plate_Len: this.form1Change.L2DDSET_Plate_Len,
            L2DDSET_Plate_Wid: this.form1Change.L2DDSET_Plate_Wid,
            L2DDSET_Plate_Thk: this.form1Change.L2DDSET_Plate_Thk,
            L2DDSET_ModFlag: 1 // 双边剪设定，点击修改按钮后，将该变量置1
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
          this.$message({
            message: '已取消修改',
            type: 'info'
          })
        })
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
      // console.log(targetPos)
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
    openHang(item) {
      item.hangFlag = false
    },
    setHang(item, index) {
      this.hangNum++
      if (this.hangNum <= 1) return
      // console.log('dynamic')
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
          // console.log('强制上冷床', res.results[0])
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
    checkboxFn(item) {
      // console.log(item)
    },
    // 树状图吊销按钮
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
    // 中间库吊销按钮
    libraryRevoke(id) {
      this.$confirm('是否确定吊销?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          let data = [
            [
              {
                plateno: id
              }
            ]
          ]
          sendMsg(data, 1816, 'HMI').then(res => {
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
              console.log('分段完成', item)
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
            label: '圆盘剪前'
          }
        ]
      }
      this.formOnline.postionList = bar[region]
    },
    // 计划表上线
    openSx(id) {
      this.libraryShow = true
      this.formOnline.plantNo = id
      this.formOnline.region = ''
      this.formOnline.postion = ''
      this.dialogVisibleOnline = true
    },
    // 中间库上线按钮
    libraryOpenSx(id) {
      this.libraryShow = false
      this.formOnline.plantNo = id
      this.formOnline.region = '7'
      this.onlineChange(this.formOnline.region)
      this.dialogVisibleOnline = true
    },
    // 中间库上线确定按钮
    librarySaveUp() {
      // console.log('上线')
      this.$confirm('是否确定上线?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          let data = [
            [
              {
                plateno: this.formOnline.plantNo,
                postion: this.formOnline.postion
              }
            ]
          ]
          sendMsg(data, 1817, 'HMI').then(res => {
            // this.dialogVisibleOnline = false
            if (res.results[0][0].msg) {
              this.$message({
                type: 'success',
                message: res.results[0][0].msg
              })
            }
            this.dialogVisibleOnline = false
          })
        })
        .catch(() => {
          this.$message({
            type: 'info',
            message: '已取消上线'
          })
        })
    },
    // 中间库吊销
    openWarehouse(id) {
      this.$confirm('是否确定吊销?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          let data = [
            [
              {
                plateno: id
              }
            ]
          ]
          sendMsg(data, 1815, 'HMI').then(res => {
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
          // console.log(this.postForm.body.params[0][0].plateno)
          this.$message({
            type: 'info',
            message: '已取消吊销'
          })
        })
    },
    // 计划表确定上线
    saveUp() {
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
    // 修改table样式
    getCellStyle({ row, column, rowIndex, columnIndex }) {
      if (row.PLATE_TYPE == 1) {
        return 'background: #F0B8F0;border: solid 1px #777;border-top:0px'
      } else if (row.PLATE_TYPE == 2 || row.PLATE_TYPE == 4) {
        return 'background: #B1E8ED;border: solid 1px #777;border-top:0px'
      } else if (row.PLATE_TYPE == 3) {
        return 'background: #CDF8CE;border: solid 1px #777;'
      }
    },
    // 表头样式
    headStyle() {
      return 'border: 1px solid #777;background: #B9C8C5'
    }
  }
}
</script>


<style scoped lang="less">
/deep/ .el-checkbox.is-bordered.el-checkbox--mini .el-checkbox__label {
  font-size: 14px;
}

.topTable {
  position: absolute;
  top: 24px;
  right: 24px;
  width: 47%;
}

/deep/ .leftForm .el-form-item:nth-child(1) {
  margin-left: 10px;
}

/*/deep/.el-form {
  .el-form-item {
    &:nth-child(0) {
      margin-left: 10px;
    }
  }
}*/
/deep/ .leftForm .el-form-item__content:nth-child(1) {
  margin-left: 10px !important;
}

.el-button--primary {
  background-color: #13356f;
  border-color: #13356f;
}

.uporback {
  .upback-box {
    .upback-item {
      width: 60px;
      position: absolute;

      &:nth-child(1) {
        left: 760px;
        top: 3px;
      }

      &:nth-child(2) {
        left: 760px;
        top: 245px;
      }

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

.lq {
  .bgc-white {
    background-color: #fff;
    box-shadow: 0px 0px 4px rgb(0 0 0 / 4%), 0px 0px 16px -2px rgb(0 0 0 / 10%);
    border-radius: 6px;
  }

  .bgc-white1 {
    background-color: #fff;
    box-shadow: 0px 0px 4px rgb(0 0 0 / 4%), 0px 0px 16px -2px rgb(0 0 0 / 10%);
    border-radius: 6px;
    height: 470px;
  }

  .leftForm {
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
      line-height: 40px;
      margin-left: -1px;
      margin-bottom: -1px;

      /deep/ .el-input--mini .el-input__inner {
        height: 26px;
        line-height: 26px;
      }

      /deep/ .el-input--suffix .el-input__inner {
        height: 26px;
        line-height: 26px;
        font-size: 13px;
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

  /deep/ .el-input-group__append,
  /deep/ .el-input-group__prepend {
    padding: 0 6px;
  }

  /deep/ .el-form-item__content .el-input-group {
    vertical-align: baseline;
  }

  .form-button {
    margin-top: 20px;
    display: flex;
    justify-content: space-between;
  }

  .banner {
    padding: 24px;
    width: 100%;
    position: relative;

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
      height: 459px;
      position: relative;
      //overflow: hidden;
      .bgimg-box {
        width: 1622px;
        height: 100%;
        //background: url('../assets/lqj.png') no-repeat 100% 100%;
        background: url('../assets/bg/lq.png') no-repeat 100% 100%;
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
