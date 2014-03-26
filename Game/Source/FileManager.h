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
		string* data;//存放資料
		const char* FileName;
		int FileMaximum(const char* fileName);
		void FillString_FromFile(const char* fileName,string* Data,int Length);
		//註記: string* Data 本來要用 address(&)但 address無法傳陣列與指標 
	public:
		FileManager(const char* fileName);//從檔案初始資料 
		~FileManager(){delete[] data;}
		string* GetData();//設定字串 最好是陣列近來即可 
		int GetLine(){return length;}//
		void SetLineData(vector<string> data);
};
/*example
	FileManager FileData("檔案名稱.副檔名");
	int Length = FileData.GetLine();         :取得長度 
	string Data[Length];                     :建置適當字串長度        Array and Pointer 都需要建置容器長度 
	FileData.Fill_Array_WithData(Data);      :用現有容器取得字串資料  Data可為pointer or Array 
*/
#endif
