//
// Created by ZDxia on 2023/10/25.
//

#ifndef QTSLABTEMPCOMPARED_SLABTEMPCOMAREDRENDER_H
#define QTSLABTEMPCOMPARED_SLABTEMPCOMAREDRENDER_H


#define SLAB_NO_LEN  14

#include <QWidget>


#include <vector>
#include <array>
#include <set>
#include "rapidcsv.h"


// 定义二维数组的行和列数
const int ROWS = 300;
const int COLS = 6;

QT_BEGIN_NAMESPACE
namespace Ui { class SlabTempComaredRender; }
QT_END_NAMESPACE

class SlabTempComaredRender : public QWidget {
Q_OBJECT

public:
    explicit SlabTempComaredRender(QWidget *parent = nullptr);

    ~SlabTempComaredRender() override;

    void initChartView();


private:
    Ui::SlabTempComaredRender *ui;

    std::string m_new_file;
    std::string m_old_file;
    std::string m_coil_id;

    rapidcsv::Document m_new_doc;
    rapidcsv::Document m_old_doc;

    //板坯记录数
    int m_slab_nums{0};
    int m_slab_oldnums{0};
    //距离
    int YR{7290};
    int YJ{15650};
    int EJ{24850};
    int JR{33550};


    //温度
    double THERMEAS_PRE_UL{0.0}, THERMEAS_PRE_DL{0.0}, THERMEAS_FIR_UL{0.0}, THERMEAS_FIR_DL{0.0}, THERMEAS_SEC_UL{
            0.0}, THERMEAS_SEC_DL{0.0}, THERMEAS_SOA_UL{0.0}, THERMEAS_SOA_DL{0.0}, FCETEMPMEASUP{0.0}, FCETEMPMEASDN{
            0.0};
    double THERMEAS_PRE_UR{0.0}, THERMEAS_PRE_DR{0.0}, THERMEAS_FIR_UR{0.0}, THERMEAS_FIR_DR{0.0}, THERMEAS_SEC_UR{
            0.0}, THERMEAS_SEC_DR{0.0}, THERMEAS_SOA_UR{0.0}, THERMEAS_SOA_DR{0.0};


    // 加热炉每段位置:dup[0]:预热,dup[1]:一加段开始记录数,dup[2]:二加, dup[3]:均热, dup[4]:热回收段临界记录数
    int dup[5] = {0, 0, 0, 0, 0}; // 距离
    int dup_slabs[5] = {0, 0, 0, 0, 0}; // 板坯数量
    int dup2[5] = {0, 0, 0, 0, 0};

    int posls[5] = {0, 0, 0, 0, 0};
    double templs[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
    double templs_dup[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

    QList<QPointF> m_new_datas;
    QList<QPointF> m_old_datas;
    QList<QPointF> m_new_calc_datas;
    std::vector<std::string> m_new_steels;
    std::vector<std::string> m_new_slabs;
//    std::set<std::string> m_uniqueElements;
    //param
//    std::array<std::vector<double>, ROWS> m_para{};
//    std::array<std::vector<double>, ROWS> m_old_para{};

    double m_para[ROWS][COLS];
    double m_old_para[ROWS][COLS];
//    double **m_para;
//    double **m_old_para;
};


#endif //QTSLABTEMPCOMPARED_SLABTEMPCOMAREDRENDER_H
