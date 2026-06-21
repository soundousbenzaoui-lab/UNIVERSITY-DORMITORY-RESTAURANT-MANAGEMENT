#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QHeaderView>
#include <QGraphicsDropShadowEffect>
#include <QDateTime>

// ════════════════════════════════════════════════════════════
// NOTE: This file only wires the existing project logic
// (Student / Room / Restaurant / Dormitory / University) to the
// Qt UI. No business logic was added or changed — every action
// below simply calls a method that already existed in your
// original classes. The Dashboard page is purely a UI summary
// built from existing getters (getNumberOfDormitories,
// getTotalRooms, getAvailableRooms, getTotalOccupancy, menus).
// ════════════════════════════════════════════════════════════

// ────────────────────────────────────────────────────────────
// Small helper: soft drop shadow used across cards
// ────────────────────────────────────────────────────────────
static void applyCardShadow(QWidget* w, int blur = 18, int dy = 3, int alpha = 18)
{
    auto* eff = new QGraphicsDropShadowEffect(w);
    eff->setBlurRadius(blur);
    eff->setOffset(0, dy);
    eff->setColor(QColor(0, 0, 0, alpha));
    w->setGraphicsEffect(eff);
}

// ────────────────────────────────────────────────────────────
// Constructor / Destructor
// ────────────────────────────────────────────────────────────
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_university("Higher Institute of Technology")
{
    ui->setupUi(this);

    applyTheme();
    setupTables();
    connectSignals();

    ui->editUnivName->setText(QString::fromStdString(m_university.getName()));

    // Dashboard is the first screen shown on launch
    ui->stackedWidget->setCurrentWidget(ui->pageDashboard);
    setActiveNav(0);
    refreshDashboard();

    logActivity("Application started.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ────────────────────────────────────────────────────────────
// Theme — Same Burgundy / Gold / Ivory palette, modernized
// ────────────────────────────────────────────────────────────
void MainWindow::applyTheme()
{
    // ── Palette constants (UNCHANGED colors) ──
    // Sidebar:   #5A1E2A
    // Gold:      #A67C52
    // Gold hover:#8B5E34
    // Background:#F8F4EF
    // Titles:    #3D1420
    // Borders:   #D8C3A5

    this->setStyleSheet("QMainWindow { background-color:#F8F4EF; }");

    // ── Sidebar ──
    ui->sidebar->setStyleSheet(R"(
        QWidget#sidebar { background-color:#5A1E2A; }
    )");

    ui->lblLogo->setStyleSheet(R"(
        color:#E8C99B;
        font-size:19px;
        font-weight:700;
        letter-spacing:3px;
        padding:6px 0 4px 0;
        background:transparent;
    )");

    QString navBtnStyle = R"(
        QPushButton {
            background-color:transparent;
            color:#E3C9AE;
            border:none;
            border-radius:10px;
            text-align:left;
            padding:11px 14px;
            font-size:13px;
            font-weight:500;
            min-height:40px;
        }
        QPushButton:hover {
            background-color:rgba(166,124,82,0.25);
            color:#FFFFFF;
        }
        QPushButton:checked {
            background-color:#A67C52;
            color:#FFFFFF;
            font-weight:700;
        }
    )";
    for (auto* b : {ui->btnNavDashboard, ui->btnNavUniversity, ui->btnNavDormitory,
                    ui->btnNavRoom, ui->btnNavStudent, ui->btnNavRestaurant})
    {
        b->setStyleSheet(navBtnStyle);
        b->setCheckable(true);
        b->setCursor(Qt::PointingHandCursor);
    }

    // ── Page titles ──
    QString titleStyle = R"(
        color:#3D1420;
        font-size:21px;
        font-weight:700;
        padding-bottom:10px;
        background:transparent;
    )";
    for (auto* l : {ui->lblUniversityTitle, ui->lblDormitoryTitle, ui->lblRoomTitle,
                    ui->lblStudentTitle, ui->lblRestaurantTitle})
        l->setStyleSheet(titleStyle);

    // ── Generic field labels ──
    QString lblStyle = "color:#5C4438; font-size:12.5px; font-weight:600; background:transparent;";
    for (auto* l : {ui->lblUnivName, ui->lblDormName, ui->lblDormCapacity,
                    ui->lblRoomDormSelect, ui->lblRoomNumber, ui->lblRoomCapacity,
                    ui->lblStudentDormSelect, ui->lblStudentRoomSelect,
                    ui->lblStudentId, ui->lblStudentName, ui->lblStudentYear,
                    ui->lblRestaurantDormSelect, ui->lblMealType})
        l->setStyleSheet(lblStyle);

    ui->lblUnivInfo->setStyleSheet(
        "color:#A67C52; font-size:14px; font-weight:700; background:transparent;");

    // ── Form / search cards (the white rounded boxes wrapping inputs) ──
    QString cardStyle = R"(
        QFrame {
            background-color:#FFFFFF;
            border:1px solid #E8DCCB;
            border-radius:12px;
        }
    )";
    for (auto* f : {ui->universityFormCard, ui->universityStatCard, ui->universityTableCard,
                    ui->dormitoryFormCard, ui->dormitoryTableCard,
                    ui->roomFormCard, ui->roomTableCard,
                    ui->studentFormCard, ui->studentTableCard,
                    ui->restaurantFormCard,
                    ui->breakfastCard, ui->lunchCard, ui->dinnerCard,
                    ui->welcomeBanner,
                    ui->statCardStudents, ui->statCardRooms, ui->statCardAvailable,
                    ui->statCardDorms, ui->statCardMeals,
                    ui->activityCard, ui->notificationsCard})
    {
        f->setStyleSheet(cardStyle);
        applyCardShadow(f);
    }

    // Section dividers inside form cards
    QString divStyle = "QFrame { background-color:#E8DCCB; max-height:1px; border:none; }";
    for (auto* f : {ui->roomFormDivider, ui->studentFormDivider, ui->restaurantFormDivider})
        f->setStyleSheet(divStyle);

    // ── Line edits ──
    QString editStyle = R"(
        QLineEdit {
            border:1.5px solid #E8DCCB;
            border-radius:9px;
            padding:7px 12px;
            background:#FBF9F5;
            color:#2C2C2C;
            font-size:13px;
            min-height:30px;
        }
        QLineEdit:focus { border-color:#A67C52; background:#FFFFFF; }
        QLineEdit:hover  { border-color:#C8A96B; }
    )";
    for (auto* e : {ui->editUnivName, ui->editDormName, ui->editSearchDormitory,
                    ui->editStudentName, ui->editSearchStudent, ui->editMealItem})
        e->setStyleSheet(editStyle);

    // ── SpinBoxes ──
    QString spinStyle = R"(
        QSpinBox {
            border:1.5px solid #E8DCCB;
            border-radius:9px;
            padding:7px 10px;
            background:#FBF9F5;
            color:#2C2C2C;
            font-size:13px;
            min-height:30px;
        }
        QSpinBox:focus { border-color:#A67C52; background:#FFFFFF; }
        QSpinBox:hover  { border-color:#C8A96B; }
        QSpinBox::up-button, QSpinBox::down-button {
            background:transparent; border:none; width:16px;
        }
    )";
    for (auto* s : {ui->spinDormCapacity, ui->spinRoomNumber, ui->spinRoomCapacity,
                    ui->spinStudentId, ui->spinStudentYear})
        s->setStyleSheet(spinStyle);

    // ── ComboBoxes ──
    QString comboStyle = R"(
        QComboBox {
            border:1.5px solid #E8DCCB;
            border-radius:9px;
            padding:7px 12px;
            background:#FBF9F5;
            color:#2C2C2C;
            font-size:13px;
            min-height:30px;
        }
        QComboBox:focus { border-color:#A67C52; }
        QComboBox:hover  { border-color:#C8A96B; }
        QComboBox::drop-down { border:none; width:24px; }
        QComboBox QAbstractItemView {
            border:1px solid #E8DCCB;
            border-radius:8px;
            background:#FFFFFF;
            selection-background-color:#EFDFC4;
            selection-color:#3D1420;
            outline:none;
            padding:4px;
        }
    )";
    for (auto* c : {ui->comboRoomDormitory, ui->comboStudentDormitory,
                    ui->comboStudentRoom, ui->comboRestaurantDormitory,
                    ui->comboMealType})
        c->setStyleSheet(comboStyle);

    // ── Primary buttons (Add / Save / Search / quick actions) ──
    QString primaryBtn = R"(
        QPushButton {
            background-color:#A67C52;
            color:#FFFFFF;
            border:none;
            border-radius:10px;
            padding:9px 20px;
            font-weight:600;
            font-size:13px;
            min-height:34px;
        }
        QPushButton:hover   { background-color:#8B5E34; }
        QPushButton:pressed { background-color:#6E4A28; }
    )";
    for (auto* b : {ui->btnSetUnivName, ui->btnAddDormitory, ui->btnSearchDormitory,
                    ui->btnAddRoom, ui->btnAddStudent, ui->btnSearchStudent,
                    ui->btnAddMealItem,
                    ui->btnQuickDormitory, ui->btnQuickRoom,
                    ui->btnQuickStudent, ui->btnQuickRestaurant})
        b->setStyleSheet(primaryBtn);

    // ── Danger / outline buttons (Delete / Remove) ──
    QString dangerBtn = R"(
        QPushButton {
            background-color:#FFFFFF;
            color:#5A1E2A;
            border:1.5px solid #5A1E2A;
            border-radius:10px;
            padding:9px 20px;
            font-weight:600;
            font-size:13px;
            min-height:34px;
        }
        QPushButton:hover   { background-color:#5A1E2A; color:#FFFFFF; }
        QPushButton:pressed { background-color:#3D1420; }
    )";
    for (auto* b : {ui->btnDeleteDormitory, ui->btnDeleteRoom,
                    ui->btnDeleteStudent, ui->btnRemoveMealItem})
        b->setStyleSheet(dangerBtn);

    // ── Table widgets ──
    QString tableStyle = R"(
        QTableWidget {
            background-color:#FFFFFF;
            alternate-background-color:#FAF6EF;
            border:none;
            border-radius:12px;
            gridline-color:#F0E7D6;
            selection-background-color:#EFDFC4;
            selection-color:#3D1420;
            font-size:13px;
            outline:none;
        }
        QTableWidget::item { padding:8px 12px; border:none; }
        QTableWidget::item:hover    { background-color:#FBF3E6; }
        QTableWidget::item:selected { background-color:#EFDFC4; color:#3D1420; }
        QHeaderView::section {
            background-color:#5A1E2A;
            color:#F0E2D0;
            padding:10px 12px;
            font-weight:700;
            font-size:12px;
            border:none;
            border-right:1px solid #6E2A38;
        }
        QHeaderView::section:first { border-top-left-radius:12px; }
        QHeaderView::section:last  { border-right:none; border-top-right-radius:12px; }
    )";
    for (auto* t : {ui->tableDormitoriesOverview, ui->tableDormitory,
                    ui->tableRoom, ui->tableStudent})
        t->setStyleSheet(tableStyle);

    // ── List widgets (restaurant menus + dashboard panels) ──
    QString listStyle = R"(
        QListWidget {
            background-color:#FFFFFF;
            border:none;
            border-radius:0 0 12px 12px;
            padding:8px;
            font-size:13px;
            outline:none;
        }
        QListWidget::item {
            padding:9px 12px;
            border-radius:8px;
            margin:2px 0;
            color:#2C2C2C;
        }
        QListWidget::item:selected { background-color:#EFDFC4; color:#3D1420; }
        QListWidget::item:hover    { background-color:#FBF3E6; }
    )";
    for (auto* l : {ui->listBreakfast, ui->listLunch, ui->listDinner,
                    ui->listRecentActivity, ui->listNotifications})
        l->setStyleSheet(listStyle);

    // ── Meal card colored headers ──
    QString mealHdrBase = R"(
        QLabel {
            color:#FFFFFF;
            font-weight:700;
            font-size:13px;
            padding:12px 14px;
            border-radius:12px 12px 0 0;
        }
    )";
    ui->lblBreakfastHdr->setStyleSheet(mealHdrBase + "QLabel{background-color:#5A1E2A;}");
    ui->lblLunchHdr->setStyleSheet(mealHdrBase + "QLabel{background-color:#A67C52;}");
    ui->lblDinnerHdr->setStyleSheet(mealHdrBase + "QLabel{background-color:#8B5E34;}");

    // ── Status bar ──
    ui->statusbar->setStyleSheet(
        "QStatusBar { background-color:#5A1E2A; color:#E8C99B; "
        "padding:4px 12px; font-size:12px; }");

    // ════════════════════════════════════════════════════════
    // Dashboard-specific styling
    // ════════════════════════════════════════════════════════
    ui->welcomeBanner->setStyleSheet(R"(
        QFrame {
            background-color:#5A1E2A;
            border:none;
            border-radius:14px;
        }
    )");
    ui->lblWelcomeTitle->setStyleSheet(
        "color:#E8C99B; font-size:20px; font-weight:700; background:transparent;");
    ui->lblWelcomeSubtitle->setStyleSheet(
        "color:#D8BFA8; font-size:13px; background:transparent;");

    // Stat cards: icon / value / caption
    struct StatStyle { QLabel* icon; QLabel* value; QLabel* caption; QString accent; };
    QList<StatStyle> stats = {
        {ui->lblStatStudentsIcon,  ui->lblStatStudentsValue,  ui->lblStatStudentsCaption,  "#5A1E2A"},
        {ui->lblStatRoomsIcon,     ui->lblStatRoomsValue,     ui->lblStatRoomsCaption,     "#A67C52"},
        {ui->lblStatAvailableIcon,ui->lblStatAvailableValue, ui->lblStatAvailableCaption, "#3D7A4D"},
        {ui->lblStatDormsIcon,     ui->lblStatDormsValue,     ui->lblStatDormsCaption,     "#8B5E34"},
        {ui->lblStatMealsIcon,     ui->lblStatMealsValue,     ui->lblStatMealsCaption,     "#7A4D5A"},
    };
    for (auto& s : stats) {
        s.icon->setStyleSheet("font-size:22px; background:transparent;");
        s.value->setStyleSheet(QString(
            "font-size:26px; font-weight:700; color:%1; background:transparent;").arg(s.accent));
        s.caption->setStyleSheet(
            "font-size:12px; color:#7A6A60; font-weight:600; background:transparent;");
    }

    ui->lblQuickActionsHdr->setStyleSheet(
        "color:#3D1420; font-size:15px; font-weight:700; background:transparent; padding-top:4px;");

    QString activityHdrStyle = R"(
        QLabel {
            color:#FFFFFF;
            background-color:#5A1E2A;
            font-weight:700;
            font-size:13px;
            padding:12px 14px;
            border-radius:12px 12px 0 0;
        }
    )";
    ui->lblActivityHdr->setStyleSheet(activityHdrStyle);
    ui->lblNotificationsHdr->setStyleSheet(activityHdrStyle.replace("#5A1E2A", "#A67C52"));
}

// ────────────────────────────────────────────────────────────
// Table setup (visual behavior only, no logic)
// ────────────────────────────────────────────────────────────
void MainWindow::setupTables()
{
    auto configure = [](QTableWidget* t) {
        t->horizontalHeader()->setStretchLastSection(true);
        t->setSelectionBehavior(QAbstractItemView::SelectRows);
        t->setEditTriggers(QAbstractItemView::NoEditTriggers);
        t->setAlternatingRowColors(true);
        t->verticalHeader()->setVisible(false);
        t->setShowGrid(false);
        t->setFrameShape(QFrame::NoFrame);
        t->verticalHeader()->setDefaultSectionSize(40);
    };
    configure(ui->tableDormitoriesOverview);
    configure(ui->tableDormitory);
    configure(ui->tableRoom);
    configure(ui->tableStudent);
}

// ────────────────────────────────────────────────────────────
// Signal connections
// ────────────────────────────────────────────────────────────
void MainWindow::connectSignals()
{
    // Navigation
    connect(ui->btnNavDashboard,  &QPushButton::clicked, this, &MainWindow::onNavDashboard);
    connect(ui->btnNavUniversity, &QPushButton::clicked, this, &MainWindow::onNavUniversity);
    connect(ui->btnNavDormitory,  &QPushButton::clicked, this, &MainWindow::onNavDormitory);
    connect(ui->btnNavRoom,       &QPushButton::clicked, this, &MainWindow::onNavRoom);
    connect(ui->btnNavStudent,    &QPushButton::clicked, this, &MainWindow::onNavStudent);
    connect(ui->btnNavRestaurant, &QPushButton::clicked, this, &MainWindow::onNavRestaurant);

    // Dashboard quick actions → jump to the relevant page
    connect(ui->btnQuickDormitory,  &QPushButton::clicked, this, &MainWindow::onNavDormitory);
    connect(ui->btnQuickRoom,       &QPushButton::clicked, this, &MainWindow::onNavRoom);
    connect(ui->btnQuickStudent,    &QPushButton::clicked, this, &MainWindow::onNavStudent);
    connect(ui->btnQuickRestaurant, &QPushButton::clicked, this, &MainWindow::onNavRestaurant);

    // University
    connect(ui->btnSetUnivName, &QPushButton::clicked, this, &MainWindow::onSetUniversityName);

    // Dormitory
    connect(ui->btnAddDormitory,    &QPushButton::clicked, this, &MainWindow::onAddDormitory);
    connect(ui->btnDeleteDormitory, &QPushButton::clicked, this, &MainWindow::onDeleteDormitory);
    connect(ui->btnSearchDormitory, &QPushButton::clicked, this, &MainWindow::onSearchDormitory);

    // Room
    connect(ui->comboRoomDormitory, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onRoomDormitoryChanged);
    connect(ui->btnAddRoom,    &QPushButton::clicked, this, &MainWindow::onAddRoom);
    connect(ui->btnDeleteRoom, &QPushButton::clicked, this, &MainWindow::onDeleteRoom);

    // Student
    connect(ui->comboStudentDormitory, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onStudentDormitoryChanged);
    connect(ui->comboStudentRoom, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::refreshStudentTable);
    connect(ui->btnAddStudent,    &QPushButton::clicked, this, &MainWindow::onAddStudent);
    connect(ui->btnDeleteStudent, &QPushButton::clicked, this, &MainWindow::onDeleteStudent);
    connect(ui->btnSearchStudent, &QPushButton::clicked, this, &MainWindow::onSearchStudent);

    // Restaurant
    connect(ui->comboRestaurantDormitory, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onRestaurantDormitoryChanged);
    connect(ui->btnAddMealItem,    &QPushButton::clicked, this, &MainWindow::onAddMealItem);
    connect(ui->btnRemoveMealItem, &QPushButton::clicked, this, &MainWindow::onRemoveMealItem);
}

// ────────────────────────────────────────────────────────────
// Navigation helper — highlights the active sidebar button
// ────────────────────────────────────────────────────────────
void MainWindow::setActiveNav(int pageIndex)
{
    QList<QPushButton*> btns = {
        ui->btnNavDashboard, ui->btnNavUniversity, ui->btnNavDormitory,
        ui->btnNavRoom, ui->btnNavStudent, ui->btnNavRestaurant
    };
    for (int i = 0; i < btns.size(); ++i)
        btns[i]->setChecked(i == pageIndex);
}

// ────────────────────────────────────────────────────────────
// Navigation slots
// ────────────────────────────────────────────────────────────
void MainWindow::onNavDashboard()
{
    ui->stackedWidget->setCurrentWidget(ui->pageDashboard);
    setActiveNav(0);
    refreshDashboard();
}

void MainWindow::onNavUniversity()
{
    ui->stackedWidget->setCurrentWidget(ui->pageUniversity);
    setActiveNav(1);
    refreshUniversityPage();
}

void MainWindow::onNavDormitory()
{
    ui->stackedWidget->setCurrentWidget(ui->pageDormitory);
    setActiveNav(2);
    refreshDormitoryTable();
}

void MainWindow::onNavRoom()
{
    ui->stackedWidget->setCurrentWidget(ui->pageRoom);
    setActiveNav(3);
    refreshDormitoryCombos();
    refreshRoomTable();
}

void MainWindow::onNavStudent()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStudent);
    setActiveNav(4);
    refreshDormitoryCombos();
    refreshStudentTable();
}

void MainWindow::onNavRestaurant()
{
    ui->stackedWidget->setCurrentWidget(ui->pageRestaurant);
    setActiveNav(5);
    refreshDormitoryCombos();
    refreshRestaurantLists();
}

// ────────────────────────────────────────────────────────────
// Recent activity log (UI convenience only)
// ────────────────────────────────────────────────────────────
void MainWindow::logActivity(const QString& text)
{
    QString stamp = QDateTime::currentDateTime().toString("HH:mm");
    m_recentActivity.prepend(stamp + "  —  " + text);
    while (m_recentActivity.size() > 8)
        m_recentActivity.removeLast();

    ui->listRecentActivity->clear();
    ui->listRecentActivity->addItems(m_recentActivity);
}

// ────────────────────────────────────────────────────────────
// Dashboard — built entirely from existing getters, no new
// business logic. (University::getNumberOfDormitories,
// Dormitory::getTotalRooms/getAvailableRooms/getTotalOccupancy,
// Restaurant::getXxxMenu)
// ────────────────────────────────────────────────────────────
void MainWindow::refreshDashboard()
{
    const auto& dorms = m_university.getDormitories();

    int totalRooms     = 0;
    int totalAvailable = 0;
    int totalStudents  = 0;
    int totalMealItems = 0;

    for (const Dormitory& d : dorms) {
        totalRooms     += d.getTotalRooms();
        totalAvailable += d.getAvailableRooms();
        totalStudents  += d.getTotalOccupancy();

        const Restaurant& r = d.getRestaurant();
        totalMealItems += static_cast<int>(r.getBreakfastMenu().size());
        totalMealItems += static_cast<int>(r.getLunchMenu().size());
        totalMealItems += static_cast<int>(r.getDinnerMenu().size());
    }

    ui->lblStatStudentsValue->setText(QString::number(totalStudents));
    ui->lblStatRoomsValue->setText(QString::number(totalRooms));
    ui->lblStatAvailableValue->setText(QString::number(totalAvailable));
    ui->lblStatDormsValue->setText(QString::number(m_university.getNumberOfDormitories()));
    ui->lblStatMealsValue->setText(QString::number(totalMealItems));

    // Notifications — simple, derived rules (UI-only, not stored state)
    ui->listNotifications->clear();
    if (dorms.empty()) {
        ui->listNotifications->addItem("⚠️  No dormitories registered yet.");
    } else {
        for (const Dormitory& d : dorms) {
            if (d.getAvailableRooms() == 0 && d.getTotalRooms() > 0) {
                ui->listNotifications->addItem(
                    "🔴  " + QString::fromStdString(d.getName()) + " is fully occupied.");
            }
        }
        if (ui->listNotifications->count() == 0)
            ui->listNotifications->addItem("✅  All dormitories have available rooms.");
    }

    if (ui->listRecentActivity->count() == 0)
        ui->listRecentActivity->addItem("No activity yet.");
}

// ────────────────────────────────────────────────────────────
// University — uses University::setName() / getName() (unchanged)
// ────────────────────────────────────────────────────────────
void MainWindow::onSetUniversityName()
{
    QString name = ui->editUnivName->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Validation", "University name cannot be empty.");
        return;
    }
    try {
        m_university.setName(name.toStdString());  // existing setter, untouched
        ui->statusbar->showMessage("University name updated.", 3000);
        logActivity("University name set to \"" + name + "\".");
        refreshUniversityPage();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
}

void MainWindow::refreshUniversityPage()
{
    ui->lblUnivInfo->setText(
        QString("Dormitories: %1").arg(m_university.getNumberOfDormitories()));

    const auto& dorms = m_university.getDormitories();
    ui->tableDormitoriesOverview->setRowCount(static_cast<int>(dorms.size()));
    int row = 0;
    for (const Dormitory& d : dorms) {
        ui->tableDormitoriesOverview->setItem(row, 0,
            new QTableWidgetItem(QString::fromStdString(d.getName())));
        ui->tableDormitoriesOverview->setItem(row, 1,
            new QTableWidgetItem(QString::number(d.getCapacity())));
        ui->tableDormitoriesOverview->setItem(row, 2,
            new QTableWidgetItem(QString::number(d.getAvailableRooms())));
        ++row;
    }
    ui->tableDormitoriesOverview->resizeColumnsToContents();
}

// ────────────────────────────────────────────────────────────
// Dormitory — uses University::addDormitory / removeDormitory /
//             findDormitory (all unchanged)
// ────────────────────────────────────────────────────────────
void MainWindow::onAddDormitory()
{
    QString name = ui->editDormName->text().trimmed();
    int capacity = ui->spinDormCapacity->value();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Dormitory name cannot be empty.");
        return;
    }

    try {
        m_university.addDormitory(Dormitory(name.toStdString(), capacity)); // existing ctor
        ui->editDormName->clear();
        refreshDormitoryTable();
        refreshDormitoryCombos();
        ui->statusbar->showMessage("Dormitory added: " + name, 3000);
        logActivity("Dormitory added: \"" + name + "\".");
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
}

void MainWindow::onDeleteDormitory()
{
    int row = ui->tableDormitory->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Info", "Please select a dormitory to delete.");
        return;
    }
    QString name = ui->tableDormitory->item(row, 0)->text();
    if (QMessageBox::question(this, "Confirm",
        "Delete dormitory \"" + name + "\"?") != QMessageBox::Yes) return;

    m_university.removeDormitory(name.toStdString());  // existing method
    refreshDormitoryTable();
    refreshDormitoryCombos();
    ui->statusbar->showMessage("Dormitory deleted: " + name, 3000);
    logActivity("Dormitory deleted: \"" + name + "\".");
}

void MainWindow::onSearchDormitory()
{
    QString query = ui->editSearchDormitory->text().trimmed();

    if (query.isEmpty()) {
        refreshDormitoryTable();
        return;
    }

    const Dormitory* found = m_university.findDormitory(query.toStdString()); // existing method
    ui->tableDormitory->setRowCount(0);
    if (!found) {
        ui->statusbar->showMessage("No dormitory found matching: " + query, 3000);
        return;
    }
    ui->tableDormitory->setRowCount(1);
    ui->tableDormitory->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(found->getName())));
    ui->tableDormitory->setItem(0, 1, new QTableWidgetItem(QString::number(found->getCapacity())));
    ui->tableDormitory->setItem(0, 2, new QTableWidgetItem(QString::number(found->getAvailableRooms())));
    ui->tableDormitory->resizeColumnsToContents();
}

