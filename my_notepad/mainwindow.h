#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTabWidget>
#include <QDockWidget>
#include <QDialog>
#include <QFileDialog>
#include <QTableWidget>
#include <QEvent>
#include <QSyntaxHighlighter>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>
#include <QStringListModel>
#include <QFont>
#include <QFontDialog>
#include <QHeaderView>

#include "highlighter.h"
#include "codeeditor.h"
#include "saveexitwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    virtual void closeEvent(QCloseEvent *event) override;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void CreateActions();
    void CreateMenu();
public slots:
    void NewFile();
    void OpenFile();
    void OpenFile(const QModelIndex&);
    void SaveFile();
    void SaveFileAs();
    void SaveAll();
    void CloseCurrentTab();
    void CloseAllTabs();
    void Exit(QCloseEvent*);

    void Cut();
    void Copy();
    void Paste();
    void Clear();
    void Redo();
    void Undo();
    void SelectAll();
    void ChangeFont();

    void showFileExplorer(bool);
    void showFileViewer(bool);

    void FileUpdated();
    void SelectDocument(const QModelIndex&);
    void YesClicked();
    void NoClicked();
private:
    //actions
    QAction *new_File_Action;
    QAction *open_File_Action;
    QAction *save_File_Action;
    QAction *save_File_As_Action;
    QAction *save_All_Action;
    QAction *close_Current_Tab_Action;
    QAction *close_All_Tabs_Action;

    QAction *cut_Text_Action;
    QAction *copy_Text_Action;
    QAction *paste_Text_Action;
    QAction *clear_Text_Action;
    QAction *select_All_Action;
    QAction *redo_Text_Action;
    QAction *undo_Text_Action;
    QAction *change_Font_Action;

    QAction *show_Explorer_Action;
    QAction *show_Viewer_Action;

    //private variables
    QWidget * MainWidget;
    QHBoxLayout *Layout;
    QMenu *file_Menu;
    QMenu *edit_Menu;
    QMenu *view_Menu;
    QDockWidget *explorer;
    QFileSystemModel *explorerModel;
    QDockWidget *viewer;
    QStringListModel * viewerModel;
    QToolBar *ToolBar;
    QTabWidget *TabWidget;
    int count=0;
    QVector<CodeEditor*> *FileVector;
    QStringList NameList;
};
#endif // MAINWINDOW_H
