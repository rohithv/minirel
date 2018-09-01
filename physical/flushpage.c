
/*
 * @author: rohith
 */

int FlushPage(int relNum)
{
	//flushes the current page 
	char page[PAGESIZE]= {0};

	//check for errors
	if(relNum<0 || relNum>=MAXOPEN){
		//display error
		return NOTOK;
	}

	if(buffer[relNum].modified==false){
		return OK;
	}

	unsigned int slotmap = buffer[relNum].page.slotmap;

	CopyIntInBinary(page, slotmap);
	strncpy(page+SLOTMAPSIZE, buffer[relNum].page.contents, MAXRECORD);

	int offset = buffer[relNum].pid * PAGESIZE;
	write(catcache[relNum].relFile, page+offset, PAGESIZE);

	buffer[relNum].modified=false;

	return OK;

}
