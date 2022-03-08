#include <QDialog>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QGridLayout>

class SaveExitWindow: public QDialog
{
    Q_OBJECT
public:
    SaveExitWindow(QWidget *parent=0);

    QPushButton* getYesButton() const;
    QPushButton* getNoButton() const;
    QPushButton* getCancelButton() const;
    QTableWidget* getExitTable() const;

private:
    QPushButton *yesButton;
    QPushButton *noButton;
    QPushButton *cancelButton;
    QTableWidget *exitTable;
    QLabel *label;
};


