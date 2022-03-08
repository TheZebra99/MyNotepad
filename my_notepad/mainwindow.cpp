#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    FileVector = new QVector<CodeEditor*>;
    MainWidget = new QWidget(this);
    Layout = new QHBoxLayout(this);
    TabWidget = new QTabWidget(this);
    TabWidget->setTabsClosable(true);
    TabWidget->setMovable(true);
    TabWidget->setDocumentMode(true);
    connect(TabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(CloseCurrentTab()));

    CreateActions();
    CreateMenu();

    view_Menu = new QMenu(tr("View"));
    menuBar()->addMenu(view_Menu);

    explorer = new QDockWidget(tr("Explorer"),this);
    explorer->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    explorer->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    explorer->hide();
    show_Explorer_Action = view_Menu->addAction(tr("Explorer"),this,SLOT(showFileExplorer(bool)));
    show_Explorer_Action->setCheckable(true);
    connect(show_Explorer_Action, SIGNAL(setChecked(bool)), this, SLOT(showFileExplorer(bool)));
    connect(explorer, SIGNAL(visibilityChanged(bool)), show_Explorer_Action, SLOT(setChecked(bool)));

    viewer = new QDockWidget(tr("Viewer of open documents"),this);
    viewer->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    viewer->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    viewer->hide();
    show_Viewer_Action = view_Menu->addAction(tr("Viewer"),this,SLOT(showFileViewer(bool)));
    show_Viewer_Action->setCheckable(true);
    connect(show_Viewer_Action, SIGNAL(setChecked(bool)), this, SLOT(showFileViewer(bool)));
    connect(viewer, SIGNAL(visibilityChanged(bool)), show_Viewer_Action, SLOT(setChecked(bool)));

    Layout->addWidget(explorer);
    Layout->addWidget(viewer);
    Layout->addWidget(TabWidget);
    MainWidget->setLayout(Layout);

    setWindowTitle("Simple Text Editor");
    resize (800, 800);
    setCentralWidget(MainWidget);
}

MainWindow::~MainWindow()
{
    FileVector->clear();
    delete FileVector;
}

