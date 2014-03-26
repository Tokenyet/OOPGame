#include "StdAfx.h"
#include <fstream>
#include "FileManager.h"
#include <iostream>
#include <vector>

FileManager::FileManager(const char* fileName)
{
	length = FileMaximum(fileName);
	data = new string[length];//必須將pointer建置連續位置 
	FillString_FromFile(fileName,data,length);
	FileName = fileName;
}
string* FileManager::GetData()
{
	return data;
}



//完美一點可以與 FillString_FromFile合併 
int FileManager::FileMaximum(const char* fileName) 
{
	int Line = 0;
	ifstream ifs(fileName);
	while(1)
	{
	string LineString;
	string TempString="";
	//ifs >> LineString; 逐字讀入 
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

//將每行字串存入陣列  但在此先存入指標 
void FileManager::FillString_FromFile(const char* fileName,string* Data,int Length)
{
	//string Temp_Data[Length];
	ifstream ifs(fileName);
	for(int i =0;i<Length;i++)
	{
		//ifs >> Data[i]; 逐字讀入 
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

