#include "saveexitwindow.h"

SaveExitWindow::SaveExitWindow(QWidget *parent)
{
    exitTable = new QTableWidget;
    label = new QLabel(tr("Save the changed files?"));
    yesButton = new QPushButton(tr("Yes"));
    noButton = new QPushButton(tr("No"));
    cancelButton = new QPushButton(tr("Cancel"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label, 0, 0);
    layout->addWidget(exitTable, 1, 0, 1, 3);
    layout->addWidget(yesButton, 2, 0);
    layout->addWidget(noButton, 2, 1);
    layout->addWidget(cancelButton, 2, 2);
    setLayout(layout);
    connect(yesButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(noButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

QPushButton* SaveExitWindow::getYesButton() const
{
    return yesButton;
}

QPushButton* SaveExitWindow::getNoButton() const
{
    return noButton;
}
QPushButton* SaveExitWindow::getCancelButton() const
{
    return cancelButton;
}
QTableWidget* SaveExitWindow::getExitTable() const
{
    return exitTable;
}
