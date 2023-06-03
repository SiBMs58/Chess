//
// Created by toonc on 12/17/2021.
//

#include <QFileDialog>
#include <QMessageBox>

bool openFileToWrite(QFile& file) {
    QString fileName = QFileDialog::getSaveFileName(nullptr,
                                                    ("Save game"), "",
                                                    ("Chess File (*.chs);;All Files (*)"));
    if (fileName.isEmpty())
        return false;
    else {
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(nullptr, ("Unable to open file"),
                                     file.errorString());
            return false;
        }
    }

    return true;
}

bool openFileToRead(QFile& file) {
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    ("Load game"), "",
                                                    ("Chess File (*.chs);;All Files (*)"));
    if (fileName.isEmpty())
        return false;
    else {
        file.setFileName(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(nullptr, ("Unable to open file"),
                                     file.errorString());
            return false;
        }
    }

    return true;
}
