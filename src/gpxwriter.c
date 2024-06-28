#include <stdlib.h>
#include <string.h>

#include "gpxwriter.h"
#include "platform.h"

extern char* get_bb_version(bool);

#define GPS_DEGREES_DIVIDER 10000000L

static const char GPX_FILE_HEADER[] =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<gpx creator=\"blackbox_decode v%s\" version=\"1.1\" xmlns=\"http://www.topografix.com/GPX/1/1\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""
        " xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd\">\n"
    "<metadata><name>Blackbox flight log</name>\n"
    " <link href=\"https://github.com/iNavFlight/blackbox-tools\">\n"
    " <text>INAV Blackbox Tools</text>\n"
    " </link>\n"
    "</metadata>\n";

static const char GPX_FILE_TRAILER[] =
    "</gpx>";

void gpxWriterAddPreamble(gpxWriter_t *gpx)
{
    gpx->file = fopen(gpx->filename, "wb");

    fprintf(gpx->file, GPX_FILE_HEADER, get_bb_version(true));
}

/**
 * Add a point to the current track.
 *
 * Time is in microseconds since device power-on. Lat and lon are degrees multiplied by GPS_DEGREES_DIVIDER. Altitude
 * is in meters.
 */
void gpxWriterAddPoint(gpxWriter_t *gpx, flightLog_t *log, int64_t time, int32_t lat, int32_t lon, int16_t altitude)
{
    char negSign[] = "-";
    char noSign[] = "";

    if (!gpx)
        return;

    if (gpx->state == GPXWRITER_STATE_EMPTY) {
        gpxWriterAddPreamble(gpx);

        fprintf(gpx->file, "<trk><name>Blackbox flight log</name><trkseg>\n");

        gpx->state = GPXWRITER_STATE_WRITING_TRACK;
    }

    int32_t latDegrees = lat / GPS_DEGREES_DIVIDER;
    int32_t lonDegrees = lon / GPS_DEGREES_DIVIDER;

    uint32_t latFracDegrees = abs(lat) % GPS_DEGREES_DIVIDER;
    uint32_t lonFracDegrees = abs(lon) % GPS_DEGREES_DIVIDER;

    char *latSign = ((lat < 0) && (latDegrees == 0)) ? negSign : noSign;
    char *lonSign = ((lon < 0) && (lonDegrees == 0)) ? negSign : noSign;

    fprintf(gpx->file, "  <trkpt lat=\"%s%d.%07u\" lon=\"%s%d.%07u\"><ele>%d</ele>", latSign, latDegrees, latFracDegrees, lonSign, lonDegrees, lonFracDegrees, altitude);

    if (time != -1) {
	char tbuf[32];
	format_gps_timez(log, time, tbuf, sizeof(tbuf));
	fprintf(gpx->file, "<time>%s</time>", tbuf);
    }
    fprintf(gpx->file, "</trkpt>\n");
}

gpxWriter_t* gpxWriterCreate(const char *filename)
{
    gpxWriter_t *result = malloc(sizeof(*result));

    result->filename = strdup(filename);
    result->state = GPXWRITER_STATE_EMPTY;
    result->file = NULL;

    return result;
}

void gpxWriterDestroy(gpxWriter_t* gpx)
{
    if (!gpx)
        return;

    if (gpx->state == GPXWRITER_STATE_WRITING_TRACK) {
        fprintf(gpx->file, "</trkseg></trk>\n");
    }

    if (gpx->state != GPXWRITER_STATE_EMPTY) {
        fprintf(gpx->file, GPX_FILE_TRAILER);
        fclose(gpx->file);
    }

    free(gpx->filename);
    free(gpx);
}
