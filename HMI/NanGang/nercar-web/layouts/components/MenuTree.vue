<template>
  <div>
    <client-only>
      <template v-for="menu in menuData">
        <el-submenu
          v-if="menu.children && menu.children.length"
          :key="menu.index"
          :index="menu.id">
          <template slot="title">
            <i
              v-if="menu.id.indexOf('-') <= 0"
              :class="menu.icon"/>
            <span slot="title">{{ menu.name }}</span>
          </template>
          <menu-tree :menu-data="menu.children"/>
        </el-submenu>
        <el-menu-item
          v-else
          :key="menu.index"
          :index="menu.id"
          :route="{ path: menu.url}"
          class="pos-par"
        >
          <em class="left-boder"/>
          <i
            v-if="menu.id.indexOf('-') <= 0"
            :class="menu.icon" />
          <span slot="title">{{ menu.name }}</span>
        </el-menu-item>
      </template>
    </client-only>
  </div>
</template>

<script>
export default {
  name: 'MenuTree',
  props: {
    menuData: {
      require: true, //必要
      type: Array,
      default: function() {
        return {}
      }
    }
  },
  methods: {}
}
</script>

<style lang="less">
.el-menu-item {
  &.is-active {
    > span {
      font-weight: 700;
      letter-spacing: 1px;
      color: #4c9fff;
    }
    > i {
      color: #4c9fff;
    }
    .left-boder {
      height: 50%;
      width: 4px;
      background-color: #4c9fff;
      position: absolute;
      left: 6px;
      top: 25%;
      border-radius: 2px;
    }
  }
}
</style>
