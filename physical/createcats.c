#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include "../include/defs.h"
#include "utils.c"

int CreateCats()
{
 return ((CreateRelCats()==OK && CreateAttrCats()==OK) ? OK : NOTOK); //Return OK if both are OK.
}



/* RELATION CATALOG
_________________________________________________________________
|relName  |recLength  |recsPerPg |numAttrs  |numRecs  |numPgs  |
-----------------------------------------------------------------
|  relcat |    90     |    4     |    6     |   2     |  1     |
|  attrcat|    75     |    4     |    5     |   11    |  3     |
-----------------------------------------------------------------
Initial values for Relation Catalog are as above.
*/

int CreateRelCats()
{
	//Check if catalog already exists.
	if (access(RELCAT, F_OK) != -1)
	{
		//Error message to be printed here
		return NOTOK;
	}

	FILE *relcat= fopen(RELCAT, wb);

	char page[PAGESIZE]= { 0 }; //buffer initialized
	int slotmap;
	
	/*
	 * Slotmap is in binary.
	 * First two slots are occupied -> 1100.. followed by 28 0s (since 32 bits is given)
	 * Slotmap converted to hex is 0xC0000000
	 */
	slotmap = 0xC0000000;

	//copy slotmap to buffer
	CopyIntInBinary(page, slotmap);

	//First entry = relcat
	strncpy(page+SLOTMAPSIZE, "relcat", 6);
	CopyIntInBinary(page+SLOTMAPSIZE+15, 90);
	CopyIntInBinary(page+SLOTMAPSIZE+30, 4);
	CopyIntInBinary(page+SLOTMAPSIZE+45, 6);
	CopyIntInBinary(page+SLOTMAPSIZE+60, 2);
	CopyIntInBinary(page+SLOTMAPSIZE+75, 1);

	//Second Entry = Attrcat
	strncpy(page+SLOTMAPSIZE+RECORDSIZE, "attrcat", 6);
	CopyIntInBinary(page+SLOTMAPSIZE+RECORDSIZE+15, 75);
	CopyIntInBinary(page+SLOTMAPSIZE+RECORDSIZE+30, 4);
	CopyIntInBinary(page+SLOTMAPSIZE+RECORDSIZE+45, 5);
	CopyIntInBinary(page+SLOTMAPSIZE+RECORDSIZE+60, 11);
	CopyIntInBinary(page+SLOTMAPSIZE+RECORDSIZE+75, 3);

	write(relcat, page, PAGESIZE);
	fclose(relcat);
	return OK;

}


/* ATTRIBUTE CATALOG
__________________________________________________
|relName  | attrName  | type  | length  | offset |
--------------------------------------------------
| relcat  | relName   |   s   |   15    |   0    |
| relcat  | recLength |   i   |   15    |   15   |
| relcat  | recsPerPg |   i   |   15    |   30   |
| relcat  | numAttrs  |   i   |   15    |   45   |
| relcat  | numRecs   |   i   |   15    |   60   |
| relcat  | numPgs    |   i   |   15    |   75   |
| attrcat | relName   |   s   |   15    |   0    |
| attrcat | attrName  |   s   |   15    |   15   |
| attrcat | type      |   s   |   15    |   30   |
| attrcat | length    |   i   |   15    |   45   |
| attrcat | offset    |   i   |   15    |   60   |
--------------------------------------------------

Initial VAlues for Attribute Catalog.

*/

