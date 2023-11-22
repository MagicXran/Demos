<template>
  <div>
    <el-pagination
      :page-size="pageSize"
      :total="total"
      :align="align"
      :current-page="currentPage"
      layout="total, prev, pager, next,jumper"
      @size-change="handleSizeChange"
      @prev-click="prevClick"
      @next-click="nextClick"
      @current-change="handleCurrentChange"/>
  </div>
</template>

<script>
export default {
  name: 'SimplePagination',
  props: {
    pageSize: {
      type: Number,
      default: 0
    },
    total: {
      type: Number,
      default: 100
    },
    align: {
      type: String,
      default: 'right'
    },
    currentPage: {
      type: Number,
      default: 0
    }
  },
  methods: {
    handleSizeChange(val) {
      this.$emit('handleSizeChangeFn', val)
    },
    handleCurrentChange(val) {
      this.$emit('handleCurrentChangeFn', val)
    },
    prevClick(val) {
      this.$emit('prevClickFn', val)
    },
    nextClick(val) {
      this.$emit('nextClickFn', val)
    }
  }
}
</script>

<style scoped>
</style>
