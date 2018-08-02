/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "tablewidget.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTableView>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>

#include <QtCharts/QVXYModelMapper>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QVBarModelMapper>
#include <QtWidgets/QHeaderView>
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE

TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent)
{
    // create simple model for storing data
    // user's table data model
    //! [1]
    m_model = new CustomTableModel;
    //! [1]

    //! [2]
    // create table view and add model to it
    QTableView *tableView = new QTableView;
    tableView->setModel(m_model);
    tableView->setMinimumWidth(300);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_model->setParent(tableView);
    //! [2]

    //! [3]
    QChart *chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);
    //! [3]

    // series 1
    //! [4]
    QBarSeries *series = new QBarSeries;

    int first = 3;
    int count = 5;
    QVBarModelMapper *mapper = new QVBarModelMapper(this);
    mapper->setFirstBarSetColumn(1);
    mapper->setLastBarSetColumn(4);
    mapper->setFirstRow(first);
    mapper->setRowCount(count);
    mapper->setSeries(series);
    mapper->setModel(m_model);
    chart->addSeries(series);
    //! [4]

    //! [5]
    // for storing color hex from the series
    QString seriesColorHex = "#000000";

    // get the color of the series and use it for showing the mapped area
    QList<QBarSet *> barsets = series->barSets();
    for (int i = 0; i < barsets.count(); i++) {
        seriesColorHex = "#" + QString::number(barsets.at(i)->brush().color().rgb(), 16).right(6).toUpper();
        m_model->addMapping(seriesColorHex, QRect(1 + i, first, 1, barsets.at(i)->count()));
    }
    //! [5]

    //! [6]
    QStringList categories;
    categories << "April" << "May" << "June" << "July" << "August";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    //! [6]

    //! [7]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);
    //! [7]


    QLineSeries *series0 = new QLineSeries();
    QLineSeries *series1 = new QLineSeries();

    *series0 << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7) << QPointF(12, 6)
             << QPointF(16, 7) << QPointF(18, 5);
    *series1 << QPointF(1, 3) << QPointF(3, 4) << QPointF(7, 3) << QPointF(8, 2) << QPointF(12, 3)
             << QPointF(16, 4) << QPointF(18, 3);

    QAreaSeries *series00 = new QAreaSeries(series0, series1);
    series00->setName("Batman");
    QPen pen(0x059605);
    pen.setWidth(3);
    series00->setPen(pen);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(0.0, 0x3cc63c);
    gradient.setColorAt(1.0, 0x26f626);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    series00->setBrush(gradient);

    QChart *chart11 = new QChart();
    chart11->addSeries(series00);
    chart11->setTitle("Simple areachart example");
    chart11->createDefaultAxes();
    chart11->axisX()->setRange(0, 20);
    chart11->axisY()->setRange(0, 10);

    QChartView *chartView11 = new QChartView(chart11);
    chartView11->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);

    QChart *chart22=chart;

    QChartView *chartView22 = new QChartView(chart22);
    chartView22->setRenderHint(QPainter::Antialiasing);
    chartView22->setMinimumSize(640, 480);
    //! [8]
    // create main layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(chartView,0,0);
    mainLayout->addWidget(tableView, 1, 0);
    mainLayout->addWidget(chartView11, 1, 1);
    mainLayout->addWidget(chartView22,0,1);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setRowStretch(0,1);
    mainLayout->setRowStretch(1,1);
    setLayout(mainLayout);
    //! [8]
}
