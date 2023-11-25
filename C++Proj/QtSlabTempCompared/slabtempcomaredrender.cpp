//
// Created by ZDxia on 2023/10/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SlabTempComaredRender.h" resolved

#include <iostream>


#include <QChart>
#include <QChartView>
#include <QValueAxis>

#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>


#include "slabtempcomaredrender.h"
#include "ui_SlabTempComaredRender.h"

#include "temp_calc.h"
#include "SlabTempCalDll.h"

#include "universal_toolbox.hpp"

#include <io.h>
#include <ctime>
#include <cstdio>
#include <fcntl.h>
#include <sys/stat.h>
#include <QSplineSeries>
#include <QToolTip>
#include <QTableWidget>


#define LOG_ERROR(errMsg, errCode)    do {        \
    char  _errBuff[256]={'\0'};                    \
    char  _dateBuff[32]={'\0'};                    \
    char  _strPath[MAX_PATH]={'\0'};            \
    DWORD _errNum = errCode;                    \
    time_t _now = time(NULL);                    \
    strftime(_dateBuff, sizeof(_dateBuff), "%Y-%m-%d %H:%M:%S", localtime(&_now));    \
    strcpy(_strPath, "./");                    \
    strcat(_strPath, "slabtempinfos(");            \
    strncpy(_strPath+(int)strlen(_strPath), _dateBuff, 10);    \
    strcat(_strPath, ").Log");                    \
    int     _hFile = _open( _strPath, _O_WRONLY|_O_CREAT|_O_APPEND, _S_IREAD|_S_IWRITE ); \
    if ( _hFile != -1 )  {                        \
        sprintf_s(_errBuff, sizeof(_errBuff), " <%s> Line: %d, ErrNum: %d, %s.\n", _dateBuff, __LINE__, _errNum, errMsg );    \
        _write(_hFile, _errBuff, strlen(_errBuff));    \
        _close(_hFile);                                \
    }                                                \
}while(0)

// 引用命名空间
QT_CHARTS_USE_NAMESPACE

SlabTempComaredRender::SlabTempComaredRender(QWidget *parent) : QWidget(parent), ui(new Ui::SlabTempComaredRender) {
    ui->setupUi(this);

    auto chart = new QChart();
//    chart->createDefaultAxes(); //不用
    chart->setParent(this);
    chart->setTitle("板坯温度对比");
    chart->setAnimationOptions(QChart::AllAnimations);
    //隐藏背景
    chart->setBackgroundVisible(false);
    //设置外边界全部为0
    chart->setContentsMargins(0, 0, 0, 0);
    //设置内边界全部为0
    chart->setMargins(QMargins(0, 0, 0, 0));
    //设置背景区域无圆角
    chart->setBackgroundRoundness(0);


    auto *series_new = new QSplineSeries();
    series_new->setName(QString("新系统数据"));
    series_new->setUseOpenGL(true);
    series_new->setColor(QColor("#2b8a3e")); //深绿色
    series_new->setPointsVisible(true);

    auto *series_old = new QSplineSeries();
    series_old->setName(QString("老系统数据"));
    series_old->setUseOpenGL(true);
    series_old->setColor(QColor("#1864ab")); //蓝色
    series_old->setPointsVisible(true);


    auto *series_new_calc = new QSplineSeries();
    series_new_calc->setName(QString("模型计算后"));
    series_new_calc->setUseOpenGL(true);
    series_new_calc->setColor(QColor("#69db7c")); //浅绿
    series_new_calc->setPointsVisible(true);

    auto *series_1 = new QSplineSeries();
    series_1->setName(QString("一加段下部温度临界"));
    series_1->setUseOpenGL(true);
    series_1->setColor(QColor("#ff6b6b")); //红色

    auto *series_2 = new QSplineSeries();
    series_2->setName(QString("二加段下部温度临界"));
    series_2->setUseOpenGL(true);
    series_2->setColor(QColor("#f03e3e")); //红色

    auto *series_3 = new QSplineSeries();
    series_3->setName(QString("均热段下部温度临界"));
    series_3->setUseOpenGL(true);
    series_3->setColor(QColor("#c92a2a")); //红色
//    series_3->setPen(QPen(Qt::NoPen));//画出的点不带轮廓



    //创建坐标轴
    //1. 先建立 QChart 对象
    //2. 建立 QLineSeries 或者其他的 Series
    //3. 建立 QValueAxis 或者其他的 Axis 对象
    //4. QChart 对象 用 addSeries 添加 QLineSeries 对象
    //5. QLineSeries 用 attachAxis 绑定 Axis 对象
    //6. 给 QLineSeries 对象添加数据
    auto axisX = new QValueAxis();
    axisX->setTitleText("点");
    axisX->applyNiceNumbers();
    axisX->setMax(50000);
    axisX->setLabelFormat("%u");
    axisX->setGridLineVisible(true);//显示坐标轴的网格线，便于观察
    axisX->setTickCount(4);//x轴由4个值分段，即分为3段
    axisX->setMinorTickCount(4);//每一段添加4个值再分一次，即每一段分成5分


    auto axisY = new QValueAxis();
    axisY->setTitleText("温度");
    axisY->applyNiceNumbers();
    axisY->setRange(0, 1500);
    axisY->setLabelFormat("%u");
    axisY->setGridLineVisible(true);//显示坐标轴的网格线，便于观察
    axisY->setTickCount(4);
    axisY->setMinorTickCount(4);//每一段添加4个值再分一次，即每一段分成5分

    chart->addSeries(series_new);
    chart->addSeries(series_old);
    chart->addSeries(series_new_calc);
    chart->addSeries(series_1);
    chart->addSeries(series_2);
    chart->addSeries(series_3);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series_3->attachAxis(axisX);
    series_3->attachAxis(axisY);
    series_2->attachAxis(axisX);
    series_2->attachAxis(axisY);
    series_1->attachAxis(axisX);
    series_1->attachAxis(axisY);
    series_old->attachAxis(axisX);
    series_old->attachAxis(axisY);
    series_new->attachAxis(axisX);
    series_new->attachAxis(axisY);
    series_new_calc->attachAxis(axisX);
    series_new_calc->attachAxis(axisY);


    ui->graphicsView->setChart(chart);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);// 设置 QChartView 渲染提示
    ui->graphicsView->setRenderHint(QPainter::TextAntialiasing);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);

    // 初始化二维数组