void MainWindow::CreateActions()
{
    QToolBar *bar = addToolBar("Toolbar");
    //File:
    new_File_Action = new QAction(tr("New"), this);
    new_File_Action->setShortcut(QKeySequence::New);
    new_File_Action->setIcon(QIcon(":/pngs/new.png"));
    bar->addAction(new_File_Action);
    connect(new_File_Action, SIGNAL(triggered()), this, SLOT(NewFile()));

    open_File_Action = new QAction(tr("Open"), this);
    open_File_Action->setShortcut(QKeySequence::Open);
    open_File_Action->setIcon(QIcon(":/pngs/open.png"));
    bar->addAction(open_File_Action);
    connect(open_File_Action, SIGNAL(triggered()),this , SLOT(OpenFile()));

    save_File_Action = new QAction(tr("Save"), this);
    save_File_Action->setShortcut(QKeySequence::Save);
    save_File_Action->setIcon(QIcon(":/pngs/save.png"));
    bar->addAction(save_File_Action);
    connect(save_File_Action, SIGNAL(triggered()),this , SLOT(SaveFile()));

    save_File_As_Action = new QAction(tr("Save As"), this);
    save_File_As_Action->setShortcut(QKeySequence::SaveAs);
    save_File_As_Action->setIcon(QIcon(":/pngs/save_as.png"));
    bar->addAction(save_File_As_Action);
    connect(save_File_As_Action, SIGNAL(triggered()),this , SLOT(SaveFileAs()));

    save_All_Action = new QAction(tr("Save All"));
    //save_File_As_Action->setShortcut(QKeySequence::SaveAll);
    save_All_Action->setIcon(QIcon(":/pngs/save_all.png"));
    bar->addAction(save_All_Action);
    connect(save_All_Action, SIGNAL(triggered()),this , SLOT(SaveAll()));

    close_Current_Tab_Action = new QAction(tr("Close current tab"), this);
    close_Current_Tab_Action->setShortcut(QKeySequence::Close);
    close_Current_Tab_Action->setIcon(QIcon(":/pngs/close.png"));
    bar->addAction(close_Current_Tab_Action);
    connect(close_Current_Tab_Action, SIGNAL(triggered()),this , SLOT(CloseCurrentTab()));

    close_All_Tabs_Action = new QAction(tr("Close All Tabs"));
    //close_All_Tabs_Action->setShortcut(QKeySequence::CloseAll);
    close_All_Tabs_Action->setIcon(QIcon(":/pngs/close_all.png"));
    bar->addAction(close_All_Tabs_Action);
    connect(close_All_Tabs_Action, SIGNAL(triggered()),this , SLOT(CloseAllTabs()));
    bar->addSeparator();

    // Edit:
    cut_Text_Action = new QAction(tr("Cut"), this);
    cut_Text_Action->setShortcut(QKeySequence::Cut);
    cut_Text_Action->setIcon(QIcon(":/pngs/cut.png"));
    bar->addAction(cut_Text_Action);
    connect(cut_Text_Action, SIGNAL(triggered()),this , SLOT(Cut()));

    copy_Text_Action = new QAction(tr("Copy"), this);
    copy_Text_Action->setShortcut(QKeySequence::Copy);
    copy_Text_Action->setIcon(QIcon(":/pngs/copy.png"));
    bar->addAction(copy_Text_Action);
    connect(copy_Text_Action, SIGNAL(triggered()),this , SLOT(Copy()));

    paste_Text_Action = new QAction(tr("Paste"), this);
    paste_Text_Action->setShortcut(QKeySequence::Paste);
    paste_Text_Action->setIcon(QIcon(":/pngs/paste.png"));
    bar->addAction(paste_Text_Action);
    connect(paste_Text_Action, SIGNAL(triggered()),this , SLOT(Paste()));

    clear_Text_Action = new QAction(tr("Clear"), this);
    clear_Text_Action->setShortcut(QKeySequence::Delete);
    clear_Text_Action->setIcon(QIcon(":/pngs/clear.png"));
    bar->addAction(clear_Text_Action);
    connect(clear_Text_Action, SIGNAL(triggered()),this , SLOT(Clear()));

    select_All_Action = new QAction(tr("Select All"), this);
    select_All_Action->setShortcut(QKeySequence::SelectAll);
    select_All_Action->setIcon(QIcon(":/pngs/select.png"));
    bar->addAction(select_All_Action);
    connect(select_All_Action, SIGNAL(triggered()),this , SLOT(SelectAll()));

    change_Font_Action = new QAction(tr("Font"), this);
    //change_Font_Action->setShortcut(QKeySequence::Font);
    change_Font_Action->setIcon(QIcon(":/pngs/font.png"));
    bar->addAction(change_Font_Action);
    connect(change_Font_Action, SIGNAL(triggered()),this , SLOT(ChangeFont()));
    bar->addSeparator();

    undo_Text_Action = new QAction(tr("Undo"), this);
    undo_Text_Action->setShortcut(QKeySequence::Undo);
    undo_Text_Action->setIcon(QIcon(":/pngs/undo.png"));
    bar->addAction(undo_Text_Action);
    connect(undo_Text_Action, SIGNAL(triggered()),this , SLOT(Undo()));

    redo_Text_Action = new QAction(tr("Redo"), this);
    redo_Text_Action->setShortcut(QKeySequence::Redo);
    redo_Text_Action->setIcon(QIcon(":/pngs/redo.png"));
    bar->addAction(redo_Text_Action);
    connect(redo_Text_Action, SIGNAL(triggered()),this , SLOT(Redo()));
}

