/*
 * gedit-bookmarks-message-goto-next.c
 * This file is part of gedit
 *
 * Copyright (C) 2011 - Paolo Borelli
 *
 * gedit is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * gedit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gedit; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 */

#include <gtk/gtk.h>
#include <gedit/gedit-view.h>
#include "gedit-bookmarks-message-goto-next.h"

#define GEDIT_BOOKMARKS_MESSAGE_GOTO_NEXT_GET_PRIVATE(object)(G_TYPE_INSTANCE_GET_PRIVATE((object), GEDIT_TYPE_BOOKMARKS_MESSAGE_GOTO_NEXT, GeditBookmarksMessageGotoNextPrivate))

enum
{
	PROP_0,

	PROP_VIEW,
	PROP_ITER,
};

struct _GeditBookmarksMessageGotoNextPrivate
{
	GeditView *view;
	GtkTextIter *iter;
};

G_DEFINE_TYPE (GeditBookmarksMessageGotoNext, gedit_bookmarks_message_goto_next, GEDIT_TYPE_MESSAGE)

static void
gedit_bookmarks_message_goto_next_finalize (GObject *obj)
{
	GeditBookmarksMessageGotoNext *msg = GEDIT_BOOKMARKS_MESSAGE_GOTO_NEXT (obj);

	if (msg->priv->view)
	{
		g_object_unref (msg->priv->view);
	}
	if (msg->priv->iter)
	{
		g_object_unref (msg->priv->iter);
	}

	G_OBJECT_CLASS (gedit_bookmarks_message_goto_next_parent_class)->finalize (obj);
}

static void
gedit_bookmarks_message_goto_next_get_property (GObject    *obj,
                                                guint       prop_id,
                                                GValue     *value,
                                                GParamSpec *pspec)
{
	GeditBookmarksMessageGotoNext *msg;

	msg = GEDIT_BOOKMARKS_MESSAGE_GOTO_NEXT (obj);

	switch (prop_id)
	{
		case PROP_VIEW:
			g_value_set_object (value, msg->priv->view);
			break;
		case PROP_ITER:
			g_value_set_boxed (value, msg->priv->iter);
			break;
	}
}

static void
gedit_bookmarks_message_goto_next_set_property (GObject      *obj,
                                                guint         prop_id,
                                                GValue const *value,
                                                GParamSpec   *pspec)
{
	GeditBookmarksMessageGotoNext *msg;

	msg = GEDIT_BOOKMARKS_MESSAGE_GOTO_NEXT (obj);

	switch (prop_id)
	{
		case PROP_VIEW:
		{
			if (msg->priv->view)
			{
				g_object_unref (msg->priv->view);
			}
			msg->priv->view = g_value_dup_object (value);
			break;
		}
		case PROP_ITER:
		{
			if (msg->priv->iter)
			{
				g_boxed_free (GTK_TYPE_TEXT_ITER, msg->priv->iter);
			}
			msg->priv->iter = g_boxed_copy (GTK_TYPE_TEXT_ITER, value);
			break;
		}
	}
}

static void
gedit_bookmarks_message_goto_next_class_init (GeditBookmarksMessageGotoNextClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->finalize = gedit_bookmarks_message_goto_next_finalize;

	object_class->get_property = gedit_bookmarks_message_goto_next_get_property;
	object_class->set_property = gedit_bookmarks_message_goto_next_set_property;

	g_object_class_install_property (object_class,
	                                 PROP_VIEW,
	                                 g_param_spec_object ("view",
	                                                      "View",
	                                                      "View",
	                                                      GEDIT_TYPE_VIEW,
	                                                      G_PARAM_READWRITE |
	                                                      G_PARAM_CONSTRUCT |
	                                                      G_PARAM_STATIC_STRINGS));

	g_object_class_install_property (object_class,
	                                 PROP_ITER,
	                                 g_param_spec_boxed ("iter",
	                                                      "Iter",
	                                                      "Iter",
	                                                      GTK_TYPE_TEXT_ITER,
	                                                      G_PARAM_READWRITE |
	                                                      G_PARAM_CONSTRUCT |
	                                                      G_PARAM_STATIC_STRINGS));

	g_type_class_add_private (object_class, sizeof (GeditBookmarksMessageGotoNextPrivate));
}

static void
gedit_bookmarks_message_goto_next_init (GeditBookmarksMessageGotoNext *message)
{
	message->priv = GEDIT_BOOKMARKS_MESSAGE_GOTO_NEXT_GET_PRIVATE (message);
}
