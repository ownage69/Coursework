#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QTextEdit>

class AccessModeDialog : public QDialog {
    Q_OBJECT

private:
    bool adminMode;

public:
    explicit AccessModeDialog(QWidget* parent = nullptr);
    
    bool isAdminMode() const { return adminMode; }

private slots:
    void selectStandardMode();
    void selectAdminMode();
};