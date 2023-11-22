/*
@author：脚本
@email: miaomia0mia0@163.com
@date：2022/6/9  15:52
@name：track.js
@product：WebStorm
@describe: Please add description
 */
let staticData = {
  realGdLen: {
    one: 156.24,
    two: 375.45,
    three: 422
  },
  pageGdLen: {
    one: 667,
    two: 1472,
    three: 1400
  },
  realGdWid: 3.51,
  pageGdWid: 30,
  realCoolWid: 53,
  realCoolHei: 32,
  pageCoolWid: 180,
  pageHeiWid: 180
}
let tagNameStr = ['lever_b_mat']
class Track {
  // static
  constructor(staticData, realData, tagNameStr) {
    this.staticData = staticData
    this.realData = realData
    this.tagNameStr = tagNameStr
  }
  static countSteelLeng() {
    console.log('static')
  }
  getTrackOneData() {
    //return 辊道一上的板坯信息数组
    let [tagList, result] = [this.realData[this.tagNameStr[0]], []]
    for (let i = 0; i < tagList.length; i++) {
      result.push({
        width: '',
        height: '',
        tailpos: '',
        plateno: '',
        platethk: '',
        platewid: '',
        platelen: '',
        platewet: '',
        cbdec: ''
      })
    }
    this.countSteelLeng()
  }
}