void MainWindow::refreshDormitoryTable()
{
    const auto& dorms = m_university.getDormitories();
    ui->tableDormitory->setRowCount(static_cast<int>(dorms.size()));
    int row = 0;
    for (const Dormitory& d : dorms) {
        ui->tableDormitory->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(d.getName())));
        ui->tableDormitory->setItem(row, 1, new QTableWidgetItem(QString::number(d.getCapacity())));
        ui->tableDormitory->setItem(row, 2, new QTableWidgetItem(QString::number(d.getAvailableRooms())));
        ++row;
    }
    ui->tableDormitory->resizeColumnsToContents();
}

void MainWindow::refreshDormitoryCombos()
{
    QString selRoom = ui->comboRoomDormitory->currentText();
    QString selStud = ui->comboStudentDormitory->currentText();
    QString selRest = ui->comboRestaurantDormitory->currentText();

    ui->comboRoomDormitory->clear();
    ui->comboStudentDormitory->clear();
    ui->comboRestaurantDormitory->clear();

    for (const Dormitory& d : m_university.getDormitories()) {
        QString n = QString::fromStdString(d.getName());
        ui->comboRoomDormitory->addItem(n);
        ui->comboStudentDormitory->addItem(n);
        ui->comboRestaurantDormitory->addItem(n);
    }

    auto restore = [](QComboBox* cb, const QString& s) {
        int i = cb->findText(s);
        if (i >= 0) cb->setCurrentIndex(i);
    };
    restore(ui->comboRoomDormitory, selRoom);
    restore(ui->comboStudentDormitory, selStud);
    restore(ui->comboRestaurantDormitory, selRest);
}

