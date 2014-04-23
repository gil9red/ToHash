#ifndef CRC32_H
#define CRC32_H

#include <QString>
#include <QIODevice>

class CRC32
{
public:
    static quint32 fromIODevice( QIODevice * device );
    static quint32 fromByteArray( const QByteArray & array );
    static quint32 fromString( const QString & text );
    static quint32 fromFile( const QString & fileName );
};

#endif // CRC32_H
