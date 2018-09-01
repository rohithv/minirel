
/*
 * @author: rohith
 */

int ReadPage(int relNum, short pid)
{
	char page[PAGESIZE] = {0};
	int retVal, offset;

	if(relNum<0 || relNum>=MAXOPEN){
		//print error
		return NOTOK;
	}

	if(pid > catcache[relNum].numPgs || pid<0){
		//print error
		return NOTOK;
	}
	else if(pid == buffer[relNum].pid){ //Already present in buffer.
		return OK;
	}
	else if(pid == catcache[relNum].numPgs){ //A new page is being requested.
		if(buffer[relNum].modified == true){
			retVal = FlushPage(relNum);
			if(retVal == NOTOK){
				return NOTOK;
			}
		}

		buffer[relNum].pid = pid;
		buffer[relNum].page.slotmap = 0;
		buffer[relNum].modified= false;
	}
	else if(pid < catcache[relNum].numPgs){ //Existing page is to be read.

		if(buffer[relNum].modified == true){
			retVal = FlushPage(relNum);
			if(retVal == NOTOK){
				return NOTOK;
			}
		}

		offset = pid * PAGESIZE;

		read(catcache[relNum].relFile, page, PAGESIZE);

		buffer[relNum].page.slotmap = ReadIntFromBinary(page);
		strncpy(buffer[relNum].page.contents, page, MAXRECORD);

		buffer[relNum].pid = pid;
		buffer[relNum].modified= false;
	}

	return OK;
}
