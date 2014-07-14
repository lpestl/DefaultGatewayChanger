#include "GatewayChanger.h"

#pragma once

namespace DefaultGatewayChanger {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

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
			
			List<String^>^ ips = core->getIpAddresses();
			List<String^>^ masks = core->getMaskIpAddresses();

			for (int i = 0; i < ips->Count; i++) {
				if (dataGridViewIps->Rows->Count != ips->Count) {
					dataGridViewIps->Rows->Add();
				}
				dataGridViewIps->Rows[i]->Cells[0]->Value = ips[i];
				dataGridViewIps->Rows[i]->Cells[1]->Value = masks[i];
			}

			labelDC->Text = core->getMacAdapter();
			labelNC->Text = core->getNameAdapter();

			textBoxOkGateway->Text = core->getMainGateway();
			textBoxRkGateway->Text = core->getReserveGateway();

			m_prevMainChan = checkedWinElements();
			timerPing->Start();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Settings()
		{
			timerPing->Stop();
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
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::StatusStrip^  statusStripInfo;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelCanal;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelPing;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelIp;
	private: System::Windows::Forms::Label^  labelNameCard;
	private: System::Windows::Forms::Label^  labelDescCard;
	private: System::Windows::Forms::Label^  labelNC;
	private: System::Windows::Forms::Label^  labelDC;
	private: System::Windows::Forms::Button^  buttonSave;
	private: System::Windows::Forms::GroupBox^  groupBoxChannel;
	private: System::Windows::Forms::RadioButton^  radioButtonRK;
	private: System::Windows::Forms::RadioButton^  radioButtonOK;
	private: System::Windows::Forms::Timer^  timerPing;
	private: System::Windows::Forms::DataGridView^  dataGridViewIps;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnIP;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnMask;
	private: System::Windows::Forms::GroupBox^  groupBoxIPs;
	private: System::Windows::Forms::TextBox^  textBoxRkGateway;

	private: System::Windows::Forms::TextBox^  textBoxOkGateway;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		GatewayChanger^ core;
		int m_prevMainChan;

		void deActivate() {
			defGatToolStripMenuItem->Enabled = false;
			resGatToolStripMenuItem->Enabled = false;
			settingToolStripMenuItem->Enabled = false;
			exitToolStripMenuItem->Enabled = false;
		}

		void activate() {
			defGatToolStripMenuItem->Enabled = true;
			resGatToolStripMenuItem->Enabled = true;
			settingToolStripMenuItem->Enabled = true;
			exitToolStripMenuItem->Enabled = true;
		}

		int checkedWinElements() {
			int channel = core->isMainChannel();

			switch (channel)
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

			return channel;
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
			this->textBoxRkGateway = (gcnew System::Windows::Forms::TextBox());
			this->textBoxOkGateway = (gcnew System::Windows::Forms::TextBox());
			this->radioButtonRK = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonOK = (gcnew System::Windows::Forms::RadioButton());
			this->timerPing = (gcnew System::Windows::Forms::Timer(this->components));
			this->dataGridViewIps = (gcnew System::Windows::Forms::DataGridView());
			this->ColumnIP = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnMask = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->groupBoxIPs = (gcnew System::Windows::Forms::GroupBox());
			this->contextMenuStripSettings->SuspendLayout();
			this->statusStripInfo->SuspendLayout();
			this->groupBoxChannel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewIps))->BeginInit();
			this->groupBoxIPs->SuspendLayout();
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
			// statusStripInfo
			// 
			this->statusStripInfo->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripStatusLabelCanal,
					this->toolStripStatusLabelPing, this->toolStripStatusLabelIp
			});
			this->statusStripInfo->Location = System::Drawing::Point(0, 275);
			this->statusStripInfo->Name = L"statusStripInfo";
			this->statusStripInfo->Size = System::Drawing::Size(356, 22);
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
			this->labelNameCard->Location = System::Drawing::Point(9, 6);
			this->labelNameCard->Name = L"labelNameCard";
			this->labelNameCard->Size = System::Drawing::Size(110, 13);
			this->labelNameCard->TabIndex = 4;
			this->labelNameCard->Text = L"Имя сетевой карты:";
			// 
			// labelDescCard
			// 
			this->labelDescCard->AutoSize = true;
			this->labelDescCard->Location = System::Drawing::Point(9, 28);
			this->labelDescCard->Name = L"labelDescCard";
			this->labelDescCard->Size = System::Drawing::Size(107, 13);
			this->labelDescCard->TabIndex = 5;
			this->labelDescCard->Text = L"Физический адрес:";
			// 
			// labelNC
			// 
			this->labelNC->AutoSize = true;
			this->labelNC->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelNC->Location = System::Drawing::Point(122, 6);
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
			this->labelDC->Location = System::Drawing::Point(122, 28);
			this->labelDC->Name = L"labelDC";
			this->labelDC->Size = System::Drawing::Size(65, 13);
			this->labelDC->TabIndex = 7;
			this->labelDC->Text = L"Описание";
			// 
			// buttonSave
			// 
			this->buttonSave->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonSave->Location = System::Drawing::Point(233, 249);
			this->buttonSave->Name = L"buttonSave";
			this->buttonSave->Size = System::Drawing::Size(114, 23);
			this->buttonSave->TabIndex = 8;
			this->buttonSave->Text = L"Сохранить";
			this->buttonSave->UseVisualStyleBackColor = true;
			this->buttonSave->Click += gcnew System::EventHandler(this, &Settings::buttonSave_Click);
			// 
			// groupBoxChannel
			// 
			this->groupBoxChannel->Controls->Add(this->textBoxRkGateway);
			this->groupBoxChannel->Controls->Add(this->textBoxOkGateway);
			this->groupBoxChannel->Controls->Add(this->radioButtonRK);
			this->groupBoxChannel->Controls->Add(this->radioButtonOK);
			this->groupBoxChannel->Location = System::Drawing::Point(12, 168);
			this->groupBoxChannel->Name = L"groupBoxChannel";
			this->groupBoxChannel->Size = System::Drawing::Size(337, 75);
			this->groupBoxChannel->TabIndex = 9;
			this->groupBoxChannel->TabStop = false;
			this->groupBoxChannel->Text = L"Текущий канал";
			// 
			// textBoxRkGateway
			// 
			this->textBoxRkGateway->Location = System::Drawing::Point(168, 44);
			this->textBoxRkGateway->Name = L"textBoxRkGateway";
			this->textBoxRkGateway->Size = System::Drawing::Size(150, 20);
			this->textBoxRkGateway->TabIndex = 3;
			// 
			// textBoxOkGateway
			// 
			this->textBoxOkGateway->Location = System::Drawing::Point(168, 18);
			this->textBoxOkGateway->Name = L"textBoxOkGateway";
			this->textBoxOkGateway->Size = System::Drawing::Size(150, 20);
			this->textBoxOkGateway->TabIndex = 2;
			// 
			// radioButtonRK
			// 
			this->radioButtonRK->AutoSize = true;
			this->radioButtonRK->Enabled = false;
			this->radioButtonRK->Location = System::Drawing::Point(15, 45);
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
			this->radioButtonOK->Enabled = false;
			this->radioButtonOK->Location = System::Drawing::Point(15, 19);
			this->radioButtonOK->Name = L"radioButtonOK";
			this->radioButtonOK->Size = System::Drawing::Size(108, 17);
			this->radioButtonOK->TabIndex = 0;
			this->radioButtonOK->Text = L"Основной канал";
			this->radioButtonOK->UseVisualStyleBackColor = true;
			this->radioButtonOK->CheckedChanged += gcnew System::EventHandler(this, &Settings::radioButtonOK_CheckedChanged);
			// 
			// timerPing
			// 
			this->timerPing->Interval = 5000;
			this->timerPing->Tick += gcnew System::EventHandler(this, &Settings::timerPing_Tick);
			// 
			// dataGridViewIps
			// 
			this->dataGridViewIps->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridViewIps->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->ColumnIP,
					this->ColumnMask
			});
			this->dataGridViewIps->Location = System::Drawing::Point(15, 19);
			this->dataGridViewIps->Name = L"dataGridViewIps";
			this->dataGridViewIps->RowHeadersVisible = false;
			this->dataGridViewIps->Size = System::Drawing::Size(303, 70);
			this->dataGridViewIps->TabIndex = 10;
			// 
			// ColumnIP
			// 
			this->ColumnIP->HeaderText = L"IP-адрес";
			this->ColumnIP->Name = L"ColumnIP";
			this->ColumnIP->Width = 150;
			// 
			// ColumnMask
			// 
			this->ColumnMask->HeaderText = L"Маска подсети";
			this->ColumnMask->Name = L"ColumnMask";
			this->ColumnMask->Width = 150;
			// 
			// groupBoxIPs
			// 
			this->groupBoxIPs->Controls->Add(this->dataGridViewIps);
			this->groupBoxIPs->Location = System::Drawing::Point(12, 53);
			this->groupBoxIPs->Name = L"groupBoxIPs";
			this->groupBoxIPs->Size = System::Drawing::Size(337, 109);
			this->groupBoxIPs->TabIndex = 11;
			this->groupBoxIPs->TabStop = false;
			this->groupBoxIPs->Text = L"IP адреса";
			// 
			// Settings
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(356, 297);
			this->Controls->Add(this->groupBoxIPs);
			this->Controls->Add(this->groupBoxChannel);
			this->Controls->Add(this->buttonSave);
			this->Controls->Add(this->labelDC);
			this->Controls->Add(this->labelNC);
			this->Controls->Add(this->labelDescCard);
			this->Controls->Add(this->labelNameCard);
			this->Controls->Add(this->statusStripInfo);
			this->Name = L"Settings";
			this->Text = L"Настройки";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Settings::Settings_FormClosing);
			this->Resize += gcnew System::EventHandler(this, &Settings::Settings_Resize);
			this->contextMenuStripSettings->ResumeLayout(false);
			this->statusStripInfo->ResumeLayout(false);
			this->statusStripInfo->PerformLayout();
			this->groupBoxChannel->ResumeLayout(false);
			this->groupBoxChannel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewIps))->EndInit();
			this->groupBoxIPs->ResumeLayout(false);
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
			 timerPing->Stop();
			 deActivate();
			 if (core->changeDefaultGateway(1)) {
				 printf("[info] Done changing gateway!!!\n");
			 }
			 else {
				 printf("[error] Bad parametr NChannel.\n");
			 }
			 activate();
			 //Sleep(5000);
			 timerPing->Start();
}

