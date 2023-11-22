<template>
  <el-row style="margin-bottom: 20px">
    <el-table
      v-loading="loading"
      :data="tableData"
      border
      style="width: 100%">
      <el-table-column
        align="center"
        label="序号"
        type="index"
        width="60"/>
      <el-table-column
        v-for="(item, index) in tableColumns"
        :key="index"
        :prop="item.key"
        :label="item.label"
        :width="item.width"
        align="center"/>
    </el-table>
  </el-row>
</template>

<script>
export default {
  name: 'ManagementTable',
  props: {
    loading: {
      type: Boolean,
      default: false
    },
    tableData: {
      type: Array,
      default() {
        return []
      }
    },
    tableColumns: {
      type: Array,
      default() {
        return []
      }
    }
  }
}
</script>

<style>
.el-table th {
  background-color: #f5f7fa;
}
</style>
