struct tokenType{
	int tokenID;
	int lineCount;
	int charCount;
	char* tokenInstance;
};
enum tokenID{IDTK,NUMTK,WSTK,KEYWRDTK,EOLTK,EOFTK};
