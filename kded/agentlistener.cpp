/*  This file is part of the KDE project

    Copyright (C) 2010  Alex Fiestas <alex@eyeos.org>
    Copyright (C) 2010 by Eduardo Robles Elvira <edulix@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License version 2 as published by the Free Software Foundation.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "agentlistener.h"
#include <QDebug>

AgentListener::AgentListener(): QThread()
{
}

AgentListener::~AgentListener()
{
    m_worker->unregister();
    m_worker->deleteLater();
}


void AgentListener::run()
{
    m_worker = new AgentListenerWorker(new QObject);
    connect(m_worker, SIGNAL(agentReleased()), this, SIGNAL(agentReleased()));
    exec();
}