QString MainWindow::currentDormName(QComboBox* combo) const
{
    return combo->currentText();
}

// ────────────────────────────────────────────────────────────
// Room — uses Dormitory::addRoom / removeRoom / getRooms (unchanged)
// ────────────────────────────────────────────────────────────
void MainWindow::onRoomDormitoryChanged()
{
    refreshRoomTable();
}

void MainWindow::onAddRoom()
{
    QString dormName = currentDormName(ui->comboRoomDormitory);
    if (dormName.isEmpty()) {
        QMessageBox::information(this, "Info", "Please select a dormitory first.");
        return;
    }
    Dormitory* d = m_university.findDormitory(dormName.toStdString());
    if (!d) return;

    int roomNumber = ui->spinRoomNumber->value();
    int capacity   = ui->spinRoomCapacity->value();

    try {
        d->addRoom(Room(roomNumber, capacity));  // existing ctor + method
        refreshRoomTable();
        refreshUniversityPage();
        ui->statusbar->showMessage(QString("Room %1 added.").arg(roomNumber), 3000);
        logActivity(QString("Room %1 added to \"%2\".").arg(roomNumber).arg(dormName));
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
}

void MainWindow::onDeleteRoom()
{
    int row = ui->tableRoom->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Info", "Please select a room to delete.");
        return;
    }
    int roomNumber = ui->tableRoom->item(row, 0)->text().toInt();
    Dormitory* d = m_university.findDormitory(
        currentDormName(ui->comboRoomDormitory).toStdString());
    if (!d) return;

    d->removeRoom(roomNumber);  // existing method
    refreshRoomTable();
    refreshUniversityPage();
    ui->statusbar->showMessage(QString("Room %1 deleted.").arg(roomNumber), 3000);
    logActivity(QString("Room %1 deleted.").arg(roomNumber));
}

