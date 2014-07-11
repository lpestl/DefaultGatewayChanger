#include "GatewayChanger.h"

#pragma once

namespace DefaultGatewayChanger {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Settings
	/// </summary>
	public ref class Settings : public System::Windows::Forms::Form
	{
	public:
		Settings(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			core = GatewayChanger::GetInstance();

			// Чтобы не отображалась на панели ПУСК
			ShowInTaskbar = false;
			this->WindowState = FormWindowState::Minimized;
			Hide();

			core->selectNetCard();
			core->checkingMainChannel();

			String^ ipStrO = gcnew String(core->getIpList()->IpAddress.String);
			String^ ipStrR = ipStrO;
			if (core->getIpListReserve() != NULL) {
				ipStrR = gcnew String(core->getIpListReserve()->IpAddress.String);
			}
			String^ maskStr = gcnew String(core->getIpList()->IpMask.String);
			String^ gwStr = gcnew String(core->getGatewayList()->IpAddress.String);
			String^ msg = "Текущие: IP:" + ipStrO + "; " + ipStrR + " Mask:" + maskStr + " GW : " + gwStr;
			toolStripStatusLabelIp->Text = msg;

			String^ nameNC = gcnew String(core->getAdapterName());
			labelNC->Text = nameNC;
			String^ descCard = gcnew String(core->getDescription());
			labelDC->Text = descCard;

			textBoxIpOK->Text = ipStrO;
			textBoxIpRK->Text = ipStrR;

			textBoxMaskOK->Text = maskStr;
			textBoxMaskRK->Text = maskStr;

			textBoxShOK->Text = core->getMainGateway();
			textBoxShRK->Text = core->getReserveGateway();
			
			checkedWinElements();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Settings()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStripSettings;
	private: System::Windows::Forms::NotifyIcon^  notifyIconTray;
	private: System::Windows::Forms::ToolStripMenuItem^  defGatToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  resGatToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  settingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	protected:

	protected:
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::GroupBox^  groupBoxOsnKan;
	private: System::Windows::Forms::Label^  labelStatIp;
	private: System::Windows::Forms::Label^  labelShluseOk;
	private: System::Windows::Forms::Label^  labelMaskOk;
	private: System::Windows::Forms::Label^  labelIpOK;
	private: System::Windows::Forms::GroupBox^  groupBoxResKan;
	private: System::Windows::Forms::Label^  labelIpRk;
	private: System::Windows::Forms::Label^  labelShluseRk;


	private: System::Windows::Forms::Label^  labelMaskRk;

	private: System::Windows::Forms::Label^  labelIpResk;

	private: System::Windows::Forms::StatusStrip^  statusStripInfo;

private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelCanal;
private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelPing;
private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelIp;
	private: System::Windows::Forms::TextBox^  textBoxShOK;

	private: System::Windows::Forms::TextBox^  textBoxMaskOK;

	private: System::Windows::Forms::TextBox^  textBoxIpOK;
	private: System::Windows::Forms::TextBox^  textBoxShRK;


	private: System::Windows::Forms::TextBox^  textBoxMaskRK;

	private: System::Windows::Forms::TextBox^  textBoxIpRK;

	private: System::Windows::Forms::Label^  labelNameCard;
	private: System::Windows::Forms::Label^  labelDescCard;
	private: System::Windows::Forms::Label^  labelNC;
	private: System::Windows::Forms::Label^  labelDC;
	private: System::Windows::Forms::Button^  buttonSave;
	private: System::Windows::Forms::GroupBox^  groupBoxChannel;
	private: System::Windows::Forms::RadioButton^  radioButtonRK;
	private: System::Windows::Forms::RadioButton^  radioButtonOK;
	private: System::Windows::Forms::Timer^  timerPing;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		GatewayChanger^ core;

		void checkedWinElements() {
			String^ ipStrO = gcnew String(core->getIpList()->IpAddress.String);
			String^ ipStrR = ipStrO;
			if (core->getIpListReserve() != NULL) {
				ipStrR = gcnew String(core->getIpListReserve()->IpAddress.String);
			}
			String^ maskStr = gcnew String(core->getIpList()->IpMask.String);
			String^ gwStr = gcnew String(core->getGatewayList()->IpAddress.String);
			String^ msg = "Текущие: IP:" + ipStrO + "; " + ipStrR + " Mask:" + maskStr + " GW : " + gwStr;
			toolStripStatusLabelIp->Text = msg;

			switch (core->isMainChannel())
			{
			case 1:
				radioButtonOK->Checked = true;
				radioButtonRK->Checked = false;
				defGatToolStripMenuItem->Checked = true;
				resGatToolStripMenuItem->Checked = false;
				toolStripStatusLabelCanal->Text = "Основной канал";
				break;
			case 2:
				radioButtonOK->Checked = false;
				radioButtonRK->Checked = true;
				defGatToolStripMenuItem->Checked = false;
				resGatToolStripMenuItem->Checked = true;
				toolStripStatusLabelCanal->Text = "Резервный канал";
				break;
			default:
				radioButtonOK->Checked = false;
				radioButtonRK->Checked = false;
				defGatToolStripMenuItem->Checked = false;
				resGatToolStripMenuItem->Checked = false;
				toolStripStatusLabelCanal->Text = "Неизвестный канал";
				break;
			}
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Settings::typeid));
			this->contextMenuStripSettings = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->defGatToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->resGatToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->settingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->notifyIconTray = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->groupBoxOsnKan = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxShOK = (gcnew System::Windows::Forms::TextBox());
			this->textBoxMaskOK = (gcnew System::Windows::Forms::TextBox());
			this->textBoxIpOK = (gcnew System::Windows::Forms::TextBox());
			this->labelStatIp = (gcnew System::Windows::Forms::Label());
			this->labelShluseOk = (gcnew System::Windows::Forms::Label());
			this->labelMaskOk = (gcnew System::Windows::Forms::Label());
			this->labelIpOK = (gcnew System::Windows::Forms::Label());
			this->groupBoxResKan = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxShRK = (gcnew System::Windows::Forms::TextBox());
			this->textBoxMaskRK = (gcnew System::Windows::Forms::TextBox());
			this->textBoxIpRK = (gcnew System::Windows::Forms::TextBox());
			this->labelIpRk = (gcnew System::Windows::Forms::Label());
			this->labelShluseRk = (gcnew System::Windows::Forms::Label());
			this->labelMaskRk = (gcnew System::Windows::Forms::Label());
			this->labelIpResk = (gcnew System::Windows::Forms::Label());
			this->statusStripInfo = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabelCanal = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabelPing = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabelIp = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->labelNameCard = (gcnew System::Windows::Forms::Label());
			this->labelDescCard = (gcnew System::Windows::Forms::Label());
			this->labelNC = (gcnew System::Windows::Forms::Label());
			this->labelDC = (gcnew System::Windows::Forms::Label());
			this->buttonSave = (gcnew System::Windows::Forms::Button());
			this->groupBoxChannel = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonRK = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonOK = (gcnew System::Windows::Forms::RadioButton());
			this->timerPing = (gcnew System::Windows::Forms::Timer(this->components));
			this->contextMenuStripSettings->SuspendLayout();
			this->groupBoxOsnKan->SuspendLayout();
			this->groupBoxResKan->SuspendLayout();
			this->statusStripInfo->SuspendLayout();
			this->groupBoxChannel->SuspendLayout();
			this->SuspendLayout();
			// 
			// contextMenuStripSettings
			// 
			this->contextMenuStripSettings->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->defGatToolStripMenuItem,
					this->resGatToolStripMenuItem, this->toolStripSeparator1, this->settingToolStripMenuItem, this->toolStripSeparator2, this->exitToolStripMenuItem
			});
			this->contextMenuStripSettings->Name = L"contextMenuStripSettings";
			this->contextMenuStripSettings->Size = System::Drawing::Size(170, 104);
			this->contextMenuStripSettings->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &Settings::contextMenuStripSettings_Opening);
			// 
			// defGatToolStripMenuItem
			// 
			this->defGatToolStripMenuItem->Name = L"defGatToolStripMenuItem";
			this->defGatToolStripMenuItem->Size = System::Drawing::Size(169, 22);
			this->defGatToolStripMenuItem->Text = L"Основной канал";
			this->defGatToolStripMenuItem->Click += gcnew System::EventHandler(this, &Settings::defGatToolStripMenuItem_Click);
			// 
			// resGatToolStripMenuItem
			// 
			this->resGatToolStripMenuItem->Name = L"resGatToolStripMenuItem";
			this->resGatToolStripMenuItem->Size = System::Drawing::Size(169, 22);
			this->resGatToolStripMenuItem->Text = L"Резервный канал";
			this->resGatToolStripMenuItem->Click += gcnew System::EventHandler(this, &Settings::resGatToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(166, 6);
			// 
			// settingToolStripMenuItem
			// 
			this->settingToolStripMenuItem->Name = L"settingToolStripMenuItem";
			this->settingToolStripMenuItem->Size = System::Drawing::Size(169, 22);
			this->settingToolStripMenuItem->Text = L"Настройки";
			this->settingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Settings::settingToolStripMenuItem_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(166, 6);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(169, 22);
			this->exitToolStripMenuItem->Text = L"Выход";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Settings::exitToolStripMenuItem_Click);
			// 
			// notifyIconTray
			// 
			this->notifyIconTray->ContextMenuStrip = this->contextMenuStripSettings;
			this->notifyIconTray->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"notifyIconTray.Icon")));
			this->notifyIconTray->Text = L"Default Gateway Changer";
			this->notifyIconTray->Visible = true;
			// 
			// groupBoxOsnKan
			// 
			this->groupBoxOsnKan->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->groupBoxOsnKan->Controls->Add(this->textBoxShOK);
			this->groupBoxOsnKan->Controls->Add(this->textBoxMaskOK);
			this->groupBoxOsnKan->Controls->Add(this->textBoxIpOK);
			this->groupBoxOsnKan->Controls->Add(this->labelStatIp);
			this->groupBoxOsnKan->Controls->Add(this->labelShluseOk);
			this->groupBoxOsnKan->Controls->Add(this->labelMaskOk);
			this->groupBoxOsnKan->Controls->Add(this->labelIpOK);
			this->groupBoxOsnKan->Location = System::Drawing::Point(12, 53);
			this->groupBoxOsnKan->Name = L"groupBoxOsnKan";
			this->groupBoxOsnKan->Size = System::Drawing::Size(350, 133);
			this->groupBoxOsnKan->TabIndex = 1;
			this->groupBoxOsnKan->TabStop = false;
			this->groupBoxOsnKan->Text = L"Основной канал";
			// 
			// textBoxShOK
			// 
			this->textBoxShOK->Location = System::Drawing::Point(123, 96);
			this->textBoxShOK->Name = L"textBoxShOK";
			this->textBoxShOK->Size = System::Drawing::Size(221, 20);
			this->textBoxShOK->TabIndex = 28;
			// 
			// textBoxMaskOK
			// 
			this->textBoxMaskOK->Location = System::Drawing::Point(123, 67);
			this->textBoxMaskOK->Name = L"textBoxMaskOK";
			this->textBoxMaskOK->ReadOnly = true;
			this->textBoxMaskOK->Size = System::Drawing::Size(221, 20);
			this->textBoxMaskOK->TabIndex = 27;
			// 
			// textBoxIpOK
			// 
			this->textBoxIpOK->Location = System::Drawing::Point(123, 38);
			this->textBoxIpOK->Name = L"textBoxIpOK";
			this->textBoxIpOK->ReadOnly = true;
			this->textBoxIpOK->Size = System::Drawing::Size(221, 20);
			this->textBoxIpOK->TabIndex = 26;
			// 
			// labelStatIp
			// 
			this->labelStatIp->AutoSize = true;
			this->labelStatIp->Location = System::Drawing::Point(6, 16);
			this->labelStatIp->Name = L"labelStatIp";
			this->labelStatIp->Size = System::Drawing::Size(190, 13);
			this->labelStatIp->TabIndex = 25;
			this->labelStatIp->Text = L"Использовать следующий IP-адрес:";
			// 
			// labelShluseOk
			// 
			this->labelShluseOk->AutoSize = true;
			this->labelShluseOk->Location = System::Drawing::Point(16, 99);
			this->labelShluseOk->Name = L"labelShluseOk";
			this->labelShluseOk->Size = System::Drawing::Size(91, 13);
			this->labelShluseOk->TabIndex = 10;
			this->labelShluseOk->Text = L"Основной шлюз:";
			// 
			// labelMaskOk
			// 
			this->labelMaskOk->AutoSize = true;
			this->labelMaskOk->Location = System::Drawing::Point(16, 70);
			this->labelMaskOk->Name = L"labelMaskOk";
			this->labelMaskOk->Size = System::Drawing::Size(87, 13);
			this->labelMaskOk->TabIndex = 5;
			this->labelMaskOk->Text = L"Маска подсети:";
			// 
			// labelIpOK
			// 
			this->labelIpOK->AutoSize = true;
			this->labelIpOK->Location = System::Drawing::Point(16, 41);
			this->labelIpOK->Name = L"labelIpOK";
			this->labelIpOK->Size = System::Drawing::Size(56, 13);
			this->labelIpOK->TabIndex = 0;
			this->labelIpOK->Text = L"IP-адрес: ";
			// 
			// groupBoxResKan
			// 
			this->groupBoxResKan->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBoxResKan->Controls->Add(this->textBoxShRK);
			this->groupBoxResKan->Controls->Add(this->textBoxMaskRK);
			this->groupBoxResKan->Controls->Add(this->textBoxIpRK);
			this->groupBoxResKan->Controls->Add(this->labelIpRk);
			this->groupBoxResKan->Controls->Add(this->labelShluseRk);
			this->groupBoxResKan->Controls->Add(this->labelMaskRk);
			this->groupBoxResKan->Controls->Add(this->labelIpResk);
			this->groupBoxResKan->Location = System::Drawing::Point(372, 53);
			this->groupBoxResKan->Name = L"groupBoxResKan";
			this->groupBoxResKan->Size = System::Drawing::Size(350, 133);
			this->groupBoxResKan->TabIndex = 2;
			this->groupBoxResKan->TabStop = false;
			this->groupBoxResKan->Text = L"Резервный канал";
			// 
			// textBoxShRK
			// 
			this->textBoxShRK->Location = System::Drawing::Point(120, 96);
			this->textBoxShRK->Name = L"textBoxShRK";
			this->textBoxShRK->Size = System::Drawing::Size(224, 20);
			this->textBoxShRK->TabIndex = 29;
			// 
			// textBoxMaskRK
			// 
			this->textBoxMaskRK->Location = System::Drawing::Point(120, 67);
			this->textBoxMaskRK->Name = L"textBoxMaskRK";
			this->textBoxMaskRK->ReadOnly = true;
			this->textBoxMaskRK->Size = System::Drawing::Size(224, 20);
			this->textBoxMaskRK->TabIndex = 28;
			// 
			// textBoxIpRK
			// 
			this->textBoxIpRK->Location = System::Drawing::Point(120, 38);
			this->textBoxIpRK->Name = L"textBoxIpRK";
			this->textBoxIpRK->ReadOnly = true;
			this->textBoxIpRK->Size = System::Drawing::Size(224, 20);
			this->textBoxIpRK->TabIndex = 27;
			// 
			// labelIpRk
			// 
			this->labelIpRk->AutoSize = true;
			this->labelIpRk->Location = System::Drawing::Point(6, 16);
			this->labelIpRk->Name = L"labelIpRk";
			this->labelIpRk->Size = System::Drawing::Size(190, 13);
			this->labelIpRk->TabIndex = 25;
			this->labelIpRk->Text = L"Использовать следующий IP-адрес:";
			// 
			// labelShluseRk
			// 
			this->labelShluseRk->AutoSize = true;
			this->labelShluseRk->Location = System::Drawing::Point(16, 99);
			this->labelShluseRk->Name = L"labelShluseRk";
			this->labelShluseRk->Size = System::Drawing::Size(91, 13);
			this->labelShluseRk->TabIndex = 10;
			this->labelShluseRk->Text = L"Основной шлюз:";
			// 
			// labelMaskRk
			// 
			this->labelMaskRk->AutoSize = true;
			this->labelMaskRk->Location = System::Drawing::Point(16, 70);
			this->labelMaskRk->Name = L"labelMaskRk";
			this->labelMaskRk->Size = System::Drawing::Size(87, 13);
			this->labelMaskRk->TabIndex = 5;
			this->labelMaskRk->Text = L"Маска подсети:";
			// 
			// labelIpResk
			// 
			this->labelIpResk->AutoSize = true;
			this->labelIpResk->Location = System::Drawing::Point(16, 41);
			this->labelIpResk->Name = L"labelIpResk";
			this->labelIpResk->Size = System::Drawing::Size(56, 13);
			this->labelIpResk->TabIndex = 0;
			this->labelIpResk->Text = L"IP-адрес: ";
			// 
			// statusStripInfo
			// 
			this->statusStripInfo->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripStatusLabelCanal,
					this->toolStripStatusLabelPing, this->toolStripStatusLabelIp
			});
			this->statusStripInfo->Location = System::Drawing::Point(0, 277);
			this->statusStripInfo->Name = L"statusStripInfo";
			this->statusStripInfo->Size = System::Drawing::Size(734, 22);
			this->statusStripInfo->TabIndex = 3;
			this->statusStripInfo->Text = L"statusStripStatus";
			// 
			// toolStripStatusLabelCanal
			// 
			this->toolStripStatusLabelCanal->ForeColor = System::Drawing::SystemColors::ControlText;
			this->toolStripStatusLabelCanal->Name = L"toolStripStatusLabelCanal";
			this->toolStripStatusLabelCanal->Size = System::Drawing::Size(115, 17);
			this->toolStripStatusLabelCanal->Text = L"Неизвестный канал";
			// 
			// toolStripStatusLabelPing
			// 
			this->toolStripStatusLabelPing->ForeColor = System::Drawing::Color::Black;
			this->toolStripStatusLabelPing->Name = L"toolStripStatusLabelPing";
			this->toolStripStatusLabelPing->Size = System::Drawing::Size(96, 17);
			this->toolStripStatusLabelPing->Text = L"Проверка пинга";
			// 
			// toolStripStatusLabelIp
			// 
			this->toolStripStatusLabelIp->Name = L"toolStripStatusLabelIp";
			this->toolStripStatusLabelIp->Size = System::Drawing::Size(120, 17);
			this->toolStripStatusLabelIp->Text = L"Текущие настройки:";
			// 
			// labelNameCard
			// 
			this->labelNameCard->AutoSize = true;
			this->labelNameCard->Location = System::Drawing::Point(24, 6);
			this->labelNameCard->Name = L"labelNameCard";
			this->labelNameCard->Size = System::Drawing::Size(110, 13);
			this->labelNameCard->TabIndex = 4;
			this->labelNameCard->Text = L"Имя сетевой карты:";
			// 
			// labelDescCard
			// 
			this->labelDescCard->AutoSize = true;
			this->labelDescCard->Location = System::Drawing::Point(24, 28);
			this->labelDescCard->Name = L"labelDescCard";
			this->labelDescCard->Size = System::Drawing::Size(138, 13);
			this->labelDescCard->TabIndex = 5;
			this->labelDescCard->Text = L"Описание сетевой карты:";
			// 
			// labelNC
			// 
			this->labelNC->AutoSize = true;
			this->labelNC->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelNC->Location = System::Drawing::Point(176, 6);
			this->labelNC->Name = L"labelNC";
			this->labelNC->Size = System::Drawing::Size(36, 13);
			this->labelNC->TabIndex = 6;
			this->labelNC->Text = L"Имя ";
			// 
			// labelDC
			// 
			this->labelDC->AutoSize = true;
			this->labelDC->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelDC->Location = System::Drawing::Point(176, 28);
			this->labelDC->Name = L"labelDC";
			this->labelDC->Size = System::Drawing::Size(65, 13);
			this->labelDC->TabIndex = 7;
			this->labelDC->Text = L"Описание";
			// 
			// buttonSave
			// 
			this->buttonSave->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonSave->Location = System::Drawing::Point(611, 251);
			this->buttonSave->Name = L"buttonSave";
			this->buttonSave->Size = System::Drawing::Size(114, 23);
			this->buttonSave->TabIndex = 8;
			this->buttonSave->Text = L"Сохранить";
			this->buttonSave->UseVisualStyleBackColor = true;
			this->buttonSave->Click += gcnew System::EventHandler(this, &Settings::buttonSave_Click);
			// 
			// groupBoxChannel
			// 
			this->groupBoxChannel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBoxChannel->Controls->Add(this->radioButtonRK);
			this->groupBoxChannel->Controls->Add(this->radioButtonOK);
			this->groupBoxChannel->Location = System::Drawing::Point(12, 192);
			this->groupBoxChannel->Name = L"groupBoxChannel";
			this->groupBoxChannel->Size = System::Drawing::Size(713, 54);
			this->groupBoxChannel->TabIndex = 9;
			this->groupBoxChannel->TabStop = false;
			this->groupBoxChannel->Text = L"Текущий канал";
			// 
			// radioButtonRK
			// 
			this->radioButtonRK->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->radioButtonRK->AutoSize = true;
			this->radioButtonRK->Location = System::Drawing::Point(360, 25);
			this->radioButtonRK->Name = L"radioButtonRK";
			this->radioButtonRK->Size = System::Drawing::Size(115, 17);
			this->radioButtonRK->TabIndex = 1;
			this->radioButtonRK->Text = L"Резервный канал";
			this->radioButtonRK->UseVisualStyleBackColor = true;
			this->radioButtonRK->CheckedChanged += gcnew System::EventHandler(this, &Settings::radioButtonRK_CheckedChanged);
			// 
			// radioButtonOK
			// 
			this->radioButtonOK->AutoSize = true;
			this->radioButtonOK->Location = System::Drawing::Point(15, 25);
			this->radioButtonOK->Name = L"radioButtonOK";
			this->radioButtonOK->Size = System::Drawing::Size(108, 17);
			this->radioButtonOK->TabIndex = 0;
			this->radioButtonOK->Text = L"Основной канал";
			this->radioButtonOK->UseVisualStyleBackColor = true;
			this->radioButtonOK->CheckedChanged += gcnew System::EventHandler(this, &Settings::radioButtonOK_CheckedChanged);
			// 
			// timerPing
			// 
			this->timerPing->Enabled = true;
			this->timerPing->Interval = 5000;
			this->timerPing->Tick += gcnew System::EventHandler(this, &Settings::timerPing_Tick);
			// 
			// Settings
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(734, 299);
			this->Controls->Add(this->groupBoxChannel);
			this->Controls->Add(this->buttonSave);
			this->Controls->Add(this->labelDC);
			this->Controls->Add(this->labelNC);
			this->Controls->Add(this->labelDescCard);
			this->Controls->Add(this->labelNameCard);
			this->Controls->Add(this->statusStripInfo);
			this->Controls->Add(this->groupBoxResKan);
			this->Controls->Add(this->groupBoxOsnKan);
			this->Name = L"Settings";
			this->Text = L"Настройки";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Settings::Settings_FormClosing);
			this->Resize += gcnew System::EventHandler(this, &Settings::Settings_Resize);
			this->contextMenuStripSettings->ResumeLayout(false);
			this->groupBoxOsnKan->ResumeLayout(false);
			this->groupBoxOsnKan->PerformLayout();
			this->groupBoxResKan->ResumeLayout(false);
			this->groupBoxResKan->PerformLayout();
			this->statusStripInfo->ResumeLayout(false);
			this->statusStripInfo->PerformLayout();
			this->groupBoxChannel->ResumeLayout(false);
			this->groupBoxChannel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void contextMenuStripSettings_Opening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	}
	private: System::Void Settings_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 if (e->CloseReason == CloseReason::UserClosing)
				 {
					 e->Cancel = true;
					 this->WindowState = FormWindowState::Minimized;
					 Hide();
				 }
	}
