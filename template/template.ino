#include <Keyboard.h>

bool complete = false;

void setup() {
  Keyboard.begin();
  sleep(500); /* needed because the keyboard takes some time to initialize */
}

void loop() {
	if(complete)
		return;

	/* exit */

	complete = true;
}

void enter(){
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
}

void write(char input[]) {
	for(int n = 0; n < strlen(input); n++){
		if (input[n] == '\n') {
			Keyboard.press(KEY_RETURN);
			Keyboard.release(KEY_RETURN);
		} else
			Keyboard.write(input[n]);
	}
}

void writeEnter(char input[]) {
	write(input);
	enter();
}

void executescript(char script) {

	/* open a command prompt */

    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_GUI); 
    Keyboard.press('r');
    Keyboard.releaseAll();
    write("cmd");
    delay(100);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500);

    /* open notepad */

    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_UP_ARROW);
    Keyboard.releaseAll();
    writeEnter("del q.bat");
    writeEnter("notepad q.bat");
    delay(500);
    enter();

	write(script);

    /* ctrl + s, alt + f4 */

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('s');
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F4);
    Keyboard.releaseAll();

    /* run it */

    delay(500);
    writeEnter("q.bat");
}
