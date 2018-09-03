/*
 * @author: Priyatam
 */

int InsertRec(int relnum, char *recPtr)
{
	if(relnum<0 || relnum>=MAXOPEN) return NOTOK;
	int no_of_pages=catcache[relnum].numPgs;
	
	int i;
	for(i=0;i<no_of_pages;i++){
		ReadPage(relnum,i);
		
		unsigned curslotmap;
		curslotmap=ReadIntFromBinary(void * (buffer[i].page.contents));
		
		int slotinpg;
		
		for(slotinpg=0; slotinpg < catcache[relnum].recsPerPg; slotinpg++){
			if( (1<<((SLOTMAPSIZE * 8) - slotinpg -1)) & curslotmap == 0){
				RID tmprid;
				tmprid.pid=i;
				tmprid.slotnum=slotinpg;
				writerec(relnum, recptr, &tmprid);
				return OK;
			}
			
		}
	}
	
	char page[PAGESIZE]= {0};
	
	
	fseek( catcache[relnum].relfile, catcache[relnum].numPgs * PAGESIZE , SEEK_SET );
	write(catcache[relname].relfile, page,PAGESIZE);
	catcache[relnum].numPgs++;
	
	RID tmprid;
	tmprid.pid=catcache[relnum].numPgs-1;
	tmprid.slotnum=0;
	writerec(relnum, recptr, &tmprid);
	return OK;
	
}
