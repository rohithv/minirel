/*
 * @author: priyatam
 */

int WriteRec(int relnum, char *recPtr,RID *recRid)
{
	if(readpage(relnum,rid->pid)==NOTOK) return NOTOK;
	
	short slot=rid->slotnum;
	
	if(slot > catcache[relnum].recsPerPg ) return NOTOK;
	
	
	buffer[relnum].page.slotnum=(buffer[relnum].page.slotnum | (1<<((SLOTMAPSIZE * 8) - slot -1)) );
	buffer[relnum].modified=TRUE;
	strncpy(buffer[relnum].page.contents + SLOTMAPSIZE*8 + (slot *RECORDSIZE) , recPtr, RECORDSIZE);

}
