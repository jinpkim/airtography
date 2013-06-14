using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace zerodayApp
{
    public partial class Form1 : Form
    {
        DirectoryInfo dirInfo1;
        //DirectoryInfo dirInfo2;
        //DirectoryInfo dirInfo_CG;
        //DirectoryInfo dirInfo_REAL;
        private string ExportFilePath = Path.GetDirectoryName(Application.ExecutablePath) + "\\IS.exe";
        private string ExportFilePath2 = Path.GetDirectoryName(Application.ExecutablePath) + "\\playsmf.exe";
        private string ExportFilePath3 = Path.GetDirectoryName(Application.ExecutablePath) + "\\smftoxml.exe";
        private string ExportFilePath4 = Path.GetDirectoryName(Application.ExecutablePath) + "\\IS_Decrypter.exe";
        private string ExportFilePath5 = Path.GetDirectoryName(Application.ExecutablePath) + "\\output.xml"; 



        string selected;
        string openstrFilename = null;
        //string folderName;
        //string folderName1;
        //string folderName2;

        public Form1()
        {
            InitializeComponent();
            textBox1.Text = "C:\\";
           // textBox2.Text = "Input the string you want to ENCRYPT";
           // textBox3.Text = "인코딩 파일을 저장할 폴더를 선택하세요";
            //textBox4.Text = "Choose the file you want to DECRYPT";
            selected = "C:\\";      //default <- 본인 컴퓨터에 맞게 변경
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
            ProcessStartInfo abc = new ProcessStartInfo(ExportFilePath3, convertFilePathForCmd(openstrFilename));
            ProcessStartInfo abc2 = new ProcessStartInfo(ExportFilePath4, "output.xml");

            abc.RedirectStandardOutput = true;
            abc.UseShellExecute = false;
            abc.WindowStyle = ProcessWindowStyle.Hidden;
            abc.CreateNoWindow = true;
            Process pXML = new Process();
            pXML.StartInfo = abc;
            pXML.Start();
            String outputxml = "";
            outputxml = pXML.StandardOutput.ReadToEnd();
            System.IO.File.WriteAllText(ExportFilePath5, outputxml);
            pXML.Close();

            abc2.UseShellExecute = false;
            abc2.WindowStyle = ProcessWindowStyle.Hidden;
            abc2.RedirectStandardOutput = true;
            abc2.CreateNoWindow = true;
            Process pDecode = new Process();
            pDecode.StartInfo = abc2;
            pDecode.Start();
            String outputDecode = pDecode.StandardOutput.ReadToEnd();
            textBox3.Text = outputDecode;
            pDecode.Close();
            MessageBox.Show("COMPLETE", "RESULT");
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            Process pISEncrypt = new Process();
            string arg = string.Concat(textBox2.Text, " ", convertFilePathForCmd(selected[selected.Length-1] == '\\' ? selected.Substring(0, selected.Length-1) : selected));
            ProcessStartInfo abc = new ProcessStartInfo(ExportFilePath, arg);
            abc.WindowStyle = ProcessWindowStyle.Hidden;
            pISEncrypt.StartInfo = abc;
            pISEncrypt.Start();
            MessageBox.Show("COMPLETE", "RESULT");
            pISEncrypt.Close();
            btnPlay.Enabled = true;
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

        private void btnPlay_Click(object sender, EventArgs e)
        {
            Process pPlay = new Process();
            string filepath = convertFilePathForCmd((selected[selected.Length - 1] == '\\' ? selected : selected + '\\') + "junkmidifile.mid");
            ProcessStartInfo abc = new ProcessStartInfo(ExportFilePath2, filepath);
            abc.WindowStyle = ProcessWindowStyle.Hidden;
            pPlay.StartInfo = abc;
            pPlay.Start();
            pPlay.Close();
        }

        private static string convertFilePathForCmd(string input)
        {
            return "\"" + input + "\"";
        }
    }
}
