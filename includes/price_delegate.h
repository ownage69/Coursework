#pragma once

#include <QStyledItemDelegate>

class PriceDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit PriceDelegate(QObject* parent = nullptr);
    ~PriceDelegate() override;

    QString displayText(const QVariant& value, const QLocale& locale) const override;
};