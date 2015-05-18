#include "SettingsDialog.h"
#include "Field.h"

#include <QApplication>
#include <QFile>

#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication a(argc, argv);
	
	{
		QFile qssFile(":/flyZ/flyZ.qss");
		qssFile.open(QIODevice::ReadOnly);
		a.setStyleSheet(QLatin1String(qssFile.readAll()));
	}

    SettingsDialog settings;

    if (settings.exec())
    {
        Field field(settings.getFieldSize(), settings.getFlyCapacity());
        field.show();
        return a.exec();
    } else
    {
        return 0;
    }
}