void MainWindow::refreshRoomTable()
{
    ui->tableRoom->setRowCount(0);
    QString dormName = currentDormName(ui->comboRoomDormitory);
    if (dormName.isEmpty()) return;

    const Dormitory* d = m_university.findDormitory(dormName.toStdString());
    if (!d) return;

    const auto& rooms = d->getRooms();
    ui->tableRoom->setRowCount(static_cast<int>(rooms.size()));
    int row = 0;
    for (const Room& r : rooms) {
        ui->tableRoom->setItem(row, 0, new QTableWidgetItem(QString::number(r.getRoomNumber())));
        ui->tableRoom->setItem(row, 1, new QTableWidgetItem(QString::number(r.getCapacity())));
        ui->tableRoom->setItem(row, 2, new QTableWidgetItem(
            QString("%1 / %2").arg(r.getCurrentOccupancy()).arg(r.getCapacity())));
        ++row;
    }
    ui->tableRoom->resizeColumnsToContents();
}

// ────────────────────────────────────────────────────────────
// Student — uses Dormitory::assignStudentToRoom /
//           removeStudentFromRoom (unchanged)
// ────────────────────────────────────────────────────────────
void MainWindow::onStudentDormitoryChanged()
{
    ui->comboStudentRoom->clear();
    QString dormName = currentDormName(ui->comboStudentDormitory);
    if (dormName.isEmpty()) return;

    const Dormitory* d = m_university.findDormitory(dormName.toStdString());
    if (!d) return;

    for (const Room& r : d->getRooms())
        ui->comboStudentRoom->addItem(QString::number(r.getRoomNumber()));

    refreshStudentTable();
}

