#pragma once

namespace UserInterface {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button_view_mage;
	private: System::Windows::Forms::ProgressBar^  progressBar_conversion;
	private: System::Windows::Forms::Label^  data_processing;
	private: System::Windows::Forms::Button^  convert_avi;
	private: System::Windows::Forms::Button^  covert_avi_manual;
	private: System::Windows::Forms::Button^  convert_to_jpeg;
	private: System::Windows::Forms::Button^  convert_jpeg_files;
	private: System::Windows::Forms::Button^  button_Exit;
	private: System::Windows::Forms::Label^  label3;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button_view_mage = (gcnew System::Windows::Forms::Button());
			this->progressBar_conversion = (gcnew System::Windows::Forms::ProgressBar());
			this->data_processing = (gcnew System::Windows::Forms::Label());
			this->convert_avi = (gcnew System::Windows::Forms::Button());
			this->covert_avi_manual = (gcnew System::Windows::Forms::Button());
			this->convert_to_jpeg = (gcnew System::Windows::Forms::Button());
			this->convert_jpeg_files = (gcnew System::Windows::Forms::Button());
			this->button_Exit = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(23, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(39, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Image:";
			this->label1->Click += gcnew System::EventHandler(this, &MainWindow::label1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(26, 45);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(387, 387);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MainWindow::pictureBox1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(419, 45);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(71, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"PatientName:";
			this->label2->Click += gcnew System::EventHandler(this, &MainWindow::label2_Click);
			// 
			// button_view_mage
			// 
			this->button_view_mage->Location = System::Drawing::Point(422, 123);
			this->button_view_mage->Name = L"button_view_mage";
			this->button_view_mage->Size = System::Drawing::Size(75, 23);
			this->button_view_mage->TabIndex = 3;
			this->button_view_mage->Text = L"view Image";
			this->button_view_mage->UseMnemonic = false;
			this->button_view_mage->UseVisualStyleBackColor = true;
			// 
			// progressBar_conversion
			// 
			this->progressBar_conversion->Location = System::Drawing::Point(423, 307);
			this->progressBar_conversion->Name = L"progressBar_conversion";
			this->progressBar_conversion->Size = System::Drawing::Size(144, 23);
			this->progressBar_conversion->TabIndex = 4;
			// 
			// data_processing
			// 
			this->data_processing->AutoSize = true;
			this->data_processing->Location = System::Drawing::Point(420, 291);
			this->data_processing->Name = L"data_processing";
			this->data_processing->Size = System::Drawing::Size(85, 13);
			this->data_processing->TabIndex = 5;
			this->data_processing->Text = L"data processing:";
			// 
			// convert_avi
			// 
			this->convert_avi->Location = System::Drawing::Point(422, 163);
			this->convert_avi->Name = L"convert_avi";
			this->convert_avi->Size = System::Drawing::Size(141, 23);
			this->convert_avi->TabIndex = 6;
			this->convert_avi->Text = L"convert to avi (folder)";
			this->convert_avi->UseVisualStyleBackColor = true;
			// 
			// covert_avi_manual
			// 
			this->covert_avi_manual->Location = System::Drawing::Point(423, 193);
			this->covert_avi_manual->Name = L"covert_avi_manual";
			this->covert_avi_manual->Size = System::Drawing::Size(140, 23);
			this->covert_avi_manual->TabIndex = 7;
			this->covert_avi_manual->Text = L"convert to avi (files)";
			this->covert_avi_manual->UseVisualStyleBackColor = true;
			// 
			// convert_to_jpeg
			// 
			this->convert_to_jpeg->Location = System::Drawing::Point(423, 223);
			this->convert_to_jpeg->Name = L"convert_to_jpeg";
			this->convert_to_jpeg->Size = System::Drawing::Size(140, 23);
			this->convert_to_jpeg->TabIndex = 8;
			this->convert_to_jpeg->Text = L"convert to .jpeg (folder)";
			this->convert_to_jpeg->UseVisualStyleBackColor = true;
			this->convert_to_jpeg->Click += gcnew System::EventHandler(this, &MainWindow::convert_to_jpeg_Click);
			// 
			// convert_jpeg_files
			// 
			this->convert_jpeg_files->Location = System::Drawing::Point(423, 252);
			this->convert_jpeg_files->Name = L"convert_jpeg_files";
			this->convert_jpeg_files->Size = System::Drawing::Size(140, 23);
			this->convert_jpeg_files->TabIndex = 9;
			this->convert_jpeg_files->Text = L"convert to .jpeg (files)";
			this->convert_jpeg_files->UseVisualStyleBackColor = true;
			// 
			// button_Exit
			// 
			this->button_Exit->ForeColor = System::Drawing::Color::Red;
			this->button_Exit->Location = System::Drawing::Point(423, 353);
			this->button_Exit->Name = L"button_Exit";
			this->button_Exit->Size = System::Drawing::Size(75, 23);
			this->button_Exit->TabIndex = 10;
			this->button_Exit->Text = L"Exit";
			this->button_Exit->UseVisualStyleBackColor = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(420, 397);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(63, 13);
			this->label3->TabIndex = 11;
			this->label3->Text = L"Debug Info:";
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(602, 483);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button_Exit);
			this->Controls->Add(this->convert_jpeg_files);
			this->Controls->Add(this->convert_to_jpeg);
			this->Controls->Add(this->covert_avi_manual);
			this->Controls->Add(this->convert_avi);
			this->Controls->Add(this->data_processing);
			this->Controls->Add(this->progressBar_conversion);
			this->Controls->Add(this->button_view_mage);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Name = L"MainWindow";
			this->Text = L"MainWindow";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void convert_to_jpeg_Click(System::Object^  sender, System::EventArgs^  e) {
	}
};
}
