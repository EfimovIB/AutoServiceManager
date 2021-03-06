#ifndef ASM_MANUFACTURERDIALOG_H
#define ASM_MANUFACTURERDIALOG_H

class QListWidgetItem;

#include <QDialog>

namespace Ui
{
    class ManufacturerDialog;
}

namespace asmt
{
class Manufacturer;
class ManufacturerDialog : public QDialog
{
    Q_OBJECT
public:
    ManufacturerDialog(QWidget* _parent = 0, Qt::WindowFlags _f = 0);
    ~ManufacturerDialog();

    static Manufacturer* getManufacturer(QWidget* _parent = 0);

    Manufacturer* choosedManufacturer() const;

private:
    void fillList();
    void updateList();

private slots:
    void addManufacturer();
    void itemClicked(QListWidgetItem* _item);

private:
    Ui::ManufacturerDialog* m_ui;
};
}

#endif //ASM_CLIENTSWIDGET_H