//    try {
//        m_para = new double *[ROWS];
//        m_old_para = new double *[ROWS];
//        // 分配内存并初始化 temp[1500][6]
//        for (int i = 0; i < ROWS; i++) {
//            m_para[i] = new double[COLS];
//            m_old_para[i] = new double[COLS];
//            for (int j = 0; j < COLS; j++) {
//                m_para[i][j] = 0.0; // 设置初始值为 0.0，可以根据需要进行修改
//                m_old_para[i][j] = 0.0; // 设置初始值为 0.0，可以根据需要进行修改
//            }
//        }
//    } catch (const std::exception &e) {
//        std::cout << "init double[][] is failed!" << e.what() << std::endl;
//    }


    connect(series_new, &QSplineSeries::hovered, this, [this](const QPointF &point, bool state) {
        if (state) {
            QToolTip::showText(QCursor::pos(), QString("新系统[%1,%2]").arg(point.x()).arg(point.y()));
        }
    });

    connect(series_old, &QSplineSeries::hovered, this, [this](const QPointF &point, bool state) {
        if (state) {
            QToolTip::showText(QCursor::pos(), QString("老系统[%1,%2]").arg(point.x()).arg(point.y()));
        }
    });

    connect(series_new_calc, &QSplineSeries::hovered, this, [this](const QPointF &point, bool state) {
        if (state) {
            QToolTip::showText(QCursor::pos(), QString("模型计算后[%1,%2]").arg(point.x()).arg(point.y()));
        }
    });

    connect(series_3, &QSplineSeries::hovered, this, [this](const QPointF &point, bool state) {
        if (state) {
            QToolTip::showText(QCursor::pos(), QString("[%1,%2]").arg(point.x()).arg(point.y()));
        }
    });

    connect(series_2, &QSplineSeries::hovered, this, [this](const QPointF &point, bool state) {
        if (state) {
            QToolTip::showText(QCursor::pos(), QString("[%1,%2]").arg(point.x()).arg(point.y()));
        }
    });

    connect(series_1, &QSplineSeries::hovered, this, [this](const QPointF &point, bool state) {
        if (state) {
            QToolTip::showText(QCursor::pos(), QString("[%1,%2]").arg(point.x()).arg(point.y()));
        }
    });

    // select new files
    connect(ui->sel_new_file_btn, &QPushButton::clicked, this, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, "选择新模型导出的数据文件", "C:/", "所有文件(*.*)");
        if (!fileName.isEmpty()) {
            m_new_file = fileName.toStdString();
            ui->new_path->setText(fileName);
            std::cout << "m_new_file:" << m_new_file << std::endl;

            try {
                m_new_doc.Load(m_new_file);


            } catch (std::exception &e) {
                std::cout << "load new csv is error: " << e.what() << std::endl;
                QMessageBox::warning(this, "load new csv is error",
                                     QString("error in select old files : %1").arg(QString(e.what())));
            }

            int fecno = 1;
            if (fileName.isEmpty() || !(fileName.at(fileName.length() - 5).isDigit())) {
                QMessageBox::warning(this, "文件名错误", "文件名最后一位数字表示炉号,当前文件名不符合规则,默认炉号=1 ");
            } else
                fecno = fileName.at(fileName.length() - 5).digitValue();

            ui->lh_txt->setText(QString::number(fecno));
            std::cout << "fecno: " << fecno << std::endl;

            //各段终点坐标:转炉侧位置：热回收，预热，一加，二加，均热
            switch (fecno) {
                case 1 : {
                    YR = 7290; //相当于 热回收的末端, 预热端的起点
                    YJ = 15650;
                    EJ = 24850;
                    JR = 33550;
                }
                    break;

                case 2 : {
                    YR = 7290;
                    YJ = 15650;
                    EJ = 24850;
                    JR = 33550;
                }
                    break;

                case 3 : {
                    YR = 7290;
                    YJ = 15650;
                    EJ = 24850;
                    JR = 33930;
                }
                    break;

                default: {
                    YR = 7290;
                    YJ = 15650;
                    EJ = 24850;
                    JR = 33550;
                }
                    break;
            }

        }
    });

    // select old files
    connect(ui->sel_old_file_btn, &QPushButton::clicked, this, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, "选择老模型导出的数据文件", "C:/", "所有文件(*.*)");
        if (!fileName.isEmpty()) {
            m_old_file = fileName.toStdString();
            ui->old_path->setText(fileName);
            std::cout << "m_old_file:" << m_old_file << std::endl;

            try {
                m_old_doc.Load(m_old_file);
//                m_old_slabs = std::move(m_old_doc.GetColumn<std::string>("slabno")); //23240753580400
//                std::cout << "m_old_slabs: " << m_old_slabs.size() << std::endl;

            } catch (std::exception &e) {
                std::cout << "load old csv is error: " << e.what() << std::endl;
                QMessageBox::warning(this, "load old csv is error",
                                     QString("error in select old files : %1").arg(QString(e.what())));

            }

        }
    });


    // 失去焦点触发
    auto lose_focus = [this]() {

        m_new_datas.clear();
        m_old_datas.clear();

        auto slabno = ui->coil_id_txt->text();
        std::cout << "editingFinished,slabno: " << slabno.toStdString() << std::endl;

        if (ui->coil_id_txt->text().length() == SLAB_NO_LEN) {
            //读取指定板坯号对应参数
            if (m_new_file.empty() || m_old_file.empty()) { QMessageBox::warning(this, "无数据", "请先选择数据文件"); }
            else {
                // read new csv
                try {

//                    reset data
                    {
                        ui->rh_txt->clear();
                        ui->yr_txt->clear();
                        ui->yj_txt->clear();
                        ui->ej_txt->clear();
                        ui->jr_txt->clear();
//                        ui->wxfl_txt->clear();
                        ui->wxdm_txt->clear();
                        ui->zlwd_txt->clear();
                        ui->bphd_txt->clear();
                    }

                    int only_once = true;

                    // 获取列数
                    auto numCols = m_new_doc.GetColumnCount();
                    auto numRows = m_new_doc.GetRowCount();
                    std::cout << "new csv cols:" << numCols << std::endl;
                    std::cout << "new csv rows:" << numRows << std::endl;


                    // 板坯数量
                    int slab_nums = 0;

                    // 遍历每一行
                    for (int row = 1; row < numRows; ++row) {
                        // 获取 "SLABNO" 列的值
                        auto slabnoValue = m_new_doc.GetCell<std::string>(0, row);
                        uni_box::utils::trimBlank(slabnoValue);

                        auto input = slabno.toStdString();
                        uni_box::utils::trimBlank(input);

                        // 如果 "SLABNO" 列的值为 slabno
                        if (slabnoValue == input) {

                            if (only_once) {
                                LOG_ERROR("新系统数据:.....................................", 0);
                                LOG_ERROR(slabno.toStdString().c_str(), 0);
                            }
                            try {

                                only_once = false;
                                //自动展示
                                if (slab_nums == 10) {

                                    ui->rh_txt->setText(
                                            QString::number(m_new_doc.GetCell<double>("THERMCORRPREUPL", row)));
                                    ui->yr_txt->setText(
                                            QString::number(m_new_doc.GetCell<double>("THERMCORRPREUPR", row)));
                                    ui->yj_txt->setText(
                                            QString::number(m_new_doc.GetCell<double>("THERMCORRFIRUPL", row)));
                                    ui->ej_txt->setText(
                                            QString::number(m_new_doc.GetCell<double>("THERMCORRSECUPL", row)));
                                    ui->jr_txt->setText(
                                            QString::number(m_new_doc.GetCell<double>("THERMCORRSOAKUPL", row)));
                                    ui->wxfl_txt->setText(QString("0"));
                                    ui->wxdm_txt->setText(
                                            QString::fromStdString(m_new_doc.GetCell<std::string>("QUATYPE", row)));
                                    ui->zlwd_txt->setText(QString::number(m_new_doc.GetCell<double>(13, row)));
                                    ui->bphd_txt->setText(QString::number(m_new_doc.GetCell<double>(7, row)));
                                }

                                auto TEMP_AVE = m_new_doc.GetCell<double>(72, row); //当前温度
                                auto DIACHARGE_AVE = m_new_doc.GetCell<double>(75, row); //当前温度
                                auto SLABCHARGEDISX = m_new_doc.GetCell<double>(12, row); //位置

                                THERMEAS_PRE_UL = m_new_doc.GetCell<double>(15, row); //位置
                                THERMEAS_PRE_UR = m_new_doc.GetCell<double>(16, row); //位置
                                THERMEAS_PRE_DL = m_new_doc.GetCell<double>(17, row); //位置
                                THERMEAS_PRE_DR = m_new_doc.GetCell<double>(18, row); //位置
                                THERMEAS_FIR_UL = m_new_doc.GetCell<double>(19, row); //位置
                                THERMEAS_FIR_UR = m_new_doc.GetCell<double>(20, row); //位置
                                THERMEAS_FIR_DL = m_new_doc.GetCell<double>(21, row); //位置
                                THERMEAS_FIR_DR = m_new_doc.GetCell<double>(22, row); //位置
                                THERMEAS_SEC_UL = m_new_doc.GetCell<double>(23, row); //位置
                                THERMEAS_SEC_UR = m_new_doc.GetCell<double>(24, row); //位置
                                THERMEAS_SEC_DL = m_new_doc.GetCell<double>(25, row); //位置
                                THERMEAS_SEC_DR = m_new_doc.GetCell<double>(26, row); //位置
                                THERMEAS_SOA_UL = m_new_doc.GetCell<double>(27, row); //位置
                                THERMEAS_SOA_UR = m_new_doc.GetCell<double>(28, row); //位置
                                THERMEAS_SOA_DL = m_new_doc.GetCell<double>(29, row); //位置
                                THERMEAS_SOA_DR = m_new_doc.GetCell<double>(30, row); //位置


                                FCETEMPMEASUP = m_new_doc.GetCell<double>(47, row); //位置
                                FCETEMPMEASDN = m_new_doc.GetCell<double>(48, row); //位置

                                if (SLABCHARGEDISX >= YR && SLABCHARGEDISX < YJ) {
                                    m_para[slab_nums][0] = (THERMEAS_PRE_UL > THERMEAS_PRE_UR) ? THERMEAS_PRE_UL
                                                                                               : THERMEAS_PRE_UR;
                                    m_para[slab_nums][1] = (THERMEAS_PRE_DL > THERMEAS_PRE_DR) ? THERMEAS_PRE_DL
                                                                                               : THERMEAS_PRE_DR;
                                } else if (SLABCHARGEDISX >= YJ && SLABCHARGEDISX < EJ) {
                                    m_para[slab_nums][0] = (THERMEAS_FIR_UL > THERMEAS_FIR_UR) ? THERMEAS_FIR_UL
                                                                                               : THERMEAS_FIR_UR;
                                    m_para[slab_nums][1] = (THERMEAS_FIR_DL > THERMEAS_FIR_DR) ? THERMEAS_FIR_DL
                                                                                               : THERMEAS_FIR_DR;

                                    if (dup[1] == 0) {
//                                        dup[1] = slab_nums;
                                        dup[1] = slab_nums;
                                        dup_slabs[1] = SLABCHARGEDISX;
                                        templs_dup[1] = m_para[slab_nums][1];
                                    }
                                } else if (SLABCHARGEDISX >= EJ && SLABCHARGEDISX < JR) {
                                    m_para[slab_nums][0] = (THERMEAS_SEC_UL > THERMEAS_SEC_UR) ? THERMEAS_SEC_UL
                                                                                               : THERMEAS_SEC_UR;
                                    m_para[slab_nums][1] = (THERMEAS_SEC_DL > THERMEAS_SEC_DR) ? THERMEAS_SEC_DL
                                                                                               : THERMEAS_SEC_DR;

                                    if (dup[2] == 0) {
                                        dup[2] = slab_nums;
                                        templs_dup[2] = m_para[slab_nums][1];
                                        dup_slabs[2] = SLABCHARGEDISX;
                                    }
                                } else if (SLABCHARGEDISX >= JR) {
                                    m_para[slab_nums][0] = (THERMEAS_SOA_UL > THERMEAS_SOA_UR) ? THERMEAS_SOA_UL
                                                                                               : THERMEAS_SOA_UR;
                                    m_para[slab_nums][1] = (THERMEAS_SOA_DL > THERMEAS_SOA_DR) ? THERMEAS_SOA_DL
                                                                                               : THERMEAS_SOA_DR;

                                    if (dup[3] == 0) {
                                        dup[3] = slab_nums;
                                        dup_slabs[3] = SLABCHARGEDISX;
                                        templs_dup[3] = m_para[slab_nums][1];
                                    }
                                } else if (SLABCHARGEDISX < YR) {
                                    m_para[slab_nums][0] = FCETEMPMEASUP; //热回收段
                                    m_para[slab_nums][1] = FCETEMPMEASDN;

                                    if (dup[4] == 0) {
                                        dup[4] = slab_nums;
                                        dup_slabs[4] = SLABCHARGEDISX;
                                        templs_dup[4] = m_para[slab_nums][1];
                                    }
                                }
                                m_para[slab_nums][2] = SLABCHARGEDISX;
                                m_para[slab_nums][3] = TEMP_AVE;
                                m_para[slab_nums][5] = DIACHARGE_AVE;//改为传DIACHARGE_AVE

                                m_new_datas.push_back(QPointF(SLABCHARGEDISX, TEMP_AVE));
//                                series_new->append(slab_nums, TEMP_AVE);

                                LOG_ERROR(uni_box::utils::string_format(
                                        "slab_nums=%d,,m_para[0~5]=%lf,%lf,%lf,%lf,%lf,%lf", slab_nums,
                                        m_para[slab_nums][0], m_para[slab_nums][1], m_para[slab_nums][2],
                                        m_para[slab_nums][3], m_para[slab_nums][4], m_para[slab_nums][5]).c_str(), 0);


                                slab_nums = slab_nums + 1;

                            }

                            catch (const std::exception &e) {
                                std::cout << "error in assign new value:" << e.what() << std::endl;
                            }

                        }

                    }

                    std::cout << "new slab [" << slabno.toStdString() << "] nums: " << slab_nums << std::endl;

                    LOG_ERROR(uni_box::utils::string_format("dup[1]=%d,dup[2]=%d,dup[3]=%d,dup[4]=%d", dup[1], dup[2],
                                                            dup[3], dup[4]).c_str(), 0);


                    LOG_ERROR(uni_box::utils::string_format("templs_dup[0~5]=%f,%f,%f,%f,%f,%f", templs_dup[0],
                                                            templs_dup[1], templs_dup[2], templs_dup[3], templs_dup[4],
                                                            templs_dup[5]).c_str(), 0);

                    if (slab_nums < 1) {
                        ui->rh_txt->clear();
                        ui->yr_txt->clear();
                        ui->yj_txt->clear();
                        ui->ej_txt->clear();
                        ui->jr_txt->clear();
                        ui->wxfl_txt->clear();
                        ui->wxdm_txt->clear();
                        ui->zlwd_txt->clear();
                        ui->bphd_txt->clear();
                        QMessageBox::warning(this, "无信息", "无此板坯信息,请确认板坯号是否存在!");
                    }

                    m_slab_nums = slab_nums;

                } catch (std::exception &e) {
                    std::cout << "error in read new csv:" << e.what() << std::endl;
                    QMessageBox::warning(this, "错误", QString("Read new csv is error: %1").arg(QString(e.what())));
                }


                //read old csv
                try {
                    // 获取列数
                    auto numCols = m_old_doc.GetColumnCount();
                    auto numRows = m_old_doc.GetRowCount();
                    std::cout << "old csv cols:" << numCols << std::endl;
                    std::cout << "old csv rows:" << numRows << std::endl;

                    // 板坯数量
                    int slab_nums = 0;

                    LOG_ERROR("老系统数据...................", 0);

                    // 遍历每一行
                    for (int row = 1; row < numRows; ++row) {
                        // 获取 "SLABNO" 列的值
                        auto slabnoValue = m_old_doc.GetCell<std::string>(0, row);
                        uni_box::utils::trimBlank(slabnoValue);

                        auto input = slabno.toStdString();
                        uni_box::utils::trimBlank(input);

                        // 如果 "SLABNO" 列的值为 slabno
                        if (slabnoValue == input) {
                            try {

                                auto TEMP_AVE = m_old_doc.GetCell<double>(66, row); //当前温度
                                auto SLABCHARGEDISX2 = m_old_doc.GetCell<int>(4, row); //位置

                                if (SLABCHARGEDISX2 >= YJ && SLABCHARGEDISX2 < EJ) {
                                    if (dup2[1] == 0) {
                                        dup2[1] = 1;
                                        posls[1] = SLABCHARGEDISX2;
                                        templs[1] = TEMP_AVE;
                                    } else {
                                        if (posls[1] == SLABCHARGEDISX2 && TEMP_AVE > templs[1]) {
                                            templs[1] = TEMP_AVE;
                                        }
                                    }


                                } else if (SLABCHARGEDISX2 >= EJ && SLABCHARGEDISX2 < JR) {
                                    if (dup2[2] == 0) {
                                        dup2[2] = 1;
                                        posls[2] = SLABCHARGEDISX2;
                                        templs[2] = TEMP_AVE;
                                    } else {
                                        if (posls[2] == SLABCHARGEDISX2 && TEMP_AVE > templs[1]) {
                                            templs[2] = TEMP_AVE;
                                        }
                                    }

                                } else if (SLABCHARGEDISX2 >= JR) {
                                    if (dup2[3] == 0) {
                                        dup2[3] = 1;
                                        posls[3] = SLABCHARGEDISX2;
                                        templs[3] = TEMP_AVE;
                                    } else {
                                        if (posls[3] == SLABCHARGEDISX2 && TEMP_AVE > templs[1]) {
                                            templs[3] = TEMP_AVE;
                                        }
                                    }

                                }


                                m_old_para[slab_nums][3] = TEMP_AVE;
//                                series_old->append(slab_nums, TEMP_AVE);
                                m_old_datas.push_back(QPointF(SLABCHARGEDISX2, TEMP_AVE));


                                LOG_ERROR(uni_box::utils::format("slab_nums=%d,pos=%d, m_old_para[slab_nums][3]=%lf",
                                                                 slab_nums, SLABCHARGEDISX2,
                                                                 m_old_para[slab_nums][3]).c_str(), 0);

                                slab_nums = slab_nums + 1;

                            }

                            catch (const std::exception &e) {
                                std::cout << "error in  assign old  value:" << e.what() << std::endl;
                            }

                        }
                    }
                    m_slab_oldnums = slab_nums;
                    std::cout << "old slab [" << slabno.toStdString() << "] nums: " << slab_nums << std::endl;


                } catch (const std::exception &e) {
                    std::cout << "error in read old csv:" << e.what() << std::endl;
                }

            }
        }

    };

    //QLineEdit 失去焦点
    connect(ui->coil_id_txt, &QLineEdit::editingFinished, this, lose_focus);

    // 重用的绘制函数
    auto commonFunction = [this, series_new_calc, series_1, series_2, series_3, series_old, series_new]() {
        try {
            if (ui->coil_id_txt->text().isEmpty()) {
                QMessageBox::critical(this, "错误", "请输入板坯号，方能开始！");
            } else if (ui->coil_id_txt->text().length() != SLAB_NO_LEN) {
                QMessageBox::warning(this, "长度错误", "板坯号长度为 14 位, 请检查输入!");
                ui->coil_id_txt->clear();
            } else {
                // call dll func
                try {

                    auto WX = ui->wxfl_txt->text().toInt();
                    int cnt = m_slab_nums; //数组长度
                    int m = 6; //数组宽度
                    int matcode = GetMatCode(ui->wxdm_txt->text().toStdString().c_str());
                    int fceno = ui->lh_txt->text().toInt();
                    auto thk = ui->bphd_txt->text().toDouble();
                    auto chargetemp = ui->zlwd_txt->text().toDouble();
                    double COFIX_REC = ui->rh_txt->text().toDouble();
                    double COFIX_PRE = ui->yr_txt->text().toDouble();
                    double COFIX_HEAT1 = ui->yj_txt->text().toDouble();
                    double COFIX_HEAT2 = ui->ej_txt->text().toDouble();
                    double COFIX_SOAK = ui->jr_txt->text().toDouble();

                    LOG_ERROR(uni_box::utils::string_format(
                            "调用Tempcalc,传入参数: WX=%d, cnt=%d, m=%d,matcode=%d,fceno=%d,thk=%f,chargetemp=%f,COFIX_REC=%f,COFIX_PRE=%f,COFIX_HEAT1=%f,COFIX_HEAT2=%f,COFIX_SOAK=%f",
                            WX, cnt, m, matcode, fceno, thk, chargetemp, COFIX_REC, COFIX_PRE, COFIX_HEAT1, COFIX_HEAT2,
                            COFIX_SOAK).c_str(), 0);

                    Tempcalc(WX, *m_para, cnt, m, matcode, fceno, thk, chargetemp, COFIX_REC, COFIX_PRE, COFIX_HEAT1,
                             COFIX_HEAT2, COFIX_SOAK);


                    m_new_calc_datas.clear();
                    for (int tpc = 0; tpc < cnt; tpc++) {
//                        m_new_calc_datas.push_back(QPointF(tpc, m_para[tpc][4]));
                        m_new_calc_datas.push_back(QPointF(m_para[tpc][2], m_para[tpc][4]));
                        LOG_ERROR(uni_box::utils::string_format("调用Tempcalc后,m_para[%d][4]=%f", tpc,
                                                                m_para[tpc][4]).c_str(), 0);
                    }


                    series_new->clear();
                    series_old->clear();
                    series_new_calc->clear();

//                    series_new->replace(m_new_datas);
//                    series_old->replace(m_old_datas);
//                    series_new_calc->replace(m_new_calc_datas);

                    series_new->append(m_new_datas);
                    series_old->append(m_old_datas);
                    series_new_calc->append(m_new_calc_datas);

                    series_1->append(dup_slabs[1], 0);
                    series_1->append(dup_slabs[1], templs_dup[1]);

                    series_2->append(dup_slabs[2], 0);
                    series_2->append(dup_slabs[2], templs_dup[2]);

                    series_3->append(dup_slabs[3], 0);
                    series_3->append(dup_slabs[3], templs_dup[3]);


                    ui->yu_bf_txt->setText(QString::number(m_para[dup[1]][3] - templs[1]));
                    ui->yr_af_txt->setText(QString::number(m_para[dup[1]][4] - templs[1]));

                    ui->yj_bf_txt->setText(QString::number(m_para[dup[2]][3] - templs[2]));
                    ui->yj_af_txt->setText(QString::number(m_para[dup[2]][4] - templs[2]));

                    ui->ej_bf_txt->setText(QString::number(m_para[dup[3]][3] - templs[3]));
                    ui->ej_af_txt->setText(QString::number(m_para[dup[3]][4] - templs[3]));

                    ui->jr_bf_txt->setText(
                            QString::number(m_para[m_slab_nums - 1][3] - m_old_para[m_slab_oldnums - 1][3]));
                    ui->jr_af_txt->setText(
                            QString::number(m_para[m_slab_nums - 1][4] - m_old_para[m_slab_oldnums - 1][3]));

//                            ui->graphicsView->show();

                } catch (const std::exception &e) {
                    std::cout << "error in call Tempcalc:" << e.what() << std::endl;
                }

            }
        } catch (const std::exception &e) {
            std::cout << "error in geneCurve: " << e.what() << std::endl;
        }

    };

    //生成曲线
    connect(ui->gen_curve_btn, &QPushButton::clicked, this, commonFunction);

    //再次生成曲线
    connect(ui->second_gen_btn, &QPushButton::clicked, this, [commonFunction]() {
        LOG_ERROR("点击再次生成按钮...........", 0);
        commonFunction();
    });


    // 展示钢种列表
    auto steelTableWidget = new QTableWidget();
    steelTableWidget->setColumnCount(1);
    steelTableWidget->setWindowTitle("新系统数据中钢种列表");
    steelTableWidget->setHorizontalHeaderLabels({"STEEL"});
    steelTableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);


    // 指定钢种所对应的 板坯列表
    auto slabTableWidget = new QTableWidget();
    slabTableWidget->setColumnCount(1);
    slabTableWidget->setWindowTitle("新系统数据中钢种列表");
    slabTableWidget->setHorizontalHeaderLabels({"SLABNO"});
    slabTableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);


    //双击选中钢种
    connect(steelTableWidget, &QTableWidget::itemDoubleClicked, this, [this, steelTableWidget](QTableWidgetItem *item) {
        if (item->isSelected()) {
            ui->grade_txt->setText(item->text());
        }

        steelTableWidget->close();

    });

    //查询钢种按钮
    connect(ui->search_steel_btn, &QPushButton::clicked, this, [this, steelTableWidget]() {

        if (m_new_file.empty() || m_old_file.empty()) {
            QMessageBox::warning(this, "无数据", "请先选择数据文件");
            return;
        }

        try {
            m_new_steels.clear();
            m_new_slabs.clear();

            // 获取列数
            auto numRows = m_new_doc.GetRowCount();
            // 遍历每一行
            for (int row = 1; row < numRows; ++row) {
                m_new_slabs.push_back(m_new_doc.GetCell<std::string>(0, row));
                m_new_steels.push_back(m_new_doc.GetCell<std::string>(3, row));
            }
        } catch (const std::exception &e) {
            std::cout << "error in 遍历钢种:" << e.what() << std::endl;
        }

//        steelTableWidget->clear();
//        steelTableWidget->setHorizontalHeaderLabels({"STEEL"});

        std::set<std::string> m_uniqueElements;
        for (const auto &element: m_new_steels) {
            m_uniqueElements.insert(element);
        }

        steelTableWidget->setRowCount(m_uniqueElements.size());


        // 输出所有不重复的元素
        int k = 0;
        for (const auto &element: m_uniqueElements) {
            steelTableWidget->setItem(k++, 0, new QTableWidgetItem(QString::fromStdString(element)));
        }

        steelTableWidget->show();


    });

    //点击 查询板坯号按钮
    connect(ui->search_slab_btn, &QPushButton::clicked, this, [this, slabTableWidget]() {

//        slabTableWidget->clear();

        if (m_new_file.empty() || m_old_file.empty() || ui->grade_txt->text().isEmpty() || (m_new_steels.empty())) {
            QMessageBox::warning(this, "无数据", "请保证已选择数据文件且填写要查询的钢种!");
            return;
        }


        //打印指定元素的所有索引,查询指定钢种所有的板坯号
        int index = 0;
        std::set<std::string> slabs;
        for (const auto &element: m_new_steels) {
            if (element == ui->grade_txt->text().trimmed().toStdString()) {
                slabs.insert(m_new_slabs.at(index));
            }
            index++;
        }

        std::cout << "steel_grade:" << ui->grade_txt->text().trimmed().toStdString() << "slabs:" << slabs.size()
                  << std::endl;

        slabTableWidget->setRowCount(slabs.size());

        int k = 0;
        for (const auto &sl: slabs) {
            slabTableWidget->setItem(k++, 0, new QTableWidgetItem(QString::fromStdString(sl)));
        }
        slabTableWidget->show();

    });


    // 双击计算
    connect(slabTableWidget, &QTableWidget::itemDoubleClicked, this,
            [this, slabTableWidget, lose_focus, commonFunction](QTableWidgetItem *item) {
                if (item->isSelected()) {
                    slabTableWidget->close();

                    ui->coil_id_txt->setText(item->text());
                    try {
                        lose_focus();
                        commonFunction();
                    }
                    catch (const std::exception &e) {
                        std::cout << "error -1: " << e.what() << std::endl;
                        LOG_ERROR(e.what(), -1);
                    }
                }


            });


}

