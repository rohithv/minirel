


/*
 * Place catalog entries in cache
 * Read only the number of records and number of pages from file (after creating entries in cache)
 * That is because FindRec() cant be used without relNum.
 */


int OpenCats()
{
	int i;
	//Check whether both files exist here. else return NOTOK


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
	
	catcache[0].attrList= CreateRelcatAttrCache();



	return OK;
}

/*
 * Creates a linkedlist of Attribute Cache for Relcat
 * Return head of linked list
 */

AttrCat* CreateRelcatAttrCache(){
	//Just initialize values as done in createcats()
}


/*
 * Creates a linkedlist of Attribute Cache for Attrcat
 */

AttrCat* CreateAttrcatAttrCache(){
	//Just initialize values as done in createcats()
}
