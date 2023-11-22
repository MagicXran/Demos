/**

 * @description: 询单状态
 */
export const CustomerOrderInfoStatus = {
  REQUIREMENT: 0, // 需求整理
  COSTING: 1, // 预算编写
  COSTING_FINISHED: 2, // 预算编写完成
  AUDITING: 3, // 询单审批中
  AUDIT_FINISH: 4, // 询单审批完成
  CONTRACT: 5, // 合同签订完成
  FINISH: 6, // 生产完成
  EXPIRED: 7, // 过期
  USELESS: 8 // 已作废
}
/**

 * @description: 采购计划状态
 */
export const PurchasingPlanStatus = {
  REQUIREMENT: 0, // 未发起流程
  AUDITING: 1, // 审批中
  AUDIT_FINISH: 2, // 流程审批完成
  PURCHASING: 3, // 采购中
  NOT_ENOUGH: 4, // 已全部兑现
  FINISHED: 5 // 已部分兑现
}
/**

 * @description: 纵剪状态
 */
export const TmpMaterialStatus = {
  UNPLANNED: 0, // 待分配计划
  PLANNED: 1, // 待生产
  PRE_ONLINE: 2, // 待上线
  IN_PRODUCTION: 3, // 已上线
  FINISHED: 4, // 生产完成
  NO_PLAN: 5, // 无生产计划
  DISCARD: 6 // 废品
}
/**

 * @description: 原料卷状态
 */
export const MaterialStatus = {
  UNPLANNED: 0, // 未分配生产计划
  PLANNED: 1, // 已分配生产计划
  IN_PRODUCTION: 2, // 正在生产
  PLAN_FINISHED: 3, // 生产已完成
  NO_PLAN: 4, // 无订单计划
  DISCARD: 5 // 报废
}
/**

 * @description: 订单状态
 */
export const OrderInfoItemStatus = {
  UNPLANNED: 0, // 未分配生产计划
  PLANNED: 1, // 已分配生产计划
  PRODUCING: 2, // 生产进行中
  FINISHED: 3 // 已完成订单
}
/**

 * @description: 成品状态
 */
export const ProductStatus = {
  UN_PRODUCTION: 0, // 未生产
  PRODUCT_FINISHED: 1, // 生产完成
  PACKAGE: 2, // 打包中
  REPAIRING: 3, // 待修复
  WAIT_FOR_DELIVERY: 4, // 待交货
  DELIVERED: 5, // 已交货
  PRODUCT: 6, // 成品
  DISCARD: 7 // 废品
}

/**
 * @author: tasily_cqs
 * @description: 订单类型
 */
export const OrderInfoItemTypes = {
  COMMON: 0, // 方/矩形管
  VIRTUAL: 1, // 虚拟订单
  U_OPEN: 2, // U肋及其他开口型钢
  TMP_TYPE: 3 // 纵剪加工
}
