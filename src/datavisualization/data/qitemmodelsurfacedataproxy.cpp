/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#include "qitemmodelsurfacedataproxy_p.h"
#include "surfaceitemmodelhandler_p.h"
#include <QTimer>

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

/*!
 * \class QItemModelSurfaceDataProxy
 * \inmodule QtDataVisualization
 * \brief Proxy class for presenting data in item models with Q3DSurface.
 * \since Qt Data Visualization 1.0
 *
 * QItemModelSurfaceDataProxy allows you to use QAbstractItemModel derived models as a data source
 * for Q3DSurface. It uses the defined mappings to map data from the model to rows, columns, and
 * values of Q3DSurface graph.
 *
 * Data is resolved asynchronously whenever the mapping or the model changes.
 * QSurfaceDataProxy::arrayReset() is emitted when the data has been resolved.
 *
 * There are three ways to use mappings:
 *
 * 1) If useModelCategories property is set to true, this proxy will map rows and
 *    columns of QAbstractItemModel to rows and columns of Q3DSurface, and uses the value returned for
 *    Qt::DisplayRole as bar value by default.
 *    The value role to be used can be redefined if Qt::DisplayRole is not suitable.
 *
 * 2) For models that do not have data already neatly sorted into rows and columns, such as
 *    QAbstractListModel based models, you can define a role from the model to map for each of row,
 *    column and value.
 *
 * 3) If you do not want to include all data contained in the model, or the autogenerated rows and
 *    columns are not ordered as you wish, you can specify which rows and columns should be included
 *    and in which order by defining an explicit list of categories for either or both of rows and
 *    columns.
 *
 *    For example, assume that you have a custom QAbstractItemModel storing surface topography data.
 *    Each item in the model has the roles "longitude", "latitude", and "height". The item model already
 *    contains the data properly sorted so that longitudes and latitudes are first encountered in
 *    correct order, which enables us to utilize the row and column category autogeneration.
 *    You could do the following to display the data in a surface graph:
 *
 *    \snippet doc_src_qtdatavisualization.cpp 5
 *
 * \sa {Qt Data Visualization Data Handling}
 */

/*!
 * \qmltype ItemModelSurfaceDataProxy
 * \inqmlmodule QtDataVisualization
 * \since QtDataVisualization 1.0
 * \ingroup datavisualization_qml
 * \instantiates QItemModelSurfaceDataProxy
 * \inherits SurfaceDataProxy
 * \brief Proxy class for presenting data in item models with Surface3D.
 *
 * This type allows you to use AbstractItemModel derived models as a data source for Surface3D.
 *
 * Data is resolved asynchronously whenever the mapping or the model changes.
 * QSurfaceDataProxy::arrayReset() is emitted when the data has been resolved.
 *
 * For more details, see QItemModelSurfaceDataProxy documentation.
 *
 * Usage example:
 *
 * \snippet doc_src_qmldatavisualization.cpp 9
 *
 * \sa SurfaceDataProxy, {Qt Data Visualization Data Handling}
 */

/*!
 * \qmlproperty list ItemModelSurfaceDataProxy::itemModel
 * The item model.
 */

/*!
 * \qmlproperty string ItemModelSurfaceDataProxy::rowRole
 * The row role of the mapping.
 * In addition to defining which row the data belongs to, the value indicated by row role
 * is also set as the Z-coordinate value of the QSurfaceDataItem when model data is resolved.
 */

/*!
 * \qmlproperty string ItemModelSurfaceDataProxy::columnRole
 * The column role of the mapping.
 * In addition to defining which column the data belongs to, the value indicated by column role
 * is also set as the X-coordinate value of the QSurfaceDataItem when model data is resolved.
 */

/*!
 * \qmlproperty string ItemModelSurfaceDataProxy::valueRole
 * The value role of the mapping.
 * The value indicated by value role is set as Y-coodrinate value of the
 * QSurfaceDataItem when model data is resolved.
 */

/*!
 * \qmlproperty list ItemModelSurfaceDataProxy::rowCategories
 * The row categories of the mapping. Only items with row roles that are found in this list are
 * included when data is resolved. The rows are ordered in the same order as they are in this list.
 */

/*!
 * \qmlproperty list ItemModelSurfaceDataProxy::columnCategories
 * The column categories of the mapping. Only items with column roles that are found in this list are
 * included when data is resolved. The columns are ordered in the same order as they are in this list.
 */

/*!
 * \qmlproperty list ItemModelSurfaceDataProxy::useModelCategories
 * When set to true, the mapping ignores row and column roles and categories, and uses
 * the rows and columns from the model instead. Defaults to false.
 */

