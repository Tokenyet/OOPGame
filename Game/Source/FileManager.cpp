#include "StdAfx.h"
#include <fstream>
#include "FileManager.h"
#include <iostream>
#include <vector>

FileManager::FileManager(const char* fileName)
{

	length = FileMaximum(fileName);
	data = new string[length];//�����Npointer�ظm�s���m 
	FillString_FromFile(fileName,data,length);
	FileName = fileName;
}
string* FileManager::GetData()
{
	return data;
}



//�����@�I�i�H�P FillString_FromFile�X�� 
int FileManager::FileMaximum(const char* fileName) 
{

	fstream file;
	file.open(fileName, ios_base::out | ios_base::in);  // will not create file
	if (file.is_open())
	{
	        file.close();
	}
	else
	{
	    file.clear();
	    file.open(fileName, ios_base::out);  // will create if necessary
	}


	int Line = 0;
	ifstream ifs(fileName);
	while(1)
	{
	string LineString;
	string TempString="";
	//ifs >> LineString; �v�rŪ�J 
	getline(ifs,LineString);
	if(LineString == TempString)
	break;
	TempString = LineString;
	Line ++;
	}
	if (ifs.is_open())
	ifs.close();
	return Line;
}

//�N�C��r��s�J�}�C  ���b�����s�J���� 
void FileManager::FillString_FromFile(const char* fileName,string* Data,int Length)
{
	//string Temp_Data[Length];
	ifstream ifs(fileName);
	for(int i =0;i<Length;i++)
	{
		//ifs >> Data[i]; �v�rŪ�J 
		getline(ifs,Data[i]);
		//cout << Temp_Data[i] << endl;
	}
	if (ifs.is_open())
	ifs.close();
	//Data = Temp_Data;
}


void FileManager::SetLineData(vector<string> inputData)
{
	remove(FileName);
	std::ofstream fout(FileName);
	if (fout)
	 	for(size_t i=0;i<inputData.size();i++)
		fout << inputData[i] << std::endl;
		fout.close();

	/*fstream file;
	file.open(FileName);
	for(int i=0;i<inputData.size();i++)
		file<<inputData[i] << endl;
	file.close();*/
}

