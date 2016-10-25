#include <iostream>


// Because the SendInput function is only supported in
// Windows 2000 and later, WINVER needs to be set as
// follows so that SendInput gets defined when windows.h
// is included below.
#define WINVER 0x0500
#include <windows.h>
#include <map>

using namespace std;
void printHelp();
void printSpecials();
std::map<std::string, int> getSpecialsMap();

bool argcheck(const char* arg, const char* long_param, const char* short_param) {
	if(strcmp(arg, short_param ) == 0 || strcmp(arg, long_param ) == 0)
		return true;
	else return false;
}

int main(int argc, char** argv)
{


	if(argc == 1) {
		printHelp();
		return 0;
	}

	int millis = 0;
	WORD key = 0x00;
	std::map<std::string, int> specialMap = getSpecialsMap();

	for(int i = 1; i < argc; i++)
	{
		if(argcheck(argv[i], "time", "t"))
			millis = atoi(argv[++i]);

		else if(argcheck(argv[i], "char", "c"))
		{
			i++;
			if(argv[i][1] != '\0') {
				cout << "Error in parameter: 'char \t    [C]  \t -  c [C]': C must be a single character";
				return 1;
			}
			key = argv[i][0];
		}

		else if(argcheck(argv[i], "ascii", "a"))
			key = atoi(argv[++i]);

		else if(argcheck(argv[i], "hex", "h"))
			key = strtol(argv[++i], NULL, 16);

		else if(argcheck(argv[i], "win-code", "w"))
			key = specialMap[std::string(argv[++i])];


		else if(argcheck(argv[i], "list-specials", "ls")) {
			printSpecials();
			return 0;
		}
		else{
			printHelp();

			cout << "Unknown parameter: " << argv[i] << endl;
		}


	}

	// This structure will be used to create the keyboard
	// input event.
	INPUT ip;

	// Pause for 5 seconds.
	Sleep(millis);

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press the "A" key
	ip.ki.wVk = key; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "A" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	// Exit normally
	return 0;
}


void printHelp() {
	cout << "Usage: keypress [OPTIONS]" << endl << endl;

	cout << "Options:" << endl;
	cout << "time       [MILLIS] -  t [MILLIS]  - Specify a sleep time in milliseconds before the key pressing"<< endl;
	cout << "hex        [HEX]    -  h [HEX]     - HEX will be processed as a hex number and converted following the special table"<< endl;
	cout << "win-code   [STRING] -  w [STRING]  - STRING will be processed as a string and converted following the special table"<< endl;
//	cout << "char       [C]      -  c [C]       - NOT WORKING - C will be processed as a normal character"<< endl;
//	cout << "ascii      [INT]    -  a [INT]     - NOT WORKING - INT will be processed as a number and converted to a key with the ASCII table"<< endl;
	cout << "list-specials       -  ls          - Show the list of special characters"<< endl<< endl;

	cout << "KEYs:" << endl;
	cout << " - Normal character (ascii - no unicode support)" << endl;
	cout << " - Character ascii code (if option [ascii] is specified)" << endl;
	cout << " - Special windows character from the list (use 'keypress ls' to show the list)" << endl;
}

// For special keys I used this regexp (with sublime text3) in this web page:
// https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
// ([a-zA-Z0-9 _-]+)\n0x([a-zA-Z0-9 _-]+)\n([a-zA-Z0-9 -_;:`~'{}()\d]+)

