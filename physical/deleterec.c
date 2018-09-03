/*
 * @author: Priyatam
 */

int DeleteRec(int relnum, Rid *rid)
{


	if(readpage(relnum,rid->pid)==NOTOK) return NOTOK;
	
	short slot=rid->slotnum;
	
	if( (1<<((SLOTMAPSIZE * 8) - slot -1)) & buffer[relnum].page.slotmap ){
		
		buffer[relnum].modified=TRUE;
		buffer[relnum].page.slotnum=(buffer[relnum].page.slotnum ^ (1<<((SLOTMAPSIZE * 8) - slot -1)) );
	}
	
	return OK;
	

}



