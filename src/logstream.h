/******************************************************************************
 *
 * package:     Log4Qt
 * file:        logstream.h
 * created:     March, 2011
 * author:      Tim Besard
 *
 *
 * Copyright 2011 Tim Besard
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#ifndef LOG4QT_LOGSTREAM_H
#define LOG4QT_LOGSTREAM_H


/******************************************************************************
 * Dependencies
 ******************************************************************************/

#include <QtCore/QDebug>
#include <QtCore/QString>
#include "level.h"


/******************************************************************************
 * Declarations
 ******************************************************************************/

namespace Log4Qt
{
    class Logger;

    class LOG4QT_EXPORT LogStream : public QDebug
    {

    private:
        QString placeholder;

        struct Stream {
            Stream() : ref(1) {}
            QString buffer;
            int ref;
        } *stream;

    public:
        inline LogStream(const Logger& iLogger, Level iLevel) : QDebug(&placeholder), stream(new Stream()),  mLogger(iLogger), mLevel(iLevel)
        {
            QDebug::operator=(QDebug(&stream->buffer));
        }
        inline LogStream(const LogStream &o) : QDebug(o), stream(o.stream), mLogger(o.mLogger), mLevel(o.mLevel)
        {
            ++stream->ref;
        }
        ~LogStream();

    private:
        const Logger& mLogger;
        Level mLevel;
    };
}

#endif // LOG4QT_LOGSTREAM_H