void printSpecials() {

	cout << "\n\n\nSPECIAL KEYS:\n";
	cout << " CODE          HEX     ACTION\n"
			"\n"
			"VK_LBUTTON     01      Left mouse button\n"
			"VK_RBUTTON     02      Right mouse button\n"
			"VK_CANCEL      03      Control-break processing\n"
			"VK_MBUTTON     04      Middle mouse button (three-button mouse)\n"
			"VK_XBUTTON1    05      X1 mouse button\n"
			"VK_XBUTTON2    06      X2 mouse button\n"
			"   -           07      Undefined\n"
			"VK_BACK        08      BACKSPACE key\n"
			"VK_TAB         09      TAB key\n"
			"   -           0A-0B   Reserved\n"
			"VK_CLEAR       0C      CLEAR key\n"
			"VK_RETURN      0D      ENTER key\n"
			"   -           0E-0F   Undefined\n"
			"VK_SHIFT       10      SHIFT key\n"
			"VK_CONTROL     11      CTRL key\n"
			"VK_MENU        12      ALT key\n"
			"VK_PAUSE       13      PAUSE key\n"
			"VK_CAPITAL     14      CAPS LOCK key\n"
			"VK_KANA        15      IME Kana mode\n"
			"VK_HANGUEL     15      IME Hanguel mode (maintained for compatibility; use VK_HANGUL)\n"
			"VK_HANGUL      15      IME Hangul mode\n"
			"   -           16      Undefined\n"
			"VK_JUNJA       17      IME Junja mode\n"
			"VK_FINAL       18      IME final mode\n"
			"VK_HANJA       19      IME Hanja mode\n"
			"VK_KANJI       19      IME Kanji mode\n"
			"   -           1A      Undefined\n"
			"VK_ESCAPE      1B      ESC key\n"
			"VK_CONVERT     1C      IME convert\n"
			"VK_NONCONVERT  1D      IME nonconvert\n"
			"VK_ACCEPT      1E      IME accept\n"
			"VK_MODECHANGE  1F      IME mode change request\n"
			"VK_SPACE       20      SPACEBAR\n"
			"VK_PRIOR       21      PAGE UP key\n"
			"VK_NEXT        22      PAGE DOWN key\n"
			"VK_END         23      END key\n"
			"VK_HOME        24      HOME key\n"
			"VK_LEFT        25      LEFT ARROW key\n"
			"VK_UP          26      UP ARROW key\n"
			"VK_RIGHT       27      RIGHT ARROW key\n"
			"VK_DOWN        28      DOWN ARROW key\n"
			"VK_SELECT      29      SELECT key\n"
			"VK_PRINT       2A      PRINT key\n"
			"VK_EXECUTE     2B      EXECUTE key\n"
			"VK_SNAPSHOT    2C      PRINT SCREEN key\n"
			"VK_INSERT      2D      INS key\n"
			"VK_DELETE      2E      DEL key\n"
			"VK_HELP        2F      HELP key\n"
			"\n"
			"\n"
			"   -           0x30        0 key\n"
			"   -           0x31        1 key\n"
			"   -           0x32        2 key\n"
			"   -           0x33        3 key\n"
			"   -           0x34        4 key\n"
			"   -           0x35        5 key\n"
			"   -           0x36        6 key\n"
			"   -           0x37        7 key\n"
			"   -           0x38        8 key\n"
			"   -           0x39        9 key\n"
			"   -           0x3A-40     Undefined\n"
			"   -           0x41        A key\n"
			"   -           0x42        B key\n"
			"   -           0x43        C key\n"
			"   -           0x44        D key\n"
			"   -           0x45        E key\n"
			"   -           0x46        F key\n"
			"   -           0x47        G key\n"
			"   -           0x48        H key\n"
			"   -           0x49        I key\n"
			"   -           0x4A        J key\n"
			"   -           0x4B        K key\n"
			"   -           0x4C        L key\n"
			"   -           0x4D        M key\n"
			"   -           0x4E        N key\n"
			"   -           0x4F        O key\n"
			"   -           0x50        P key\n"
			"   -           0x51        Q key\n"
			"   -           0x52        R key\n"
			"   -           0x53        S key\n"
			"   -           0x54        T key\n"
			"   -           0x55        U key\n"
			"   -           0x56        V key\n"
			"   -           0x57        W key\n"
			"   -           0x58        X key\n"
			"   -           0x59        Y key\n"
			"   -           0x5A        Z key\n"
			"\n"
			"VK_LWIN        5B      Left Windows key (Natural keyboard)\n"
			"VK_RWIN        5C      Right Windows key (Natural keyboard)\n"
			"VK_APPS        5D      Applications key (Natural keyboard)\n"
			"-              5E      Reserved\n"
			"VK_SLEEP       5F      Computer Sleep key\n"
			"VK_NUMPAD0     60      Numeric keypad 0 key\n"
			"VK_NUMPAD1     61      Numeric keypad 1 key\n"
			"VK_NUMPAD2     62      Numeric keypad 2 key\n"
			"VK_NUMPAD3     63      Numeric keypad 3 key\n"
			"VK_NUMPAD4     64      Numeric keypad 4 key\n"
			"VK_NUMPAD5     65      Numeric keypad 5 key\n"
			"VK_NUMPAD6     66      Numeric keypad 6 key\n"
			"VK_NUMPAD7     67      Numeric keypad 7 key\n"
			"VK_NUMPAD8     68      Numeric keypad 8 key\n"
			"VK_NUMPAD9     69      Numeric keypad 9 key\n"
			"VK_MULTIPLY    6A      Multiply key\n"
			"VK_ADD         6B      Add key\n"
			"VK_SEPARATOR   6C      Separator key\n"
			"VK_SUBTRACT    6D      Subtract key\n"
			"VK_DECIMAL     6E      Decimal key\n"
			"VK_DIVIDE      6F      Divide key\n"
			"VK_F1          70      F1 key\n"
			"VK_F2          71      F2 key\n"
			"VK_F3          72      F3 key\n"
			"VK_F4          73      F4 key\n"
			"VK_F5          74      F5 key\n"
			"VK_F6          75      F6 key\n"
			"VK_F7          76      F7 key\n"
			"VK_F8          77      F8 key\n"
			"VK_F9          78      F9 key\n"
			"VK_F10         79      F10 key\n"
			"VK_F11         7A      F11 key\n"
			"VK_F12         7B      F12 key\n"
			"VK_F13         7C      F13 key\n"
			"VK_F14         7D      F14 key\n"
			"VK_F15         7E      F15 key\n"
			"VK_F16         7F      F16 key\n"
			"VK_F17         80      F17 key\n"
			"VK_F18         81      F18 key\n"
			"VK_F19         82      F19 key\n"
			"VK_F20         83      F20 key\n"
			"VK_F21         84      F21 key\n"
			"VK_F22         85      F22 key\n"
			"VK_F23         86      F23 key\n"
			"VK_F24         87      F24 key\n"
			"   -           88-8F   Unassigned\n"
			"VK_NUMLOCK     90      NUM LOCK key\n"
			"VK_SCROLL      91      SCROLL LOCK key\n"
			"   -           92-96\n"
			"OEM specific\n"
			"   -           97-9F   Unassigned\n"
			"VK_LSHIFT      A0      Left SHIFT key\n"
			"VK_RSHIFT      A1      Right SHIFT key\n"
			"VK_LCONTROL    A2      Left CONTROL key\n"
			"VK_RCONTROL    A3      Right CONTROL key\n"
			"VK_LMENU       A4      Left MENU key\n"
			"VK_RMENU       A5      Right MENU key\n"
			"VK_BROWSER_BACK        A6      Browser Back key\n"
			"VK_BROWSER_FORWARD     A7      Browser Forward key\n"
			"VK_BROWSER_REFRESH     A8      Browser Refresh key\n"
			"VK_BROWSER_STOP        A9      Browser Stop key\n"
			"VK_BROWSER_SEARCH      AA      Browser Search key\n"
			"VK_BROWSER_FAVORITES   AB      Browser Favorites key\n"
			"VK_BROWSER_HOME        AC      Browser Start and Home key\n"
			"VK_VOLUME_MUTE         AD      Volume Mute key\n"
			"VK_VOLUME_DOWN         AE      Volume Down key\n"
			"VK_VOLUME_UP           AF      Volume Up key\n"
			"VK_MEDIA_NEXT_TRACK    B0      Next Track key\n"
			"VK_MEDIA_PREV_TRACK    B1      Previous Track key\n"
			"VK_MEDIA_STOP          B2      Stop Media key\n"
			"VK_MEDIA_PLAY_PAUSE    B3      Play/Pause Media key\n"
			"VK_LAUNCH_MAIL         B4      Start Mail key\n"
			"VK_LAUNCH_MEDIA_SELECT B5      Select Media key\n"
			"VK_LAUNCH_APP1         B6      Start Application 1 key\n"
			"VK_LAUNCH_APP2         B7      Start Application 2 key\n"
			"\n"
			"   -           B8-B9   Reserved\n"
			"VK_OEM_1       BA      Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ';:' key\n"
			"VK_OEM_PLUS    BB      For any country/region, the '+' key\n"
			"VK_OEM_COMMA   BC      For any country/region, the ',' key\n"
			"VK_OEM_MINUS   BD      For any country/region, the '-' key\n"
			"VK_OEM_PERIOD  BE      For any country/region, the '.' key\n"
			"VK_OEM_2       BF      Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '/?' key\n"
			"VK_OEM_3       C0      Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '`~' key\n"
			"   -           C1-D7       Reserved\n"
			"   -           D8-DA       Unassigned\n"
			"VK_OEM_4       DB      Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '[{' key\n"
			"VK_OEM_5       DC      Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '\\|' key\n"
			"VK_OEM_6       DD      Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ']}' key\n"
			"VK_OEM_7       DE      Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the 'single-quote/double-quote' key\n"
			"VK_OEM_8       DF      Used for miscellaneous characters; it can vary by keyboard.\n"
			"   -           E0      Reserved\n"
			"   -           E1      OEM specific\n"
			"VK_OEM_102     E2      Either the angle bracket key or the backslash key on the RT 102-key keyboard\n"
			"   -           E3-E4   OEM specific\n"
			"VK_PROCESSKEY  E5      IME PROCESS key\n"
			"   -           E6      OEM specific\n"
			"VK_PACKET      E7      Used to pass Unicode characters as if they were keystrokes. The VK_PACKET key is the low word of a 32-bit Virtual Key value sed for non-keyboard input methods. For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP\n"
			"   -           E8      Unassigned\n"
			"   -           0xE9-F5 OEM specific\n"
			"VK_ATTN        F6      Attn key\n"
			"VK_CRSEL       F7      CrSel key\n"
			"VK_EXSEL       F8      ExSel key\n"
			"VK_EREOF       F9      Erase EOF key\n"
			"VK_PLAY        FA      Play key\n"
			"VK_ZOOM        FB      Zoom key\n"
			"VK_NONAME      FC      Reserved\n"
			"VK_PA1         FD      PA1 key\n"
			"VK_OEM_CLEAR   FE      Clear key\n\n\n";

}