/*!
 * \qmlproperty list ItemModelSurfaceDataProxy::autoRowCategories
 * When set to true, the mapping ignores any explicitly set row categories
 * and overwrites them with automatically generated ones whenever the
 * data from model is resolved. Proxy minimum and maximum row values are also
 * autogenerated from data when this is set to true. Defaults to true.
 */

/*!
 * \qmlproperty list ItemModelSurfaceDataProxy::autoColumnCategories
 * When set to true, the mapping ignores any explicitly set column categories
 * and overwrites them with automatically generated ones whenever the
 * data from model is resolved. Proxy minimum and maximum column values are also
 * autogenerated from data when this is set to true. Defaults to true.
 */

/*!
 * Constructs QItemModelSurfaceDataProxy with optional \a parent.
 */
QItemModelSurfaceDataProxy::QItemModelSurfaceDataProxy(QObject *parent)
    : QSurfaceDataProxy(new QItemModelSurfaceDataProxyPrivate(this), parent)
{
    dptr()->connectItemModelHandler();
}

/*!
 * Constructs QItemModelSurfaceDataProxy with \a itemModel and optional \a parent. Proxy doesn't take
 * ownership of the \a itemModel, as typically item models are owned by other controls.
 */
QItemModelSurfaceDataProxy::QItemModelSurfaceDataProxy(const QAbstractItemModel *itemModel,
                                                       QObject *parent)
    : QSurfaceDataProxy(new QItemModelSurfaceDataProxyPrivate(this), parent)
{
    dptr()->m_itemModelHandler->setItemModel(itemModel);
    dptr()->connectItemModelHandler();
}

/*!
 * Constructs QItemModelSurfaceDataProxy with \a itemModel and optional \a parent. Proxy doesn't take
 * ownership of the \a itemModel, as typically item models are owned by other controls.
 * The value role is set to \a valueRole.
 * This constructor is meant to be used with models that have data properly sorted
 * in rows and columns already, so it also sets useModelCategories property to true.
 */
QItemModelSurfaceDataProxy::QItemModelSurfaceDataProxy(const QAbstractItemModel *itemModel,
                                                       const QString &valueRole,
                                                       QObject *parent)
    : QSurfaceDataProxy(new QItemModelSurfaceDataProxyPrivate(this), parent)
{
    dptr()->m_itemModelHandler->setItemModel(itemModel);
    dptr()->m_valueRole = valueRole;
    dptr()->m_useModelCategories = true;
    dptr()->connectItemModelHandler();
}

/*!
 * Constructs QItemModelSurfaceDataProxy with \a itemModel and optional \a parent. Proxy doesn't take
 * ownership of the \a itemModel, as typically item models are owned by other controls.
 * The role mappings are set with \a rowRole, \a columnRole, and \a valueRole.
 */
QItemModelSurfaceDataProxy::QItemModelSurfaceDataProxy(const QAbstractItemModel *itemModel,
                                                       const QString &rowRole,
                                                       const QString &columnRole,
                                                       const QString &valueRole,
                                                       QObject *parent)
    : QSurfaceDataProxy(new QItemModelSurfaceDataProxyPrivate(this), parent)
{
    dptr()->m_itemModelHandler->setItemModel(itemModel);
    dptr()->m_rowRole = rowRole;
    dptr()->m_columnRole = columnRole;
    dptr()->m_valueRole = valueRole;
    dptr()->connectItemModelHandler();
}

/*!
 * Constructs QItemModelSurfaceDataProxy with \a itemModel and optional \a parent. Proxy doesn't take
 * ownership of the \a itemModel, as typically item models are owned by other controls.
 * The role mappings are set with \a rowRole, \a columnRole, and \a valueRole.
 * Row and column categories are set with \a rowCategories and \a columnCategories.
 * This constructor also sets autoRowCategories and autoColumnCategories to false.
 */
QItemModelSurfaceDataProxy::QItemModelSurfaceDataProxy(const QAbstractItemModel *itemModel,
                                                       const QString &rowRole,
                                                       const QString &columnRole,
                                                       const QString &valueRole,
                                                       const QStringList &rowCategories,
                                                       const QStringList &columnCategories,
                                                       QObject *parent)
    : QSurfaceDataProxy(new QItemModelSurfaceDataProxyPrivate(this), parent)
{
    dptr()->m_itemModelHandler->setItemModel(itemModel);
    dptr()->m_rowRole = rowRole;
    dptr()->m_columnRole = columnRole;
    dptr()->m_valueRole = valueRole;
    dptr()->m_rowCategories = rowCategories;
    dptr()->m_columnCategories = columnCategories;
    dptr()->m_autoRowCategories = false;
    dptr()->m_autoColumnCategories = false;
    dptr()->connectItemModelHandler();
}

