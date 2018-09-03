/*
 * @author : bhavani
 */
 
int CloseCats()
{
	//Check whether both files exist here. else return NOTOK
	if( access(RELCAT, F_OK) == -1 || access(ATTRCAT, F_OK) == -1){
		//Error message to be printed here
		return NOTOK;
	}
	
	//Closing the relations if they are opened
 	for(i=2;i<MAXOPEN;i++){
		if( catcache[i].occupied == true){
			if( CloseRel(i) == NOTOK){
				// Error in Closing the Relation with relNo i
				return NOTOK;
			}
			catcache[i].occupied = false;
		}
	}
	
	// commmitting the relcat or attrcat to the disk if they are modified
	if( catcache[0].modified == true || catcache[1].modified == true){
		char smallbuffer[240] = { 0 };
		FILE *relcat = fopen(RELCAT, wb);
		
		//copying the relcat entries to small buffer
		strncpy(smallbuffer, "relcat", 6);
		CopyIntInBinary(smallbuffer+15, 90);
		CopyIntInBinary(smallbuffer+30, 4);
		CopyIntInBinary(smallbuffer+45, 6);
		CopyIntInBinary(smallbuffer+60, catcache[0].recsPerPg);
		CopyIntInBinary(smallbuffer+75, catcache[0].numPgs);
		
		//copying the attrcat entries to small buffer
		strncpy(smallbuffer, "attrcat", 7);
		CopyIntInBinary(smallbuffer+RECORDSIZE+15, 75);
		CopyIntInBinary(smallbuffer+RECORDSIZE+30, 4);
		CopyIntInBinary(smallbuffer+RECORDSIZE+45, 5);
		CopyIntInBinary(smallbuffer+RECORDSIZE+60, catcache[1].recsPerPg);
		CopyIntInBinary(smallbuffer+RECORDSIZE+75, catcache[1].numPgs);
		
		fseek(relcat,SEEK_SET,SLOTMAPSIZE);  //SEEK Positon to point first record in relcat relaton
		write(relcat, smallbuffer, 240); 
	}
	
	catcache[0].occupied= false;
	catcache[1].occupied= false;
	
	fclose(catcache[0].relFile);
	fclose(catcache[1].relFile);
	return OK;
}
