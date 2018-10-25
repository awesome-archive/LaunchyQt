/*
Launchy: Application Launcher
Copyright (C) 2007-2010  Josh Karlin, Simon Capewell

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#pragma once

#include <QThread>
#include "catalog_types.h"
#include "plugin_handler.h"

class CatalogBuilder : public QObject, public INotifyProgressStep {
	Q_OBJECT
public:
	CatalogBuilder(PluginHandler* plugin);
    virtual ~CatalogBuilder();

	Catalog* getCatalog() const;
	int getProgress() const;
	int isRunning() const;
	bool progressStep(int newStep);

public slots:
	void buildCatalog();

signals:
	void catalogIncrement(int);
	void catalogFinished();

private:
	void indexDirectory(const QString& dir, const QStringList& filters,
                        bool fdirs, bool fbin, int depth);

	PluginHandler* m_plugin;
	Catalog* m_catalog;
	QSet<QString> m_indexed;
	int m_progress;
	int m_currentItem;
	int m_totalItems;
};