/*!
 * Destroys QItemModelSurfaceDataProxy.
 */
QItemModelSurfaceDataProxy::~QItemModelSurfaceDataProxy()
{
}

/*!
 * \property QItemModelSurfaceDataProxy::itemModel
 *
 * Defines item model. Does not take ownership of the model, but does connect to it to listen for
 * changes.
 */
void QItemModelSurfaceDataProxy::setItemModel(const QAbstractItemModel *itemModel)
{
    dptr()->m_itemModelHandler->setItemModel(itemModel);
}

const QAbstractItemModel *QItemModelSurfaceDataProxy::itemModel() const
{
    return dptrc()->m_itemModelHandler->itemModel();
}

/*!
 * \property QItemModelSurfaceDataProxy::rowRole
 *
 * Defines the row role for the mapping.
 */
void QItemModelSurfaceDataProxy::setRowRole(const QString &role)
{
    if (dptr()->m_rowRole != role) {
        dptr()->m_rowRole = role;
        emit rowRoleChanged(role);
    }
}

QString QItemModelSurfaceDataProxy::rowRole() const
{
    return dptrc()->m_rowRole;
}

/*!
 * \property QItemModelSurfaceDataProxy::columnRole
 *
 * Defines the column role for the mapping.
 */
void QItemModelSurfaceDataProxy::setColumnRole(const QString &role)
{
    if (dptr()->m_columnRole != role) {
        dptr()->m_columnRole = role;
        emit columnRoleChanged(role);
    }
}

QString QItemModelSurfaceDataProxy::columnRole() const
{
    return dptrc()->m_columnRole;
}

/*!
 * \property QItemModelSurfaceDataProxy::valueRole
 *
 * Defines the value role for the mapping.
 */
void QItemModelSurfaceDataProxy::setValueRole(const QString &role)
{
    if (dptr()->m_valueRole != role) {
        dptr()->m_valueRole = role;
        emit valueRoleChanged(role);
    }
}

QString QItemModelSurfaceDataProxy::valueRole() const
{
    return dptrc()->m_valueRole;
}

/*!
 * \property QItemModelSurfaceDataProxy::rowCategories
 *
 * Defines the row categories for the mapping.
 */
void QItemModelSurfaceDataProxy::setRowCategories(const QStringList &categories)
{
    if (dptr()->m_rowCategories != categories) {
        dptr()->m_rowCategories = categories;
        emit rowCategoriesChanged(categories);
    }
}

QStringList QItemModelSurfaceDataProxy::rowCategories() const
{
    return dptrc()->m_rowCategories;
}

/*!
 * \property QItemModelSurfaceDataProxy::columnCategories
 *
 * Defines the column categories for the mapping.
 */
void QItemModelSurfaceDataProxy::setColumnCategories(const QStringList &categories)
{
    if (dptr()->m_columnCategories != categories) {
        dptr()->m_columnCategories = categories;
        emit columnCategoriesChanged(categories);
    }
}

QStringList QItemModelSurfaceDataProxy::columnCategories() const
{
    return dptrc()->m_columnCategories;
}

/*!
 * \property QItemModelSurfaceDataProxy::useModelCategories
 *
 * When set to true, the mapping ignores row and column roles and categories, and uses
 * the rows and columns from the model instead. Defaults to false.
 */
void QItemModelSurfaceDataProxy::setUseModelCategories(bool enable)
{
    if (dptr()->m_useModelCategories != enable) {
        dptr()->m_useModelCategories = enable;
        emit useModelCategoriesChanged(enable);
    }
}

bool QItemModelSurfaceDataProxy::useModelCategories() const
{
    return dptrc()->m_useModelCategories;
}

/*!
 * \property QItemModelSurfaceDataProxy::autoRowCategories
 *
 * When set to true, the mapping ignores any explicitly set row categories
 * and overwrites them with automatically generated ones whenever the
 * data from model is resolved. Defaults to true.
 */
void QItemModelSurfaceDataProxy::setAutoRowCategories(bool enable)
{
    if (dptr()->m_autoRowCategories != enable) {
        dptr()->m_autoRowCategories = enable;
        emit autoRowCategoriesChanged(enable);
    }
}

bool QItemModelSurfaceDataProxy::autoRowCategories() const
{
    return dptrc()->m_autoRowCategories;
}

/*!
 * \property QItemModelSurfaceDataProxy::autoColumnCategories
 *
 * When set to true, the mapping ignores any explicitly set column categories
 * and overwrites them with automatically generated ones whenever the
 * data from model is resolved. Defaults to true.
 */
void QItemModelSurfaceDataProxy::setAutoColumnCategories(bool enable)
{
    if (dptr()->m_autoColumnCategories != enable) {
        dptr()->m_autoColumnCategories = enable;
        emit autoColumnCategoriesChanged(enable);
    }
}

