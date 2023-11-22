<template>
  <div class="ypj">
    <div
      v-tag:tag="variable"
      data-page="ypj"/>
    <div class="banner bgc-white">
      <div class="bgimg">
        <div class="bgimg-box"/>
        <div class="track-box">
          <div class="one-box">
            <trackItem
              :track-data="trackData"
              :top="75"
              :left="7"
              :type="1"
              @opdialog="opdialog"
              @getTableDataByTwo="getTableDataByTwo"
            />
          </div>
          <div class="cmd-box">
            <ul>
              <li
                v-for="(item, index) in cmdList"
                v-if="item.value == 1"
                :style="'top:63px;'+'left:'+(item.x + 0)+'px'"
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
        <!--        //圆盘剪设定-->
        <el-col :span="7">
          <div
            class="type1 bgc-white">
            <div
              class="type-box"
              style="padding: 20px;">
              <div
                class="title"
                style="margin-bottom: 8px">
                <p>圆盘剪设定<span
                  v-if="!form1.changeFlag"
                  style="margin-left: 205px; color: #FFA958;font-size: 13px">修改中... <i
                    style="font-size: 20px;cursor: pointer"
                    class="el-icon-circle-close"
                    @click="openRefresh(form1)"
                /></span></p>
              </div>
              <div class="form-boder">
                <div v-if="form1.changeFlag">
                  <el-form
                    ref="form"
                    :model="form1"
                    class="leftForm"
                    label-width="85px">
                    <el-form-item
                      label="L2投用"
                      style="font-weight: 600; width: 60%">
                      <el-switch
                        v-model="form1.L2CSSET_UseFlag"
                        active-color="green"
                        inactive-color="red"
                        @change="closeRefresh(form1)"
                      />
                    </el-form-item>
                    <el-form-item
                      label="人工修正值"
                      style="width: 40%"
                      class="dandu-item1"/>
                    <el-form-item
                      label="钢板号"
                      style="width: 60%">
                      <el-input
                        v-model="form1.L2CSSET_PlateNo"
                        size="mini"
                        @focus="closeRefresh(form1)"
                      >
                        <el-button
                          slot="append"
                          icon="el-icon-search"
                          @click="getTableDataByTwo(form1.L2CSSET_PlateNo,3)"/>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      label="-"
                      style="width: 40%"/>
                    <el-form-item
                      label="母板长度"
                      style="width: 60%">
                      <el-input
                        v-model="form1.L2CSSET_Plate_Len"
                        size="mini"
                        @focus="closeRefresh(form1)"
                      >
                        <template slot="append">mm</template>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      label=""
                      class="dandu-item2"
                      style="width: 40%"/>
                    <el-form-item
                      label="母板宽度"
                      style="width: 60%">
                      <el-input
                        v-model="form1.L2CSSET_Plate_Wid"
                        size="mini"
                        @focus="closeRefresh(form1)"
                      >
                        <template slot="append">mm</template>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      class="dandu-item2"
                      label=""
                      style="width: 40%"/>
                    <el-form-item
                      label="母板厚度"
                      style="width: 60%">
                      <el-input
                        v-model="form1.L2CSSET_Plate_Thk"
                        size="mini"
                        @focus="closeRefresh(form1)"
                      >
                        <template slot="append">mm</template>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      label=""
                      style="width: 40%"
                      class="dandu-item"/>
                    <el-form-item
                      label="厚度间隙值"
                      style="width: 60%">
                      <el-input
                        v-model="form1.L2CSSET_Gap_Thk"
                        size="mini"
                        @focus="closeRefresh(form1)"
                      >
                        <template slot="append">mm</template>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      label=""
                      style="width: 40%"
                      class="dandu-item">
                      <!--圆盘剪设定-厚度间隙值-人工修正值-->
                      <el-input
                        v-model="form1.L2CSSET_Gap_Thk_MOD"
                        size="mini"
                        @focus="closeRefresh(form1)"
                      />
                    </el-form-item>
                    <el-form-item
                      label="厚度重合值"
                      style="width: 60%">
                      <el-input
                        v-model="form1.L2CSSET_Coincide_Thk"
                        size="mini"
                        @focus="closeRefresh(form1)"
                      >
                        <template slot="append">N/mm²</template>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      label=""
                      style="width: 40%"
                      class="dandu-item">
                      <!--圆盘剪设定-厚度重合值-人工修正值-->
                      <el-input
                        v-model="form1.L2CSSET_Coincide_Thk_MOD"
                        size="mini"
                        @focus="closeRefresh(form1)"
                      />
                    </el-form-item>

                    <el-form-item
                      label="激光划线宽"
                      style="width: 60%">
                      <el-input
                        v-model="form1.L2CSSET_LaserWid"
                        size="mini"
                        @focus="closeRefresh(form1)"
                      >
                        <template slot="append">N/mm²</template>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      label=""
                      style="width: 40%"
                      class="dandu-item">
                      <!--圆盘剪设定-激光划线宽-人工修正值-->
                      <el-input
                        v-model="form1.L2CSSET_LaserWid_MOD"
                        size="mini"
                        @focus="closeRefresh(form1)"
                      />
                    </el-form-item>

                    <el-form-item
                      label="剪机横移宽"
                      style="width: 60%">
                      <el-input
                        v-model="form1.L2CSSET_CS_Wid"
                        size="mini"
                        @focus="closeRefresh(form1)"
                      >
                        <template slot="append">N/mm²</template>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      label=""
                      style="width: 40%"
                      class="dandu-item">
                      <!--圆盘剪设定-剪机横移宽-人工修正值-->
                      <el-input
                        v-model="form1.L2CSSET_CS_Wid_MOD"
                        size="mini"
                        @focus="closeRefresh(form1)"
                      />
                    </el-form-item>
                    <el-form-item
                      label="空过标志"
                      style="width: 60%">
                      <el-switch
                        v-model="form1.L2CSSET_CS_Empty"
                        active-color="#13356F"
                        inactive-color="#5e0f0f"
                        @change="closeRefresh(form1)"/>
                    </el-form-item>
                    <el-form-item
                      label="-"
                      style="width: 40%"
                      class="dandu-item"/>
                  </el-form>
                </div>
                <div v-if="!form1.changeFlag">
                  <el-form
                    ref="form"
                    :model="form1Change"
                    class="leftForm"
                    label-width="85px">
                    <el-form-item
                      label="L2投用"
                      style="font-weight: 600; width: 60%">
                      <el-switch
                        v-model="form1Change.L2CSSET_UseFlag"
                        active-color="green"
                        inactive-color="red"
                      />
                    </el-form-item>
                    <el-form-item
                      label="人工修正值"
                      style="width: 40%"
                      class="dandu-item1"/>
                    <el-form-item
                      label="钢板号"
                      style="width: 60%">
                      <el-input
                        v-model="form1Change.L2CSSET_PlateNo"
                        size="mini"
                      >
                        <el-button
                          slot="append"
                          icon="el-icon-search"
                          @click="getTableDataByTwo(form1Change.L2CSSET_PlateNo,3)"/>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      label="-"
                      style="width: 40%"
                      class="dandu-item"/>
                    <el-form-item
                      label="母板长度"
                      style="width: 60%">
                      <el-input
                        v-model="form1Change.L2CSSET_Plate_Len"
                        size="mini"
                      >
                        <template slot="append">mm</template>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      label="-"
                      class="dandu-item2"
                      style="width: 40%"/>
                    <el-form-item
                      label="母板宽度"
                      style="width: 60%">
                      <el-input
                        v-model="form1Change.L2CSSET_Plate_Wid"
                        size="mini"
                      >
                        <template slot="append">mm</template>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      class="dandu-item2"
                      label="-"
                      style="width: 40%"/>
                    <el-form-item
                      label="母板厚度"
                      style="width: 60%">
                      <el-input
                        v-model="form1Change.L2CSSET_Plate_Thk"
                        size="mini"
                      >
                        <template slot="append">mm</template>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      label="-"
                      style="width: 40%"
                      class="dandu-item"/>
                    <el-form-item
                      label="厚度间隙值"
                      style="width: 60%">
                      <el-input
                        v-model="form1Change.L2CSSET_Gap_Thk"
                        size="mini"
                      >
                        <template slot="append">mm</template>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      label=""
                      style="width: 40%"
                      class="dandu-item">
                      <!--圆盘剪设定-厚度间隙值-人工修正值-->
                      <el-input
                        v-model="form1Change.L2CSSET_Gap_Thk_MOD"
                        size="mini"
                      />
                    </el-form-item>
                    <el-form-item
                      label="厚度重合值"
                      style="width: 60%">
                      <el-input
                        v-model="form1Change.L2CSSET_Coincide_Thk"
                        size="mini"
                      >
                        <template slot="append">N/mm²</template>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      label=""
                      style="width: 40%"
                      class="dandu-item">
                      <!--圆盘剪设定-厚度重合值-人工修正值-->
                      <el-input
                        v-model="form1Change.L2CSSET_Coincide_Thk_MOD"
                        size="mini"
                      />
                    </el-form-item>

                    <el-form-item
                      label="激光划线宽"
                      style="width: 60%">
                      <el-input
                        v-model="form1Change.L2CSSET_LaserWid"
                        size="mini"
                      >
                        <template slot="append">N/mm²</template>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      label=""
                      style="width: 40%"
                      class="dandu-item">
                      <!--圆盘剪设定-激光划线宽-人工修正值-->
                      <el-input
                        v-model="form1Change.L2CSSET_LaserWid_MOD"
                        size="mini"
                      />
                    </el-form-item>

                    <el-form-item
                      label="剪机横移宽"
                      style="width: 60%">
                      <el-input
                        v-model="form1Change.L2CSSET_CS_Wid"
                        size="mini"
                      >
                        <template slot="append">N/mm²</template>
                      </el-input>
                    </el-form-item>
                    <el-form-item
                      label=""
                      style="width: 40%"
                      class="dandu-item">
                      <!--圆盘剪设定-剪机横移宽-人工修正值-->
                      <el-input
                        v-model="form1Change.L2CSSET_CS_Wid_MOD"
                        size="mini"
                      />
                    </el-form-item>
                    <el-form-item
                      label="空过标志"
                      style="width: 60%">
                      <el-switch
                        v-model="form1Change.L2CSSET_CS_Empty"
                        active-color="#13356F"
                        inactive-color="#5e0f0f"
                      />
                    </el-form-item>
                    <el-form-item
                      label="-"
                      style="width: 40%"/>
                  </el-form>
                </div>
              </div>
              <div
                class="form-footer"
                style="margin-top: 20px; overflow: hidden;display: flex;justify-content: flex-end;">
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
          </div>
        </el-col>
        <el-col :span="17">
          <el-table
            v-loading="tableLoading"
            :data="steelTableSon"
            :tree-props="{children: 'children', hasChildren: 'hasChildren'}"
            :row-class-name="tableRowClassName"
            :empty-text="'暂无数据'"
            :cell-style="getCellStyle"
            :header-cell-style="{border: '1px solid #777',backgroundColor: '#B9C8C5'}"
            class="eltablecss"
            style="width: 100%;"
            height="510"
            row-key="PLATE_NO"
            border
            default-expand-all
            @selection-change="handleSelectionChange">
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
              width="160"
              align="center"/>
            <el-table-column
              fixed="right"
              label="操作"
              width="180">
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
                <el-button
                  v-if="scope.row.PLATE_TYPE == 2 || scope.row.PLATE_TYPE == 4 || scope.row.PLATE_TYPE == 1"
                  type="text"
                  size="mini"
                  @click="openWarehouse(scope.row.PLATE_NO)">中间库</el-button>
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
              prop="PLATE_THK"
              label="厚度"
              width="60"
              align="center"/>
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
      <el-row style="margin-top: 20px">
        <el-col :span="24">
          <warn-info
            :warn-type="2"
          />
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
import HmiTable from '@/components/HmiTable'
import { getHmiData, sendMsg, sendTag, stopGetData } from '@/lib/GetData'
import steelInfo from '@/pages/components/steelInfo'
import warnInfo from '@/pages/components/warnInfo'
import modifInfo from '@/pages/components/modifInfo'
import trackItem from '@/pages/components/trackItem'
export default {
  name: 'Lcb2',
  components: { HmiTable, steelInfo, warnInfo, modifInfo, trackItem },
  data() {
    return {
      variable: [
        'rechmi6',
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
        'L2CSSET_PlateNo',
        'L2CSSET_Plate_Len',
        'L2CSSET_Plate_Wid',
        'L2CSSET_Plate_Thk',
        'L2CSSET_Gap_Thk',
        'L2CSSET_Coincide_Thk',
        'L2CSSET_LaserWid',
        'L2CSSET_CS_Wid',
        'L2CSSET_CS_Empty',
        'L2CSSET_UseFlag',
        'L2CSSET_ModFlag',
        'L2CSSET_Gap_Thk_MOD',
        'L2CSSET_Coincide_Thk_MOD',
        'L2CSSET_LaserWid_MOD',
        'L2CSSET_CS_Wid_MOD'
      ],
      cmdList: [
        {
          key: 'L2CSTRACK.CSCMD1',
          value: '',
          x: 0
        },
        {
          key: 'L2CSTRACK.CSCMD2',
          value: '',
          x: 170.0483092
        },
        {
          key: 'L2CSTRACK.CSCMD3',
          value: '',
          x: 340.0966184
        },
        {
          key: 'L2CSTRACK.CSCMD4',
          value: '',
          x: 494.6859903
        },
        {
          key: 'L2CSTRACK.CSCMD5',
          value: '',
          x: 649.2753623
        },
        {
          key: 'L2CSTRACK.CSCMD6',
          value: '',
          x: 899.7101449
        },
        {
          key: 'L2CSTRACK.CSCMD7',
          value: '',
          x: 1072.850242
        },
        {
          key: 'L2CSTRACK.CSCMD8',
          value: '',
          x: 1244.444444
        },
        {
          key: 'L2CSTRACK.CSCMD9',
          value: '',
          x: 1383.074879
        },
        {
          key: 'L2CSTRACK.CSCMD10',
          value: '',
          x: 1600
        }
      ],
      form1: {
        changeFlag: true,
        L2CSSET_PlateNo: '',
        L2CSSET_Plate_Len: '',
        L2CSSET_Plate_Wid: '',
        L2CSSET_Plate_Thk: '',
        L2CSSET_Gap_Thk: '',
        L2CSSET_Coincide_Thk: '',
        L2CSSET_LaserWid: '',
        L2CSSET_CS_Wid: '',
        L2CSSET_CS_Empty: '',
        L2CSSET_UseFlag: '',
        L2CSSET_ModFlag: '',
        L2CSSET_Gap_Thk_MOD: '',
        L2CSSET_Coincide_Thk_MOD: '',
        L2CSSET_LaserWid_MOD: '',
        L2CSSET_CS_Wid_MOD: ''
      },
      form1Change: {},
      trackData: [],
      tableLoading: false,
      currentId: [],
      steelTablePar: [{}, {}, {}, {}],
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
      steelTableSon: [],
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
  mounted() {
    this.getHmiData()
  },
  destroyed() {
    stopGetData()
  },
  methods: {
    //封装成对象方法使用
    trackSteel(data) {
      // 页面和实际比例 以整个图为例 宽度: 实际3.51m  页面55px  总长  长度: 实际165318-269620m  页面长度 1611px
      // 辊道 实际3.51m  页面55px
      let [actWid, pageWid, actLen, pageLen, actgd, pagegd] = [
        3.51 * 1000,
        55,
        104.302 * 1000,
        1611,
        3.51 * 1000,
        55
      ]
      this.trackData = []
      for (let i = 0; i < data['rechmi6'].length; i++) {
        let item = data['rechmi6'][i]
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
    },
    initCmd(data) {
      this.cmdList.forEach(item => {
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
    },
    getHmiData() {
      getHmiData(
        'ypj',
        data => {
          data['rechmi6'].forEach(item => {
            item.tailX = item.tail_x
            item.Vpos = item.v_pos
            item.headX = item.head_x
          })
          data['rechmi6'].map((item, index) => {
            item.v_pos = item.v_pos - 67270
            item.tail_x = item.tail_x - 165318
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
    getTableDataByProcess(data) {
      let fordata = data['rechmi6']
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
        this.getTableDataChild(plateno, type, itemInfo.region)
        this.tableLoading = true
      }, 400)
    },
    initFormData(data) {
      this.form1.L2CSSET_UseFlag = data['L2CSSET_UseFlag'] == 1 ? true : false
      this.form1.L2CSSET_PlateNo = data['L2CSSET_PlateNo']
      this.form1.L2CSSET_Plate_Wid = data['L2CSSET_Plate_Wid'].toFixed(2)
      this.form1.L2CSSET_Plate_Len = data['L2CSSET_Plate_Len'].toFixed(2)
      this.form1.L2CSSET_Plate_Thk = data['L2CSSET_Plate_Thk'].toFixed(2)
      this.form1.L2CSSET_Gap_Thk = data['L2CSSET_Gap_Thk'].toFixed(2)
      this.form1.L2CSSET_Coincide_Thk = data['L2CSSET_Coincide_Thk'].toFixed(2)
      this.form1.L2CSSET_LaserWid = data['L2CSSET_LaserWid'].toFixed(2)
      this.form1.L2CSSET_CS_Wid = data['L2CSSET_CS_Wid'].toFixed(2)
      this.form1.L2CSSET_CS_Empty = data['L2CSSET_CS_Empty'].toFixed(2)
      this.form1.L2CSSET_ModFlag = data['L2CSSET_ModFlag'].toFixed(2)
      this.form1.L2CSSET_Gap_Thk_MOD = data['L2CSSET_Gap_Thk_MOD'].toFixed(2)
      this.form1.L2CSSET_Coincide_Thk_MOD = data[
        'L2CSSET_Coincide_Thk_MOD'
      ].toFixed(2)
      this.form1.L2CSSET_LaserWid_MOD = data['L2CSSET_LaserWid_MOD'].toFixed(2)
      this.form1.L2CSSET_CS_Wid_MOD = data['L2CSSET_CS_Wid_MOD'].toFixed(2)
    },
    openRefresh(form) {
      form.changeFlag = true
    },
    closeRefresh(form) {
      form.changeFlag = false
      this.initForm()
      console.log('关闭实时刷新')
    },
    initForm() {
      this.form1Change = { ...this.form1 } //不参加原数组修改
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
    againSet() {
      let data = [
        [
          {
            plateno: this.form1.L2CSSET_PlateNo,
            process: '7'
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
    saveSet() {
      this.$confirm('是否确定修改?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          let data = {
            L2CSSET_PlateNo: this.form1Change.L2CSSET_PlateNo,
            L2CSSET_Plate_Len: this.form1Change.L2CSSET_Plate_Len,
            L2CSSET_Plate_Wid: this.form1Change.L2CSSET_Plate_Wid,
            L2CSSET_Gap_Thk: this.form1Change.L2CSSET_Gap_Thk,
            L2CSSET_Coincide_Thk: this.form1Change.L2CSSET_Coincide_Thk,
            L2CSSET_LaserWid: this.form1Change.L2CSSET_LaserWid,
            L2CSSET_CS_Wid: this.form1Change.L2CSSET_CS_Wid,
            L2CSSET_CS_Empty:
              this.form1Change.L2CSSET_CS_Empty == true ? '1' : '0',
            L2CSSET_Gap_Thk_MOD: this.form1Change.L2CSSET_Gap_Thk_MOD,
            L2CSSET_Coincide_Thk_MOD: this.form1Change.L2CSSET_Coincide_Thk_MOD,
            L2CSSET_LaserWid_MOD: this.form1Change.L2CSSET_LaserWid_MOD,
            L2CSSET_CS_Wid_MOD: this.form1Change.L2CSSET_CS_Wid_MOD,
            L2CSSET_UseFlag:
              this.form1Change.L2CSSET_UseFlag == true ? '1' : '0',
            L2CSSET_ModFlag: 1
          }
          console.log(data)
          sendTag(data).then(res => {
            if (res.code == 200) {
              this.$message({
                message: '修改成功',
                type: 'success'
              })
              this.form1.changeFlag = true
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
    arraySpanMethod({ row, column, rowIndex, columnIndex }) {
      if (rowIndex == 0) {
        if (columnIndex == 1) {
          return [1, 3]
        } else if (columnIndex == 2 || columnIndex == 3) {
          return [0, 0]
        }
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
    checkboxFn(item) {},
    revoke(item) {
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
      console.log('分段开始', item)
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
    // 中间库上线
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
          console.log(this.postForm.body.params[0][0].plateno)
          this.$message({
            type: 'info',
            message: '已取消吊销'
          })
        })
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
    getTableDataChild(plateno, type, clickRegion) {
      console.log(clickRegion)
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
        return 'background: #CDF8CE;border: solid 1px #777;'
      }
    }
  }
}
</script>


<style scoped lang="less">
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
.leftForm {
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
  justify-content: space-between;
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
.ypj {
  .bgc-white {
    background-color: #fff;
    box-shadow: 0px 0px 4px rgb(0 0 0 / 4%), 0px 0px 16px -2px rgb(0 0 0 / 10%);
    border-radius: 6px;
  }

  .banner {
    height: 326px;
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
      height: 182px;
      position: relative;
      //overflow: hidden;
      .bgimg-box {
        width: 1622px;
        height: 100%;
        //background: url('../assets/ypj.png') no-repeat 100% 100%;
        background: url('../assets/bg/ypj.png') no-repeat 100% 100%;
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
</style>
