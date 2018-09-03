/*
 * @author : bhavani
 */


int CloseRel(int relNum)
{
	//check whether relNum is valid or not.if it is invalid return failure
	if(relNum<0 && relNum>=20){
		//error
		return NOTOK;
	}
	
	//check whether relation is closed or not.if closed return success
	if(catcache[relName].occupied == false){
		return OK;
	}
	
	//check whether the buffer page of relation is dirty or not. if dirty commit it
	if(buffer[relNum].modified == true){
		FlushPage(relNum);
	}

	//check whether the catcache entry corresponding to relNum is modified or not. if modified update it in relcat relation
	if(catcache[relNum].modified == true){
		char recPtr[RECORDSIZE]={ 0 };
		
		strncpy(recPtr,catcache[relNum].relName,15);
		CopyIntInBinary(recPtr+1*15, catcache[relNum].recLength);
		CopyIntInBinary(recPtr+2*15, 4);	//records per page
		CopyIntInBinary(recPtr+3*15, catcache[relNum].numAttrs);
		CopyIntInBinary(recPtr+4*15, catcache[relNum].numRecs);
		CopyIntInBinary(recPtr+5*15, catcache[relNum].numPgs);
		
		Rid recRid= catcache[relNum].relcatRid;

		WriteRec(0,recPtr,recRid); 	//updates the record entries in relation catlog corresponding to recRid
	}
	
	return OK;
}
