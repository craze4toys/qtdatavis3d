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

#ifndef DATAVIS3DQML2_PLUGIN_H
#define DATAVIS3DQML2_PLUGIN_H

#include "datavis3dglobal_p.h"
#include "declarativebars_p.h"
#include "declarativescatter_p.h"
#include "qitemmodelbardatamapping.h"
#include "qitemmodelscatterdatamapping.h"
#include "q3dvalueaxis.h"
#include "q3dcategoryaxis.h"
#include "qitemmodelbardataproxy.h"
#include "qitemmodelscatterdataproxy.h"

#include <QQmlExtensionPlugin>

QT_DATAVIS3D_USE_NAMESPACE

Q_DECLARE_METATYPE(DeclarativeBars *)
Q_DECLARE_METATYPE(DeclarativeScatter *)

Q_DECLARE_METATYPE(QItemModelBarDataMapping *)
Q_DECLARE_METATYPE(QItemModelScatterDataMapping *)
Q_DECLARE_METATYPE(const QAbstractItemModel *)
Q_DECLARE_METATYPE(QDataVis *)

Q_DECLARE_METATYPE(Q3DAbstractAxis *)
Q_DECLARE_METATYPE(Q3DCategoryAxis *)
Q_DECLARE_METATYPE(Q3DValueAxis *)

Q_DECLARE_METATYPE(QAbstractDataProxy *)
Q_DECLARE_METATYPE(QBarDataProxy *)
Q_DECLARE_METATYPE(QItemModelBarDataProxy *)
Q_DECLARE_METATYPE(QScatterDataProxy *)
Q_DECLARE_METATYPE(QItemModelScatterDataProxy *)

QT_DATAVIS3D_BEGIN_NAMESPACE

class Datavis3Dqml2Plugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

QT_DATAVIS3D_END_NAMESPACE

#endif // DATAVIS3DQML2_PLUGIN_H

