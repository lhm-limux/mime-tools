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
#include <KMimeTypeTrader>

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);
    QCoreApplication::setApplicationName("mime-assocs-for");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Given a MIME type, print associated desktop files line-wise.");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("mimeType", "MIME type");

    parser.process(application);

    const QStringList arguments = parser.positionalArguments();

    if (arguments.length() != 1)
    {
        parser.showHelp(1);
    }

    QString mimeType = arguments.at(0);

    QTextStream out(stdout);

    KService::List services = KMimeTypeTrader::self()->query(mimeType);

    if (services.empty())
    {
        return 2;
    }

    for (auto service: services)
    {
        out << service->entryPath() << endl;
    }
    return 0;
}
