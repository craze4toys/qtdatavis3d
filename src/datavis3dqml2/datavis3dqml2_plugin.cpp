/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtDataVis3D module.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "datavis3dqml2_plugin.h"

#include <qqml.h>
#include <QDebug>

QT_DATAVIS3D_BEGIN_NAMESPACE

void Datavis3dqml2Plugin::registerTypes(const char *uri)
{
    qDebug() << "Datavis3dqml2Plugin::registerTypes()";

    // @uri com.digia.QtDataVis3D
    qmlRegisterUncreatableType<QAbstractItemModel>(uri, 1, 0, "AbstractItemModel",
                                                   QLatin1String("Trying to create uncreatable: AbstractItemModel."));

    qmlRegisterType<QItemModelBarDataMapping>(uri, 1, 0, "BarDataMapping");
    qmlRegisterType<QItemModelMapDataMapping>(uri, 1, 0, "MapDataMapping");
    qmlRegisterType<QItemModelScatterDataMapping>(uri, 1, 0, "ScatterDataMapping");

    qmlRegisterType<DeclarativeBars>(uri, 1, 0, "Bars3D");
    qmlRegisterType<DeclarativeMaps>(uri, 1, 0, "Maps3D");
    qmlRegisterType<DeclarativeScatter>(uri, 1, 0, "Scatter3D");
}

QT_DATAVIS3D_END_NAMESPACE

