#include "price_delegate.h"

PriceDelegate::PriceDelegate(QObject* parent) : QStyledItemDelegate(parent) {}

PriceDelegate::~PriceDelegate() {}

QString PriceDelegate::displayText(const QVariant& value, const QLocale& locale) const {
    if (value.type() == QVariant::Double || value.type() == QVariant::String) {
        bool ok;
        double num = value.toDouble(&ok);
        if (ok) {
            return QString("$%1").arg(num, 0, 'f', 2);
        }
    }
    return QStyledItemDelegate::displayText(value, locale);
}