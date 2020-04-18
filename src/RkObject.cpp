/**
 * File name: RkObject.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2020 Iurie Nistor
 *
 * This file is part of Redkite.
 *
 * Redkite is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "RkObject.h"
#include "RkLog.h"
#include "RkObserver.h"

RkObject::RkObject(RkObject *parent)
        : o_ptr{std::make_unique<RkObjectImpl>(this, parent)}
{
        if (o_ptr->parent())
                o_ptr->parent()->addChild(this);
}

RkObject::~RkObject()
{
}

void RkObject::setEventQueue(RkEventQueue* queue)
{
        o_ptr->setEventQueue(queue);
}

RkEventQueue* RkObject::eventQueue()
{
        return o_ptr->eventQueue();
}

void RkObject::event(const RkEvent *event)
{
}

void RkObject::addChild(RkObject* child)
{
        if (child)
                o_ptr->addChild(child);
}

RkEventQueue* RkObject::eventQueue()
{
        return objEventQueue;
}

