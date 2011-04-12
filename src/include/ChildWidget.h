/**********************************************************************
* File:        ChildWidget.h
* Description: ChildWidget functions
* Author:      Marcel Kolodziejczyk
* Created:     2010-01-06
*
* (C) Copyright 2010, Marcel Kolodziejczyk
* (C) Copyright 2011, Zdenko Podobny
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**    http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*
**********************************************************************/

#ifndef CHILDWIDGET_H_
#define CHILDWIDGET_H_

#include <QStandardItemModel>
#include <QTableView>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QtGui/QClipboard>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsRectItem>
#include <QtGui/QMouseEvent>
#include <QtGui/QPixmap>
#include <QtGui/QSplitter>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QtGui/QApplication>
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QtCore/qmath.h>
#include <QTransform>
#include <QSettings>


class QGraphicsScene;
class QGraphicsView;
class QAbstractItemModel;
class QItemSelectionModel;
class QTableView;
class QGraphicsItem;
class QGraphicsRectItem;

class ChildWidget : public QSplitter
{
    Q_OBJECT

  public:
    ChildWidget(QWidget* parent = 0);

    bool isModified()
    {
      return modified;
    }
    bool isBoxSelected();
    bool isBold();
    bool isItalic();
    bool isUnderLine();
    bool isShowSymbol();
    bool isDrawBoxes();
    bool symbolShown;
    bool boxesVisible;

    QString userFriendlyCurrentFile();
    QString currentBoxFile();
    QString canonicalImageFileName()
    {
      return imageFile;
    }

    bool save(const QString& fileName);
    bool loadImage(const QString& fileName);
    bool loadBoxes(const QString& fileName);
    void setSelectionRect();
    void setBolded(bool v);
    void setItalic(bool v);
    void setUnderline(bool v);
    void setZoom(float scale);
    void zoomOriginal();
    void zoomIn();
    void zoomOut();
    void zoomToSelection();
    void zoomToFit();
    void zoomToHeight();
    void zoomToWidth();
    void showSymbol();
    void drawBoxes();
    void deleteBoxes(const QList<QGraphicsItem*> &items);
    void moveSymbolRow(int direction);
    void copyFromCell();
    void pasteToCell();

  public slots:
    void insertSymbol();
    void splitSymbol();
    void joinSymbol();
    void deleteSymbol();

  private slots:
    void documentWasModified();
    void emitBoxChanged();
    void drawSelectionRects();

    void moveUp();
    void moveDown();

  private:
    QColor rectColor;
    QColor rectFillColor;
    QColor boxColor;
    QColor backgroundColor;
    QGraphicsItem* m_message;

  protected:
    virtual void mousePressEvent(QMouseEvent* event);
    bool eventFilter(QObject* object, QEvent* event);
    void closeEvent(QCloseEvent* event);
    bool maybeSave();
    void setCurrentImageFile(const QString& fileName);
    void setCurrentBoxFile(const QString& fileName);

    QString strippedName(const QString& fullFileName);

  signals:
    void boxChanged();
    void modifiedChanged();

  protected:
    QGraphicsScene* imageScene;
    QGraphicsView* imageView;
    QGraphicsItem* imageItem;
    QGraphicsRectItem* imageSelectionRect;
    QGraphicsTextItem* text2;

    QTableView* table;

    QAbstractItemModel* model;
    QItemSelectionModel* selectionModel;

    QString imageFile;
    QString boxFile;

    bool modified;
    int imageHeight;
    int imageWidth;
    int widgetWidth;
};

#endif /* CHILDWIDGET_H_ */
