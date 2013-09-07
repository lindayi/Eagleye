#include <windows.h> 
#include <tlhelp32.h> 
#include<stdio.h>

int ProcessList()
{
       PROCESSENTRY32 pe32;
       pe32.dwSize=sizeof(pe32);
       int count=0;
 
       HANDLE hProcessSnap=::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
 
       if(hProcessSnap==INVALID_HANDLE_VALUE)
       {
              //printf("CreateToolhelp32Snapshot调用失败!");
              return -1;
       }
 
       BOOL bMore=::Process32First(hProcessSnap,&pe32);
      
       printf("%25s\t%10s\n","进程名","PID");
       printf("===================================================\n");
       while(bMore)
       {
              count++;
              printf("%25s\t%10d\n",pe32.szExeFile,pe32.th32ProcessID);
              bMore=::Process32Next(hProcessSnap,&pe32);
       }
       printf("====================================================\n");
       printf("\n当前系统进程数为:%d\n",count);
	   ::CloseHandle(hProcessSnap);
       return 0;
}

int main()
{
	ProcessList();
	return 0;
} 