void MainWindow::onAddStudent()
{
    QString dormName = currentDormName(ui->comboStudentDormitory);
    QString roomStr  = ui->comboStudentRoom->currentText();
    if (dormName.isEmpty() || roomStr.isEmpty()) {
        QMessageBox::information(this, "Info", "Please select a dormitory and room.");
        return;
    }

    int id = ui->spinStudentId->value();
    QString name = ui->editStudentName->text().trimmed();
    int year = ui->spinStudentYear->value();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Student name cannot be empty.");
        return;
    }

    Dormitory* d = m_university.findDormitory(dormName.toStdString());
    if (!d) return;

    try {
        Student s(id, name.toStdString(), year);  // existing ctor
        bool ok = d->assignStudentToRoom(s, roomStr.toInt());  // existing method
        if (!ok) {
            QMessageBox::warning(this, "Error",
                "Could not assign student.\n"
                "The room may be full or the student is already assigned.");
            return;
        }
        ui->editStudentName->clear();
        refreshStudentTable();
        refreshRoomTable();
        ui->statusbar->showMessage("Student assigned: " + name, 3000);
        logActivity("Student \"" + name + "\" assigned to room " + roomStr + ".");
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
}

void MainWindow::onDeleteStudent()
{
    int row = ui->tableStudent->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Info", "Please select a student to remove.");
        return;
    }
    int studentId = ui->tableStudent->item(row, 0)->text().toInt();
    QString name  = ui->tableStudent->item(row, 1)->text();
    int roomNo    = ui->comboStudentRoom->currentText().toInt();

    Dormitory* d = m_university.findDormitory(
        currentDormName(ui->comboStudentDormitory).toStdString());
    if (!d) return;

    d->removeStudentFromRoom(studentId, roomNo);  // existing method
    refreshStudentTable();
    refreshRoomTable();
    ui->statusbar->showMessage("Student removed: " + name, 3000);
    logActivity("Student \"" + name + "\" removed.");
}

