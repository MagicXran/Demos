<template>
  <div class="set-info">
    <div
      v-if="typeFlag == 1"
      class="type1 bgcfff">
      <div
        class="type-box"
        style="padding: 20px 20px 60px 20px;">
        <div
          class="title"
          style="margin-bottom: 8px">
          <p>{{ type1Title }}<span
            v-if="!type1Show"
            style="margin-left: 265px; color: #FFA958;font-size: 13px">修改中... <i
              style="font-size: 20px;cursor: pointer"
              class="el-icon-circle-close"
              @click="openRefresh()"
          /></span></p>
        </div>
        <div class="form-boder">
          <div v-if="type1Show">
            <el-form
              ref="form"
              :model="type1Form"
              label-width="80px">
              <el-form-item
                label="L2投用"
                style="font-weight: 600; width: 60%">
                <el-switch
                  v-model="type1Form.DSS_Use_Flag"
                  active-color="green"
                  inactive-color="red"
                  @change="closeRefresh('type1')"
                />
              </el-form-item>
              <el-form-item
                label="人工修正值"
                style="width: 40%"
                class="dandu-item1"/>
              <!-- 双边剪设定iii -->
              <el-form-item
                label="钢板号"
                style="width: 60%">
                <el-input
                  v-model="type1Form.L1DSSSET_PlateNo"
                  size="mini"
                  @focus="closeRefresh('type1')"
                >
                  <el-button
                    slot="append"
                    icon="el-icon-search"
                    @click="getTableDataByTwo(type1Form.L1DSSSET_PlateNo,3)"/>
                </el-input>
              </el-form-item>
              <el-form-item
                label="-"
                style="width: 40%"/>
              <el-form-item
                label="母板长度"
                style="width: 60%">
                <el-input
                  v-model="type1Form.L1DSSSET_Plate_Len"
                  size="mini"
                  @focus="closeRefresh('type1')"
                >
                  <template slot="append">mm</template>
                </el-input>
              </el-form-item>
              <el-form-item
                label=""
                class="dandu-item2"
                style="width: 40%">
                <el-switch
                  v-model="type1Form.sele_fix_len"
                  active-color="#13356F"
                  inactive-color="#5e0f0f"
                  @change="closeRefresh('type1')"
                />
              </el-form-item>
              <el-form-item
                label="母板宽度"
                style="width: 60%">
                <el-input
                  v-model="type1Form.L1DSSSET_Plate_Wid"
                  size="mini"
                  @focus="closeRefresh('type1')"
                >
                  <template slot="append">mm</template>
                </el-input>
              </el-form-item>
              <el-form-item
                class="dandu-item2"
                label=""
                style="width: 40%">
                <el-switch
                  v-model="type1Form.sele_fix_wid"
                  active-color="#13356F"
                  inactive-color="#5e0f0f"
                  @change="closeRefresh('type1')"
                />
              </el-form-item>
              <el-form-item
                label="母板厚度"
                style="width: 60%">
                <el-input
                  v-model="type1Form.L1DSSSET_Plate_Thk"
                  size="mini"
                  @focus="closeRefresh('type1')"
                >
                  <template slot="append">mm</template>
                </el-input>
              </el-form-item>
              <!-- <el-form-item
                label=""
                style="width: 40%"
                class="dandu-item">
                <el-input
                  v-model="type1Form.L1DSSSET_DSS_THK_MOD"
                  size="mini"
                  @focus="closeRefresh('type1')"
                />
              </el-form-item> -->
              <el-form-item
                style="width: 40%"
                class="dandu-item"
                label="">
                <el-input-number
                  v-model="type1Form.L1DSSSET_DSS_THK_MOD"
                  size="mini"
                  @change="closeRefresh('type1')"/>
              </el-form-item>
              <el-form-item
                label="剪切宽度"
                style="width: 60%">
                <el-input
                  v-model="type1Form.L1DSSSET_DSS_Wid"
                  size="mini"
                  @focus="closeRefresh('type1')"
                >
                  <template slot="append">mm</template>
                </el-input>
              </el-form-item>
              <!-- <el-form-item
                label=""
                style="width: 40%"
                class="dandu-item">
                <el-input
                  v-model="type1Form.L1DSSSET_DSS_Wid_MOD"
                  size="mini"
                  @focus="closeRefresh('type1')"
                />
              </el-form-item> -->
              <el-form-item
                style="width: 40%"
                class="dandu-item"
                label="">
                <el-input-number
                  v-model="type1Form.L1DSSSET_DSS_Wid_MOD"
                  size="mini"
                  @change="closeRefresh('type1')"/>
              </el-form-item>
              <!--              <el-form-item
                label="屈服强度"
                style="width: 60%">
                <el-input
                  v-model="type1Form.DSS_Strength"
                  size="mini"
                  @focus="closeRefresh('type1')"
                >
                  <template slot="append">N/mm²</template>
                </el-input>
              </el-form-item>
              <el-form-item
                label="-"
                style="width: 40%"/>
              <el-form-item
                label="空过标志"
                style="width: 60%">
                <el-switch
                  v-model="type1Form.L1DSSSET_DSS_Empty"
                  active-color="#13356F"
                  inactive-color="#5e0f0f"
                  @change="closeRefresh('type1')"/>
              </el-form-item>
              <el-form-item
                label="-"
                style="width: 40%"/>-->
            </el-form>
          </div>
          <div v-if="!type1Show">
            <el-form
              ref="form"
              :model="tempType1Obj"
              label-width="80px">
              <el-form-item
                label="L2投用"
                style="font-weight: 600; width: 60%">
                <el-switch
                  v-model="tempType1Obj.DSS_Use_Flag"
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
                  v-model="tempType1Obj.L1DSSSET_PlateNo"
                  size="mini"
                >
                  <el-button
                    slot="append"
                    icon="el-icon-search"
                    @click="getTableDataByTwo(tempType1Obj.L1DSSSET_PlateNo,3)"/>
                </el-input>
              </el-form-item>
              <el-form-item
                label="-"
                style="width: 40%"/>
              <el-form-item
                label="母板长度"
                style="width: 60%">
                <el-input
                  v-model="tempType1Obj.L1DSSSET_Plate_Len"
                  size="mini"
                >
                  <template slot="append">mm</template>
                </el-input>
              </el-form-item>
              <el-form-item
                label=""
                class="dandu-item2"
                style="width: 40%">
                <el-switch
                  v-model="type1Form.sele_fix_len"
                  active-color="#13356F"
                  inactive-color="#5e0f0f"
                  @change="closeRefresh('type1')"
                />
              </el-form-item>
              <el-form-item
                label="母板宽度"
                style="width: 60%">
                <el-input
                  v-model="tempType1Obj.L1DSSSET_Plate_Wid"
                  size="mini"
                >
                  <template slot="append">mm</template>
                </el-input>
              </el-form-item>
              <el-form-item
                class="dandu-item2"
                label=""
                style="width: 40%">
                <el-switch
                  v-model="type1Form.sele_fix_wid"
                  active-color="#13356F"
                  inactive-color="#5e0f0f"
                  @change="closeRefresh('type1')"
                />
              </el-form-item>
              <el-form-item
                label="母板厚度"
                style="width: 60%">
                <el-input
                  v-model="tempType1Obj.L1DSSSET_Plate_Thk"
                  size="mini"
                >
                  <template slot="append">mm</template>
                </el-input>
              </el-form-item>
              <!-- <el-form-item
                label=""
                style="width: 40%"
                class="dandu-item">
                <el-input
                  v-model="tempType1Obj.L1DSSSET_DSS_THK_MOD"
                  size="mini"
                />
              </el-form-item> -->
              <el-form-item
                style="width: 40%"
                class="dandu-item"
                label="">
                <el-input-number
                  v-model="tempType1Obj.L1DSSSET_DSS_THK_MOD"
                  size="mini"/>
              </el-form-item>
              <el-form-item
                label="剪切宽度"
                style="width: 60%">
                <el-input
                  v-model="tempType1Obj.L1DSSSET_DSS_Wid"
                  size="mini"
                >
                  <template slot="append">mm</template>
                </el-input>
              </el-form-item>
              <!-- <el-form-item
                label=""
                style="width: 40%"
                class="dandu-item">
                <el-input
                  v-model="tempType1Obj.L1DSSSET_DSS_Wid_MOD"
                  size="mini"
                />
              </el-form-item> -->
              <el-form-item
                style="width: 40%"
                class="dandu-item"
                label="">
                <el-input-number
                  v-model="tempType1Obj.L1DSSSET_DSS_Wid_MOD"
                  size="mini"/>
              </el-form-item>
              <!--              <el-form-item
                label="屈服强度"
                style="width: 60%">
                <el-input
                  v-model="tempType1Obj.DSS_Strength"
                  size="mini"
                >
                  <template slot="append">N/mm²</template>
                </el-input>
              </el-form-item>
              <el-form-item
                label="-"
                style="width: 40%"/>
              <el-form-item
                label="空过标志"
                style="width: 60%">
                <el-switch
                  v-model="tempType1Obj.L1DSSSET_DSS_Empty"
                  active-color="#13356F"
                  inactive-color="#5e0f0f"
                />
              </el-form-item>
              <el-form-item
                label="-"
                style="width: 40%"/>-->
            </el-form>
          </div>
        </div>
        <div
          class="form-footer"
          style="margin-top: 20px; overflow: hidden;display: flex;
    justify-content: flex-end;">
          <el-button
            type="primary"
            size="mini"
            @click="saveSet()">修改
          </el-button>
          <el-button
            style=""
            type="primary"
            size="mini"
            @click="againSet()">重新设定
          </el-button>
        </div>
      </div>
    </div>
    <div
      v-if="typeFlag == 2"
      class="type2">
      <el-row class="bgcfff">
        <div>
          <el-col
            v-if="type2Show"
            :span="14"
            class="bgcfff">
            <div
              style="padding: 24px;"
              class="bgc-white bgc-padding">
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
                      v-model="type2Form.L1DSSET_UseFlag"
                      active-color="green"
                      inactive-color="red"
                      @change="closeRefresh('type2')"/>
                  </div>
                </div>
              </div>
              <div class="form-boder">
                <el-row :gutter="5">
                  <el-col :span="10">
                    <el-form
                      ref="form"
                      :model="type2Form"
                      label-width="75px">
                      <el-form-item label="钢板号">
                        <el-input
                          v-model="type2Form.L1DSSET_PlateNo"
                          size="mini"
                          @focus="closeRefresh('type2')">
                          <el-button
                            slot="append"
                            icon="el-icon-search"
                            @click="getTableDataByTwo(type2Form.L1DSSET_PlateNo,3)"/>
                        </el-input>
                      </el-form-item>
                      <!--                      <el-form-item label="钢种">
                        <el-input
                          v-model="type2Form.L1DSSET_Steelgrade"
                          size="mini"
                          @focus="closeRefresh('type2')"/>
                      </el-form-item>-->
                      <el-form-item label="母板长度">
                        <el-input
                          v-model="type2Form.L1DSSET_Plate_Len"
                          size="mini"
                          @focus="closeRefresh('type2')">
                          <template slot="append">mm</template>
                        </el-input>
                      </el-form-item>
                      <el-form-item label="母板宽度">
                        <el-input
                          v-model="type2Form.L1DSSET_Plate_Wid"
                          size="mini"
                          @focus="closeRefresh('type2')">
                          <template slot="append">mm</template>
                        </el-input>
                      </el-form-item>
                      <el-form-item label="母板厚度">
                        <el-input
                          v-model="type2Form.L1DSSET_Plate_Thk"
                          size="mini"
                          @focus="closeRefresh('type2')">
                          <template slot="append">mm</template>
                        </el-input>
                      </el-form-item>
                    </el-form>
                  </el-col>
                  <el-col
                    :span="14"
                    class="pad0">
                    <el-table
                      :data="type2TableSet"
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
                            @focus="closeRefresh('type2')">
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
                            @focus="closeRefresh('type2')">
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
                    plateno: type2Form.L1DSSET_PlateNo,
                    region: 0
                },0,1)">查询</el-button>-->
                <el-button
                  type="primary"
                  size="mini"
                  @click="realLength()">实际长度
                </el-button>
                <el-button
                  type="primary"
                  size="mini"
                  @click="bigSaveSet()">放大修改
                </el-button>
                <el-button
                  type="primary"
                  size="mini"
                  @click="saveSet()">修改
                </el-button>
                <el-button
                  style=""
                  type="primary"
                  size="mini"
                  @click="againSet()">重新设定
                </el-button>
              </div>
            </div>
          </el-col>
          <el-col
            v-if="!type2Show"
            :span="14"
            class="bgcfff">
            <div
              style="padding: 24px;padding-right:0px;"
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
                    @click="openRefresh()"
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
                      v-model="tempType2Obj.L1DSSET_UseFlag"
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
                      :model="tempType2Obj"
                      label-width="75px">
                      <el-form-item label="钢板号">
                        <el-input
                          v-model="tempType2Obj.L1DSSET_PlateNo"
                          size="mini"
                        >
                          <el-button
                            slot="append"
                            icon="el-icon-search"
                            @click="getTableDataByTwo(tempType2Obj.L1DSSET_PlateNo,3)"/>
                        </el-input>
                      </el-form-item>
                      <!--                      <el-form-item label="钢种">
                        <el-input
                          v-model="tempType2Obj.L1DSSET_Steelgrade"
                          size="mini"
                        />
                      </el-form-item>-->
                      <el-form-item label="母板长度">
                        <el-input
                          v-model="tempType2Obj.L1DSSET_Plate_Len"
                          size="mini"
                        >
                          <template slot="append">mm</template>
                        </el-input>
                      </el-form-item>
                      <el-form-item label="母板宽度">
                        <el-input
                          v-model="tempType2Obj.L1DSSET_Plate_Wid"
                          size="mini"
                        >
                          <template slot="append">mm</template>
                        </el-input>
                      </el-form-item>
                      <el-form-item label="母板厚度">
                        <el-input
                          v-model="tempType2Obj.L1DSSET_Plate_Thk"
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
                      :data="tempType2TableSet"
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
                  @click="getTableDataByTwo(type2Form.L1DSSET_PlateNo,0)">查询
                </el-button>
                <el-button
                  type="primary"
                  size="mini"
                  @click="saveSet()">修改
                </el-button>
                <el-button
                  style=""
                  type="primary"
                  size="mini"
                  @click="againSet()">重新设定
                </el-button>
              </div>
            </div>
          </el-col>
        </div>
        <el-col
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
              :data="type2TableAct"
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
                    size="mini">已剪切
                  </el-button>
                  <el-button
                    v-if="scope.row.com == 0"
                    type="warning"
                    plain
                    size="mini">未剪切
                  </el-button>
                </template>
              </el-table-column>
            </el-table>
          </div>
        </el-col>
      </el-row>
    </div>
    <div
      v-if="typeFlag == 3"
      class="type1 bgcfff">
      33333
    </div>
    <div
      v-if="typeFlag == 4"
      class="type1 bgcfff">
      <div
        class="type-box"
        style="padding: 20px;">
        <div class="title">
          <p>{{ type4Title }}</p>
        </div>
        <div class="form-boder">
          <el-form
            ref="form"
            :model="type4Form"
            label-width="80px">
            <el-form-item
              label="L2投用"
              style="border: none; font-weight: 600;">
              <el-switch
                v-model="type4Form.DSS_Use_Flag"
                active-color="green"
                inactive-color="red"
                @change="closeRefresh('DSS_Use_Flag')"
              />
            </el-form-item>
            <el-form-item label="钢板号">
              <el-input
                v-model="type4Form.L1DSSSET_PlateNo"
                size="mini"
                @focus="closeRefresh('L1DSSSET_PlateNo')"
              />
            </el-form-item>
            <el-form-item label="母板长度">
              <el-input
                v-model="type4Form.L1DSSSET_Plate_Len"
                size="mini"
                @focus="closeRefresh('L1DSSSET_Plate_Len')"
              />
            </el-form-item>
            <el-form-item label="母板宽度">
              <el-input
                v-model="type4Form.L1DSSSET_Plate_Wid"
                size="mini"
                @focus="closeRefresh('L1DSSSET_Plate_Wid')"
              />
            </el-form-item>
            <el-form-item label="母板厚度">
              <el-input
                v-model="type4Form.L1DSSSET_Plate_Thk"
                size="mini"
                @focus="closeRefresh('L1DSSSET_Plate_Thk')"
              />
            </el-form-item>
            <el-form-item label="固定值">
              <el-switch
                v-model="type4Form.sele_fix"
                active-color="#13356F"
                inactive-color="#5e0f0f"
                @change="closeRefresh('sele_fix')"
              />
            </el-form-item>
            <el-form-item label="空过标志">
              <el-switch
                v-model="type4Form.L1DSSSET_DSS_Empty"
                active-color="#13356F"
                inactive-color="#5e0f0f"
                @change="closeRefresh('L1DSSSET_DSS_Empty')"/>
            </el-form-item>
          </el-form>
        </div>
        <div
          class="form-footer"
          style="margin-top: 20px; overflow: hidden;display: flex;
    justify-content: flex-end;">
          <el-button
            type="primary"
            size="mini"
            @click="getTableDataByTwo(type4Form.L1DSSSET_PlateN,0)">查询
          </el-button>
          <el-button
            type="primary"
            size="mini"
            @click="saveSet()">修改
          </el-button>
          <el-button
            style=""
            type="primary"
            size="mini"
            @click="againSet()">重新设定
          </el-button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import { getHmiData, stopGetData, sendMsg, sendTag } from '@/lib/GetData'

