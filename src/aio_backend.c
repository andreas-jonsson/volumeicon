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

#include <assert.h>
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

#include "aio_backend.h"

//##############################################################################
// Static variables
//##############################################################################
static char *m_channel = NULL;
static GList *m_channel_names = NULL;
static int m_master_volume = 100;
static gboolean m_master_muted = FALSE;

//##############################################################################
// Static functions
//##############################################################################
void set_master_volume(int volume) {
	char buffer[80];
	float fvol = ((float)volume / 100.0f) * 256.0f;

	sprintf(buffer, "mixerctl -w outputs.%s=%d > /dev/null", m_channel, (int)fvol);
	system(buffer);
}

//##############################################################################
// Exported functions
//##############################################################################
const gchar *aio_get_channel() { return m_channel; }

const GList *aio_get_channel_names() { return m_channel_names; }

int aio_get_volume()
{
	return m_master_volume;
}

gboolean aio_get_mute()
{
	return m_master_muted;
}

gboolean aio_setup(const gchar *card, const gchar *channel,
                   void (*volume_changed)(int, gboolean))
{
	m_channel = g_strdup(channel ? channel : "master");
	m_channel_names = g_list_append(m_channel_names, m_channel);	

	char buffer[80];
	sprintf(buffer, "mixerctl -n outputs.%s", m_channel);

	FILE *fp = popen(buffer, "r");
	if (!fp) {
		printf("Failed to run mixerctl!\n" );
		return FALSE;
	}

	if (fscanf(fp, "%d", &m_master_volume) != 1)
		printf("Could not read current volume from mixerctl!\n");
	m_master_volume = (int)(((float)m_master_volume / 255.0f) * 100.0f);

	pclose(fp);
	return TRUE;
}

void aio_set_channel(const gchar *channel)
{
	assert(channel);
	if (m_channel)
		g_free(m_channel);
	m_channel = g_strdup(channel);
}

void aio_set_mute(gboolean mute)
{
	m_master_muted = mute;
	set_master_volume(mute ? 0 : 100);
}

void aio_set_volume(int volume)
{
	m_master_volume = (volume < 0) ? 0 : ((volume > 100) ? 100 : volume);
	set_master_volume(m_master_volume);
}