void MainWindow::onSearchStudent()
{
    QString query = ui->editSearchStudent->text().trimmed();
    QString dormName = currentDormName(ui->comboStudentDormitory);
    if (dormName.isEmpty()) return;

    const Dormitory* d = m_university.findDormitory(dormName.toStdString());
    if (!d) return;

    QString roomStr = ui->comboStudentRoom->currentText();
    if (roomStr.isEmpty()) return;
    int roomNo = roomStr.toInt();

    ui->tableStudent->setRowCount(0);

    for (const Room& r : d->getRooms()) {
        if (r.getRoomNumber() != roomNo) continue;

        const auto& students = r.getStudents();  // existing getter
        int row = 0;
        for (const Student& s : students) {
            bool matches = query.isEmpty()
                || QString::fromStdString(s.getFullName()).contains(query, Qt::CaseInsensitive)
                || QString::number(s.getId()) == query;
            if (!matches) continue;

            ui->tableStudent->insertRow(row);
            ui->tableStudent->setItem(row, 0, new QTableWidgetItem(QString::number(s.getId())));
            ui->tableStudent->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(s.getFullName())));
            ui->tableStudent->setItem(row, 2, new QTableWidgetItem(QString::number(s.getAcademicYear())));
            ++row;
        }
        break;
    }
    ui->tableStudent->resizeColumnsToContents();
}

