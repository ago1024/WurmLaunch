// WurmLaunch.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <TCHAR.H> 
#include <stdio.h>
#include <stdlib.h>

int _tWinMain(HINSTANCE hInstance,
	    HINSTANCE hPrevInstance,
	    LPTSTR    lpCmdLine,
	    int       nCmdShow)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	TCHAR cmdline[1024];
	const TCHAR *jnlp = "http://www.wurmonline.com/client/wurmclient.jnlp";

	if (_tcscmp(lpCmdLine, "stable") == 0)
	    jnlp = "http://www.wurmonline.com/client/wurmclient.jnlp";
	else if (_tcscmp(lpCmdLine, "unstable") == 0)
	    jnlp = "http://www.wurmonline.com/client/wurmclient_unstable.jnlp";
	else if (_tcscmp(lpCmdLine, "test") == 0 || _tcscmp(lpCmdLine, "testing") == 0)
	    jnlp = "http://www.wurmonline.com/client/wurmclient_test.jnlp";
	   
	_sntprintf(cmdline, sizeof(cmdline), "javaws -wait -Xnosplash %s", jnlp);

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	if( !CreateProcess( NULL,   // No module name (use command line)
		cmdline,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi )           // Pointer to PROCESS_INFORMATION structure
	) 
	{
	    MessageBox(NULL, "Could not launch Wurm Online.\nPlease make sure you have Java installed.", "Error", MB_ICONERROR);
	    return -1;
	}

	// Wait until child process exits.
	WaitForSingleObject( pi.hProcess, INFINITE );

	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	return 0;

}