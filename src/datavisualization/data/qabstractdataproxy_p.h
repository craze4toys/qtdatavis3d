/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the QtDataVisualization module.
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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the QtDataVisualization API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#include "datavisualizationglobal_p.h"
#include "qabstractdataproxy.h"
#include <QString>

#ifndef QABSTRACTDATAPROXY_P_H
#define QABSTRACTDATAPROXY_P_H

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

class QAbstract3DSeries;

class QAbstractDataProxyPrivate : public QObject
{
    Q_OBJECT
public:
    QAbstractDataProxyPrivate(QAbstractDataProxy *q, QAbstractDataProxy::DataType type);
    virtual ~QAbstractDataProxyPrivate();

    inline QAbstract3DSeries *series() { return m_series; }
    virtual void setSeries(QAbstract3DSeries *series);

protected:
    QAbstractDataProxy *q_ptr;
    QAbstractDataProxy::DataType m_type;
    QAbstract3DSeries *m_series;

private:
    friend class QAbstractDataProxy;
};

QT_END_NAMESPACE_DATAVISUALIZATION

#endif
