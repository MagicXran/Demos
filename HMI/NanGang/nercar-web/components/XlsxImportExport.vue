<template>
  <div>
    <el-button-group>
      <el-button
        v-if = "isFileExport"
        type="primary"
        size="small"
        @click = "collateSata()"
      >{{ ExportButtonName }}
        <a
          id = "hf"
          :download = "download"
          href = ""
        />
      </el-button>
      <el-button
        v-if = "isFileUpload"
        type="warning"
        class="fileinput-button"
      >
        {{ ImportButtonName }}
        <input
          type = "file"
          @change = "importf($event)"
        >
      </el-button>
    </el-button-group>
    <el-dialog
      :visible.sync="isShow"
      title = "数据上传"
      width="70%"
    >
      <el-table
        :data="uploadData"
        :row-class-name="rowClassName"
        border
        style="width: 100%">
        <!-- <el-table-column
          type="index"
          width="50"
        /> -->
        <div
          v-for = "property in propertyArray"
          :key = "property.textKey"
        >
          <el-table-column
            :prop="property.key"
            :label="property.textKey"
          >
            <template slot-scope="scope">
              {{ formatterDate(scope, property) }}
            </template>
          </el-table-column>
        </div>
        <el-table-column
          label="操作"
        >
          <template slot-scope="scope">
            <el-button
              type="danger"
              size="small"
              @click="remove(scope)"
            >移除</el-button>
          </template>
        </el-table-column>
      </el-table>
      <div slot = "footer">
        <el-button
          type="success"
          @click = "filesUpload()"
        >数据上传</el-button>
        <el-button
          type="warning"
          @click = "isShow = false"
        >关闭</el-button>
      </div>
    </el-dialog>
  </div>
