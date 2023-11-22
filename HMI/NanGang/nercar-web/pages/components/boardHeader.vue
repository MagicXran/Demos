<template>
  <div class="header">
    <div class="logo">
      <img
        src="../../assets/logo-list.png"
        alt="logo">
    </div>
    <div class="companylogo">
      <img
        src="../../assets/board_img/nercarfont.png"
        alt="logo">
    </div>
    <div class="time">{{ realtime }}</div>
    <p>{{ title }}</p>
  </div>
</template>

<script>
import moment from 'moment'
export default {
  name: 'BoardHeader',
  props: {
    title: {
      type: String,
      default: ''
    }
  },
  data() {
    return {
      realtime: moment().format('YYYY-MM-DD HH:mm'),
      timer: null
    }
  },
  mounted() {
    this.timer = setInterval(() => {
      this.getReaTime()
    }, 1000)
  },
  destroyed() {
    this.timer = null
  },
  methods: {
    getReaTime() {
      this.realtime = moment().format('YYYY-MM-DD HH:mm')
    }
  }
}
</script>

<style scoped lang="less">
.header {
  width: 100%;
  height: 93px;
  padding: 11px;
  background: url('../../assets/board_img/header_bg.png') no-repeat;
  text-align: center;
  line-height: 53px;
  overflow: hidden;
  position: relative;
  .logo {
    //width: 125px;
    height: 35px;
    display: block;
    margin-left: 20px;
    position: absolute;
    left: 20px;
    > img {
      display: block;
      width: 100%;
      height: 100%;
    }
  }
  .companylogo {
    width: auto;
    height: 35px;
    display: block;
    position: absolute;
    right: 35px;
    > img {
      display: block;
      //width: 100%;
      height: 100%;
    }
  }
  .time {
    position: absolute;
    left: 100px;
    width: 136px;
    height: 36px;
    margin-left: 60px;
    background: url('../../assets/board_img/time_bg.png') no-repeat;
    background-size: 100% 100%;
    font-size: 14px;
    line-height: 36px;
  }
  p {
    font-weight: 900;
    font-size: 38px;
    letter-spacing: 2px;
    background: linear-gradient(360deg, #87daff 0%, #ffffff 100%);
    background-clip: text;
  }
}
</style>