SlabTempComaredRender::~SlabTempComaredRender() {

    try {
        delete ui;

        m_new_doc.Clear();
        m_old_file.clear();

        // 删除 temp[1500][6]
//        for (int i = 0; i < ROWS; i++) {
//            delete[] m_para[i];
//            delete[] m_old_para[i];
//        }
//        delete[] m_para;
//        delete[] m_old_para;
    } catch (const std::exception &e) {
        std::cout << "destructor is failed!" << e.what() << std::endl;
    }
}

void SlabTempComaredRender::initChartView() {

    auto chart = new QChart();
    chart->setParent(this);
    chart->setTitle("板坯温度对比");
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).back()->setTitleText("y");
    chart->axes(Qt::Horizontal).back()->setTitleText("x");

    //创建坐标轴
//    auto axisX = new QValueAxis(chart);
//    axisX->setParent(this);
//    axisX->setTitleText("点");
//    auto axisY = new QValueAxis(chart);
//    axisY->setParent(this);
//    axisY->setTitleText("温度");
//
//    chart->addAxis(axisX, Qt::AlignBottom);
//    chart->addAxis(axisY, Qt::AlignLeft);

    chart->setAnimationOptions(QChart::AllAnimations);

    auto view = new QChartView(this);
    chart->setParent(view);

    view->setChart(chart);
    view->setRenderHint(QPainter::Antialiasing);// 设置 QChartView 渲染提示
    view->setRenderHint(QPainter::TextAntialiasing);
    view->setRenderHint(QPainter::SmoothPixmapTransform);

    ui->image_dock->setWidget(view);

}
