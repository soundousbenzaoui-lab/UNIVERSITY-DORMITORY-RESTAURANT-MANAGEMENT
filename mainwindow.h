#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QComboBox>
#include <QStringList>

// ── Existing project classes (UNCHANGED) ──
#include "University.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    // ── Navigation ──
    void onNavDashboard();
    void onNavUniversity();
    void onNavDormitory();
    void onNavRoom();
    void onNavStudent();
    void onNavRestaurant();

    // ── University ──
    void onSetUniversityName();

    // ── Dormitory ──
    void onAddDormitory();
    void onDeleteDormitory();
    void onSearchDormitory();

    // ── Room ──
    void onRoomDormitoryChanged();
    void onAddRoom();
    void onDeleteRoom();

    // ── Student ──
    void onStudentDormitoryChanged();
    void onAddStudent();
    void onDeleteStudent();
    void onSearchStudent();

    // ── Restaurant ──
    void onRestaurantDormitoryChanged();
    void onAddMealItem();
    void onRemoveMealItem();

private:
    Ui::MainWindow* ui;

    // ── The single core model object (logic untouched) ──
    University m_university;

    // ── Recent activity log (UI-only, does not affect business logic) ──
    QStringList m_recentActivity;
    void logActivity(const QString& text);

    // ── Setup helpers ──
    void applyTheme();
    void connectSignals();
    void setupTables();
    void setActiveNav(int pageIndex);

    // ── Refresh helpers ──
    void refreshDashboard();
    void refreshUniversityPage();
    void refreshDormitoryTable();
    void refreshDormitoryCombos();
    void refreshRoomTable();
    void refreshRoomCombo();
    void refreshStudentTable();
    void refreshRestaurantLists();

    QString currentDormName(QComboBox* combo) const;
};

#endif // MAINWINDOW_H