int CreateAttrCats()
{
	//Check if catalog already exists.
	if (access(ATTRCAT, F_OK) != -1)
	{
		//Error message to be printed here
		return NOTOK;
	}
	
	FILE *attrcat = fopen(ATTRCAT,wb);
	
	char page[PAGESIZE] = { 0 };	//buffer intialized
	int slotmap;

	/*
	 * Slotmap is in binary.
	 * First two slots are occupied -> 1111.. followed by 28 0s (since 32 bits is given)
	 * Slotmap converted to hex is 0xf0000000
	 */
	slotmap = 0xf0000000;

	//copy slotmap to buffer
	CopyIntInBinary(page, slotmap);

	//First entry = relname
	strncpy(page+SLOTMAPSIZE, "relcat", 6);
	strncpy(page+SLOTMAPSIZE+15, "relName", 7);
	strncpy(page+SLOTMAPSIZE+30, "s", 1); 
	CopyIntInBinary(page+SLOTMAPSIZE+45, 15);
	CopyIntInBinary(page+SLOTMAPSIZE+60, 0);

	//Second Entry = recLength
	strncpy(page+SLOTMAPSIZE+RECORDSIZE, "relcat", 6);
	strncpy(page+SLOTMAPSIZE+RECORDSIZE+15, "recLength", 9);
	strncpy(page+SLOTMAPSIZE+RECORDSIZE+30, "i", 1); 
	CopyIntInBinary(page+SLOTMAPSIZE+RECORDSIZE+45, 15);
	CopyIntInBinary(page+SLOTMAPSIZE+RECORDSIZE+60, 15);

	//Third Entry = recsPerPg
	strncpy(page+SLOTMAPSIZE+2*RECORDSIZE, "relcat", 6);
	strncpy(page+SLOTMAPSIZE+2*RECORDSIZE+15, "recsPerPg", 9);
	strncpy(page+SLOTMAPSIZE+2*RECORDSIZE+30, "i", 1); 
	CopyIntInBinary(page+SLOTMAPSIZE+2*RECORDSIZE+45, 15);
	CopyIntInBinary(page+SLOTMAPSIZE+2*RECORDSIZE+60, 30);

	//Fourth Entry = numAttrs
	strncpy(page+SLOTMAPSIZE+3*RECORDSIZE, "relcat", 6);
	strncpy(page+SLOTMAPSIZE+3*RECORDSIZE+15, "numAttrs", 8);
	strncpy(page+SLOTMAPSIZE+3*RECORDSIZE+30, "i", 1); 
	CopyIntInBinary(page+SLOTMAPSIZE+3*RECORDSIZE+45, 15);
	CopyIntInBinary(page+SLOTMAPSIZE+3*RECORDSIZE+60, 45);

	write(attrcat, page, PAGESIZE);  //first page in attribute catalog
	
	//page[PAGESIZE] = { 0 };
	memset(page,0,sizeof(page));

	slotmap = 0xf0000000;   //(11110...............)

	//copy slotmap to buffer
	CopyIntInBinary(page, slotmap);

	//First entry = numRecs
	strncpy(page+SLOTMAPSIZE, "relcat", 6);
	strncpy(page+SLOTMAPSIZE+15, "numRecs", 7);
	strncpy(page+SLOTMAPSIZE+30, "s", 1); 
	CopyIntInBinary(page+SLOTMAPSIZE+45, 15);
	CopyIntInBinary(page+SLOTMAPSIZE+60, 60);

	//Second Entry = numPgs
	strncpy(page+SLOTMAPSIZE+RECORDSIZE, "relcat", 6);
	strncpy(page+SLOTMAPSIZE+RECORDSIZE+15, "numPgs", 6);
	strncpy(page+SLOTMAPSIZE+RECORDSIZE+30, "i", 1); 
	CopyIntInBinary(page+SLOTMAPSIZE+RECORDSIZE+45, 15);
	CopyIntInBinary(page+SLOTMAPSIZE+RECORDSIZE+60, 75);

	//Third Entry = relName
	strncpy(page+SLOTMAPSIZE+2*RECORDSIZE, "attrcat", 7);
	strncpy(page+SLOTMAPSIZE+2*RECORDSIZE+15, "relName", 7);
	strncpy(page+SLOTMAPSIZE+2*RECORDSIZE+30, "s", 1); 
	CopyIntInBinary(page+SLOTMAPSIZE+2*RECORDSIZE+45, 15);
	CopyIntInBinary(page+SLOTMAPSIZE+2*RECORDSIZE+60, 0);

	//Fourth Entry = attrName
	strncpy(page+SLOTMAPSIZE+3*RECORDSIZE, "attrcat", 6);
	strncpy(page+SLOTMAPSIZE+3*RECORDSIZE+15, "attrName", 8);
	strncpy(page+SLOTMAPSIZE+3*RECORDSIZE+30, "s", 1); 
	CopyIntInBinary(page+SLOTMAPSIZE+3*RECORDSIZE+45, 15);
	CopyIntInBinary(page+SLOTMAPSIZE+3*RECORDSIZE+60, 15);

	write(attrcat, page, PAGESIZE);  //second page in attribute catalog

	
	memset(page,0,sizeof(page));

	slotmap = 0xe0000000;   //(1110.................)

	//copy slotmap to buffer
	CopyIntInBinary(page, slotmap);

	//First entry = type
	strncpy(page+SLOTMAPSIZE, "attrcat", 6);
	strncpy(page+SLOTMAPSIZE+15, "type", 4);
	strncpy(page+SLOTMAPSIZE+30, "s", 1); 
	CopyIntInBinary(page+SLOTMAPSIZE+45, 15);
	CopyIntInBinary(page+SLOTMAPSIZE+60, 60);

	//Second Entry = length
	strncpy(page+SLOTMAPSIZE+RECORDSIZE, "relcat", 6);
	strncpy(page+SLOTMAPSIZE+RECORDSIZE+15, "length", 6);
	strncpy(page+SLOTMAPSIZE+RECORDSIZE+30, "i", 1); 
	CopyIntInBinary(page+SLOTMAPSIZE+RECORDSIZE+45, 15);
	CopyIntInBinary(page+SLOTMAPSIZE+RECORDSIZE+60, 75);

	//Third Entry = offset
	strncpy(page+SLOTMAPSIZE+2*RECORDSIZE, "relcat", 6);
	strncpy(page+SLOTMAPSIZE+2*RECORDSIZE+15, "offset", 6);
	strncpy(page+SLOTMAPSIZE+2*RECORDSIZE+30, "s", 1); 
	CopyIntInBinary(page+SLOTMAPSIZE+2*RECORDSIZE+45, 15);
	CopyIntInBinary(page+SLOTMAPSIZE+2*RECORDSIZE+60, 0);


	write(attrcat, page, PAGESIZE);  //third page in attribute catalog
	
	fclose(attrcat);
	
}