std::map<std::string, int> getSpecialsMap(){
	std::map<std::string, int> specialMap = {
			{"VK_LBUTTON", 0x01},
			{"VK_RBUTTON", 0x02},
			{"VK_CANCEL", 0x03},
			{"VK_MBUTTON", 0x04},
			{"VK_XBUTTON1", 0x05},
			{"VK_XBUTTON2", 0x06},
			{"VK_BACK", 0x08},
			{"VK_TAB", 0x09},
			{"VK_CLEAR", 0x0C},
			{"VK_RETURN", 0x0D},
			{"VK_SHIFT", 0x10},
			{"VK_CONTROL", 0x11},
			{"VK_MENU", 0x12},
			{"VK_PAUSE", 0x13},
			{"VK_CAPITAL", 0x14},
			{"VK_KANA", 0x15},
			{"VK_HANGUEL", 0x15},
			{"VK_HANGUL", 0x15},
			{"VK_JUNJA", 0x17},
			{"VK_FINAL", 0x18},
			{"VK_HANJA", 0x19},
			{"VK_KANJI", 0x19},
			{"VK_ESCAPE", 0x1B},
			{"VK_CONVERT", 0x1C},
			{"VK_NONCONVERT", 0x1D},
			{"VK_ACCEPT", 0x1E},
			{"VK_MODECHANGE", 0x1F},
			{"VK_SPACE", 0x20},
			{"VK_PRIOR", 0x21},
			{"VK_NEXT", 0x22},
			{"VK_END", 0x23},
			{"VK_HOME", 0x24},
			{"VK_LEFT", 0x25},
			{"VK_UP", 0x26},
			{"VK_RIGHT", 0x27},
			{"VK_DOWN", 0x28},
			{"VK_SELECT", 0x29},
			{"VK_PRINT", 0x2A},
			{"VK_EXECUTE", 0x2B},
			{"VK_SNAPSHOT", 0x2C},
			{"VK_INSERT", 0x2D},
			{"VK_DELETE", 0x2E},
			{"VK_HELP", 0x2F},
			{"VK_LWIN", 0x5B},
			{"VK_RWIN", 0x5C},
			{"VK_APPS", 0x5D},
			{"VK_SLEEP", 0x5F},
			{"VK_NUMPAD0", 0x60},
			{"VK_NUMPAD1", 0x61},
			{"VK_NUMPAD2", 0x62},
			{"VK_NUMPAD3", 0x63},
			{"VK_NUMPAD4", 0x64},
			{"VK_NUMPAD5", 0x65},
			{"VK_NUMPAD6", 0x66},
			{"VK_NUMPAD7", 0x67},
			{"VK_NUMPAD8", 0x68},
			{"VK_NUMPAD9", 0x69},
			{"VK_MULTIPLY", 0x6A},
			{"VK_ADD", 0x6B},
			{"VK_SEPARATOR", 0x6C},
			{"VK_SUBTRACT", 0x6D},
			{"VK_DECIMAL", 0x6E},
			{"VK_DIVIDE", 0x6F},
			{"VK_F1", 0x70},
			{"VK_F2", 0x71},
			{"VK_F3", 0x72},
			{"VK_F4", 0x73},
			{"VK_F5", 0x74},
			{"VK_F6", 0x75},
			{"VK_F7", 0x76},
			{"VK_F8", 0x77},
			{"VK_F9", 0x78},
			{"VK_F10", 0x79},
			{"VK_F11", 0x7A},
			{"VK_F12", 0x7B},
			{"VK_F13", 0x7C},
			{"VK_F14", 0x7D},
			{"VK_F15", 0x7E},
			{"VK_F16", 0x7F},
			{"VK_F17", 0x80},
			{"VK_F18", 0x81},
			{"VK_F19", 0x82},
			{"VK_F20", 0x83},
			{"VK_F21", 0x84},
			{"VK_F22", 0x85},
			{"VK_F23", 0x86},
			{"VK_F24", 0x87},
			{"VK_NUMLOCK", 0x90},
			{"VK_SCROLL", 0x91},
			{"VK_LSHIFT", 0xA0},
			{"VK_RSHIFT", 0xA1},
			{"VK_LCONTROL", 0xA2},
			{"VK_RCONTROL", 0xA3},
			{"VK_LMENU", 0xA4},
			{"VK_RMENU", 0xA5},
			{"VK_BROWSER_BACK", 0xA6},
			{"VK_BROWSER_FORWARD", 0xA7},
			{"VK_BROWSER_REFRESH", 0xA8},
			{"VK_BROWSER_STOP", 0xA9},
			{"VK_BROWSER_SEARCH", 0xAA},
			{"VK_BROWSER_FAVORITES", 0xAB},
			{"VK_BROWSER_HOME", 0xAC},
			{"VK_VOLUME_MUTE", 0xAD},
			{"VK_VOLUME_DOWN", 0xAE},
			{"VK_VOLUME_UP", 0xAF},
			{"VK_MEDIA_NEXT_TRACK", 0xB0},
			{"VK_MEDIA_PREV_TRACK", 0xB1},
			{"VK_MEDIA_STOP", 0xB2},
			{"VK_MEDIA_PLAY_PAUSE", 0xB3},
			{"VK_LAUNCH_MAIL", 0xB4},
			{"VK_LAUNCH_MEDIA_SELECT", 0xB5},
			{"VK_LAUNCH_APP1", 0xB6},
			{"VK_LAUNCH_APP2", 0xB7},
			{"VK_OEM_1", 0xBA},
			{"VK_OEM_PLUS", 0xBB},
			{"VK_OEM_COMMA", 0xBC},
			{"VK_OEM_MINUS", 0xBD},
			{"VK_OEM_PERIOD", 0xBE},
			{"VK_OEM_2", 0xBF},
			{"VK_OEM_3", 0xC0},
			{"VK_OEM_4", 0xDB},
			{"VK_OEM_5", 0xDC},
			{"VK_OEM_6", 0xDD},
			{"VK_OEM_7", 0xDE},
			{"VK_OEM_8", 0xDF},
			{"VK_OEM_102", 0xE2},
			{"VK_PROCESSKEY", 0xE5},
			{"VK_PACKET", 0xE7},
			{"VK_ATTN", 0xF6},
			{"VK_CRSEL", 0xF7},
			{"VK_EXSEL", 0xF8},
			{"VK_EREOF", 0xF9},
			{"VK_PLAY", 0xFA},
			{"VK_ZOOM", 0xFB},
			{"VK_NONAME", 0xFC},
			{"VK_PA1", 0xFD},
			{"VK_OEM_CLEAR", 0xFE}
	};
	return specialMap;
};
/*
 * CODE			HEX		ACTION

VK_LBUTTON		01		Left mouse button
VK_RBUTTON		02		Right mouse button
VK_CANCEL		03		Control-break processing
VK_MBUTTON		04		Middle mouse button (three-button mouse)
VK_XBUTTON1		05		X1 mouse button
VK_XBUTTON2		06		X2 mouse button
	-			07		Undefined
VK_BACK			08		BACKSPACE key
VK_TAB			09		TAB key
	-			0A-0B	Reserved
VK_CLEAR		0C		CLEAR key
VK_RETURN		0D		ENTER key
	-			0E-0F	Undefined
VK_SHIFT		10		SHIFT key
VK_CONTROL		11		CTRL key
VK_MENU			12		ALT key
VK_PAUSE		13		PAUSE key
VK_CAPITAL		14		CAPS LOCK key
VK_KANA			15		IME Kana mode
VK_HANGUEL		15		IME Hanguel mode (maintained for compatibility; use VK_HANGUL)
VK_HANGUL		15		IME Hangul mode
	-			16		Undefined
VK_JUNJA		17		IME Junja mode
VK_FINAL		18		IME final mode
VK_HANJA		19		IME Hanja mode
VK_KANJI		19		IME Kanji mode
	-			1A		Undefined
VK_ESCAPE		1B		ESC key
VK_CONVERT		1C		IME convert
VK_NONCONVERT	1D		IME nonconvert
VK_ACCEPT		1E		IME accept
VK_MODECHANGE	1F		IME mode change request
VK_SPACE		20		SPACEBAR
VK_PRIOR		21		PAGE UP key
VK_NEXT			22		PAGE DOWN key
VK_END			23		END key
VK_HOME			24		HOME key
VK_LEFT			25		LEFT ARROW key
VK_UP			26		UP ARROW key
VK_RIGHT		27		RIGHT ARROW key
VK_DOWN			28		DOWN ARROW key
VK_SELECT		29		SELECT key
VK_PRINT		2A		PRINT key
VK_EXECUTE		2B		EXECUTE key
VK_SNAPSHOT		2C		PRINT SCREEN key
VK_INSERT		2D		INS key
VK_DELETE		2E		DEL key
VK_HELP			2F		HELP key


	-			0x30		0 key
	-			0x31		1 key
	-			0x32		2 key
	-			0x33		3 key
	-			0x34		4 key
	-			0x35		5 key
	-			0x36		6 key
	-			0x37		7 key
	-			0x38		8 key
	-			0x39		9 key
	-			0x3A-40		Undefined
	-			0x41		A key
	-			0x42		B key
	-			0x43		C key
	-			0x44		D key
	-			0x45		E key
	-			0x46		F key
	-			0x47		G key
	-			0x48		H key
	-			0x49		I key
	-			0x4A		J key
	-			0x4B		K key
	-			0x4C		L key
	-			0x4D		M key
	-			0x4E		N key
	-			0x4F		O key
	-			0x50		P key
	-			0x51		Q key
	-			0x52		R key
	-			0x53		S key
	-			0x54		T key
	-			0x55		U key
	-			0x56		V key
	-			0x57		W key
	-			0x58		X key
	-			0x59		Y key
	-			0x5A		Z key

VK_LWIN			5B		Left Windows key (Natural keyboard)
VK_RWIN			5C		Right Windows key (Natural keyboard)
VK_APPS			5D		Applications key (Natural keyboard)
-				5E		Reserved
VK_SLEEP		5F		Computer Sleep key
VK_NUMPAD0		60		Numeric keypad 0 key
VK_NUMPAD1		61		Numeric keypad 1 key
VK_NUMPAD2		62		Numeric keypad 2 key
VK_NUMPAD3		63		Numeric keypad 3 key
VK_NUMPAD4		64		Numeric keypad 4 key
VK_NUMPAD5		65		Numeric keypad 5 key
VK_NUMPAD6		66		Numeric keypad 6 key
VK_NUMPAD7		67		Numeric keypad 7 key
VK_NUMPAD8		68		Numeric keypad 8 key
VK_NUMPAD9		69		Numeric keypad 9 key
VK_MULTIPLY		6A		Multiply key
VK_ADD			6B		Add key
VK_SEPARATOR	6C		Separator key
VK_SUBTRACT		6D		Subtract key
VK_DECIMAL		6E		Decimal key
VK_DIVIDE		6F		Divide key
VK_F1			70		F1 key
VK_F2			71		F2 key
VK_F3			72		F3 key
VK_F4			73		F4 key
VK_F5			74		F5 key
VK_F6			75		F6 key
VK_F7			76		F7 key
VK_F8			77		F8 key
VK_F9			78		F9 key
VK_F10			79		F10 key
VK_F11			7A		F11 key
VK_F12			7B		F12 key
VK_F13			7C		F13 key
VK_F14			7D		F14 key
VK_F15			7E		F15 key
VK_F16			7F		F16 key
VK_F17			80		F17 key
VK_F18			81		F18 key
VK_F19			82		F19 key
VK_F20			83		F20 key
VK_F21			84		F21 key
VK_F22			85		F22 key
VK_F23			86		F23 key
VK_F24			87		F24 key
	-			88-8F	Unassigned
VK_NUMLOCK		90		NUM LOCK key
VK_SCROLL		91		SCROLL LOCK key
	-			92-96
OEM specific
	-			97-9F		Unassigned
VK_LSHIFT		A0		Left SHIFT key
VK_RSHIFT		A1		Right SHIFT key
VK_LCONTROL		A2		Left CONTROL key
VK_RCONTROL		A3		Right CONTROL key
VK_LMENU		A4		Left MENU key
VK_RMENU		A5		Right MENU key
VK_BROWSER_BACK			A6		Browser Back key
VK_BROWSER_FORWARD		A7		Browser Forward key
VK_BROWSER_REFRESH		A8		Browser Refresh key
VK_BROWSER_STOP			A9		Browser Stop key
VK_BROWSER_SEARCH		AA		Browser Search key
VK_BROWSER_FAVORITES	AB		Browser Favorites key
VK_BROWSER_HOME			AC		Browser Start and Home key
VK_VOLUME_MUTE			AD		Volume Mute key
VK_VOLUME_DOWN			AE		Volume Down key
VK_VOLUME_UP			AF		Volume Up key
VK_MEDIA_NEXT_TRACK		B0		Next Track key
VK_MEDIA_PREV_TRACK		B1		Previous Track key
VK_MEDIA_STOP			B2		Stop Media key
VK_MEDIA_PLAY_PAUSE		B3		Play/Pause Media key
VK_LAUNCH_MAIL			B4		Start Mail key
VK_LAUNCH_MEDIA_SELECT	B5		Select Media key
VK_LAUNCH_APP1			B6		Start Application 1 key
VK_LAUNCH_APP2			B7		Start Application 2 key

	-			B8-B9		Reserved
VK_OEM_1		BA		Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ';:' key
VK_OEM_PLUS		BB		For any country/region, the '+' key
VK_OEM_COMMA	BC		For any country/region, the ',' key
VK_OEM_MINUS	BD		For any country/region, the '-' key
VK_OEM_PERIOD	BE		For any country/region, the '.' key
VK_OEM_2		BF		Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '/?' key
VK_OEM_3		C0		Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '`~' key
	-			C1-D7		Reserved
	-			D8-DA		Unassigned
VK_OEM_4		DB		Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '[{' key
VK_OEM_5		DC		Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '\|' key
VK_OEM_6		DD		Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ']}' key
VK_OEM_7		DE		Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the 'single-quote/double-quote' key
VK_OEM_8		DF		Used for miscellaneous characters; it can vary by keyboard.
	-			E0		Reserved
	-			E1		OEM specific
VK_OEM_102		E2		Either the angle bracket key or the backslash key on the RT 102-key keyboard
	-			E3-E4		OEM specific
VK_PROCESSKEY	E5		IME PROCESS key
	-			E6		OEM specific
VK_PACKET		E7		Used to pass Unicode characters as if they were keystrokes. The VK_PACKET key is the low word of a 32-bit Virtual Key value sed for non-keyboard input methods. For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP
	-			E8		Unassigned
	-			0xE9-F5	OEM specific
VK_ATTN			F6		Attn key
VK_CRSEL		F7		CrSel key
VK_EXSEL		F8		ExSel key
VK_EREOF		F9		Erase EOF key
VK_PLAY			FA		Play key
VK_ZOOM			FB		Zoom key
VK_NONAME		FC		Reserved
VK_PA1			FD		PA1 key
VK_OEM_CLEAR	FE		Clear key
 */