#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{}

bool Highlighter::setSettings(QString string)
{
    QDomDocument document (":/pngs/XML_settings.xml");
    QFile file (":/pngs/XML_settings.xml");
    if (!file.open(QIODevice::ReadOnly))
    {
        return 0;
    }
    if (!document.setContent(&file))
    {
        file.close();
        return 0;
    }

    file.close();
    highlightingRules.clear();

    QDomNode syntaxes = document.documentElement().namedItem("syntaxes");
    QDomElement pattern, format;
    HighlightingRule HR;
    QString nodeName;
    // syntax loop for different languages;
    for(auto syntax = syntaxes.firstChild(); !syntax.isNull(); syntax = syntax.nextSibling())
    {
        if (!syntax.toElement().attribute("ext_list").contains(string))
            continue;
        for (auto rule = syntax.firstChild(); !rule.isNull(); rule = rule.nextSibling())
        {
            nodeName = rule.toElement().tagName();
            if(nodeName == "rule")
            {
                pattern = rule.namedItem("pattern").toElement();
                format = rule.namedItem("format").toElement();
                HR.pattern = QRegularExpression(pattern.attribute("value"));
                HR.format.setForeground(QColor(format.attribute("foreground")));
                HR.format.setFontWeight(format.attribute("font_weight").toInt());
                highlightingRules.append(HR);
            }
            else
            if (nodeName == "startComment")
            {
                pattern = rule.namedItem("pattern").toElement();
                commentStartExpression = QRegularExpression(pattern.attribute("value"));
            }
            else
            if (nodeName == "endComment")
            {
                pattern = rule.namedItem("pattern").toElement();
                commentEndExpression = QRegularExpression(pattern.attribute("value"));
            }
            else
            if (nodeName == "multiLineComment")
            {
                format = rule.namedItem("format").toElement();
                multiLineCommentFormat.setForeground(QColor(format.attribute("foreground")));
            }
        }
    }
    return 1;
}


void Highlighter::highlightBlock(const QString &text)
{
    if (highlightingRules.isEmpty())
    {
        return;
    }

    for (const HighlightingRule &rule : qAsConst(highlightingRules))
    {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    setCurrentBlockState(0);
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

    while (startIndex >= 0)
    {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
