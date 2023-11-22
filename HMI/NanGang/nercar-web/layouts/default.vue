<template>
  <div class="nav">
    <el-container>
      <!--      <el-header>
        <el-row :gutter="20">
          <el-col :span="3">
            <div class="grid-content bg-purple company-info">
              <div class="logo">
                <img
                  src="../assets/logo.png"
                  alt="">
              </div>
              <div class="company"/>
            </div>
          </el-col>
          <el-col :span="18">
            <div class="grid-content bg-purple">
              <div class="search">
                &lt;!&ndash;                <el-input
                  v-model="headerInput"
                  prefix-icon="el-icon-search"
                  placeholder="请输入内容"/>&ndash;&gt;
              </div>
            </div>
          </el-col>
          <el-col :span="3">
            &lt;!&ndash;            <div class="grid-content bg-purple">
              <div class="user-info">
                <ul>
                  <li class="imessage">
                    &lt;!&ndash;                    <el-badge
                      :value="12"
                      class="item">

                      &lt;!&ndash;                      <span class="posi-num"/>&ndash;&gt;
                    </el-badge>&ndash;&gt;

                    <el-badge
                      :value="12"
                      class="item">
                      <i
                        class="el-icon-bell"
                        style="font-size: 20px"/>
                    </el-badge>
                  </li>
                  <li class="portrait">
                    &lt;!&ndash;                    <img
                      src=""
                      alt="">&ndash;&gt;
                  </li>
                  <li class="user-name">
                    <span style="margin-right: 5px;cursor: pointer">张三</span>
                    <el-dropdown>
                      <i
                        class="el-icon-caret-bottom"
                        style="margin-right: 15px"/>
                      <el-dropdown-menu slot="dropdown">
                        <el-dropdown-item>退出登录</el-dropdown-item>
                      </el-dropdown-menu>
                    </el-dropdown>

                  </li>
                </ul>
              </div>
            </div>&ndash;&gt;
          </el-col>
        </el-row>
      </el-header>-->
      <el-container :style="'height:'+(parseInt(windowHeight) - 0)+'px'">
        <el-aside
          width="200px"
          height="100%">
          <div class="logo-list">
            <img
              src="../assets/logo-list.png"
              alt="">
          </div>
          <SideBar/>
        </el-aside>
        <el-main>
          <nuxt />
        </el-main>
      </el-container>
    </el-container>
  </div>
</template>

<script>
import SideBar from '@/layouts/components/SideBar'
export default {
  head() {
    return {}
  },
  components: { SideBar },
  data() {
    return {
      windowHeight: '',
      headerInput: ''
    }
  },
  computed: {},
  watch: {
    $route: {
      handler: function(val, oldVal) {},
      immediate: false
    }
  },

  beforeCreate() {
    // console.log('beforeCreate', this)
  },
  created() {
    // console.log('created', this)
  },
  beforeMount() {
    // console.log('beforeMount', this)
  },
  mounted() {
    console.log('route', $nuxt.$route.name)
    // this.showActive()
    let vm = this
    window.onresize = () => {
      return (() => {
        vm.handleWindowHeight()
      })()
    }
    this.handleWindowHeight()
    this.locationPage()
  },
  beforeUpdate() {},
  updated() {},
  beforeDestroy() {},
  destroyed() {},
  methods: {
    //定时刷新清空缓存 3h
    locationPage() {
      setInterval(() => {
        location.reload()
      }, 1000 * 60 * 60 * 3)
    },
    handleOpenNav(key, keyPath) {
      console.log(key, keyPath)
    },
    handleCloseNav(key, keyPath) {
      console.log(key, keyPath)
    },
    handleWindowHeight() {
      this.windowHeight = document.documentElement.clientHeight
    }
  }
}
</script>
<style scoped lang="less">
.logo-list {
  width: 100%;
  margin-bottom: 20px;
  > img {
    display: block;
    margin: 0 auto 6px;
  }
}
.el-menu {
  font-family: 'Noto Sans SC' !important;
  //padding-right: 10px;
  .is-active {
    background: #0f2a59 !important;
    border-left: 2px solid #b8c2d4;
  }
}
.el-header {
  height: 70px !important;
  line-height: 70px;
  box-shadow: 0 2px 10px 0 rgb(0 0 0 / 10%);
  .company-info {
    width: 260px;

    .logo {
      height: 70px;
      width: auto;
      padding: 10px 8px;
      img {
        display: block;
        width: auto;
        height: 100%;
      }
    }
  }

  .search {
    height: 36px;
    width: 250px;
  }

  .user-info {
    float: right;
    ul {
      li {
        float: left;
        margin-right: 20px;
      }
    }
    .portrait {
      width: 38px;
      height: 38px;
      margin-top: 10px;
      border-radius: 50%;
      background: pink;
    }
    .imessage {
      margin-right: 30px;
    }
  }
}

.el-aside {
  padding-top: 20px;
  background-color: #13356f;
  color: #ffffff;

  .home {
    margin-bottom: 10px;
  }
}

.el-menu {
  border-right: none;
  //padding-left: 10px;

  .el-menu-item {
    font-size: 14px;
    letter-spacing: 1px;
    padding-left: 48px !important;
  }
}
.el-main {
  background-color: #f4f4f5;
}
/deep/ .el-badge__content.is-fixed {
  top: 22px;
}
.nav {
}
</style>