void MainWindow::refreshStudentTable()
{
    ui->tableStudent->setRowCount(0);
    QString dormName = currentDormName(ui->comboStudentDormitory);
    if (dormName.isEmpty()) return;

    const Dormitory* d = m_university.findDormitory(dormName.toStdString());
    if (!d) return;

    QString roomStr = ui->comboStudentRoom->currentText();
    if (roomStr.isEmpty()) return;
    int roomNo = roomStr.toInt();

    for (const Room& r : d->getRooms()) {
        if (r.getRoomNumber() != roomNo) continue;

        const auto& students = r.getStudents();
        ui->tableStudent->setRowCount(static_cast<int>(students.size()));
        int row = 0;
        for (const Student& s : students) {
            ui->tableStudent->setItem(row, 0, new QTableWidgetItem(QString::number(s.getId())));
            ui->tableStudent->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(s.getFullName())));
            ui->tableStudent->setItem(row, 2, new QTableWidgetItem(QString::number(s.getAcademicYear())));
            ++row;
        }
        break;
    }
    ui->tableStudent->resizeColumnsToContents();
}

// ────────────────────────────────────────────────────────────
// Restaurant — uses Restaurant::addXxxItem / removeXxxItem
//              (all unchanged)
// ────────────────────────────────────────────────────────────
void MainWindow::onRestaurantDormitoryChanged()
{
    refreshRestaurantLists();
}

