#pragma once

#include <QStyledItemDelegate>

class PriceDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    PriceDelegate(QObject* parent = nullptr);
    ~PriceDelegate();

    QString displayText(const QVariant& value, const QLocale& locale) const override;
};