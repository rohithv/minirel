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
	CopyIntInBinary(slotmap, page);

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

}