export default {
  name: 'SetInfo',
  props: {
    // 1: 矫直冷床双边剪, 2: 1#定尺剪, 3: 标印-垛扳 4: 冷床切分剪 5: 圆盘剪 6: 2#定尺剪 7: 2#垛扳机
    typeFlag: {
      type: Number,
      default: 1
    },
    type1Title: {
      type: String,
      default: ''
    },
    type1Form: {
      type: Object,
      default: () => {
        return {}
      }
    },
    type4Title: {
      type: String,
      default: ''
    },
    type4Form: {
      type: Object,
      default: () => {
        return {}
      }
    },
    //------------------
    type2Form: {
      type: Object,
      default: () => {
        return {}
      }
    },
    type2TableSet: {
      type: Array,
      default: () => {
        return []
      }
    },
    type2TableAct: {
      type: Array,
      default: () => {
        return []
      }
    }
  },
  data() {
    return {
      tempType1Obj: {},
      tempType2Obj: {},
      tempType2TableSet: {},
      type1Show: true,
      type2Show: true
    }
  },
  computed: {},
  watch: {},
  mounted() {},
  methods: {
    initType1Form() {
      this.tempType1Obj = { ...this.type1Form }
    },
    initType2Form() {
      this.tempType2Obj = { ...this.type2Form } //不参加原数组修改
      this.tempType2TableSet = [...this.type2TableSet]
    },
    openRefresh() {
      this.type1Show = true
      this.type2Show = true
    },
    closeRefresh(type) {
      let typeMap = {
        type1: () => {
          this.type1Show = false
          this.initType1Form()
          return
        },
        type2: () => {
          this.type2Show = false
          this.initType2Form()
          //每次重新init都会刷新set表格数据
          return
        }
      }
      const getType = bar => {
        console.log(11)
        return typeMap[bar]()
      }
      getType(type)
      // console.log(type)
      // this.initType1Form()
      // this.type1Show = false
    },
    getTableDataByTwo(plateno, type) {
      this.$emit('getTableDataByTwoSon', plateno, type)
      console.log(plateno, type)
      this.openRefresh() //查询钢板号 关闭修改中
    },
    bigSaveSet() {
      this.tempType2Obj_ = { ...this.type2Form }
      this.tempType2TableSet_ = [...this.type2TableSet]
      this.$emit('bigSaveSet', this.tempType2Obj_, this.tempType2TableSet_)
    },
    realLength() {
      this.$emit('realLength')
    },
    saveSet() {
      this.$confirm('是否确定修改?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          //判断typeFlag 决定submitForm
          let data
          if (this.typeFlag == 1) {
            data = {
              DSS_Use_Flag: this.tempType1Obj.DSS_Use_Flag == true ? '1' : '0',
              L1DSSSET_PlateNo: this.tempType1Obj.L1DSSSET_PlateNo,
              L1DSSSET_Plate_Len: this.tempType1Obj.L1DSSSET_Plate_Len,
              L1DSSSET_Plate_Wid: this.tempType1Obj.L1DSSSET_Plate_Wid,
              L1DSSSET_Plate_Thk: this.tempType1Obj.L1DSSSET_Plate_Thk,
              L1DSSSET_DSS_Wid: this.tempType1Obj.L1DSSSET_DSS_Wid,
              L1DSSSET_DSS_Wid_MOD: this.tempType1Obj.L1DSSSET_DSS_Wid_MOD,
              L1DSSSET_DSS_THK_MOD: this.tempType1Obj.L1DSSSET_DSS_THK_MOD,
              L1DSSSET_DSS_Empty:
                this.tempType1Obj.L1DSSSET_DSS_Empty == true ? '1' : '0',
              DSS_Strength: this.tempType1Obj.DSS_Strength,
              sele_fix: this.tempType1Obj.sele_fix == true ? '0' : '1',
              sele_fix_len: this.tempType1Obj.sele_fix_len == true ? '0' : '1',
              sele_fix_wid: this.tempType1Obj.sele_fix_wid == true ? '0' : '1',
              L1DSSSET_FLAG: 1 // 双边剪设定，点击修改按钮后，将该变量置1
            }
          } else if (this.typeFlag == 2) {
            data = {
              L1DSSET_UseFlag:
                this.tempType2Obj.L1DSSET_UseFlag == true ? '1' : '0',
              L1DSSET_PlateNo: this.tempType2Obj.L1DSSET_PlateNo,
              L1DSSET_Plate_Len: this.tempType2Obj.L1DSSET_Plate_Len,
              L1DSSET_Plate_Wid: this.tempType2Obj.L1DSSET_Plate_Wid,
              L1DSSET_Plate_Thk: this.tempType2Obj.L1DSSET_Plate_Thk,
              L1DSSET_Steelgrade: this.tempType2Obj.L1DSSET_Steelgrade,
              L1DSSET_FLAG: 1, // 双边剪设定，点击修改按钮后，将该变量置1
              L1DSSET_HMI: []
            }
            for (let i = 0; i < this.tempType2TableSet.length; i++) {
              data['L1DSSET_HMI'].push({
                len: this.tempType2TableSet[i].len,
                type: this.tempType2TableSet[i].selectModel
              })
            }
          }
          sendTag(data).then(res => {
            this.type1Show = true
            this.type2Show = true
            this.$emit('refreshHmi')
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
    },
    againSet() {
      let data
      if (this.typeFlag == 1) {
        data = [
          [
            {
              plateno: this.type1Form.L1DSSSET_PlateNo,
              process: '1'
            }
          ]
        ]
      } else if (this.typeFlag == 2) {
        data = [
          [
            {
              plateno: this.type2Form.L1DSSET_PlateNo,
              process: '2'
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
    }
  }
}
</script>

<style scoped lang="less">
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
        /deep/ .el-form-item__label {
          width: 120px !important;
        }
      }

      .dandu-item2 {
        /deep/ .el-form-item__label {
          width: 10px;
        }

        /deep/ .el-form-item__content {
          margin-left: 20px !important;
        }
      }

      .dandu-item {
        /deep/ .el-form-item__label {
          width: 10px;
        }

        /deep/ .el-form-item__content {
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
        /*.el-input .el-input-number__increase {
          border: 1px solid #dcdfe6;
        }*/

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
</style>
<style>
.el-table th {
  display: table-cell !important;
}
</style>
