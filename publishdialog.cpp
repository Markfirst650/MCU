#include "publishdialog.h"
#include "ui_publishdialog.h"
#include "models.h"
#include <QMessageBox>
#include <QDoubleValidator>
#include <QFileDialog>
#include <QFileInfo>

PublishDialog::PublishDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PublishDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("发布新贴");
    this->resize(800, 850);        //创建 ui 对象，设置窗口标题和大小

    ui->editPrice->setValidator(new QDoubleValidator(0.0, 99999.0, 2, this));
    ui->editInfo->setPlaceholderText("请输入详细信息...");
    ui->editContact->setPlaceholderText("联系方式 (必填)");  //输入限制与提示文字（让用户更好填）

    auto updateSubTypes = [=](int index) {
        ui->comboSubType->clear();
        ui->btnSelectImg->setVisible(true);
        ui->lblImgPreview->setVisible(true);
          //用户选择不同的大类时，小分类要跟着变
        if (index == 0) { // 闲置
            ui->comboSubType->addItems({"出", "收", "租"});
            ui->editPrice->setVisible(true);
        } else if (index == 1) { // 组队
            ui->comboSubType->addItems({"拼车", "拼单"});
            ui->editPrice->setVisible(false);
        } else { // 问答
            ui->comboSubType->addItems({"问", "答"});
            ui->editPrice->setVisible(false);
        }

    updateSubTypes(ui->comboType->currentIndex());
    connect(ui->comboType, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, updateSubTypes);

    connect(ui->btnSelectImg, &QPushButton::clicked, this, [=](){
        QString path = QFileDialog::getOpenFileName(this, "选择图片", "", "Images (*.png *.jpg *.jpeg)");
        if (!path.isEmpty()) {
            this->selectedImagePath = path;
            ui->lblImgPreview->setText("已选: " + QFileInfo(path).fileName());
            ui->lblImgPreview->setStyleSheet("color: #2E7D32; font-weight: bold;");
        }
    });    //点“选择图片”按钮，弹出文件选择窗口，只允许选 png/jpg/jpeg

    if (ui->btnConfirm) connect(ui->btnConfirm, &QPushButton::clicked, this, &QDialog::accept);
}

PublishDialog::~PublishDialog() { delete ui; }  //避免内存泄露

std::shared_ptr<BasePost> PublishDialog::getCreatedPost() {   //读取用户输入
    QString info = ui->editInfo->text().trimmed();
    QString contact = ui->editContact->text().trimmed();
    QString subType = ui->comboSubType->currentText();
    int typeIndex = ui->comboType->currentIndex();

    if (info.isEmpty() || contact.isEmpty()) {  //必填校验，内容和联系方式不能为空
        QMessageBox::warning(this, "提示", "内容和联系方式必填！");
        return nullptr;
    }

    std::shared_ptr<BasePost> post;  //根据类型创建不同的 Post（核心对象创建）
    if (typeIndex == 0) {
        auto item = std::make_shared<TradeItem>(0, g_currentUserInfo, info, ui->editPrice->text().toDouble(), contact, STATUS_ACTIVE, subType);
        post = item;
    } else if (typeIndex == 1) {
        post = std::make_shared<TeamUp>(0, g_currentUserInfo, info, contact, STATUS_ACTIVE, subType);
    } else {
        post = std::make_shared<QAItem>(0, g_currentUserInfo, info, contact, STATUS_ACTIVE, subType);
    }

    // 统一赋值图片路径，图片属于“所有帖子共有的字段”
    if (post) post->imagePath = this->selectedImagePath;
    return post;
}
