struct tokenType{
	int tokenID;
	int lineCount;
	int charCount;
	char* tokenInstance;
};
enum tokenID{IDTK,NUMTK,WSTK,KEYWRDTK,EOLTK,GTTK,LTTK,EQTK,DBEQTK,CLNTK,CLNEQTK,PSTK,MINTK,ASKTK,SLTK,PCTTK,PERTK,EOFTK};
