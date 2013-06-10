/*
  Copyright (C) 2012-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, kevin.krammer@kdab.com
  Author: Tobias Koenig, tobias.koenig@kdab.com

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

#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>

class QTextDocument;

class Editor : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QTextDocument* document READ document CONSTANT)
  Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

  Q_PROPERTY(bool undoAvailable READ undoAvailable NOTIFY undoAvailableChanged)
  Q_PROPERTY(bool redoAvailable READ redoAvailable NOTIFY redoAvailableChanged)

  public:
    explicit Editor(QObject *parent = 0);
    ~Editor();

    QTextDocument *document() const;
    bool undoAvailable() const;
    bool redoAvailable() const;

    void setFileName(const QString &fileName);
    QString fileName() const;

  Q_SIGNALS:
    void fileNameChanged(const QString &fileName);
    void requestSaveFileName();
    void undoAvailableChanged();
    void redoAvailableChanged();

    void information(const QString &message);
    void critical(const QString &message);

  public Q_SLOTS:
    void newDocument();
    void open(const QString &fileName);
    void save();

  private Q_SLOTS:
    void undoAvailable(bool);
    void redoAvailable(bool);

  private:
    QTextDocument *m_document;
    QString m_fileName;
    bool m_undoAvailable;
    bool m_redoAvailable;
};

#endif // EDITOR_H
