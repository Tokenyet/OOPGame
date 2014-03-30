#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class FileManager
{
	private:
		int length;
		string* data;//�s����
		const char* FileName;
		int FileMaximum(const char* fileName);
		void FillString_FromFile(const char* fileName,string* Data,int Length);
		//���O: string* Data ���ӭn�� address(&)�� address�L�k�ǰ}�C�P���� 
	public:
		FileManager(const char* fileName);//�q�ɮת�l��� 
		~FileManager();
		string* GetData();//�]�w�r�� �̦n�O�}�C��ӧY�i 
		int GetLine(){return length;}//
		void SetLineData(vector<string> data);
};
/*example
	FileManager FileData("�ɮצW��.���ɦW");
	int Length = FileData.GetLine();         :���o���� 
	string Data[Length];                     :�ظm�A��r�����        Array and Pointer ���ݭn�ظm�e������ 
	FileData.Fill_Array_WithData(Data);      :�β{���e�����o�r����  Data�i��pointer or Array 
*/
#endif