private: System::Void settingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 Show();
			 this->WindowState = FormWindowState::Normal;
}
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 Application::Exit();
}
private: System::Void Settings_Resize(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void defGatToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 //defGatToolStripMenuItem->Checked = true;
			 //resGatToolStripMenuItem->Checked = false;
			 //if (radioButtonOK->Checked) {
				 //if (core->setNetworkCardGateway(1)) {
				 if (core->setNetworkGateway(1)) {
					 printf("[info] Done changing gateway!!!\n");
				 }
				 else {
					 printf("[error] Bad parametr NChannel.\n");
				 }
			 //}
}
private: System::Void resGatToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 //defGatToolStripMenuItem->Checked = false;
			 //resGatToolStripMenuItem->Checked = true;
			 //if (radioButtonRK->Checked) {
				 //if (core->setNetworkCardGateway(2)) {
				 if (core->setNetworkGateway(2)) {
					 printf("[info] Done changing gateway!!!\n");
				 }
				 else {
					 printf("[error] Bad parametr NChannel.\n");
				 }
			 //}
}
private: System::Void timerPing_Tick(System::Object^  sender, System::EventArgs^  e) {
			 core->selectNetCard();
			 core->checkingMainChannel();
			 checkedWinElements();
			 
			 printf("____________________\nPing tick\n");
			 if (core->pingGateway()) {
				 notifyIconTray->Icon = core->getTrueIco();
				 toolStripStatusLabelPing->Text = "Шлюз доступен";
				 toolStripStatusLabelPing->ForeColor = Color::Green;
			 }
			 else {
				 notifyIconTray->Icon = core->getFalseIco();
				 toolStripStatusLabelPing->Text = "Шлюз недоступен";
				 toolStripStatusLabelPing->ForeColor = Color::Red;
			 }
}
private: System::Void buttonSave_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((core->setMainGateway(textBoxShOK->Text)) && (core->setReserveGateway(textBoxShRK->Text))) {
				 core->saveXmlSettings();
			 }
}
private: System::Void radioButtonRK_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (radioButtonRK->Checked) {
				 //if (core->setNetworkCardGateway(2)) {
				 if (core->setNetworkGateway(2)) {
					 printf("[info] Done changing gateway!!!\n");
				 }
				 else {
					 printf("[error] Bad parametr NChannel.\n");
				 }
			 }
}
private: System::Void radioButtonOK_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (radioButtonOK->Checked) {
				 //if (core->setNetworkCardGateway(1)) {
				 if (core->setNetworkGateway(1)) {
					 printf("[info] Done changing gateway!!!\n");
				 }
				 else {
					 printf("[error] Bad parametr NChannel.\n");
				 }
			 }
}
};
}
