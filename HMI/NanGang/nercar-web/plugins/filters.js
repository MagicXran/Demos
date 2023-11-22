import Vue from 'vue'
import moment from 'moment'
Vue.filter('testFilter', (data, p1, p2) => {
  return data + 'filter'
})
Vue.filter('formatDate', (data, p1, p2) => {
  if (data != '') {
    return moment(Number(data)).format(p1)
  }
})
Vue.filter('timestampFormatDate', (data, p1, p2) => {
  let d = timestampFormatDate(data, p1)
  return d
})
//处理数据小数点(特殊需求)
Vue.filter('formatNum', (data, p1, p2) => {
  if (String(data).indexOf('/') != -1) {
    return data
  } else {
    return String(data).substring(0, 5)
  }
})
//下次建议更换时间
Vue.filter('nextCDate', (data, p1, p2) => {
  let time = 0
  if (data.changeTimeStampStr != '') {
    if (data.standBookChangeSchedule.changePeriodUnit == 'M/月') {
      time =
        Number(data.changeTimeStampStr) +
        Number(data.standBookChangeSchedule.changePeriod) *
          30 *
          24 *
          60 *
          60 *
          1000
    } else if (data.standBookChangeSchedule.changePeriodUnit == 'Y/年') {
      time =
        Number(data.changeTimeStampStr) +
        Number(data.standBookChangeSchedule.changePeriod) *
          12 *
          30 *
          24 *
          60 *
          60 *
          1000
    } else if (data.standBookChangeSchedule.changePeriodUnit == 'D/日') {
      time =
        Number(data.changeTimeStampStr) +
        Number(data.standBookChangeSchedule.changePeriod) * 24 * 60 * 60 * 1000
    } else if (data.standBookChangeSchedule.changePeriodUnit == 'S/时') {
      time =
        Number(data.changeTimeStampStr) +
        Number(data.standBookChangeSchedule.changePeriod) * 60 * 60 * 1000
    } else if (data.standBookChangeSchedule.changePeriodUnit == 'M/分') {
      time =
        Number(data.changeTimeStampStr) +
        Number(data.standBookChangeSchedule.changePeriod) * 60 * 60 * 1000
    }
    let timeToString = moment(Number(time)).format('YYYY-MM-DD HH:mm:ss')
    return timeToString
  }
})

Vue.filter('filterZero', value => {
  if (value == 0) {
    return ''
  } else {
    return value
  }
})

//公共函数
Vue.use({
  install(Vue) {
    Vue.prototype.comsys = {
      //表格序号
      tableRowIndex: function($index, currentPage, pageSize) {
        return (currentPage - 1) * pageSize + $index + 1
      },
      //表格斑马线效果
      tabRowClassName: function({ row, rowIndex }) {
        let index = rowIndex + 1
        if (index % 2 == 0) {
          return 'light-row'
        } else {
          return 'dack-row'
        }
      },
      //表格数组处理为区间格式
      tabRange: function(data, val, WeightList) {
        let range = []
        for (var i = 0; i < data.length; i++) {
          let styleSpan = 'font-size: 12px;font-weight: normal'
          if (i == 0) {
            /*if (parseFloat(val) <= parseFloat(data[i])) {
              color = '#ff5a56'
            }
            range.push(
              '<span style="color: ' +
                color +
                '">(-∞, ' +
                data[i] +
                ']-' +
                WeightList[i] +
                '；  </span>'
            )*/
          } else {
            if (
              parseFloat(val) > parseFloat(data[i - 1]) &&
              parseFloat(val) <= parseFloat(data[i])
            ) {
              //color = '#ff5a56'
              styleSpan = 'font-size: 14px;font-weight: bolder; '
            }
            range.push(
              '<span style=" ' +
                styleSpan +
                '">(' +
                data[i - 1] +
                ', ' +
                data[i] +
                ']—' +
                WeightList[i] +
                '；  </span>'
            )
          }
          styleSpan = 'font-size: 12px;font-weight: normal'
          if (i == data.length - 1) {
            if (parseFloat(val) > parseFloat(data[i])) {
              styleSpan = 'font-size: 14px;font-weight: bolder;'
            }
            range.push(
              '<span style="' +
                styleSpan +
                '">(' +
                data[i] +
                ', +∞)—' +
                WeightList[i + 1] +
                '</span>'
            )
          }
        }
        return range.join('')
      }
    }
  }
})