private: System::Void resGatToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 timerPing->Stop();
			 deActivate();
			 if (core->changeDefaultGateway(2)) {
				 printf("[info] Done changing gateway!!!\n");
			 }
			 else {
				 printf("[error] Bad parametr NChannel.\n");
			 }
			 activate();
			 //Sleep(5000);
			 timerPing->Start();
}

private: System::Void timerPing_Tick(System::Object^  sender, System::EventArgs^  e) {			 
			 //if (m_prevMainChan != core->isMainChannel()) {
			 checkedWinElements();
			 //	m_prevMainChan = core->isMainChannel();
			 //}

			 List<String^>^ gateways = core->getGateways();
			 toolStripStatusLabelIp->Text = "Шлюз: ";
			 for (int i = 0; i < gateways->Count; i++) {
				 toolStripStatusLabelIp->Text += gateways[i];
				 toolStripStatusLabelIp->Text += "; ";
			 }
			 
			 if (core->pingGateway()) {
				 notifyIconTray->Icon = core->getTrueIco();
				 toolStripStatusLabelPing->Text = "Шлюз доступен";
				 toolStripStatusLabelPing->ForeColor = Color::Green;
			 }
			 else {
				 notifyIconTray->Icon = core->getFalseIco();
				 toolStripStatusLabelPing->Text = "Шлюз не доступен";
				 toolStripStatusLabelPing->ForeColor = Color::Red;
			 }
}

private: System::Void buttonSave_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((core->checkIpString(textBoxOkGateway->Text)) && (core->checkIpString(textBoxRkGateway->Text))) {
				 core->setMainCanIpGateway(textBoxOkGateway->Text);
				 core->setReserveCanIpGateway(textBoxRkGateway->Text);
				 core->saveXmlSettings();
			 }
}
private: System::Void radioButtonRK_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 //timerPing->Stop();
			 //if (radioButtonRK->Checked) {
				// //if (core->setNetworkCardGateway(2)) {
				// if (core->changeDefaultGateway(2)) {
				//	 printf("[info] Done changing gateway!!!\n");
				// }
				// else {
				//	 printf("[error] Bad parametr NChannel.\n");
				// }
			 //}
			 //timerPing->Start();
}
private: System::Void radioButtonOK_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 //timerPing->Stop();
			 //if (radioButtonOK->Checked) {
				// //if (core->setNetworkCardGateway(1)) {
				// if (core->changeDefaultGateway(1)) {
				//	 printf("[info] Done changing gateway!!!\n");
				// }
				// else {
				//	 printf("[error] Bad parametr NChannel.\n");
				// }
			 //}
			 //timerPing->Start();
}
};
}
