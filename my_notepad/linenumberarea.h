#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include "codeeditor.h"
#include <QSize>

class LineNumberArea : public QWidget
{
    Q_OBJECT
public:
    LineNumberArea(CodeEditor *editor);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    CodeEditor *codeEditor;

};

#endif // LINENUMBERAREA_H
