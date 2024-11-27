//##############################################################################
// volumeicon
//
// oss_backend.c - implements a volume control abstraction using oss
//
// Copyright 2011 Maato
// Copyright 2024 Andreas T Jonsson
//
// Authors:
//    Andreas T Jonsson <mail@andreasjonsson.se>
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License version 3, as published
// by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranties of
// MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
// PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.
//##############################################################################

#include <sys/audioio.h>
#include <sys/ioctl.h>
#include <assert.h>
#include <fcntl.h>
#include <glib.h>
#include <stdlib.h>

#include "aio_backend.h"

//##############################################################################
// Static variables
//##############################################################################
static char *m_channel = NULL;
static GList *m_channel_names = NULL;

//##############################################################################
// Static functions
//##############################################################################

//##############################################################################
// Exported functions
//##############################################################################
const gchar *aio_get_channel() { return m_channel; }

const GList *aio_get_channel_names() { return m_channel_names; }

int aio_get_volume()
{
	return 0;
}

gboolean aio_get_mute()
{
	return FALSE;
}

gboolean aio_setup(const gchar *card, const gchar *channel,
                   void (*volume_changed)(int, gboolean))
{
	return TRUE;
}

void aio_set_channel(const gchar *channel)
{
}

void aio_set_mute(gboolean mute)
{
}

void aio_set_volume(int volume)
{
}
