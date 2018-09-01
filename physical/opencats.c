


/*
 * Place catalog entries in cache
 * Read only the number of records and number of pages from file (after creating entries in cache)
 * That is because FindRec() cant be used without relNum.
 */


int OpenCats()
{
	int i;
	//Check whether both files exist here. else return NOTOK
	if( access(RELCAT, F_OK) == -1 || access(ATTRCAT, F_OK) == -1){
		//Error message to be printed here
		return NOTOK;
	}

	//initializing the control fields
	for(i=0;i<MAXOPEN;i++){
		buffer[i].pid= -1;
		buffer[i].modified= false;
	}

	for(i=2;i<MAXOPEN;i++){
		catcache[i].modified=false;
		catcache[i].occupied=false;
	}

	//Keep the records in catcache as done for createcats() except number of records and number of pages
	//relcat entry relNum=0
	// Use ReadIntFromBinary() for storing integer in catcache[0].numPgs etc. from buffer.

	char page[PAGESIZE] = { 0 };
	
	FILE *relcat= fopen(RELCAT,wb);
	read(relcat,page,PAGESIZE);

	catcache[0].relName= "relcat";
	catcache[0].recLength= 90;
	catcache[0].recsPerPg= 4;
	catcache[0].numAttrs= 6;
	catcache[0].relcatRid.pid= 0;
	catcache[0].relcatRid.slotnum= 0;
	catcache[0].occupied= true;
	catcache[0].modified= false;
	
	catcache[0].relFile= relcat;
	catcache[0].recsPerPg= ReadIntFromBinary(page+SLOTMAPSIZE+4*15);
	catcache[0].numPgs= ReadIntFromBinary(page+SLOTMPAPSIZE+5*15);
	
	catcache[0].attrList= CreateRelcatAttrCache();

	catcache[1].relName= "attrcat";
	catcache[1].recLength= 75;
	catcache[1].recsPerPg= 4;
	catcache[1].numAttrs= 5;
	catcache[1].relcatRid.pid= 0;
	catcache[1].relcatRid.slotnum= 1;
	catcache[1].occupied= true;
	catcache[1].modified= false;
	
	catcache[1].relFile= relcat;
	catcache[1].recsPerPg= ReadIntFromBinary(page+SLOTMAPSIZE+RECORDSIZE+4*15);
	catcache[1].numPgs= ReadIntFromBinary(page+SLOTMAPSIZE+RECORDSIZE+5*15);
	
	catcache[1].attrList= CreateAttrcatAttrCache();

	return OK;
}

/*
 * Creates a linkedlist of Attribute Cache for Relcat
 * Return head of linked list
 */

AttrCat* CreateRelcatAttrCache(){
	//Just initialize values as done in createcats()
	// create linked list in reverse order
	
	AttrCat *relcatAttrHead= NULL,*temp;
	
	//sixth attribute
	temp= (Attrcat *)malloc(sizeof(Attrcat));
	
	strcpy(temp.relName, RELCAT);
	strcpy(temp.attrName, "numPgs");
	strcpy(temp.type, "i");
	temp.length= 15;
	temp.offset= 75;
	
	temp->next= relcatAttrHead;
	relcatAttrHead= temp;
	
	//fifth attribute
	temp= (Attrcat *)malloc(sizeof(Attrcat));
	
	strcpy(temp.relName, RELCAT);
	strcpy(temp.attrName, "numRecs");
	strcpy(temp.type, "i");
	temp.length= 15;
	temp.offset= 60;
	
	temp->next= relcatAttrHead;
	relcatAttrHead= temp;
	
	//fourth attribute
	temp= (Attrcat *)malloc(sizeof(Attrcat));
	
	strcpy(temp.relName, RELCAT);
	strcpy(temp.attrName, "numAttrs");
	strcpy(temp.type, "i");
	temp.length= 15;
	temp.offset= 45;
	
	temp->next= relcatAttrHead;
	relcatAttrHead= temp;
	
	//third attribute
	temp= (Attrcat *)malloc(sizeof(Attrcat));
	
	strcpy(temp.relName, RELCAT);
	strcpy(temp.attrName, "recsPerPg");
	strcpy(temp.type, "i");
	temp.length= 15;
	temp.offset= 30;
	
	temp->next= relcatAttrHead;
	relcatAttrHead= temp;
	
	//second attribute
	temp= (Attrcat *)malloc(sizeof(Attrcat));
	
	strcpy(temp.relName, RELCAT);
	strcpy(temp.attrName, "recLength");
	strcpy(temp.type, "i");
	temp.length= 15;
	temp.offset= 15;
	
	temp->next= relcatAttrHead;
	relcatAttrHead= temp;
	
	//first attribute
	temp= (Attrcat *)malloc(sizeof(Attrcat));
	
	strcpy(temp.relName, RELCAT);
	strcpy(temp.attrName, "relName");
	strcpy(temp.type, "s");
	temp.length= 15;
	temp.offset= 0;
	
	temp->next= relcatAttrHead;
	relcatAttrHead= temp;
	
	return relcatAttrHead;			
}


/*
 * Creates a linkedlist of Attribute Cache for Attrcat
 */

AttrCat* CreateAttrcatAttrCache(){
	//Just initialize values as done in createcats()
	// create linked list in reverse order
	
	AttrCat *attrcatAtrrHead= NULL,*temp;
	
	//fifth attribute
	temp= (Attrcat *)malloc(sizeof(Attrcat));
	
	strcpy(temp.relName, ATTRCAT);
	strcpy(temp.attrName, "offset");
	strcpy(temp.type, "i");
	temp.length= 15;
	temp.offset= 60;
	
	temp->next= relcatAttrHead;
	relcatAttrHead= temp;
	
	//fourth attribute
	temp= (Attrcat *)malloc(sizeof(Attrcat));
	
	strcpy(temp.relName, ATTRCAT);
	strcpy(temp.attrName, "length");
	strcpy(temp.type, "i");
	temp.length= 15;
	temp.offset= 45;
	
	temp->next= relcatAttrHead;
	relcatAttrHead= temp;
	
	//third attribute
	temp= (Attrcat *)malloc(sizeof(Attrcat));
	
	strcpy(temp.relName, ATTRCAT);
	strcpy(temp.attrName, "type");
	strcpy(temp.type, "s");
	temp.length= 15;
	temp.offset= 30;
	
	temp->next= relcatAttrHead;
	relcatAttrHead= temp;
	
	//second attribute
	temp= (Attrcat *)malloc(sizeof(Attrcat));
	
	strcpy(temp.relName, ATTRCAT);
	strcpy(temp.attrName, "attrName");
	strcpy(temp.type, "s");
	temp.length= 15;
	temp.offset= 15;
	
	temp->next= relcatAttrHead;
	relcatAttrHead= temp;
	
	//first attribute
	temp= (Attrcat *)malloc(sizeof(Attrcat));
	
	strcpy(temp.relName, ATTRCAT);
	strcpy(temp.attrName, "relName");
	strcpy(temp.type, "s");
	temp.length= 15;
	temp.offset= 0;
	
	temp->next= relcatAttrHead;
	relcatAttrHead= temp;
	
	return relcatAttrHead;		
}
