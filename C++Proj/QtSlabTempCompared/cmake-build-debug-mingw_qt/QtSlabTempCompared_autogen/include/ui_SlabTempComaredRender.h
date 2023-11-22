/********************************************************************************
** Form generated from reading UI file 'slabtempcomaredrender.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLABTEMPCOMAREDRENDER_H
#define UI_SLABTEMPCOMAREDRENDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qchartview.h>

QT_BEGIN_NAMESPACE

class Ui_SlabTempComaredRender
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout;
    QPushButton *sel_new_file_btn;
    QLabel *new_path;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *sel_old_file_btn;
    QLabel *old_path;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_10;
    QLineEdit *coil_id_txt;
    QPushButton *gen_curve_btn;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *search_steel_btn;
    QLineEdit *grade_txt;
    QPushButton *search_slab_btn;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QLineEdit *rh_txt;
    QVBoxLayout *verticalLayout_17;
    QLabel *label_3;
    QLineEdit *yr_txt;
    QVBoxLayout *verticalLayout_18;
    QLabel *label_4;
    QLineEdit *yj_txt;
    QVBoxLayout *verticalLayout_19;
    QLabel *label_5;
    QLineEdit *ej_txt;
    QVBoxLayout *verticalLayout_20;
    QLabel *label_9;
    QLineEdit *jr_txt;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_21;
    QLabel *label_23;
    QLineEdit *wxfl_txt;
    QVBoxLayout *verticalLayout_22;
    QLabel *label_24;
    QLineEdit *wxdm_txt;
    QVBoxLayout *verticalLayout_23;
    QLabel *label_25;
    QLineEdit *lh_txt;
    QVBoxLayout *verticalLayout_24;
    QLabel *label_26;
    QLineEdit *zlwd_txt;
    QVBoxLayout *verticalLayout_25;
    QLabel *label_27;
    QLineEdit *bphd_txt;
    QSpacerItem *verticalSpacer_5;
    QPushButton *second_gen_btn;
    QHBoxLayout *horizontalLayout_9;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *yu_bf_txt;
    QLineEdit *yj_bf_txt;
    QLineEdit *ej_bf_txt;
    QLineEdit *jr_bf_txt;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_8;
    QVBoxLayout *verticalLayout_8;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QHBoxLayout *horizontalLayout_15;
    QLineEdit *yr_af_txt;
    QLineEdit *yj_af_txt;
    QLineEdit *ej_af_txt;
    QLineEdit *jr_af_txt;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *image_box;
    QVBoxLayout *verticalLayout_3;
    QDockWidget *image_dock;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    QtCharts::QChartView *graphicsView;

    void setupUi(QWidget *SlabTempComaredRender)
    {
        if (SlabTempComaredRender->objectName().isEmpty())
            SlabTempComaredRender->setObjectName(QString::fromUtf8("SlabTempComaredRender"));
        SlabTempComaredRender->resize(1246, 703);
        SlabTempComaredRender->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	color: #206864;\n"
"	text-align: center; \n"
"font-size: 20px\n"
"\n"
"   \n"
"}"));
        gridLayout_2 = new QGridLayout(SlabTempComaredRender);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        sel_new_file_btn = new QPushButton(SlabTempComaredRender);
        sel_new_file_btn->setObjectName(QString::fromUtf8("sel_new_file_btn"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sel_new_file_btn->sizePolicy().hasHeightForWidth());
        sel_new_file_btn->setSizePolicy(sizePolicy);
        sel_new_file_btn->setMaximumSize(QSize(16777215, 52));

        horizontalLayout->addWidget(sel_new_file_btn);

        new_path = new QLabel(SlabTempComaredRender);
        new_path->setObjectName(QString::fromUtf8("new_path"));
        new_path->setStyleSheet(QString::fromUtf8("\n"
"font: 10pt \"MS Shell Dlg 2\";"));

        horizontalLayout->addWidget(new_path);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 9);

        verticalLayout_9->addLayout(horizontalLayout);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        sel_old_file_btn = new QPushButton(SlabTempComaredRender);
        sel_old_file_btn->setObjectName(QString::fromUtf8("sel_old_file_btn"));
        sizePolicy.setHeightForWidth(sel_old_file_btn->sizePolicy().hasHeightForWidth());
        sel_old_file_btn->setSizePolicy(sizePolicy);
        sel_old_file_btn->setMaximumSize(QSize(16777215, 52));

        horizontalLayout_12->addWidget(sel_old_file_btn);

        old_path = new QLabel(SlabTempComaredRender);
        old_path->setObjectName(QString::fromUtf8("old_path"));
        old_path->setStyleSheet(QString::fromUtf8("\n"
"font: 10pt \"MS Shell Dlg 2\";"));

        horizontalLayout_12->addWidget(old_path);

        horizontalLayout_12->setStretch(0, 1);
        horizontalLayout_12->setStretch(1, 9);

        verticalLayout_9->addLayout(horizontalLayout_12);


        verticalLayout_2->addLayout(verticalLayout_9);

        tabWidget = new QTabWidget(SlabTempComaredRender);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_10 = new QVBoxLayout(tab);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        coil_id_txt = new QLineEdit(tab);
        coil_id_txt->setObjectName(QString::fromUtf8("coil_id_txt"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(coil_id_txt->sizePolicy().hasHeightForWidth());
        coil_id_txt->setSizePolicy(sizePolicy1);
        coil_id_txt->setMaximumSize(QSize(16777215, 30));

        verticalLayout_10->addWidget(coil_id_txt);

        gen_curve_btn = new QPushButton(tab);
        gen_curve_btn->setObjectName(QString::fromUtf8("gen_curve_btn"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(gen_curve_btn->sizePolicy().hasHeightForWidth());
        gen_curve_btn->setSizePolicy(sizePolicy2);
        gen_curve_btn->setMaximumSize(QSize(16777215, 50));

        verticalLayout_10->addWidget(gen_curve_btn);

        verticalLayout_10->setStretch(0, 4);
        verticalLayout_10->setStretch(1, 4);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        search_steel_btn = new QPushButton(tab_2);
        search_steel_btn->setObjectName(QString::fromUtf8("search_steel_btn"));

        horizontalLayout_2->addWidget(search_steel_btn);

        grade_txt = new QLineEdit(tab_2);
        grade_txt->setObjectName(QString::fromUtf8("grade_txt"));

        horizontalLayout_2->addWidget(grade_txt);

        search_slab_btn = new QPushButton(tab_2);
        search_slab_btn->setObjectName(QString::fromUtf8("search_slab_btn"));

        horizontalLayout_2->addWidget(search_slab_btn);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 5);
        horizontalLayout_2->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);


        horizontalLayout_4->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        groupBox_2 = new QGroupBox(SlabTempComaredRender);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_13 = new QVBoxLayout(groupBox_2);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_2);

        rh_txt = new QLineEdit(groupBox_2);
        rh_txt->setObjectName(QString::fromUtf8("rh_txt"));
        sizePolicy1.setHeightForWidth(rh_txt->sizePolicy().hasHeightForWidth());
        rh_txt->setSizePolicy(sizePolicy1);
        rh_txt->setMaximumSize(QSize(16777215, 30));
        rh_txt->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(rh_txt);


        horizontalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_17->addWidget(label_3);

        yr_txt = new QLineEdit(groupBox_2);
        yr_txt->setObjectName(QString::fromUtf8("yr_txt"));
        sizePolicy1.setHeightForWidth(yr_txt->sizePolicy().hasHeightForWidth());
        yr_txt->setSizePolicy(sizePolicy1);
        yr_txt->setMaximumSize(QSize(16777215, 30));
        yr_txt->setAlignment(Qt::AlignCenter);

        verticalLayout_17->addWidget(yr_txt);


        horizontalLayout_6->addLayout(verticalLayout_17);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_18->addWidget(label_4);

        yj_txt = new QLineEdit(groupBox_2);
        yj_txt->setObjectName(QString::fromUtf8("yj_txt"));
        sizePolicy1.setHeightForWidth(yj_txt->sizePolicy().hasHeightForWidth());
        yj_txt->setSizePolicy(sizePolicy1);
        yj_txt->setMaximumSize(QSize(16777215, 30));
        yj_txt->setAlignment(Qt::AlignCenter);

        verticalLayout_18->addWidget(yj_txt);


        horizontalLayout_6->addLayout(verticalLayout_18);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_19->addWidget(label_5);

        ej_txt = new QLineEdit(groupBox_2);
        ej_txt->setObjectName(QString::fromUtf8("ej_txt"));
        sizePolicy1.setHeightForWidth(ej_txt->sizePolicy().hasHeightForWidth());
        ej_txt->setSizePolicy(sizePolicy1);
        ej_txt->setMaximumSize(QSize(16777215, 30));
        ej_txt->setAlignment(Qt::AlignCenter);

        verticalLayout_19->addWidget(ej_txt);


        horizontalLayout_6->addLayout(verticalLayout_19);

        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_20->addWidget(label_9);

        jr_txt = new QLineEdit(groupBox_2);
        jr_txt->setObjectName(QString::fromUtf8("jr_txt"));
        sizePolicy1.setHeightForWidth(jr_txt->sizePolicy().hasHeightForWidth());
        jr_txt->setSizePolicy(sizePolicy1);
        jr_txt->setMaximumSize(QSize(16777215, 30));
        jr_txt->setAlignment(Qt::AlignCenter);

        verticalLayout_20->addWidget(jr_txt);


        horizontalLayout_6->addLayout(verticalLayout_20);


        verticalLayout_13->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setAlignment(Qt::AlignCenter);

        verticalLayout_21->addWidget(label_23);

        wxfl_txt = new QLineEdit(groupBox_2);
        wxfl_txt->setObjectName(QString::fromUtf8("wxfl_txt"));
        sizePolicy1.setHeightForWidth(wxfl_txt->sizePolicy().hasHeightForWidth());
        wxfl_txt->setSizePolicy(sizePolicy1);
        wxfl_txt->setMaximumSize(QSize(16777215, 30));
        wxfl_txt->setAlignment(Qt::AlignCenter);

        verticalLayout_21->addWidget(wxfl_txt);


        horizontalLayout_7->addLayout(verticalLayout_21);

        verticalLayout_22 = new QVBoxLayout();
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        label_24 = new QLabel(groupBox_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setAlignment(Qt::AlignCenter);

        verticalLayout_22->addWidget(label_24);

        wxdm_txt = new QLineEdit(groupBox_2);
        wxdm_txt->setObjectName(QString::fromUtf8("wxdm_txt"));
        sizePolicy1.setHeightForWidth(wxdm_txt->sizePolicy().hasHeightForWidth());
        wxdm_txt->setSizePolicy(sizePolicy1);
        wxdm_txt->setMaximumSize(QSize(16777215, 30));
        wxdm_txt->setAlignment(Qt::AlignCenter);

        verticalLayout_22->addWidget(wxdm_txt);


        horizontalLayout_7->addLayout(verticalLayout_22);

        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        label_25 = new QLabel(groupBox_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setAlignment(Qt::AlignCenter);

        verticalLayout_23->addWidget(label_25);

        lh_txt = new QLineEdit(groupBox_2);
        lh_txt->setObjectName(QString::fromUtf8("lh_txt"));
        sizePolicy1.setHeightForWidth(lh_txt->sizePolicy().hasHeightForWidth());
        lh_txt->setSizePolicy(sizePolicy1);
        lh_txt->setMaximumSize(QSize(16777215, 30));
        lh_txt->setAlignment(Qt::AlignCenter);

        verticalLayout_23->addWidget(lh_txt);


        horizontalLayout_7->addLayout(verticalLayout_23);

        verticalLayout_24 = new QVBoxLayout();
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        label_26 = new QLabel(groupBox_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setAlignment(Qt::AlignCenter);

        verticalLayout_24->addWidget(label_26);

        zlwd_txt = new QLineEdit(groupBox_2);
        zlwd_txt->setObjectName(QString::fromUtf8("zlwd_txt"));
        sizePolicy1.setHeightForWidth(zlwd_txt->sizePolicy().hasHeightForWidth());
        zlwd_txt->setSizePolicy(sizePolicy1);
        zlwd_txt->setMaximumSize(QSize(16777215, 30));
        zlwd_txt->setAlignment(Qt::AlignCenter);

        verticalLayout_24->addWidget(zlwd_txt);


        horizontalLayout_7->addLayout(verticalLayout_24);

        verticalLayout_25 = new QVBoxLayout();
        verticalLayout_25->setObjectName(QString::fromUtf8("verticalLayout_25"));
        label_27 = new QLabel(groupBox_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setAlignment(Qt::AlignCenter);

        verticalLayout_25->addWidget(label_27);

        bphd_txt = new QLineEdit(groupBox_2);
        bphd_txt->setObjectName(QString::fromUtf8("bphd_txt"));
        sizePolicy1.setHeightForWidth(bphd_txt->sizePolicy().hasHeightForWidth());
        bphd_txt->setSizePolicy(sizePolicy1);
        bphd_txt->setMaximumSize(QSize(16777215, 30));
        bphd_txt->setAlignment(Qt::AlignCenter);

        verticalLayout_25->addWidget(bphd_txt);


        horizontalLayout_7->addLayout(verticalLayout_25);


        verticalLayout_13->addLayout(horizontalLayout_7);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_5);

        second_gen_btn = new QPushButton(groupBox_2);
        second_gen_btn->setObjectName(QString::fromUtf8("second_gen_btn"));
        sizePolicy.setHeightForWidth(second_gen_btn->sizePolicy().hasHeightForWidth());
        second_gen_btn->setSizePolicy(sizePolicy);
        second_gen_btn->setMaximumSize(QSize(16777215, 50));

        verticalLayout_13->addWidget(second_gen_btn);

        verticalLayout_13->setStretch(0, 2);
        verticalLayout_13->setStretch(1, 2);
        verticalLayout_13->setStretch(2, 1);
        verticalLayout_13->setStretch(3, 6);

        horizontalLayout_4->addWidget(groupBox_2);

        horizontalLayout_4->setStretch(0, 3);
        horizontalLayout_4->setStretch(2, 5);

        gridLayout_2->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        groupBox_3 = new QGroupBox(SlabTempComaredRender);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_6 = new QVBoxLayout(groupBox_3);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_11);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_12);

        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_13);

        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_14);


        verticalLayout_5->addLayout(horizontalLayout_3);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        yu_bf_txt = new QLineEdit(groupBox_3);
        yu_bf_txt->setObjectName(QString::fromUtf8("yu_bf_txt"));
        sizePolicy1.setHeightForWidth(yu_bf_txt->sizePolicy().hasHeightForWidth());
        yu_bf_txt->setSizePolicy(sizePolicy1);
        yu_bf_txt->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_10->addWidget(yu_bf_txt);

        yj_bf_txt = new QLineEdit(groupBox_3);
        yj_bf_txt->setObjectName(QString::fromUtf8("yj_bf_txt"));
        sizePolicy1.setHeightForWidth(yj_bf_txt->sizePolicy().hasHeightForWidth());
        yj_bf_txt->setSizePolicy(sizePolicy1);
        yj_bf_txt->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_10->addWidget(yj_bf_txt);

        ej_bf_txt = new QLineEdit(groupBox_3);
        ej_bf_txt->setObjectName(QString::fromUtf8("ej_bf_txt"));
        sizePolicy1.setHeightForWidth(ej_bf_txt->sizePolicy().hasHeightForWidth());
        ej_bf_txt->setSizePolicy(sizePolicy1);
        ej_bf_txt->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_10->addWidget(ej_bf_txt);

        jr_bf_txt = new QLineEdit(groupBox_3);
        jr_bf_txt->setObjectName(QString::fromUtf8("jr_bf_txt"));
        sizePolicy1.setHeightForWidth(jr_bf_txt->sizePolicy().hasHeightForWidth());
        jr_bf_txt->setSizePolicy(sizePolicy1);
        jr_bf_txt->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_10->addWidget(jr_bf_txt);


        verticalLayout_5->addLayout(horizontalLayout_10);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        verticalLayout_5->setStretch(0, 2);
        verticalLayout_5->setStretch(1, 2);
        verticalLayout_5->setStretch(2, 3);
        verticalLayout_5->setStretch(3, 3);

        horizontalLayout_11->addLayout(verticalLayout_5);


        verticalLayout_6->addLayout(horizontalLayout_11);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(label_8);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_19 = new QLabel(groupBox_3);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_19);

        label_20 = new QLabel(groupBox_3);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_20);

        label_21 = new QLabel(groupBox_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_21);

        label_22 = new QLabel(groupBox_3);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_22);


        verticalLayout_8->addLayout(horizontalLayout_5);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        yr_af_txt = new QLineEdit(groupBox_3);
        yr_af_txt->setObjectName(QString::fromUtf8("yr_af_txt"));
        sizePolicy1.setHeightForWidth(yr_af_txt->sizePolicy().hasHeightForWidth());
        yr_af_txt->setSizePolicy(sizePolicy1);
        yr_af_txt->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_15->addWidget(yr_af_txt);

        yj_af_txt = new QLineEdit(groupBox_3);
        yj_af_txt->setObjectName(QString::fromUtf8("yj_af_txt"));
        sizePolicy1.setHeightForWidth(yj_af_txt->sizePolicy().hasHeightForWidth());
        yj_af_txt->setSizePolicy(sizePolicy1);
        yj_af_txt->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_15->addWidget(yj_af_txt);

        ej_af_txt = new QLineEdit(groupBox_3);
        ej_af_txt->setObjectName(QString::fromUtf8("ej_af_txt"));
        sizePolicy1.setHeightForWidth(ej_af_txt->sizePolicy().hasHeightForWidth());
        ej_af_txt->setSizePolicy(sizePolicy1);
        ej_af_txt->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_15->addWidget(ej_af_txt);

        jr_af_txt = new QLineEdit(groupBox_3);
        jr_af_txt->setObjectName(QString::fromUtf8("jr_af_txt"));
        sizePolicy1.setHeightForWidth(jr_af_txt->sizePolicy().hasHeightForWidth());
        jr_af_txt->setSizePolicy(sizePolicy1);
        jr_af_txt->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_15->addWidget(jr_af_txt);


        verticalLayout_8->addLayout(horizontalLayout_15);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_4);

        verticalLayout_8->setStretch(0, 2);
        verticalLayout_8->setStretch(1, 2);
        verticalLayout_8->setStretch(2, 3);
        verticalLayout_8->setStretch(3, 3);

        horizontalLayout_14->addLayout(verticalLayout_8);


        verticalLayout_6->addLayout(horizontalLayout_14);

        verticalLayout_6->setStretch(0, 1);
        verticalLayout_6->setStretch(1, 1);

        horizontalLayout_9->addWidget(groupBox_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);

        image_box = new QGroupBox(SlabTempComaredRender);
        image_box->setObjectName(QString::fromUtf8("image_box"));
        verticalLayout_3 = new QVBoxLayout(image_box);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        image_dock = new QDockWidget(image_box);
        image_dock->setObjectName(QString::fromUtf8("image_dock"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(dockWidgetContents->sizePolicy().hasHeightForWidth());
        dockWidgetContents->setSizePolicy(sizePolicy3);
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new QtCharts::QChartView(dockWidgetContents);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        image_dock->setWidget(dockWidgetContents);

        verticalLayout_3->addWidget(image_dock);


        horizontalLayout_9->addWidget(image_box);

        horizontalLayout_9->setStretch(0, 3);
        horizontalLayout_9->setStretch(2, 5);

        gridLayout_2->addLayout(horizontalLayout_9, 1, 0, 1, 1);


        retranslateUi(SlabTempComaredRender);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SlabTempComaredRender);
    } // setupUi

    void retranslateUi(QWidget *SlabTempComaredRender)
    {
        SlabTempComaredRender->setWindowTitle(QCoreApplication::translate("SlabTempComaredRender", "\346\235\277\345\235\257\346\270\251\345\272\246\345\257\271\346\257\224\347\250\213\345\272\217", nullptr));
        sel_new_file_btn->setText(QCoreApplication::translate("SlabTempComaredRender", "\351\200\211\346\213\251\346\226\260\347\263\273\347\273\237\346\226\207\344\273\266", nullptr));
        new_path->setText(QString());
        sel_old_file_btn->setText(QCoreApplication::translate("SlabTempComaredRender", "\351\200\211\346\213\251\350\200\201\347\263\273\347\273\237\346\226\207\344\273\266", nullptr));
        old_path->setText(QString());
        coil_id_txt->setPlaceholderText(QCoreApplication::translate("SlabTempComaredRender", "\350\257\267\350\276\223\345\205\245\346\235\277\345\235\257\345\217\267", nullptr));
        gen_curve_btn->setText(QCoreApplication::translate("SlabTempComaredRender", "\347\224\237\346\210\220\346\233\262\347\272\277", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SlabTempComaredRender", "\350\276\223\345\205\245\345\215\267\345\217\267", nullptr));
        search_steel_btn->setText(QCoreApplication::translate("SlabTempComaredRender", "\346\237\245\350\257\242\351\222\242\347\247\215", nullptr));
        grade_txt->setPlaceholderText(QCoreApplication::translate("SlabTempComaredRender", "\346\240\271\346\215\256\346\214\207\345\256\232\351\222\242\347\247\215\346\237\245\350\257\242\345\215\267\345\217\267", nullptr));
        search_slab_btn->setText(QCoreApplication::translate("SlabTempComaredRender", "\346\237\245\350\257\242\346\235\277\345\235\257\345\217\267", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("SlabTempComaredRender", "\351\200\232\350\277\207\351\222\242\347\247\215\346\237\245\350\257\242\345\215\267\345\217\267", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SlabTempComaredRender", "\345\217\202\346\225\260", nullptr));
        label_2->setText(QCoreApplication::translate("SlabTempComaredRender", "\347\203\255\345\233\236\346\224\266", nullptr));
        label_3->setText(QCoreApplication::translate("SlabTempComaredRender", "\351\242\204\347\203\255", nullptr));
        label_4->setText(QCoreApplication::translate("SlabTempComaredRender", "\344\270\200\345\212\240", nullptr));
        label_5->setText(QCoreApplication::translate("SlabTempComaredRender", "\344\272\214\345\212\240", nullptr));
        label_9->setText(QCoreApplication::translate("SlabTempComaredRender", "\345\235\207\347\203\255", nullptr));
        label_23->setText(QCoreApplication::translate("SlabTempComaredRender", "\347\211\251\346\200\247\345\210\206\347\261\273", nullptr));
        label_24->setText(QCoreApplication::translate("SlabTempComaredRender", "\347\211\251\346\200\247\344\273\243\347\240\201", nullptr));
        label_25->setText(QCoreApplication::translate("SlabTempComaredRender", "\347\202\211\345\217\267", nullptr));
        label_26->setText(QCoreApplication::translate("SlabTempComaredRender", "\350\243\205\347\202\211\346\270\251\345\272\246", nullptr));
        label_27->setText(QCoreApplication::translate("SlabTempComaredRender", "\346\235\277\345\235\257\345\216\232\345\272\246", nullptr));
        second_gen_btn->setText(QCoreApplication::translate("SlabTempComaredRender", "\345\206\215\346\254\241\347\224\237\346\210\220", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("SlabTempComaredRender", "\346\270\251\345\267\256", nullptr));
        label_6->setText(QCoreApplication::translate("SlabTempComaredRender", "<html><head/><body><p>\344\277\256</p><p>\346\255\243</p><p>\345\211\215</p></body></html>", nullptr));
        label_11->setText(QCoreApplication::translate("SlabTempComaredRender", "\351\242\204\347\203\255", nullptr));
        label_12->setText(QCoreApplication::translate("SlabTempComaredRender", "\344\270\200\345\212\240", nullptr));
        label_13->setText(QCoreApplication::translate("SlabTempComaredRender", "\344\272\214\345\212\240", nullptr));
        label_14->setText(QCoreApplication::translate("SlabTempComaredRender", "\345\235\207\347\203\255", nullptr));
        label_8->setText(QCoreApplication::translate("SlabTempComaredRender", "<html><head/><body><p>\344\277\256</p><p>\346\255\243</p><p>\345\211\215</p></body></html>", nullptr));
        label_19->setText(QCoreApplication::translate("SlabTempComaredRender", "\351\242\204\347\203\255", nullptr));
        label_20->setText(QCoreApplication::translate("SlabTempComaredRender", "\344\270\200\345\212\240", nullptr));
        label_21->setText(QCoreApplication::translate("SlabTempComaredRender", "\344\272\214\345\212\240", nullptr));
        label_22->setText(QCoreApplication::translate("SlabTempComaredRender", "\345\235\207\347\203\255", nullptr));
        image_box->setTitle(QCoreApplication::translate("SlabTempComaredRender", "\345\233\276\345\203\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SlabTempComaredRender: public Ui_SlabTempComaredRender {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLABTEMPCOMAREDRENDER_H
