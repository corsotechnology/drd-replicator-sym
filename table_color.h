#ifndef TABLE_COLOR_H
#define TABLE_COLOR_H
#include <QStyledItemDelegate>
#include <QPainter>
class GreenTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit GreenTableDelegate(QObject *parent = 0)
        : QStyledItemDelegate(parent)
    {
    }

    // background color manipulation
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QColor background = QColor(230, 255, 247); // RGB value: https://www.rapidtables.com/web/color/blue-color.html
        painter->fillRect(option.rect, background);
    }

};
class RedTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit RedTableDelegate(QObject *parent = 0)
        : QStyledItemDelegate(parent)
    {
    }

    // background color manipulation
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QColor background = QColor(255, 214, 204); // RGB value: https://www.rapidtables.com/web/color/blue-color.html
        painter->fillRect(option.rect, background);
    }

};
#endif // TABLE_COLOR_H