void MainWindow::CreateMenu()
{
    file_Menu = menuBar()->addMenu(tr("File"));
    file_Menu->addAction(new_File_Action);
    file_Menu->addAction(open_File_Action);
    file_Menu->addAction(save_File_Action);
    file_Menu->addAction(save_File_As_Action);
    file_Menu->addAction(save_All_Action);
    file_Menu->addAction(close_Current_Tab_Action);
    file_Menu->addAction(close_All_Tabs_Action);
    file_Menu->addSeparator();
    QAction *exit_Action = file_Menu->addAction(tr("Exit"), this, &QWidget::close);
    exit_Action->setIcon(QIcon(":/pngs/exit.png"));
    exit_Action->setShortcuts(QKeySequence::Quit);

    edit_Menu = menuBar()->addMenu(tr("Edit"));
    edit_Menu->addAction(cut_Text_Action);
    edit_Menu->addAction(copy_Text_Action);
    edit_Menu->addAction(paste_Text_Action);
    edit_Menu->addAction(clear_Text_Action);
    edit_Menu->addAction(select_All_Action);
    edit_Menu->addAction(change_Font_Action);
    edit_Menu->addSeparator();
    edit_Menu->addAction(redo_Text_Action);
    edit_Menu->addAction(undo_Text_Action);
}

//File:
void MainWindow::NewFile()
{
    ++count;
    CodeEditor *newFile = new CodeEditor(this);
    QString filename = "File " + QString::number(count);
    auto index = TabWidget->addTab(newFile, filename);
    FileVector->push_back(newFile);
    TabWidget->addTab(FileVector->at(index), filename);
    TabWidget->setCurrentIndex(FileVector->indexOf(newFile));
    connect(newFile, SIGNAL(textChanged()), SLOT(FileUpdated()));
    NameList << TabWidget->tabText(TabWidget->currentIndex());
    showFileViewer(viewer->isVisible());
}

void MainWindow::OpenFile()
{
    QString file_path = QFileDialog::getOpenFileName(this,
                                                     tr("Open file"),
                                                     QDir::currentPath(),
                                                     tr("Any file (*) ;; C++ file (*.h *.hpp *.cpp);; Python file (*.py)"));
        if (file_path != "")
        {
            QString file_name = file_path.section('/', -1);
            bool flag = true;
            int index=0;
            for (int i = 0; i < FileVector->size(); ++i)
            {
                if (TabWidget->tabText(i) == file_name)
                {
                    flag = false;
                    index = i;
                }
            }
            if (flag)
            {
                QFile file(file_path);
                if ( !file.open(QFile::ReadOnly|QFile::Text))
                {
                    QMessageBox::warning(this, tr("Warning, "), tr("cant open the file"));
                    return;
                }
                QTextStream TextStream(&file);
                CodeEditor *newFile = new CodeEditor(this);

                if (file_name.contains(".cpp") || file_name.contains(".h") || file_name.contains(".hpp") || file_name.contains(".py"))
                {
                    Highlighter * highlighter = new Highlighter(newFile->document());
                    if(!highlighter->setSettings(QFileInfo(file_path).suffix()))
                    {
                        QMessageBox::warning(this, tr("Error"), tr("A problem with an xml-settings file occured, syntax highlighting not applied to the file"));
                    }
                }

                newFile->setPlainText(file.readAll());
                FileVector->push_back(newFile);
                TabWidget->addTab(FileVector->at(FileVector->indexOf(newFile)),
                                  file_path.section('/', -1));
                TabWidget->setCurrentIndex(FileVector->indexOf(newFile));
                connect(newFile, SIGNAL(textChanged()), SLOT(FileUpdated()));
                NameList << TabWidget->tabText(TabWidget->currentIndex());
                showFileViewer(viewer->isVisible());
                file.flush();
                file.close();
            }
            else
            {
                TabWidget->setCurrentIndex(index);
            }
        }
        else
        {
            QMessageBox::critical(this, tr("Warning!"), tr("You didnt choose any file in the popup menu!"));
            return;
        }
}



