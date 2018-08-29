    /* 
	This is the basic definition file.
    */
/*************************************************************
		CONSTANTS
*************************************************************/
#define PAGESIZE	512	/* number of bytes in a page */
#define	MAXRECORD	508	/* PAGESIZE minus number of bytes taken up
                                   for slot map */

#define RELNAME		20	/* max length of a relation name */
#define MAXOPEN		20  	/* max number of files that can be open
                                   at the same time */

#define	OK		0	/* return codes */
#define NOTOK		-1

#define RELCAT		"relcat"   /* name of the relation catalog file */
#define ATTRCAT		"attrcat"  /* name of the attribute catalog file */

#define SLOTMAPSIZE 4
#define RECORDSIZE 120

/*************************************************************
		TYPE DEFINITIONS 
*************************************************************/

/* Rid structure */
typedef struct recid {
	short	pid;
	short	slotnum;
} Rid;


/* Page Structure */
typedef struct ps {
	unsigned slotmap;
	char contents [MAXRECORD];
	} Page;


typedef struct AttrCat{
	unsigned offset;
	unsigned length;
	char type[15];
	char attrName[15];
	char relName[15];
} Attrcat;

typedef struct RelCat{
	char relName[15];
	unsigned recLength;
	unsigned recsPerPg;
	unsigned numAttrs;
	unsigned numRecs;
	unsigned numPgs;
	Rid relcatRid;
	FILE *relFile;
	bool modified;
	bool occupied;
	Attrcat *attrList;
} RelCat;

typedef struct Buffer{
	Page page;
	short pid;
	bool modified;
}Buffer;
/*****************************************************************/
