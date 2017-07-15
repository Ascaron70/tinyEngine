#pragma once

#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include<iostream>
using namespace std;

#define Log(msg) cout << msg << endl;
#define LogSet(msg) cout << msg << " [ SET ]\n" << endl;
#define LogStart(msg) cout << msg << " [ START ]\n" << endl;
#define LogEnd(msg) cout << msg << " [ END ]\n" << endl;
#define LogError(msg) cout << "[ ERROR ]" << msg << emdl << endl;

#define Check(x, msg, err) if(x) { Log(msg << endl); } else { Log("Error - " <<  err << endl); }
#define Compare(x, y, msg, err) if(x == y) { Log(msg); } else { Log("Error - " <<  err); }
#define CompareToNULL(x, msg, err, ter) if(x == nullptr) { Log("Error - " << err); ter; } else { Log(msg); }

static void LogGlfwError(int id, const char* description)
{
	cout << "[ GLFW ERROR ] : " << description << " !!!" << endl << endl;
}