bool QItemModelSurfaceDataProxy::autoColumnCategories() const
{
    return dptrc()->m_autoColumnCategories;
}

/*!
 * Changes \a rowRole, \a columnRole, \a valueRole, \a rowCategories and \a columnCategories to the
 * mapping.
 */
void QItemModelSurfaceDataProxy::remap(const QString &rowRole,
                                       const QString &columnRole,
                                       const QString &valueRole,
                                       const QStringList &rowCategories,
                                       const QStringList &columnCategories)
{
    setRowRole(rowRole);
    setColumnRole(columnRole);
    setValueRole(valueRole);
    setRowCategories(rowCategories);
    setColumnCategories(columnCategories);
}

/*!
 * /return index of the specified \a category in row categories list.
 * If the row categories list is empty, -1 is returned.
 * \note If the automatic row categories generation is in use, this method will
 * not return a valid index before the data in the model is resolved for the first time.
 */
int QItemModelSurfaceDataProxy::rowCategoryIndex(const QString &category)
{
    return dptr()->m_rowCategories.indexOf(category);
}

/*!
 * /return index of the specified \a category in column categories list.
 * If the category is not found, -1 is returned.
 * \note If the automatic column categories generation is in use, this method will
 * not return a valid index before the data in the model is resolved for the first time.
 */
int QItemModelSurfaceDataProxy::columnCategoryIndex(const QString &category)
{
    return dptr()->m_columnCategories.indexOf(category);
}

/*!
 * \internal
 */
QItemModelSurfaceDataProxyPrivate *QItemModelSurfaceDataProxy::dptr()
{
    return static_cast<QItemModelSurfaceDataProxyPrivate *>(d_ptr.data());
}

/*!
 * \internal
 */
const QItemModelSurfaceDataProxyPrivate *QItemModelSurfaceDataProxy::dptrc() const
{
    return static_cast<const QItemModelSurfaceDataProxyPrivate *>(d_ptr.data());
}

// QItemModelSurfaceDataProxyPrivate

QItemModelSurfaceDataProxyPrivate::QItemModelSurfaceDataProxyPrivate(QItemModelSurfaceDataProxy *q)
    : QSurfaceDataProxyPrivate(q),
      m_itemModelHandler(new SurfaceItemModelHandler(q)),
      m_useModelCategories(false),
      m_autoRowCategories(true),
      m_autoColumnCategories(true)
{
}

QItemModelSurfaceDataProxyPrivate::~QItemModelSurfaceDataProxyPrivate()
{
    delete m_itemModelHandler;
}

QItemModelSurfaceDataProxy *QItemModelSurfaceDataProxyPrivate::qptr()
{
    return static_cast<QItemModelSurfaceDataProxy *>(q_ptr);
}

void QItemModelSurfaceDataProxyPrivate::connectItemModelHandler()
{
    QObject::connect(m_itemModelHandler, &SurfaceItemModelHandler::itemModelChanged,
                     qptr(), &QItemModelSurfaceDataProxy::itemModelChanged);
    QObject::connect(qptr(), &QItemModelSurfaceDataProxy::rowRoleChanged,
                     m_itemModelHandler, &AbstractItemModelHandler::handleMappingChanged);
    QObject::connect(qptr(), &QItemModelSurfaceDataProxy::columnRoleChanged,
                     m_itemModelHandler, &AbstractItemModelHandler::handleMappingChanged);
    QObject::connect(qptr(), &QItemModelSurfaceDataProxy::valueRoleChanged,
                     m_itemModelHandler, &AbstractItemModelHandler::handleMappingChanged);
    QObject::connect(qptr(), &QItemModelSurfaceDataProxy::rowCategoriesChanged,
                     m_itemModelHandler, &AbstractItemModelHandler::handleMappingChanged);
    QObject::connect(qptr(), &QItemModelSurfaceDataProxy::columnCategoriesChanged,
                     m_itemModelHandler, &AbstractItemModelHandler::handleMappingChanged);
    QObject::connect(qptr(), &QItemModelSurfaceDataProxy::useModelCategoriesChanged,
                     m_itemModelHandler, &AbstractItemModelHandler::handleMappingChanged);
    QObject::connect(qptr(), &QItemModelSurfaceDataProxy::autoRowCategoriesChanged,
                     m_itemModelHandler, &AbstractItemModelHandler::handleMappingChanged);
    QObject::connect(qptr(), &QItemModelSurfaceDataProxy::autoColumnCategoriesChanged,
                     m_itemModelHandler, &AbstractItemModelHandler::handleMappingChanged);
}

QT_END_NAMESPACE_DATAVISUALIZATION
