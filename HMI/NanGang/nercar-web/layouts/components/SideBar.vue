<template>
  <el-menu
    router="router"
    default-active="1"
    class="el-menu-vertical-demo"
    @select="handleSelect"
    @open="handleOpenNav"
    @close="handleCloseNav">
    <MenuTree :menu-data="navList"/>
  </el-menu>
</template>

<script>
import MenuTree from '@/layouts/components/MenuTree'

export default {
  name: 'SideBar',
  components: { MenuTree },
  data() {
    return {
      navList: [
        {
          name: '精整主画面',
          id: '1',
          icon: 'el-icon-data-analysis',
          children: [],
          url: 'home'
        },
        {
          name: '子画面跟踪',
          id: '2',
          icon: 'el-icon-data-line',
          url: '',
          children: [
            {
              name: '离线分段剪',
              id: '5-11',
              icon: 'el-icon-menu',
              children: [],
              url: 'lxfdj'
            },
            {
              name: '矫直冷床双边剪',
              id: '2-1',
              icon: 'el-icon-menu',
              children: [],
              url: 'jls'
            },
            {
              name: '1#定尺剪',
              id: '2-2',
              icon: 'el-icon-menu',
              children: [],
              url: '1dcj'
            },
            {
              name: '标印-垛扳',
              id: '2-3',
              icon: 'el-icon-menu',
              children: [],
              url: '1dbj'
            },
            {
              name: '冷床切分剪',
              id: '2-4',
              icon: 'el-icon-menu',
              children: [],
              url: 'lq'
            },
            {
              name: '圆盘剪',
              id: '2-5',
              icon: 'el-icon-menu',
              children: [],
              url: 'ypj'
            },
            {
              name: '2#定尺剪',
              id: '2-6',
              icon: 'el-icon-menu',
              children: [],
              url: '2dcj'
            },
            {
              name: '2#垛扳机',
              id: '2-7',
              icon: 'el-icon-menu',
              children: [],
              url: '2dbj'
            }
          ]
        },
        {
          name: '工艺维护',
          id: '3',
          icon: 'el-icon-date',
          children: [],
          url: 'technologyManage'
        },
        {
          name: '定尺剪测长系统',
          id: '4',
          icon: 'el-icon-c-scale-to-original',
          url: '',
          children: [
            {
              name: '2#定尺剪工作',
              id: '4-1',
              icon: 'el-icon-menu',
              children: [],
              url: 'dcjWorking'
            },
            {
              name: '2#定尺剪历史',
              id: '4-2',
              icon: 'el-icon-menu',
              children: [],
              url: 'dcjHistory'
            }
          ]
        },
        {
          name: '报表实绩',
          id: '5',
          icon: 'el-icon-document-copy',
          children: [
            {
              name: '冷床报表',
              id: '5-1',
              icon: 'el-icon-menu',
              children: [],
              url: 'lcManagement'
            },
            {
              name: '1#双边剪报表',
              id: '5-2',
              icon: 'el-icon-menu',
              children: [],
              url: 'sbjManagement1'
            },
            {
              name: '1#定尺剪报表',
              id: '5-3',
              icon: 'el-icon-menu',
              children: [],
              url: 'dcjManagement1'
            },
            {
              name: '1#子板报表',
              id: '5-4',
              icon: 'el-icon-menu',
              children: [],
              url: 'zbManagement1'
            },
            {
              name: '2#圆盘剪报表',
              id: '5-5',
              icon: 'el-icon-menu',
              children: [],
              url: 'ypjManagement2'
            },
            {
              name: '2#定尺剪报表',
              id: '5-6',
              icon: 'el-icon-menu',
              children: [],
              url: 'dcjManagement2'
            },
            {
              name: '2#子板报表',
              id: '5-7',
              icon: 'el-icon-menu',
              children: [],
              url: 'zbManagement2'
            },
            {
              name: '班组报表',
              id: '5-8',
              icon: 'el-icon-menu',
              children: [],
              url: 'bzManagement1'
            },
            {
              name: '计划表',
              id: '5-9',
              icon: 'el-icon-menu',
              children: [],
              url: 'jhManagement1'
            },
            {
              name: '二线标印实际表',
              id: '5-10',
              icon: 'el-icon-menu',
              children: [],
              url: 'qfjManagement2'
            }
          ],
          url: ''
        },
        {
          name: '报警信息',
          id: '5',
          icon: 'el-icon-warning-outline',
          children: [],
          url: 'alarm'
        },
        {
          name: '统计数据',
          id: '6',
          icon: 'el-icon-pie-chart',
          children: [],
          url: 'statistics'
        }
      ],
      temp: []
    }
  },
  computed: {},
  mounted() {},
  methods: {
    handleOpenNav(key, keyPath) {
      console.log(key, keyPath)
    },
    handleCloseNav(key, keyPath) {
      console.log(key, keyPath)
    },
    handleSelect(key, keyPath) {}
  }
}
</script>

<style lang="less">
.el-aside {
  background-color: #13356f;
}

.el-menu {
  background-color: #13356f;
}
.el-submenu__title:focus,
.el-submenu__title:hover {
  background-color: #172845 !important;
}
.el-submenu__title {
  color: #fff !important;
}

.el-menu-item {
  color: #fff !important;
}

.el-submenu__title i {
  color: #fff;
}
.el-menu-item i {
  color: #fff;
}

.el-menu-item:focus,
.el-menu-item:hover {
  outline: 0;
  background-color: #172845 !important;
}

.el-menu-item.is-active > span {
  font-weight: 700;
  letter-spacing: 1px;
  //color: #4c9fff;
  color: #ffffff;
}
</style>
