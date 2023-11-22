<template>
  <div class="modif-box">
    <div
      v-if="poschangeshow"
      :style="{left:posboxsty.left +'px',top:posboxsty.top+'px'}"
      class="pos-change">
      <el-card
        :shadow="'never'"
        class="box-card">
        <div
          slot="header"
          class="clearfix">
          <span>校正</span>
        </div>
        <div
          class="body1"
          style="margin-bottom: 4px">
          <div>
            <el-form
              ref="form"
              :model="posForm"
              label-width="70px">
              <el-form-item
                label="板坯号">
                <el-input
                  :disabled="isReadOnly == 1"
                  v-model="posForm.plant"
                  style="width: 150px"
                  @change="isReadOnly = 2"/>
              </el-form-item>
              <el-form-item
                label="位移方向">
                <el-radio
                  v-if="direction == 'all' || direction == 'horizontal'"
                  :disabled="isReadOnly == 2"
                  v-model="posForm.radio"
                  label="1">上</el-radio>
                <el-radio
                  v-if="direction == 'all' || direction == 'horizontal'"
                  :disabled="isReadOnly == 2"
                  v-model="posForm.radio"
                  label="2">下</el-radio>
                <el-radio
                  v-if="direction == 'all' || direction == 'vertical'"
                  :disabled="isReadOnly == 2"
                  v-model="posForm.radio"
                  label="3">左</el-radio>
                <el-radio
                  v-if="direction == 'all' || direction == 'vertical'"
                  :disabled="isReadOnly == 2"
                  v-model="posForm.radio"
                  label="4">右</el-radio>
              </el-form-item>
              <el-form-item
                label="增量">
                <el-input
                  :disabled="isReadOnly == 2"
                  v-model="posForm.unit"
                  style="width: 100px"
                  @change="isReadOnly = 1"/>
              </el-form-item>
              <el-form-item
                label="位移距离">
                <el-input-number
                  :disabled="isReadOnly == 2"
                  v-model="posForm.num"
                  :step="Number(posForm.unit)"
                  size="mini"
                  @change="handleChangeNum"/>
              </el-form-item>
            </el-form>
          </div>
          <div
            class=""
            style="display: flex;flex-direction: row-reverse;margin-top: 16px"
          >
            <el-button
              type="primary"
              style="margin-left: 10px"
              size="mini"
              @click="submitPos()">确 定</el-button>
            <el-button
              size="mini"
              @click="closepos()">取 消</el-button>
          </div>
        </div>
      </el-card>
    </div>
  </div>
</template>

<script>
import { sendMsg } from '@/lib/GetData'

export default {
  name: 'ModifInfo',
  props: {
    //horizontal  vertical
    direction: {
      type: String,
      default: () => {
        return 'all'
      }
    },
    poschangeshow: {
      type: Boolean,
      default: () => {
        return false
      }
    },
    posboxsty: {
      type: Object,
      default: () => {
        return {
          top: 0,
          left: 0
        }
      }
    },
    posForm: {
      type: Object,
      default: () => {
        return {}
      }
    }
  },
  data() {
    return {
      isReadOnly: 3
    }
  },
  methods: {
    handleChangeNum() {
      this.isReadOnly = 1
    },
    submitPos() {
      if (this.isReadOnly == 2) {
        console.log('修改钢板号')
        let data = [
          [
            {
              plateno_old: this.posForm.oldId,
              plateno_new: this.posForm.plant,
              region: this.posForm.region
            }
          ]
        ]
        console.log(data)
        sendMsg(data, 1806, 'HMI').then(res => {
          if (res.results[0][0].msg) {
            this.$message({
              message: res.results[0][0].msg,
              type: 'success'
            })
          }
          setTimeout(() => {
            /*this.poschangeshow = false
            this.posForm.num = ''*/
            this.$emit('submitPos')
            this.isReadOnly = 3
          }, 1000)
        })
      } else {
        console.log('修改位置')
        let [x_correct, y_correct] = [0, 0]
        if (this.posForm.radio == 1 || this.posForm.radio == 2) {
          y_correct = this.posForm.num
        } else {
          x_correct = this.posForm.num
        }
        // 下和右是正数 左和上是负数
        if (this.posForm.radio == 1 || this.posForm.radio == 3) {
          y_correct = -y_correct
          x_correct = -x_correct
        }
        let data = [
          [
            {
              plateno: this.posForm.plant,
              region: this.posForm.region + '',
              x_correct: x_correct + '',
              y_correct: y_correct + ''
            }
          ]
        ]
        this.$confirm('是否确定修改钢板位置, 是否继续?', '提示', {
          confirmButtonText: '确定',
          cancelButtonText: '取消',
          type: 'warning'
        }).then(() => {
          sendMsg(data, 1807, 'HMI').then(res => {
            if (res.results[0][0].msg) {
              this.$message({
                message: res.results[0][0].msg,
                type: 'success'
              })
            }
            setTimeout(() => {
              this.$emit('submitPos')
              this.isReadOnly = 3
            }, 1000)
          })
        })
      }
    },
    closepos() {
      this.$emit('closePos')
      //重置数据
      this.isReadOnly = 3
    }
  }
}
</script>

<style scoped lang="less">
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
</style>
