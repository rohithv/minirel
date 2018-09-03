
/*
 * @author: rohith
 */

int GetNextRec(int relNum, Rid startRid, Rid *foundRid, char **recPtr)
{
	unsigned int slotmap, temp;
	if(relNum<0 || relNum>=MAXOPEN){
		//error
		return NOTOK;
	}

	if(catcache[relNum].occupied == false){
		//error
		return NOTOK;
	}

	if(startRid.pid >= catcache[relNum].numPgs){
		//error
		return NOTOK;
	}

	while(getNextValidRid(relNum,startRid, foundRid)==OK){
		ReadPage(foundRid->pid);

		slotmap = buffer[relNum].slotmap;
		temp = 1;
		temp = temp << (sizeof(int) - foundRid->slotnum - 1);
		if((slotmap & temp) != 0){ //slot is not empty -> record is valid
			*recPtr = buffer[relNum].contents + RECORDSIZE*(foundRid->slotnum); //To be changed here after removing restriction
			return OK;
		}

		startRid = *foundRid;
	}
	return NOTOK;
}


/*
 * Takes a Rid as argument and returns its next Rid.
 * Arguments: relNum, currRid, a pointer to nextRid.
 * returns OK on success, NOTOK on failure-> if currRid is last record in the file.
 * currRid = { -1, -1} to start from beginning.
 */

int getNextValidRid(int relNum, Rid currRid, Rid *nextRid){
	int numPgs = catcache[relNum].numPgs;
	int recsPerPg = catcache[relNum].recsPerPg;

	if(currRid.pid == -1 && numPgs>0){
		nextRid->pid = 0;
		nextRid->slotnum = 0;
	}
	else if(numPgs<=0){
		//error
		return NOTOK;
	}
	else if(currRid.slotnum< recsPerPg-1){
		nextRid->pid = currRid.pid;
		nextRid->slotnum = currRid.slotnum + 1;
	}
	else if(currRid.pid < numPgs-1){
		nextRid->pid = currRid.pid + 1;
		nextRid->slotnum= 0;
	}
	else{	//currRec is last record.
		//error
		return NOTOK;
	}
	return OK;
}