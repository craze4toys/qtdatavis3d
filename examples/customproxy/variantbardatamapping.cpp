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

#include "variantbardatamapping.h"

VariantBarDataMapping::VariantBarDataMapping()
    : QObject(0),
      m_rowIndex(0),
      m_columnIndex(1),
      m_valueIndex(2)
{
}

VariantBarDataMapping::VariantBarDataMapping(const VariantBarDataMapping &other)
    : QObject(0),
      m_rowIndex(0),
      m_columnIndex(1),
      m_valueIndex(2)
{
    operator=(other);
}

VariantBarDataMapping::VariantBarDataMapping(int rowIndex, int columnIndex, int valueIndex,
                                             const QStringList &rowCategories,
                                             const QStringList &columnCategories)
    : QObject(0),
      m_rowIndex(0),
      m_columnIndex(1),
      m_valueIndex(2)
{
    m_rowIndex = rowIndex;
    m_columnIndex = columnIndex;
    m_valueIndex = valueIndex;
    m_rowCategories = rowCategories;
    m_columnCategories = columnCategories;
}

VariantBarDataMapping::~VariantBarDataMapping()
{
}

VariantBarDataMapping &VariantBarDataMapping::operator=(const VariantBarDataMapping &other)
{
    m_rowIndex = other.m_rowIndex;
    m_columnIndex = other.m_columnIndex;
    m_valueIndex = other.m_valueIndex;
    m_rowCategories = other.m_rowCategories;
    m_columnCategories = other.m_columnCategories;

    return *this;
}

void VariantBarDataMapping::setRowIndex(int index)
{
    m_rowIndex = index;
    emit mappingChanged();
}

int VariantBarDataMapping::rowIndex() const
{
    return m_rowIndex;
}

void VariantBarDataMapping::setColumnIndex(int index)
{
    m_columnIndex = index;
    emit mappingChanged();
}

int VariantBarDataMapping::columnIndex() const
{
    return m_columnIndex;
}

void VariantBarDataMapping::setValueIndex(int index)
{
    m_valueIndex = index;
    emit mappingChanged();
}

int VariantBarDataMapping::valueIndex() const
{
    return m_valueIndex;
}

void VariantBarDataMapping::setRowCategories(const QStringList &categories)
{
    m_rowCategories = categories;
    emit mappingChanged();
}

const QStringList &VariantBarDataMapping::rowCategories() const
{
    return m_rowCategories;
}

void VariantBarDataMapping::setColumnCategories(const QStringList &categories)
{
    m_columnCategories = categories;
    emit mappingChanged();
}

const QStringList &VariantBarDataMapping::columnCategories() const
{
    return m_columnCategories;
}

void VariantBarDataMapping::remap(int rowIndex, int columnIndex, int valueIndex,
                                  const QStringList &rowCategories,
                                  const QStringList &columnCategories)
{
    m_rowIndex = rowIndex;
    m_columnIndex = columnIndex;
    m_valueIndex = valueIndex;
    m_rowCategories = rowCategories;
    m_columnCategories = columnCategories;
    emit mappingChanged();
}