void MainWindow::SaveFile()
{
    int index = TabWidget->currentIndex();
    if (index==-1)
    {
        QMessageBox::critical(this, tr("Warning!"), tr("You have not yet opened any files to save!"));
        return;
    }
    QString filename = TabWidget->tabText(TabWidget->currentIndex()).section('*', -1);
    if (filename.contains("File "))
    {
        SaveFileAs();
        return;
    }
    QFile File(QDir::currentPath() + filename);
    if (!File.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::critical(this, tr("Warning!"), tr("Cant open the file!"));
        return;
    }
    QTextStream TextStream(&File);
    TextStream <<qobject_cast<CodeEditor*>(TabWidget->widget(TabWidget->currentIndex()))->toPlainText();
    TabWidget->setTabText(TabWidget->currentIndex(), filename);
    NameList.replace(TabWidget->currentIndex(), filename);
    showFileViewer(viewer->isVisible());
    File.close();
}

void MainWindow::SaveFileAs()
{
    int index = TabWidget->currentIndex();
    if (index==-1)
    {
        QMessageBox::critical(this, tr("Warning!"), tr("You have not yet opened any files to save!"));
        return;
    }
    QString FilePath = QFileDialog::getSaveFileName(this, tr("Save As"), "", "*.txt");
    QFile File(FilePath);
    if (!File.open(QFile::WriteOnly|QFile::Text))
    {
        if (FilePath!="")
        {
            QMessageBox::critical(this, tr("Warning!"), tr("Cant open the file"));
            return;
        }
        else
        {
            QMessageBox::critical(this, tr("Warning!"), tr("You have not chosen any file in the popup menu, file was not saved!"));
            return;
        }
    }
    QTextStream TextStream(&File);
    TextStream <<qobject_cast<CodeEditor*>(TabWidget->widget(TabWidget->currentIndex()))->toPlainText();
    TabWidget->setTabText(TabWidget->currentIndex(), FilePath.section('/', -1));
    NameList.replace(TabWidget->currentIndex(), FilePath.section('/', -1));
    showFileViewer(viewer->isVisible());
    File.close();
}

void MainWindow::SaveAll()
{
    if (FileVector->size() == 0)
    {
        QMessageBox::critical(this, tr("Warning!"), tr("You have not yet opened any files to save!"));
        return;
    }
    for (int i=0; i < FileVector->size(); ++i)
    {
        TabWidget->setCurrentIndex(i);
        SaveFile();
    }
}

void MainWindow::CloseCurrentTab()
{
    int index = TabWidget->currentIndex();
    if (index==-1)
    {
        QMessageBox::critical(this, tr("Warning!"), tr("You have not yet opened any tabs to close!"));
        return;
    }
    if (TabWidget->tabText(index).contains("*"))
    {
        int answer = QMessageBox::question(this, tr("Close the file"), tr("Save changes in ") +
                                           TabWidget->tabText(index).section('*', -1) +
                                           "?", tr("Yes"), tr("No"), tr("Cancel"));
        if (answer == 0)
        {
            TabWidget->setCurrentIndex(index);
            SaveFile();
        }
        else
            if (answer == 2)
                return;
    }
    FileVector->remove(index);
    TabWidget->removeTab(index);
    NameList.removeAt(index);
    showFileViewer(viewer->isVisible());
}

void MainWindow::CloseAllTabs()
{
    int index = TabWidget->currentIndex();
    if (index==-1)
    {
        QMessageBox::critical(this, tr("Warning!"), tr("You have not yet opened any tabs to close!"));
        return;
    }
    bool flag = false;
    for (int i = 0; i < FileVector->size(); ++i)
    {
        if (TabWidget->tabText(i).contains("*"))
        {
            flag = true;
            TabWidget->setTabText(i, TabWidget->tabText(i).section("*", -1));
        }
    }
    if (flag)
    {
        int answer = QMessageBox::question(this, tr("Close all files"), tr("Save changes?"), tr("Yes"), tr("No"), tr("Cancel"));
        if (answer == 0)
            SaveAll();
        else
            if (answer == 2)
                return;
    }
    FileVector->clear();
    TabWidget->clear();
    NameList.clear();
    showFileViewer(viewer->isVisible());
}

