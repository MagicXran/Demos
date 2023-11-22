<template>
  <div>
    <div v-if="tableHead">
      <div class="layout-search">
        <div class="layout-search-body">
          <slot name="TableHead"/>
        </div>
      </div>
    </div>
    <div class="u-table-main">
      <el-table
        ref="tasilyTable"
        :row-style="tableRowStyle"
        :header-cell-style="tableHeaderColor"
        :data="tableData"
        :row-class-name="rowClassName"
        :span-method="spanMethod"
        :cell-class-name="cellClassName"
        :height="tableHeight"
        :stripe="tableStripe"
        :empty-text="loadInfo"
        :default-sort = "defaultSort"
        border
        @selection-change="handleSelectionChange"
        @row-click="rowClick"
        @expand-change="expandChange"
        @cell-dblclick="cellDblclick"
        @cell-click="cellClick">
        <template slot="empty">
          <i
            class="iconfont icon-shuju5"
            style="font-size: 40px;color:#409eff;"/>
          <p style="color:#409eff;">暂无数据</p>
        </template>
        <el-table-column
          v-if="indexType === 'index'"
          :index="formatterTableDataIndex"
          :type="indexType"
          label="序号"
          align="center"
          width="50"/>
        <el-table-column
          v-if="isShowSelect"
          type="selection"
          align="center"
          fixed />
        <!--数据源-->
        <slot name="TableBody"/>
      </el-table>
    </div>
    <div>
      <div
        v-if="tableFoot"
        class="pagination-border">
        <slot name="TableFoot"/>
      </div>
      <div
        v-show="isPaginationShow"
        class="pagination-border">
        <el-pagination
          :current-page="currentPage"
          :page-sizes="pageSizeList"
          :page-size="pageSize"
          :total="total"
          :pager-count="5"
          class="u-pagination"
          align="right"
          layout="prev, pager, next"
          background
          @size-change="handleSizeChange"
          @current-change="handleCurrentChange" />
      </div>
    </div>
  </div>
</template>

<script>
export default {
  props: {
    // 表格数据格式
    tableData: {
      type: Array,
      default: () => []
    },
    // 表格的字段展示 默认为空数组
    tableHeader: {
      type: Array,
      default: () => []
    },
    isShowSelect: {
      type: Boolean,
      default: false
    },
    // 是否显示分页，默认显示
    isPaginationShow: {
      type: Boolean,
      default: true
    },
    // 是否显示组件头部，默认显示
    tableHead: {
      type: Boolean,
      default: true
    },
    // 是否显示组件底部，默认显示
    tableFoot: {
      type: Boolean,
      default: false
    },
    // 数据的总条数，用于分页
    total: {
      type: Number,
      default: 0
    },
    // 分页，每页的数据项数
    pageSizeList: {
      type: Array,
      default: function() {
        return [5, 10, 20, 30]
      }
    },
    rowClassName: {
      type: Function,
      default: () => {}
    },
    cellClassName: {
      type: Function,
      default: () => {}
    },
    spanMethod: {
      type: Function,
      default: () => {}
    },
    tableHeight: {
      type: [String, Number],
      default: '100%'
    },
    pageSize: {
      type: Number,
      default: 30
    },
    currentPage: {
      type: Number,
      default: 1
    },
    tableStripe: {
      type: Boolean,
      default: true
    },
    loadInfo: {
      type: String,
      default: '暂无数据'
    },
    defaultSort: {
      type: Object,
      default: () => {
        return {}
      }
    },
    indexType: {
      type: String,
      default: 'none'
    }
  },
  data() {
    return {}
  },
  methods: {
    tableRowStyle({ row, rowIndex }) {
      return 'background-color:pink;font-size:15px;'
    },
    tableHeaderColor({ row, rowIndex }) {},
    formatterTableDataIndex(index) {
      var pageIndex = 0
      if (this.pageSize || this.currentPage) {
        var pageIndex = (this.currentPage - 1) * this.pageSize + index + 1
      } else {
        pageIndex = index + 1
      }
      return pageIndex
    },
    /**
     * @author: wangHongFei
     * @description: 行单击事件
     */
    rowClick(data, column) {
      this.$emit('row-click', data, column)
    },
    /**
     * @author: wangHongFei
     * @description: 单元格双击
     */
    cellDblclick(row, cloumn) {
      this.$emit('cell-dblclick', row, cloumn)
    },
    /**
     * @author: wangHongFei
     * @description: 单元格单击
     */
    cellClick(row, cloumn) {
      this.$emit('cell-click', row, cloumn)
    },
    /**
     * @author: wangHongFei
     * @description: 展开行事件
     */
    expandChange(row, expandedRows) {
      this.$emit('expand-change', row, expandedRows)
    },
    /**
     * @author: wangHongFei
     * @description: 每页条数的改变
     */
    handleSizeChange(val) {
      this.$emit('handle-size-change', val)
    },
    /**
     * @author: wangHongFei
     * @description: 切换页码
     */
    handleCurrentChange(val) {
      this.$emit('handle-current-change', val)
    },
    handleSelectionChange(val) {
      this.$emit('handle-selection-change', val)
    },
    clearTableSelect() {
      this.$refs.tasilyTable.clearSelection()
    }
  }
}
</script>

<style scoped>
.u-table-main {
  margin-bottom: 15px;
}
.layout-search {
  height: 30px;
}
/deep/ .el-table__empty-text {
  line-height: 50px;
}
/deep/.el-table__header tr,
/deep/.el-table__header th {
  padding: 0;
  height: 42px;
  font-size: 12px;
}
</style>
