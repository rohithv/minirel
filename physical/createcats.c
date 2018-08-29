

CreateCats()
{
 printf("CreateCats \n ");
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
