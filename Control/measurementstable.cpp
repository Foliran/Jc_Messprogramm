#include "measurementstable.h"
#include <QVBoxLayout>
#include <QDebug>

//fertig

#include "../Core/measurementsequence.h"

MeasurementsTable::MeasurementsTable(QWidget* parent)
    : QWidget(parent)
    , listWidget(new QListWidget(this))
    , vecSeq()
{
    setupUI();
}

QSize MeasurementsTable::sizeHint() const
{
    return QSize(200, 500);
}

QSize MeasurementsTable::minimumSizeHint() const
{
    return QSize(100, 300);
}

void MeasurementsTable::newMeasurement(const std::vector<std::shared_ptr<const MeasurementSequence>>& mSeq)
{
    for (const auto& mesSeq : mSeq)
    {
        vecSeq.push_back(mesSeq);
    }

    for (unsigned long i = 0; i < mSeq.size(); i++)
    {
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(mSeq[i]->getFileName());
        listWidget->addItem(item);
    }
}

void MeasurementsTable::activeMeasurement(const std::shared_ptr<const MeasurementSequence> mesSeq)
{
    auto it = vecSeq.begin();
    QColor color;
    std::for_each(vecSeq.begin(), vecSeq.end(),
        [&](const auto& el)
        {
            color = (mesSeq == el) ? Qt::red : Qt::black;
            listWidget->item(it++ - vecSeq.begin())->setForeground(color);
        });


}

void MeasurementsTable::setupUI()
{
    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(listWidget);
    setLayout(mainLayout);
}

