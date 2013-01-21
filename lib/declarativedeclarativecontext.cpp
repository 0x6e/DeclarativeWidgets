/*
  Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, krake@kdab.com
  Author: Tobias Koenig, tokoe@kdab.com

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "declarativedeclarativecontext_p.h"

#include <QDeclarativeView>

DeclarativeDeclarativeContext::DeclarativeDeclarativeContext(QObject *parent)
  : DeclarativeObjectProxy2<DeclarativeContext>(parent)
{
}

void DeclarativeDeclarativeContext::createProxiedObject() const
{
  AbstractDeclarativeObject *declarativeParent = dynamic_cast<AbstractDeclarativeObject*>(parent());
  if (declarativeParent) {
    DeclarativeContext *parentContext = qobject_cast<DeclarativeContext*>(declarativeParent->object());
    if (parentContext) {
      DeclarativeContext *context = new DeclarativeContext(parentContext);
      m_proxiedObject = QPointer<DeclarativeContext>(context);
      connectAllSignals(m_proxiedObject, this);
      return;
    }
  } else {
    QDeclarativeView *view = qobject_cast<QDeclarativeView*>(parent());
    if (view) {
      DeclarativeContext *context = DeclarativeContext::createWrapper(view->rootContext());
      m_proxiedObject = QPointer<DeclarativeContext>(context);
      connectAllSignals(m_proxiedObject, this);
      return;
    }
  }

  qmlInfo(this) << "Cannot create DeclarativeContext, parent is neither DeclarativeView nor DeclarativeContext";
}

void DeclarativeDeclarativeContext::dataAppend(QObject *object)
{
  DeclarativeContextProperty *contextProperty = qobject_cast<DeclarativeContextProperty*>(object);
  if (contextProperty) {
    if (!m_proxiedObject)
      createProxiedObject();

    contextProperty->setContext(m_proxiedObject);
  }

  DeclarativeObjectProxy2<DeclarativeContext>::dataAppend(object);
}

CUSTOM_METAOBJECT(DeclarativeDeclarativeContext, DeclarativeContext)