void::MainWindow::FileUpdated()
{
    if (!TabWidget->tabText(TabWidget->currentIndex()).contains("*"))
    {
        TabWidget->setTabText(TabWidget->currentIndex(), "*" + TabWidget->tabText(TabWidget->currentIndex()));
    }
}

void MainWindow::Exit(QCloseEvent *event)
{
    SaveExitWindow * dialog = new SaveExitWindow(this);
    dialog->setWindowTitle(tr("Save changes?"));
    dialog->getExitTable()->setColumnCount(2);
    dialog->setFixedSize(400, 400);
    dialog->getExitTable()->setHorizontalHeaderLabels(QStringList()
                                                      << tr("File")
                                                      << tr("Path"));
    dialog->getExitTable()->setFixedSize(400, 400);
    dialog->getExitTable()->horizontalHeader()->setStretchLastSection(true);
    dialog->getExitTable()->verticalHeader()->hide();
    connect(dialog->getYesButton(), SIGNAL(clicked()), this, SLOT(YesClicked()));
    connect(dialog->getNoButton(), SIGNAL(clicked()), this, SLOT(NoClicked()));

    bool flag = false;
    int row = 0;
    QString path;
    for (int i = 0; i<FileVector->size(); ++i)
    {
        if (TabWidget->tabText(i).contains("*"))
        {
            path =QDir::currentPath() + TabWidget->tabText(i).section("*",-1);
            QTableWidgetItem *table_item = new QTableWidgetItem(TabWidget->tabText(i).section("*",-1));
            QTableWidgetItem *table_item1 = new QTableWidgetItem(path);
            dialog->getExitTable()->insertRow(row);
            dialog->getExitTable()->setItem(row, 0, table_item);
            dialog->getExitTable()->setItem(row, 1, table_item1);
            flag = true;
            ++row;
        }
    }
    if (flag)
    {
        dialog->setModal(true);
        if (dialog->exec() == QDialog::Rejected)
        {
            delete dialog;
            event->ignore();
            return;
        }
        delete dialog;
        event->accept();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Exit(event);
}

void MainWindow::YesClicked()
{
    SaveAll();
    FileVector->clear();
    TabWidget->clear();
    NameList.clear();
}

void MainWindow::NoClicked()
{
    FileVector->clear();
    TabWidget->clear();
    NameList.clear();
}

//Edit:
void MainWindow::Cut()
{
    if (TabWidget->currentWidget() == NULL)
    {
        QMessageBox::critical(this, tr("Warning!"), tr("You have not yet opened any tabs to perform this operation!"));
        return;
    }
    qobject_cast<CodeEditor*>(TabWidget->currentWidget())->cut();
}

void MainWindow::Copy()
{
    if (TabWidget->currentWidget() == NULL)
    {
        QMessageBox::critical(this, tr("Warning!"), tr("You have not yet opened any tabs to perform this operation!"));
        return;
    }
    qobject_cast<CodeEditor*>(TabWidget->currentWidget())->copy();
}

void MainWindow::Paste()
{
    if (TabWidget->currentWidget() == NULL)
    {
        QMessageBox::critical(this, tr("Warning!"), tr("You have not yet opened any tabs to perform this operation!"));
        return;
    }
    qobject_cast<CodeEditor*>(TabWidget->currentWidget())->paste();
}

void MainWindow::Clear()
{
    if (TabWidget->currentWidget() == NULL)
    {
        QMessageBox::critical(this, tr("Warning!"), tr("You have not yet opened any tabs to perform this operation!"));
        return;
    }
    qobject_cast<CodeEditor*>(TabWidget->currentWidget())->clear();
}

void MainWindow::Redo()
{
    if (TabWidget->currentWidget() == NULL)
    {
        QMessageBox::critical(this, tr("Warning!"), tr("You have not yet opened any tabs to perform this operation!"));
        return;
    }
    qobject_cast<CodeEditor*>(TabWidget->currentWidget())->redo();
}

void MainWindow::Undo()
{
    if (TabWidget->currentWidget() == NULL)
    {
        QMessageBox::critical(this, tr("Warning!"), tr("You have not yet opened any tabs to perform this operation!"));
        return;
    }
    qobject_cast<CodeEditor*>(TabWidget->currentWidget())->undo();
}

void MainWindow::SelectAll()
{
    if (TabWidget->currentWidget() == NULL)
    {
        QMessageBox::critical(this, tr("Warning!"), tr("You have not yet opened any tabs to perform this operation!"));
        return;
    }
    qobject_cast<CodeEditor*>(TabWidget->currentWidget())->selectAll();
}

void MainWindow::ChangeFont()
{
    if (TabWidget->currentWidget() == NULL)
    {
        QMessageBox::critical(this, tr("Warning!"), tr("You have not yet opened any tabs to perform this operation!"));
        return;
    }
    qobject_cast<CodeEditor*>(TabWidget->currentWidget())->font();
    bool flag; // проверяем наличие выбранного шрифта
    QFont font = QFontDialog::getFont(&flag, this);
    if (flag)
        qobject_cast<CodeEditor*>(TabWidget->currentWidget())->setFont(font);
    else
        return;
}

//View:
void MainWindow::showFileExplorer(bool flag)
{
    QTreeView *FileExplorer = new QTreeView(explorer);
    explorerModel = new QFileSystemModel(explorer);
    explorerModel->setRootPath(QDir::rootPath());
    FileExplorer->setModel(explorerModel);
    explorer->setWidget(FileExplorer);
    explorer->setMaximumWidth(800);
    connect(FileExplorer, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OpenFile(QModelIndex)));
    if (flag)
        explorer->show();
    else
        explorer->hide();
}

