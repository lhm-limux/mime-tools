/*
 * Mime association analysis for KDE Plasma 5
 *
 * Copyright (C) 2017 Max Harmathy <max.harmathy@web.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QTextStream>
#include <QTimer>
//#include <KService>


class MimeAssociations : public QObject
{
    Q_OBJECT
public:
    MimeAssociations(const QString mime, QObject *parent);
    ~MimeAssociations();
public slots:
    void process();
signals:
    void done();
private:
    QString mime;
};

#include "mime-assocs-for.moc"

MimeAssociations::MimeAssociations(const QString mime, QObject *parent=0)
    :QObject(parent)
{
    this->mime = mime;
}

MimeAssociations::~MimeAssociations() {}

void MimeAssociations::process()
{
    QTextStream out(stdout);
    out << mime << endl;

    emit done();
}

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);
    QCoreApplication::setApplicationName("mime-assocs-for");

    QCommandLineParser parser;
    parser.setApplicationDescription("Given a MIME type, print associated desktop files line-wise.");
    parser.addHelpOption();
    parser.addPositionalArgument("mimeType", "MIME type");

    parser.process(application);

    const QStringList arguments = parser.positionalArguments();

    if (arguments.length() != 1)
    {
        parser.showHelp();
        return 1;
    }

    MimeAssociations *task = new MimeAssociations(arguments.at(0), &application);
    QObject::connect(task, SIGNAL(done()), &application, SLOT(quit()));
    QTimer::singleShot(0, task, SLOT(process()));

    return application.exec();
}




/*

from PyQt4.QtGui import QApplication

from PyKDE4.kdecore import KMimeType
from PyKDE4.kdecore import KMimeTypeTrader


parser = argparse.ArgumentParser(description = '')
parser.add_argument('mime_type', metavar = 'MIME-type', type = unicode,
  help = 'MIME type')

args = parser.parse_args()

app = QApplication(sys.argv)

if KMimeType.mimeType(args.mime_type, KMimeType.ResolveAliases) is None:
    print('Bad mime type: ' + args.mime_type, file = sys.stderr)
    raise SystemExit(1)

trader = KMimeTypeTrader.self()
services = trader.query(args.mime_type)
desktop_locs = [ unicode(service.entryPath()) for service in services ]
for desktop_loc in desktop_locs:
    print(desktop_loc)
*/
