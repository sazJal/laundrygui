#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bt = new bluetoothuart();
    serialPort = new QSerialPort();
    laundryAdmin = new admin(bt, serialPort);
    entity = new user();

    ui->radio_weight->setChecked(true);

    connect(ui->button_admin, &QPushButton::clicked, this, &MainWindow::open_admin);

    connect(ui->button_daftar, &QPushButton::clicked, this, &MainWindow::open_register);
    connect(ui->button_cap, &QPushButton::clicked, this, &MainWindow::capitalize_all);

    connect(ui->radio_name,  &QRadioButton::clicked, this, &MainWindow::evaluate_radio_option);
    connect(ui->radio_addr,  &QRadioButton::clicked, this, &MainWindow::evaluate_radio_option);
    connect(ui->radio_phone, &QRadioButton::clicked, this, &MainWindow::evaluate_radio_option);

    connect(ui->button_0, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_1, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_2, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_3, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_4, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_5, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_6, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_7, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_8, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_9, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_a, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_b, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_c, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_d, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_e, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_f, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_g, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_h, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_i, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_j, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_k, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_l, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_m, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_n, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_o, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_p, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_q, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_r, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_s, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_t, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_u, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_v, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_w, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_x, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_y, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_x, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);

    connect(ui->button_dot, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_dsh, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_sls, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_spc, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);
    connect(ui->button_bsp, &QPushButton::clicked, this, &MainWindow::on_keyboard_clicked);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open_admin()
{

    if(laundryAdmin->exec() == QDialog::Accepted)
    {

    }
}

void MainWindow::open_register()
{
    entity->Name    = name_str;
    entity->Address = address_str;
    entity->Phone   = phone_str;
    if(ui->radio_weight->isChecked())
        entity->Option = "Kiloan";
    else {
        entity->Option = "Satuan";
    }

    locker *loker = new locker(entity, bt, serialPort);
    if(loker->exec() == QDialog::Accepted)
    {
        /* clear stuff */
        clear_param();
    }
}

void MainWindow::evaluate_radio_option()
{
    QRadioButton *radio_button  = (QRadioButton*) (sender());
    QString id = radio_button->objectName();
    if(id == "radio_name")
    {
        NameIsChecked = true;
        ui->radio_addr->setChecked(false);
        AddrIsChecked = false;
        ui->radio_phone->setChecked(false);
        PhoneIsChecked = false;
    }
    else if (id == "radio_addr")
    {
        AddrIsChecked = true;
        ui->radio_name->setChecked(false);
        NameIsChecked = false;
        ui->radio_phone->setChecked(false);
        PhoneIsChecked = false;
    }
    else if (id == "radio_phone")
    {
        PhoneIsChecked = true;
        ui->radio_name->setChecked(false);
        NameIsChecked = false;
        ui->radio_addr->setChecked(false);
        AddrIsChecked = false;
    }
}

void MainWindow::on_keyboard_clicked()
{
    QPushButton *button = (QPushButton *)(sender());
    QString text = button->text();

    if(text == "space")
    {
        text = " ";
    }

    if(NameIsChecked)
    {
        if((text == "backspace") && (name_idx >= 1))
        {
            name_idx--;
            name_str.remove(name_idx, 1);
        }
        else if (text != "backspace")
        {
            name_str.insert(name_idx, text);
            name_idx++;
        }
        ui->line_name->setText(name_str);
    }

    if(AddrIsChecked)
    {
        if((text == "backspace") && (address_idx >= 1))
        {
            address_idx--;
            address_str.remove(address_idx, 1);
        }
        else if (text != "backspace")
        {
            address_str.insert(address_idx, text);
            address_idx++;
        }
        ui->line_addr->setText(address_str);
    }

    if(PhoneIsChecked)
    {
        if((text == "backspace") && (phone_idx >= 1))
        {
            phone_idx--;
            phone_str.remove(phone_idx, 1);
        }
        else if (text.contains("0") || text.contains("1") || text.contains("2") || text.contains("3") || text.contains("4") ||
                 text.contains("5") || text.contains("6") || text.contains("7") || text.contains("8") || text.contains("9"))
        {
            phone_str.insert(phone_idx, text);
            phone_idx++;
        }
        ui->line_phone->setText(phone_str);
    }
}

void MainWindow::capitalize_all()
{
    if(isCapsLocked)
    {
        ui->button_a->setText("A"); ui->button_b->setText("B");
        ui->button_c->setText("C"); ui->button_d->setText("D");
        ui->button_e->setText("E"); ui->button_f->setText("F");
        ui->button_g->setText("G"); ui->button_h->setText("H");
        ui->button_i->setText("I"); ui->button_j->setText("J");
        ui->button_k->setText("K"); ui->button_l->setText("L");
        ui->button_m->setText("M"); ui->button_n->setText("N");
        ui->button_o->setText("O"); ui->button_p->setText("P");
        ui->button_q->setText("Q"); ui->button_r->setText("R");
        ui->button_s->setText("S"); ui->button_t->setText("T");
        ui->button_u->setText("U"); ui->button_v->setText("V");
        ui->button_w->setText("W"); ui->button_x->setText("X");
        ui->button_y->setText("Y"); ui->button_z->setText("Z");
        ui->button_cap->setForegroundRole(QPalette::Dark);
        isCapsLocked = false;
    }
    else
    {
        ui->button_a->setText("a"); ui->button_b->setText("b");
        ui->button_c->setText("c"); ui->button_d->setText("d");
        ui->button_e->setText("e"); ui->button_f->setText("f");
        ui->button_g->setText("g"); ui->button_h->setText("h");
        ui->button_i->setText("i"); ui->button_j->setText("j");
        ui->button_k->setText("k"); ui->button_l->setText("l");
        ui->button_m->setText("m"); ui->button_n->setText("n");
        ui->button_o->setText("o"); ui->button_p->setText("p");
        ui->button_q->setText("q"); ui->button_r->setText("r");
        ui->button_s->setText("s"); ui->button_t->setText("t");
        ui->button_u->setText("u"); ui->button_v->setText("v");
        ui->button_w->setText("w"); ui->button_x->setText("x");
        ui->button_y->setText("y"); ui->button_z->setText("z");
        isCapsLocked = true;
    }
}

void MainWindow::clear_param()
{
    ui->line_name->clear();
    ui->line_addr->clear();
    ui->line_phone->clear();
    name_str.clear();
    address_str.clear();
    phone_str.clear();
    name_idx    = 0;
    address_idx = 0;
    phone_idx   = 0;
}