void MainWindow::OpenFile(const QModelIndex& index)
{
    if (!explorerModel->hasChildren(index))
    {
        QFile temp_file(explorerModel->filePath(index));
        QString file_name = explorerModel->filePath(index).section('/', -1);
        bool flag = true;
        int index=0;
        for (int i = 0; i < FileVector->size(); ++i)
        {
            if (TabWidget->tabText(i) == file_name)
            {
                flag = false;
                index = i;
            }
        }
        if (flag)
        {
            if (!temp_file.open(QFile::ReadOnly|QFile::Text))
            {
                QMessageBox::critical(this, tr("Warning!"), tr("Cant open the file"));
                return;
            }
            QTextStream TextStream(&temp_file);
            CodeEditor *newFile = new CodeEditor(this);

            if (file_name.contains(".cpp") || file_name.contains(".h") || file_name.contains(".hpp") || file_name.contains(".py"))
            {
                Highlighter * highlighter = new Highlighter(newFile->document());
                if(!highlighter->setSettings(QFileInfo(file_name).suffix()))
                {
                    QMessageBox::warning(this, tr("Error"), tr("A problem with an xml-settings file occured, syntax highlighting not applied to the file"));
                }
            }

            newFile->setPlainText(temp_file.readAll());
            FileVector->push_back(newFile);
            TabWidget->addTab(FileVector->at(FileVector->indexOf(newFile)), file_name);
            TabWidget->setCurrentIndex(FileVector->indexOf(newFile));
            connect(newFile, SIGNAL(textChanged()), SLOT(FileUpdated()));
            NameList << TabWidget->tabText(TabWidget->currentIndex());
            showFileViewer(viewer->isVisible());
            temp_file.flush();
            temp_file.close();
        }
        else
        {
            TabWidget->setCurrentIndex(index);
        }
    }
}

void MainWindow::SelectDocument(const QModelIndex& index)
{
    QString name = viewerModel->data(index).toString();
    TabWidget->setCurrentIndex(NameList.indexOf(name));
}

void MainWindow::showFileViewer(bool flag)
{
    viewerModel = new QStringListModel(viewer);
    QListView *FileViewer = new QListView(viewer);
    viewerModel->setStringList(NameList);
    FileViewer->setModel(viewerModel);
    viewer->setWidget(FileViewer);
    viewer->setMaximumWidth(800);
    connect(FileViewer, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(SelectDocument(QModelIndex)));
    if (flag)
        viewer->show();
    else
        viewer->hide();
}
