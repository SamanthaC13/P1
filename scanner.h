struct charType{
	char character;
	int lineNum;
	int charNum;
};
struct tokenType scanner(char*,int,int);
struct charType getNextChar(char*,int);
int convertToColumn(struct charType);
struct tokenType FADriver(struct charType,char*,int);
