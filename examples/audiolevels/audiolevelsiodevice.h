/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the QtDataVis3D module.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#ifndef AUDIOLEVELSIODEVICE_H
#define AUDIOLEVELSIODEVICE_H

#include <QtDataVis3D/qbardataproxy.h>
#include <QIODevice>

QT_DATAVIS3D_USE_NAMESPACE

class AudioLevelsIODevice : public QIODevice
{
    Q_OBJECT
public:
    explicit AudioLevelsIODevice(QBarDataProxy *proxy, QObject *parent = 0);

protected:
    qint64 readData(char *data, qint64 maxSize);
    qint64 writeData(const char *data, qint64 maxSize);

private:
    QBarDataProxy *m_proxy;
    int m_visibleCount;
};

#endif