void MainWindow::onAddMealItem()
{
    QString dormName = currentDormName(ui->comboRestaurantDormitory);
    if (dormName.isEmpty()) {
        QMessageBox::information(this, "Info", "Please select a dormitory first.");
        return;
    }
    QString item = ui->editMealItem->text().trimmed();
    if (item.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Item name cannot be empty.");
        return;
    }

    Dormitory* d = m_university.findDormitory(dormName.toStdString());
    if (!d) return;
    Restaurant& r = d->getRestaurant();  // existing non-const getter

    try {
        switch (ui->comboMealType->currentIndex()) {
            case 0: r.addBreakfastItem(item.toStdString()); break; // existing methods
            case 1: r.addLunchItem(item.toStdString());     break;
            default: r.addDinnerItem(item.toStdString());   break;
        }
        ui->editMealItem->clear();
        refreshRestaurantLists();
        ui->statusbar->showMessage("Menu item added: " + item, 3000);
        logActivity("Menu item \"" + item + "\" added to " + dormName + ".");
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
}

void MainWindow::onRemoveMealItem()
{
    QString dormName = currentDormName(ui->comboRestaurantDormitory);
    if (dormName.isEmpty()) return;

    Dormitory* d = m_university.findDormitory(dormName.toStdString());
    if (!d) return;
    Restaurant& r = d->getRestaurant();

    QListWidget* activeList = nullptr;
    switch (ui->comboMealType->currentIndex()) {
        case 0: activeList = ui->listBreakfast; break;
        case 1: activeList = ui->listLunch;     break;
        default: activeList = ui->listDinner;   break;
    }

    QListWidgetItem* sel = activeList->currentItem();
    if (!sel) {
        QMessageBox::information(this, "Info", "Please select an item to remove.");
        return;
    }
    std::string item = sel->text().toStdString();

    switch (ui->comboMealType->currentIndex()) {
        case 0: r.removeBreakfastItem(item); break;  // existing methods
        case 1: r.removeLunchItem(item);     break;
        default: r.removeDinnerItem(item);   break;
    }
    refreshRestaurantLists();
    ui->statusbar->showMessage("Menu item removed.", 3000);
    logActivity("Menu item removed.");
}

void MainWindow::refreshRestaurantLists()
{
    ui->listBreakfast->clear();
    ui->listLunch->clear();
    ui->listDinner->clear();

    QString dormName = currentDormName(ui->comboRestaurantDormitory);
    if (dormName.isEmpty()) return;

    const Dormitory* d = m_university.findDormitory(dormName.toStdString());
    if (!d) return;

    const Restaurant& r = d->getRestaurant();  // existing const getter

    for (const std::string& item : r.getBreakfastMenu())
        ui->listBreakfast->addItem(QString::fromStdString(item));
    for (const std::string& item : r.getLunchMenu())
        ui->listLunch->addItem(QString::fromStdString(item));
    for (const std::string& item : r.getDinnerMenu())
        ui->listDinner->addItem(QString::fromStdString(item));
}