</template>
<script>
// import Alert from './Alert.vue'
import XLSX from 'xlsx'
import Moment from 'moment'
// import Datagrid from '../components/DataGrid.vue'
// import Modal from '../components/Modal.vue'
// import Noty from 'noty'
export default {
  // components: {
  //   Alert,
  //   Datagrid,
  //   Modal
  // },
  props: {
    majorKey: {
      // 判断的主键
      type: String,
      default: ''
    },
    repeatingData: {
      // 数据验证
      type: Array,
      default: function() {
        return []
      }
    },
    download: {
      // 导出按钮名
      type: String,
      required: false,
      default: '导出'
    },
    isFileExport: {
      // 文件导出
      type: Boolean,
      required: false,
      default: true
    },
    isFileUpload: {
      // 文件上传
      type: Boolean,
      required: false,
      default: false
    },
    ExportButtonName: {
      // 导出按钮名
      type: String,
      required: false,
      default: '导出记录'
    },
    ImportButtonName: {
      // 导入按钮名
      type: String,
      required: false,
      default: '导入记录'
    },
    propertyArray: {
      // 整理数据的格式
      type: Array,
      required: false,
      default: function() {
        return []
      }
    },
    xlsxDataArray: {
      // 上传的数据
      type: Array,
      required: false,
      default: function() {
        return []
      }
    }
  },
  data() {
    return {
      uploadData: [], // 上传数据的确认
      isShow: false, // 上传数据弹窗的显示
      pageSizes: [10, 20, 30, 50], // 上传表格的表格
      operatingBtn: [false, false, false, true], // 上传数据确认表格按钮的控制
      tmpDown: null,
      wb: [], // 读取后的数据
      rABS: false, // 是否将文件读取为二进制字符串
      time: 5000,
      codeIsShow: false,
      detailInfoKey: 'detailInfo', // 自定义字段的key
      detailEntity: {
        detailInfo: []
      }, // 单个上传数据详情
      isShowItem: false, // 显示相信信息
      isShowDetails: false, // 是否显示详情
      departmentArray: [], // 部门
      equipments: [] // 项目
    }
  },
  created() {
    this.equipments = this.$store.state.equipments // 所有的项目
    // this.departmentArray = JSON.parse(sessionStorage.getItem('departmentArray')) // 所有的部门
  },
  methods: {
    /**

     * @description: 移除导入数据
     */
    remove(scope) {
      this.uploadData.splice(scope.$index, 1)
    },
    /**

     * @description: 行的 className 的回调方法，也可以使用字符串为所有行设置一个固定的 className。
     */
    rowClassName({ row, rowIndex }) {
      console.debug('重复数据：', this.repeatingData)
      var repetition = this.repeatingData.filter(value => {
        return value === row[this.majorKey]
      })
      var rowClassName = ''
      if (repetition[0]) {
        rowClassName = 'style-red-row '
      }
      return rowClassName
    },
    /**

     * @description: 数据上传
     */
    filesUpload() {
      // this.isShow = false
      console.debug('数据添加')
      this.$emit('disposalData', this.uploadData)
    },
    /**

     * @description: 整理数据格式
     */
    formatterDate(scope, property) {
      var itemName = scope.column.property
      if (!scope.row[itemName]) {
        return ''
      }
      var date = scope.row[itemName]
      if (property.type === 'date') {
        date = Moment(scope.row[itemName]).format('YYYY年MM月DD日')
      } else if (property.editOptions) {
        var editOptions = property.editOptions
        console.debug('property.editOptions')
      }
      return date
    },
    /**
     * [detailsShow 查看单个上传数据详情]
     * @param  {[type]} event  [description]
     * @param  {[type]} entity [description]
     * @param  {[type]} index  [description]
     * @param  {[type]} num    [description]
     * @return {[type]}        [description]
     */
    detailsShow(event, entity, index, num) {
      console.debug(
        this.detailInfoKey,
        '测试',
        this.detailEntity[this.detailInfoKey]
      )
      this.detailEntity = entity
      this.isShowItem = true
    },
    /**
     * [closeModal 关闭确认上传信息窗口]
     * @param  {[type]} msg [description]
     * @return {[type]}     [description]
     */
    closeModal(msg) {
      if (msg.flag === 'close') {
        if (!this.isShowItem) {
          this.isShow = false
        } else {
          this.isShowItem = false
        }
      } else {
        this.isShow = false
        console.debug('数据添加')
        this.$emit('disposalData', this.uploadData)
      }
    },
    /**
     * [downloadExl 文件导出]
     * @param  {[type]} json     [description]
     * @param  {[type]} type     [description]
     * @param  {[type]} filename [description]
     * @return {[type]}          [description]
     */
    downloadExl(json, type, filename) {
      console.debug('文件格式：', type)
      // this.filename = filename
      var vm = this
      var tmpdata = json[0]
      json.unshift({})
      var keyMap = [] // 获取keys
      for (var k in tmpdata) {
        keyMap.push(k)
        json[0][k] = k
      }
      tmpdata = [] // 用来保存转换好的json
      json
        .map((v, i) =>
          keyMap.map((k, j) =>
            Object.assign(
              {},
              {
                v: v[k],
                position:
                  (j > 25 ? vm.getCharCol(j) : String.fromCharCode(65 + j)) +
                  (i + 1)
              }
            )
          )
        )
        .reduce((prev, next) => prev.concat(next))
        .forEach((v, i) => {
          tmpdata[v.position] = {
            v: v.v
          }
        })
      var outputPos = Object.keys(tmpdata) // 设置区域,比如表格从A1到D10
      var tmpWB = {
        SheetNames: ['mySheet'], // 保存的表标题
        Sheets: {
          mySheet: Object.assign(
            {},
            tmpdata, // 内容
            {
              '!ref': outputPos[0] + ':' + outputPos[outputPos.length - 1] // 设置填充区域
            }
          )
        }
      }
      vm.tmpDown = new Blob(
        [
          vm.s2ab(
            XLSX.write(
              tmpWB,
              {
                bookType: type === undefined ? 'xlsx' : type,
                bookSST: false,
                type: 'binary'
              } // 这里的数据是用来定义导出的格式类型
            )
          )
        ],
        { type: '' }
      ) // 创建二进制对象写入转换好的字节流
      var href = URL.createObjectURL(vm.tmpDown) // 创建对象超链接
      document.getElementById('hf').href = href // 绑定a标签
      document.getElementById('hf').click() // 模拟点击实现下载
      setTimeout(function() {
        // 延时释放
        URL.revokeObjectURL(vm.tmpDown) // 用URL.revokeObjectURL()来释放这个object URL
        vm.tmpDown = [] // 清空导出的url
        // window.$.noty.closeAll()
      }, 100)
    },
    getCharCol(n) {
      // var temCol = ''
      var s = ''
      var m = 0
      while (n > 0) {
        m = (n % 26) + 1
        s = String.fromCharCode(m + 64) + s
        n = (n - m) / 26
      }
      return s
    },
    /**
     * [s2ab 字符串转字符流]
     * @param  {[type]} s [description]
     * @return {[type]}   [description]
     */
    s2ab(s) {
      var buf = new ArrayBuffer(s.length)
      var view = new Uint8Array(buf)
      for (var i = 0; i !== s.length; ++i) view[i] = s.charCodeAt(i) & 0xff
      return buf
    },
    /**
     * [importf 文件导入]
     * @param  {[type]} obj [description]
     * @return {[type]}     [description]
     */
    importf(obj) {
      console.debug('导入的文件', obj.srcElement.value.split('.')[1])
      if (obj.srcElement.value.split('.')[1] !== 'xlsx') {
        this.messages.push({
          text: '请选择xlsx格式文件！',
          class: 'ambiance ambiance-error'
        })
        return
      }
      let vm = this
      if (!obj.currentTarget.files) {
        return
      }
      var f = obj.currentTarget.files[0]
      var reader = new FileReader()
      reader.onload = function(e) {
        console.debug('数据：', e)
        var data = e.target.result
        if (vm.rABS) {
          vm.wb = XLSX.read(btoa(vm.fixdata(data)), {
            // 手动转化
            type: 'base64'
          })
        } else {
          vm.wb = XLSX.read(data, {
            type: 'binary'
          })
        }
        // console.debug(vm.wb, '导入的文件', JSON.stringify(XLSX.utils.sheet_to_json(vm.wb.Sheets[vm.wb.SheetNames[0]])), XLSX.utils.sheet_to_json(vm.wb.Sheets[vm.wb.SheetNames[0]]))
        vm.collateSata(
          XLSX.utils.sheet_to_json(vm.wb.Sheets[vm.wb.SheetNames[0]])
        )
        vm.wb = null
      }
      if (vm.rABS) {
        reader.readAsArrayBuffer(f)
      } else {
        reader.readAsBinaryString(f)
      }
    },
    // /**
    //  * [noty 加载等待窗]
    //  * @return {[type]} [description]
    //  */
    // noty() {
    //   Noty({
    //     text: '',
    //     layout: 'topRight',
    //     timeout: 2000,
    //     type: 'success',
    //     dismissQueue: false,
    //     template:
    //       '<div class="text-center" style="height:40px;line-height:40px;"><i class="fa fa-spin fa-spinner"></i> Loading...</div>'
    //   })
    // },
    /**
     * [collateSata 整理导入或导出的数据]
     * @param  {[type]} downloadExl [description]
     * @return {[type]}             [description]
     */
    collateSata(downloadExl) {
      // console.debug('整理数据', downloadExl)
      let vm = this
      var uploadData
      if (!vm.propertyArray) {
        // 判断是否需要整理导出或导出的数据
        uploadData = vm.xlsxDataArray
        if (downloadExl) {
          // 判断导出的文件是否存在
          vm.uploadData = uploadData
          vm.isShow = true // 确认导出的数据的弹窗
          // window.$.noty.closeAll()
        } else {
          vm.downloadExl(uploadData)
        }
        return
      }
      if (downloadExl) {
        // 判断导出的文件是否存在
        uploadData = downloadExl
      } else {
        uploadData = vm.xlsxDataArray
      }
      var neatenUploadData = []
      uploadData.map((data, index) => {
        var item = !index && !downloadExl ? vm.addDefault(data) : data
        // console.debug(index + '单个信息：', item)
        var itemObj = vm.getProperty(item)
        // console.debug('整理后单个信息：', itemObj)
        neatenUploadData.push(itemObj)
      })
      // console.debug(neatenUploadData)
      if (downloadExl) {
        // 判断导出的文件是否存在
        vm.uploadData = neatenUploadData
        vm.isShow = true // 确认导出的数据的弹窗
        // window.$.noty.closeAll()
      } else {
        vm.downloadExl(neatenUploadData)
      }
    },
    /**
     * [addDefault 给第一条数据添加默认属性]
     * @param {[type]} data [description]
     */
    addDefault(data) {
      let vm = this
      var itemObj = {}
      vm.propertyArray.map((property, i) => {
        itemObj[property.key] = data[property.key] || ''
      })
      return itemObj
    },
    /**
     * [getProperty 获取上传的单条数据的对象]
     * @param  {[type]} data [description]
     * @return {[type]}      [description]
     */
    getProperty(data) {
      var vm = this
      var itemObj = {}
      var item
      for (item in data) {
        // console.debug('item:', item, 'data[item]:', data[item])
        var value = data[item]
        var newKey = null
        var importOrExport
        vm.propertyArray.map((property, i) => {
          switch (item) {
            case property.textKey: // 导入
              newKey = property.key
              importOrExport = true
              break
            case property.key: // 导出
              newKey = property.textKey
              importOrExport = false
              break
          }
          if (newKey) {
            var newValue = null
            switch (property.type) {
              case 'department': // 部门
                newValue = value
                vm.departmentArray.map((depart, departIndex) => {
                  if (depart.name === newValue && importOrExport) {
                    itemObj['deptId'] = depart.id
                  }
                })
                break
              case 'equipment': // 项目
                newValue = value
                vm.equipments.map((equip, equipIndex) => {
                  if (equip.name === newValue && importOrExport) {
                    itemObj['equipmentId'] = equip.id
                  }
                })
                break
              case 'string': // 字符串
                newValue = value
                break
              case 'number': // 数字
                newValue = parseInt(value)
                break
              case 'date': // 时间
                newValue = value
                  ? importOrExport
                    ? Moment(value)
                        .utc()
                        .valueOf()
                    : Moment(value).format('YYYY/MM/DD HH:mm:ss')
                  : ''
                break
              case 'editOptions': // 需要转换的字符
                var editOptions = JSON.parse(property.editOptions)
                // newValue = editOptions[value]
                var edit
                for (edit in editOptions) {
                  var editValue = editOptions[edit]
                  switch (value) {
                    case edit: // 导入
                      newValue = editValue
                      break
                    case editValue: // 导出
                      newValue = edit
                      break
                  }
                }
                break
              case 'definition':
                newValue = []
                if (importOrExport) {
                  if (!data[property.textKey]) {
                    console.debug('无自定义数据')
                    break
                  }
                  vm.isShowDetails = true
                  vm.detailInfoKey = newKey
                  console.debug('导入', data[property.textKey])
                  var detailInfoString = data[property.textKey].split('\n ')
                  console.debug('自定义字段：', detailInfoString)
                  detailInfoString.map((item, i) => {
                    if (item) {
                      var itemArray = item.split(':')
                      var oneItem = {
                        key: itemArray[0],
                        val: itemArray[1] || ''
                      }
                      newValue.push(oneItem)
                    }
                  })
                } else {
                  if (!data[property.key]) {
                    console.debug('无自定义数据')
                    break
                  }
                  console.debug('导出')
                  var detailInfoArray = JSON.parse(data[property.key]) || []
                  detailInfoArray.map((item, i) => {
                    if (item.val) {
                      newValue = newValue + item.key + ':' + item.val + '\n '
                    }
                    // itemObj[item.key] = item.val || ''
                  })
                }
                console.debug('自定义数据：', newValue)
                break
            }
            itemObj[newKey] = newValue || ''
            newKey = null
          }
        })
      }
      return itemObj
    },
    /**
     * [fixdata 文件流转BinaryString]
     * @param  {[type]} data [description]
     * @return {[type]}      [description]
     */
    fixdata(data) {
      var o = ''
      var l = 0
      var w = 10240
      for (; l < data.byteLength / w; ++l)
        o += String.fromCharCode.apply(
          null,
          new Uint8Array(data.slice(l * w, l * w + w))
        )
      o += String.fromCharCode.apply(null, new Uint8Array(data.slice(l * w)))
      return o
    }
  }
}
</script>
<style scoped>
.el-table >>> .style-red-row {
  /* color: #c0c4cc; */
  cursor: not-allowed;
  background-image: none;
  background-color: #ff3b0059;
  border-color: #ebeef5;
}
</style>

<style type="text/css">
.fileinput-button {
  position: relative;
  display: inline-block;
  overflow: hidden;
}

.fileinput-button input {
  position: absolute;
  right: 0px;
  top: 0px;
  opacity: 0;
  -ms-filter: 'alpha(opacity=0)';
}
</style>
