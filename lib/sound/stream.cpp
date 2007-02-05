/*
	This file is part of Warzone 2100.
	Copyright (C) 1999-2004  Eidos Interactive
	Copyright (C) 2005-2007  Warzone Resurrection Project

	Warzone 2100 is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	Warzone 2100 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Warzone 2100; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

	$Revision$
	$Id$
	$HeadURL$
*/

#include "stream.hpp"
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>
#include <string>
#include "constants.hpp"

soundStream::soundStream(bool b2D) : source(new soundSource(b2D)), bufferSize(OpenAL_BufferSize), playing(false)
{
}

soundStream::~soundStream()
{
}

boost::weak_ptr<soundSource> soundStream::getSource()
{
    if (source->is2D())
        throw std::string("soundStream: can't retrieve source if stream is 2D");
    return boost::weak_ptr<soundSource>(source);
}

bool soundStream::update()
{
    if (!playing) return false;

    bool buffersFull = true;

    for (unsigned int update = source->numProcessedBuffers() ; update != 0 ; --update)
    {
        boost::shared_ptr<soundBuffer> buffer(source->unqueueBuffer());

        buffersFull = stream(buffer);

        if (buffersFull)
            source->queueBuffer(buffer);
    }

    return buffersFull;
}

bool soundStream::stream(boost::shared_ptr<soundBuffer> buffer)
{
}

bool soundStream::play(bool reset)
{
}

void soundStream::setBufferSize(unsigned int size)
{
    bufferSize = size;
}

unsigned int soundStream::getBufferSize()
{
    return bufferSize;
}
