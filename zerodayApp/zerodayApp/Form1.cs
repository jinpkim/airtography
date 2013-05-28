using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace zerodayApp
{
    public partial class Form1 : Form
    {
        DirectoryInfo dirInfo1;
        //DirectoryInfo dirInfo2;
        //DirectoryInfo dirInfo_CG;
        //DirectoryInfo dirInfo_REAL;
        private string ExportFilePath = Path.GetDirectoryName(Application.ExecutablePath) + "\\IS.exe"; 



        string selected;
        string openstrFilename = null;
        //string folderName;
        //string folderName1;
        //string folderName2;

        public Form1()
        {
            InitializeComponent();
            textBox1.Text = "C:";
           // textBox2.Text = "Input the string you want to ENCRYPT";
           // textBox3.Text = "인코딩 파일을 저장할 폴더를 선택하세요";
            //textBox4.Text = "Choose the file you want to DECRYPT";
            selected = "C:";      //default <- 본인 컴퓨터에 맞게 변경
        }

        private void Form1_Load(object sender, EventArgs e)
        {
    
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            //인코딩 파일을 저장할 폴더 선택!!
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                selected = dialog.SelectedPath;
                Directory.SetCurrentDirectory(selected);
                dirInfo1 = new DirectoryInfo(Directory.GetCurrentDirectory());
                textBox1.Text = selected;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            OpenFileDialog openfile = new OpenFileDialog();
            openfile.Filter = "MIDI File (*.mid)|*.mid";
            openfile.Title = "Select a MIDI File";
            if (openfile.ShowDialog() == DialogResult.OK)
            {
                openstrFilename = openfile.FileName;     //경로 
                textBox4.Text = openstrFilename;         //경로 출력

                //파일을 받아와서 어떤 type으로 어떻게 저장해 놓을 건지 변수와 저장 알고리즘 필요
                // 변수 =  encoding_data
            }
        }

        private void button4_Click_1(object sender, EventArgs e)
        {

            /*Decoding button 누르면 encoding_data를 처리하여
              textBox3.Text에 출력한다!! 
            */
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            string arg = string.Concat(textBox2.Text, " ", textBox1.Text);
            System.Diagnostics.Process.Start(ExportFilePath, arg);
            MessageBox.Show("COMPLETE", "RESULT");
        }

        private void label3_Click(object sender, EventArgs e)
        {
            
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
           
        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }


        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

    }
}
